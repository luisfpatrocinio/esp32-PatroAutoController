/**
 * @file HardwareIO.cpp
 * @author Luis Felipe Patrocinio
 * @brief Implementation of hardware input/output operations.
 * @version 0.3
 * @date 2025-11-14
 */

#include "HardwareIO.h"
#include "config.h"
#include <Arduino.h>

void io_init() {
  pinMode(LED_PIN, OUTPUT);
  // No pinMode needed for analog input on ESP32
}

int io_read_potentiometer_raw() {
  return analogRead(POTENTIOMETER_PIN);
}

void io_blink_led() {
  digitalWrite(LED_PIN, HIGH);
  vTaskDelay(pdMS_TO_TICKS(LED_BLINK_DURATION_MS));
  digitalWrite(LED_PIN, LOW);
}