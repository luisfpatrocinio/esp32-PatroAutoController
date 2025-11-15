/**
 * @file main.cpp
 * @author Luis Felipe Patrocinio (patrocinioluisf@gmail.com)
 * @brief PatroAutroController - An ESP32 FreeRTOS-based Joystick.
 * @version 0.1
 * @date 2025-11-14
 * @copyright Copyright (c) 2025
 * @see https://github.com/luisfpatrocinio
 */

#include <Arduino.h>

// --- Hardware Pin Definitions ---
const int POTENTIOMETER_PIN = 34; // ADC1_CH6
const int LED_PIN = 2;            // Onboard LED

// --- Global Variables ---
// Shared variable for press interval in ms.
// It's volatile because it is modified and read by different tasks.
volatile int joystick_delay = 1000;

/**
 * @brief Reads the potentiometer to update the joystick press delay.
 * @param pvParameters Task parameters (unused).
 */
void task_read_potentiometer(void *pvParameters) {
  (void)pvParameters; // Avoid compiler warnings for unused parameter

  for (;;) {
    // Potentiometer reading logic will be implemented in the next step.
    vTaskDelay(pdMS_TO_TICKS(100)); // Check potentiometer value every 100ms
  }
}

/**
 * @brief Simulates the joystick button press at a variable interval.
 * @param pvParameters Task parameters (unused).
 */
void task_joystick_press(void *pvParameters) {
  (void)pvParameters;

  for (;;) {
    // Joystick HID press and LED feedback logic will be added here.
    Serial.printf("Button pressed! Next press in %d ms\n", joystick_delay);

    // Block this task for the duration defined by the potentiometer.
    vTaskDelay(pdMS_TO_TICKS(joystick_delay));
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  // A small delay to ensure Serial Monitor is ready.
  vTaskDelay(pdMS_TO_TICKS(1000));
  Serial.println("--- PatroAutroController ---");
  Serial.println("System starting...");

  // Create FreeRTOS tasks.
  xTaskCreate(
      task_read_potentiometer,
      "ReadPotTask",        // Task name
      2048,                 // Stack size (bytes)
      NULL,                 // Parameter
      1,                    // Priority
      NULL);                // Task handle

  xTaskCreate(
      task_joystick_press,
      "JoystickPressTask",
      2048,
      NULL,
      1,
      NULL);

  Serial.println("Tasks created successfully.");
}

void loop() {
  // The default Arduino loop() task is not needed when using a FreeRTOS scheduler.
  // We delete it to free up resources.
  vTaskDelete(NULL);
}