/**
 * @file main.cpp
 * @author Luis Felipe Patrocinio (patrocinioluisf@gmail.com)
 * @brief PatroAutroController - An ESP32 FreeRTOS-based Joystick.
 * @version 0.3
 * @date 2025-11-14
 * @copyright Copyright (c) 2025
 * @see https://github.com/luisfpatrocinio
 */

#include <Arduino.h>
#include "config.h"
#include "HardwareIO.h"

// --- Global Variables ---
// Shared variable for press interval in ms.
volatile int joystick_delay = 1000;

/**
 * @brief Reads the potentiometer to update the joystick press delay.
 * @param pvParameters Task parameters (unused).
 */
void task_read_potentiometer(void *pvParameters) {
  (void)pvParameters;

  for (;;) {
    int rawValue = io_read_potentiometer_raw();
    // The mapping logic stays here, as it's part of the application's behavior.
    joystick_delay = map(rawValue, 0, 4095, MIN_JOYSTICK_DELAY_MS, MAX_JOYSTICK_DELAY_MS);
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

/**
 * @brief Simulates the joystick button press at a variable interval.
 * @param pvParameters Task parameters (unused).
 */
void task_joystick_press(void *pvParameters) {
  (void)pvParameters;

  for (;;) {
    io_blink_led();

    Serial.printf("Button pressed! Current delay: %d ms\n", joystick_delay);

    vTaskDelay(pdMS_TO_TICKS(joystick_delay));
  }
}

void setup() {
  Serial.begin(115200);
  io_init(); // Initialize hardware using our new module

  vTaskDelay(pdMS_TO_TICKS(1000));
  Serial.println("--- PatroAutroController ---");
  Serial.println("System starting...");

  xTaskCreate(
      task_read_potentiometer, "ReadPotTask", 2048, NULL, 1, NULL);
  xTaskCreate(
      task_joystick_press, "JoystickPressTask", 2048, NULL, 1, NULL);

  Serial.println("Tasks created successfully.");
}

void loop() {
  vTaskDelete(NULL);
}