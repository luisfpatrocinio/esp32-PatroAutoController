/**
 * @file JoystickController.cpp
 * @author Luis Felipe Patrocinio
 * @brief Implementation of the Bluetooth (BLE) Joystick controller.
 * @version 0.4
 * @date 2025-11-14
 */

#include "JoystickController.h"
#include <BleGamepad.h>

// Instantiate the BLE Gamepad object
// Parameters: Device Name, Manufacturer Name, Battery Level
BleGamepad bleGamepad("PatroAutroController", "LFP", 100);

void joystick_init()
{
    bleGamepad.begin();
}

void joystick_press_button(int button_number)
{
    if (bleGamepad.isConnected())
    {
        bleGamepad.press(button_number);
    }
}

void joystick_release_button(int button_number)
{
    if (bleGamepad.isConnected())
    {
        bleGamepad.release(button_number);
    }
}

bool joystick_is_connected()
{
    return bleGamepad.isConnected();
}