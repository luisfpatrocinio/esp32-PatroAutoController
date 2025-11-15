/**
 * @file config.h
 * @author Luis Felipe Patrocinio
 * @brief Centralized configuration file for the PatroAutroController project.
 * @version 0.3
 * @date 2025-11-14
 */

#pragma once

// --- Hardware Pin Definitions ---
constexpr int POTENTIOMETER_PIN = 4; // ADC2_CH0
constexpr int LED_PIN = 2;           // Onboard LED

// --- Timing Constants ---
constexpr int MIN_JOYSTICK_DELAY_MS = 50;   // Fastest press rate
constexpr int MAX_JOYSTICK_DELAY_MS = 2000; // Slowest press rate
constexpr int LED_BLINK_DURATION_MS = 40;   // How long the LED stays on per blink