#include <Arduino.h>
#include "rgb_lcd_port.h"
#include "gt911.h"
#include "lvgl_port.h"
#include "ui.h"
#include "vars.h"

uint32_t counter = 0;

void setup() {

    Serial.begin(115200);

    static esp_lcd_panel_handle_t panel_handle = NULL;
    static esp_lcd_touch_handle_t tp_handle = NULL;

    tp_handle = touch_gt911_init();
    panel_handle = waveshare_esp32_s3_rgb_lcd_init();
    wavesahre_rgb_lcd_bl_on();
    ESP_ERROR_CHECK(lvgl_port_init(panel_handle, tp_handle));

    if (lvgl_port_lock(-1)) {
        ui_init();
        lvgl_port_unlock();
    }
}

void loop() {
    if (lvgl_port_lock(-1)) {
        eez::flow::setGlobalVariable(FLOW_GLOBAL_VARIABLE_COUNTER, counter++);
        ui_tick();
        lvgl_port_unlock();
    }

    delay(1000);
}