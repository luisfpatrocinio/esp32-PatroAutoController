/**
 * @file JoystickController.h
 * @author Luis Felipe Patrocinio
 * @brief Interface for the Bluetooth (BLE) Joystick controller.
 * @version 0.4
 * @date 2025-11-14
 */

#pragma once

/**
 * @brief Initializes and starts the BLE Gamepad service.
 */
void joystick_init();

/**
 * @brief Presses a specific button on the gamepad.
 * @param button_number The button to press (e.g., 1 for the first button).
 */
void joystick_press_button(int button_number);

/**
 * @brief Releases a specific button on the gamepad.
 * @param button_number The button to release.
 */
void joystick_release_button(int button_number);

/**
 * @brief Checks if a client (computer) is connected to the gamepad.
 * @return true if connected, false otherwise.
 */
bool joystick_is_connected();