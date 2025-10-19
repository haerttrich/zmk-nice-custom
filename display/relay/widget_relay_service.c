#include <zephyr/kernel.h>  
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/conn.h>

#include "widget_relay_service.h"

// Custom UUID for our widget relay service
#define WIDGET_RELAY_SERVICE_UUID \
    BT_UUID_128_ENCODE(0x00000001, 0x7e62, 0x5d0b, 0x0000, 0x000000000000)

#define WIDGET_RELAY_CHAR_UUID \
    BT_UUID_128_ENCODE(0x00000002, 0x7e62, 0x5d0b, 0x0000, 0x000000000000)

static struct bt_uuid_128 widget_relay_svc_uuid = BT_UUID_INIT_128(WIDGET_RELAY_SERVICE_UUID);
static struct bt_uuid_128 widget_relay_char_uuid = BT_UUID_INIT_128(WIDGET_RELAY_CHAR_UUID);

#if IS_ENABLED(CONFIG_ZMK_SPLIT) && !IS_ENABLED(CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
// ============ PERIPHERAL SIDE ============

static widget_relay_callback_t relay_callback = NULL;

// GATT characteristic write handler
static ssize_t on_widget_data_write(struct bt_conn *conn,
                                    const struct bt_gatt_attr *attr,
                                    const void *buf, uint16_t len,
                                    uint16_t offset, uint8_t flags) {
    if (len != sizeof(struct widget_relay_data)) {
        return BT_GATT_ERR(BT_ATT_ERR_INVALID_ATTRIBUTE_LEN);
    }

    struct widget_relay_data *data = (struct widget_relay_data *)buf;

    if (relay_callback) {
        relay_callback(data);
    }

    return len;
}

// Define GATT service
BT_GATT_SERVICE_DEFINE(widget_relay_svc,
    BT_GATT_PRIMARY_SERVICE(&widget_relay_svc_uuid),
    BT_GATT_CHARACTERISTIC(&widget_relay_char_uuid.uuid,
                          BT_GATT_CHRC_WRITE | BT_GATT_CHRC_WRITE_WITHOUT_RESP,
                          BT_GATT_PERM_WRITE,
                          NULL, on_widget_data_write, NULL),
);

int widget_relay_service_init_peripheral(widget_relay_callback_t callback) {
    relay_callback = callback;
    return 0;
}

#else
// ============ CENTRAL SIDE ============

#include <zmk/split/bluetooth/central.h>

static struct bt_gatt_discover_params discover_params;
static struct bt_conn *relay_conn = NULL;
static uint16_t relay_char_handle = 0;
static bool discovery_complete = false;

// Discover the characteristic handle
static uint8_t discover_func(struct bt_conn *conn,
                             const struct bt_gatt_attr *attr,
                             struct bt_gatt_discover_params *params) {
    if (!attr) {
        discovery_complete = true;
        return BT_GATT_ITER_STOP;
    }

    if (bt_uuid_cmp(params->uuid, &widget_relay_char_uuid.uuid) == 0) {
        relay_char_handle = attr->handle + 1;
    }

    return BT_GATT_ITER_CONTINUE;
}

// Callback when split peripheral connects
static void on_split_peripheral_connected(struct bt_conn *conn) {
    if (relay_conn) {
        return;
    }
    
    relay_conn = conn;
    discovery_complete = false;
    relay_char_handle = 0;
    
    // Discover the characteristic
    memset(&discover_params, 0, sizeof(discover_params));
    discover_params.uuid = &widget_relay_char_uuid.uuid;
    discover_params.func = discover_func;
    discover_params.start_handle = BT_ATT_FIRST_ATTRIBUTE_HANDLE;
    discover_params.end_handle = BT_ATT_LAST_ATTRIBUTE_HANDLE;
    discover_params.type = BT_GATT_DISCOVER_CHARACTERISTIC;

    bt_gatt_discover(conn, &discover_params);
}

// Callback when split peripheral disconnects
static void on_split_peripheral_disconnected(struct bt_conn *conn) {
    if (conn == relay_conn) {
        relay_conn = NULL;
        relay_char_handle = 0;
        discovery_complete = false;
    }
}

// Connection callbacks
static struct bt_conn_cb conn_callbacks = {
    .connected = on_split_peripheral_connected,
    .disconnected = on_split_peripheral_disconnected,
};

int widget_relay_service_init_central(void) {
    bt_conn_cb_register(&conn_callbacks);
    return 0;
}

int widget_relay_send(struct widget_relay_data *data) {
    if (!relay_conn || !discovery_complete || relay_char_handle == 0) {
        return -ENOTCONN;
    }

    int err = bt_gatt_write_without_response(relay_conn, relay_char_handle,
                                             data, sizeof(struct widget_relay_data),
                                             false);
    return err;
}

#endif