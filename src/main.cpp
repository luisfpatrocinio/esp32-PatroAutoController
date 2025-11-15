/**
 * @file main.cpp
 * @author Luis Felipe Patrocinio (patrocinioluisf@gmail.com)
 * @brief PatroAutroController - An ESP32 FreeRTOS-based Joystick.
 * @version 0.4
 * @date 2025-11-14
 * @copyright Copyright (c) 2025
 * @see https://github.com/luisfpatrocinio
 */

#include <Arduino.h>
#include "config.h"
#include "HardwareIO.h"
#include "JoystickController.h"

// --- Global Variables ---
volatile int joystick_delay = 1000;

/**
 * @brief Reads the potentiometer to update the joystick press delay.
 * @param pvParameters Task parameters (unused).
 */
void task_read_potentiometer(void *pvParameters)
{
    (void)pvParameters;

    for (;;)
    {
        int rawValue = io_read_potentiometer_raw();
        joystick_delay = map(rawValue, 0, 4095, MIN_JOYSTICK_DELAY_MS, MAX_JOYSTICK_DELAY_MS);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

/**
 * @brief Simulates the joystick button press at a variable interval.
 * @param pvParameters Task parameters (unused).
 */
void task_joystick_press(void *pvParameters)
{
    (void)pvParameters;

    for (;;)
    {
        if (joystick_is_connected())
        {
            // Blink LED to signal a button press
            io_blink_led();

            // Press and immediately release the first button
            joystick_press_button(2);
            joystick_release_button(2);

            Serial.printf("Button 2 pressed! Current delay: %d ms\n", joystick_delay);

            // Wait for the next cycle
            vTaskDelay(pdMS_TO_TICKS(joystick_delay));
        }
        else
        {
            // If not connected, wait a bit before checking again.
            // A slow blink could also indicate "waiting for connection" status.
            Serial.println("Waiting for connection...");
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
    }
}

void setup()
{
    Serial.begin(115200);
    io_init();
    joystick_init(); // Initialize our new joystick module

    vTaskDelay(pdMS_TO_TICKS(1000));
    Serial.println("--- PatroAutroController ---");
    Serial.println("System starting... Waiting for BLE connection.");

    xTaskCreate(
        task_read_potentiometer, "ReadPotTask", 2048, NULL, 1, NULL);
    xTaskCreate(
        task_joystick_press, "JoystickPressTask", 4096, NULL, 1, NULL); // Increased stack size for BLE

    Serial.println("Tasks created successfully.");
}

void loop()
{
    vTaskDelete(NULL);
}