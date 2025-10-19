set(DISPLAY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../../display")

message(STATUS "Display directory: ${DISPLAY_DIR}")

# Shield specific file
target_sources(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/custom_screen.c)

# Collect all display sources
file(GLOB SCREEN_SOURCES "${DISPLAY_DIR}/screens/*.c")
file(GLOB WIDGET_SOURCES "${DISPLAY_DIR}/widgets/*.c")
file(GLOB EVENT_SOURCES "${DISPLAY_DIR}/events/*.c")
file(GLOB ASSET_SOURCES "${DISPLAY_DIR}/assets/*.c")
file(GLOB RELAY_SOURCES "${DISPLAY_DIR}/relay/*.c")

# Add util.c
set(UTIL_SOURCE "${DISPLAY_DIR}/util.c")

# Debug: Show what was found
message(STATUS "Found ${CMAKE_MATCH_COUNT} screen sources")
message(STATUS "Found widget sources: ${WIDGET_SOURCES}")

# Add all sources
target_sources(app PRIVATE
    ${UTIL_SOURCE}
    ${SCREEN_SOURCES}
    ${WIDGET_SOURCES}
    ${EVENT_SOURCES}
    ${ASSET_SOURCES}
    ${RELAY_SOURCES}
)

# Include paths for headers
target_include_directories(app PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../
    ${DISPLAY_DIR}
    ${DISPLAY_DIR}/widgets
    ${DISPLAY_DIR}/events
    ${DISPLAY_DIR}/screens
    ${DISPLAY_DIR}/assets
    ${DISPLAY_DIR}/relay
)