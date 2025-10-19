#include <zephyr/bluetooth/uuid.h>
#include <zephyr/logging/log.h>
#include <zephyr/kernel.h>

#include "display/relay/widget_relay_service.h"

LOG_MODULE_REGISTER(widget_relay, CONFIG_ZMK_LOG_LEVEL);

// Custom UUID for our widget relay service
// Format: 00000001-7e62-5d0b-0000-000000000000
#define WIDGET_RELAY_SERVICE_UUID \
    BT_UUID_128_ENCODE(0x00000001, 0x7e62, 0x5d0b, 0x0000, 0x000000000000)

#define WIDGET_RELAY_CHAR_UUID \
    BT_UUID_128_ENCODE(0x00000002, 0x7e62, 0x5d0b, 0x0000, 0x000000000000)

static struct bt_uuid_128 widget_relay_svc_uuid = BT_UUID_INIT_128(WIDGET_RELAY_SERVICE_UUID);
static struct bt_uuid_128 widget_relay_char_uuid = BT_UUID_INIT_128(WIDGET_RELAY_CHAR_UUID);

#if IS_ENABLED(CONFIG_ZMK_SPLIT) && !IS_ENABLED(CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
// ============ PERIPHERAL SIDE ============

static widget_relay_callback_t relay_callback = NULL;

// GATT characteristic write handler - called when central sends data
static ssize_t on_widget_data_write(struct bt_conn *conn, const struct bt_gatt_attr *attr, const void *buf, uint16_t len, uint16_t offset, uint8_t flags) {
    if (len != sizeof(struct widget_relay_data)) {
        LOG_ERR("Invalid widget relay data length: %d", len);
        return BT_GATT_ERR(BT_ATT_ERR_INVALID_ATTRIBUTE_LEN);
    }

    struct widget_relay_data *data = (struct widget_relay_data *)buf;
    LOG_DBG("Received relay data - type: %d, value: %d", data->type, data->value);

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
    LOG_INF("Widget relay peripheral service initialized");
    return 0;
}

#else
// ============ CENTRAL SIDE ============

static struct bt_gatt_discover_params discover_params;
static struct bt_gatt_write_params write_params;
static struct bt_conn *relay_conn = NULL;
static uint16_t relay_char_handle = 0;

// Discover the characteristic handle
static uint8_t discover_func(struct bt_conn *conn,
                             const struct bt_gatt_attr *attr,
                             struct bt_gatt_discover_params *params) {
    if (!attr) {
        LOG_DBG("Discovery complete");
        return BT_GATT_ITER_STOP;
    }

    LOG_DBG("Attribute handle %u", attr->handle);

    if (bt_uuid_cmp(params->uuid, &widget_relay_char_uuid.uuid) == 0) {
        relay_char_handle = attr->handle;
        LOG_INF("Found widget relay characteristic at handle %u", relay_char_handle);
    }

    return BT_GATT_ITER_CONTINUE;
}

// Called when peripheral connects
static void on_split_connected(struct bt_conn *conn) {
    relay_conn = conn;
    
    // Discover the characteristic
    discover_params.uuid = &widget_relay_char_uuid.uuid;
    discover_params.func = discover_func;
    discover_params.start_handle = BT_ATT_FIRST_ATTRIBUTE_HANDLE;
    discover_params.end_handle = BT_ATT_LAST_ATTRIBUTE_HANDLE;
    discover_params.type = BT_GATT_DISCOVER_CHARACTERISTIC;

    int err = bt_gatt_discover(conn, &discover_params);
    if (err) {
        LOG_ERR("Discover failed (err %d)", err);
    }
}

int widget_relay_service_init_central(void) {
    LOG_INF("Widget relay central service initialized");
    // TODO: Hook into ZMK's split connection event to call on_split_connected
    return 0;
}

int widget_relay_send(struct widget_relay_data *data) {
    if (!relay_conn || relay_char_handle == 0) {
        LOG_WRN("Relay not ready - conn: %p, handle: %u", relay_conn, relay_char_handle);
        return -ENOTCONN;
    }

    write_params.func = NULL; // No response needed
    write_params.handle = relay_char_handle;
    write_params.offset = 0;
    write_params.data = data;
    write_params.length = sizeof(struct widget_relay_data);

    int err = bt_gatt_write_without_response(relay_conn, relay_char_handle,
                                             data, sizeof(struct widget_relay_data),
                                             false);
    if (err) {
        LOG_ERR("Write failed (err %d)", err);
        return err;
    }

    LOG_DBG("Sent relay data - type: %d, value: %d", data->type, data->value);
    return 0;
}

#endif