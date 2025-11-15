/**
 * @file HardwareIO.h
 * @author Luis Felipe Patrocinio
 * @brief Interface for hardware input/output operations.
 * @version 0.3
 * @date 2025-11-14
 */

#pragma once

/**
 * @brief Initializes all hardware pins to their correct modes.
 */
void io_init();

/**
 * @brief Reads the raw value from the potentiometer.
 * @return int The raw ADC value (0-4095).
 */
int io_read_potentiometer_raw();

/**
 * @brief Performs a quick blink on the feedback LED.
 */
void io_blink_led();