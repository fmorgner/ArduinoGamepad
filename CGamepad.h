#ifndef __CJOYSTICK_H
#define __CJOYSTICK_H

#include <Arduino.h>

#define FEATURE_NOT_AVAILABLE 255
#define BUTTON_PRESSED        true
#define BUTTON_RELEASED       false

enum JoystickSensitivity
  {
  JoystickSensitivityLow    = 12,
  JoystickSensitivityNormal = 24,
  JoystickSensitivityMedium = 36,
  JoystickSensitivityHigh   = 48
  };

class Gamepad
  {
  protected:
    unsigned char m_nJoystickXAxisPin;
    int m_nJoystickXAxisMinimum;
    int m_nJoystickXAxisMaximum;
    int m_nJoystickXAxisCalibrationValue;
    char m_nJoystickXPosition;                            // The current calibrated and scaled X position of the joystick

    unsigned char m_nJoystickYAxisPin;
    int m_nJoystickYAxisMinimum;
    int m_nJoystickYAxisMaximum;
    int m_nJoystickYAxisCalibrationValue;
    char m_nJoystickYPosition;                            // The current calibrated and scaled Y position of the joystick

    unsigned int m_nJoystickSensitivity;

    bool m_bButtonActiveState;             // The states that singals a pushed button (LOW or HIGH)
    unsigned char  m_nButtonCount;                  // The number of buttons on the gamepad
    unsigned char* m_anButtonPins;                   // The pins to which the buttons are connected to
    bool* m_abButtonStates;                      // The states of the connected buttons

    unsigned char  m_nAccelerometerAxisCount;         // The pin to wich the Y-axis of the accelerometer is connected
    unsigned char* m_anAccelerometerAxisPins;        // The pin to wich the X-axis of the accelerometer is connected
    int* m_anAccelerometerAxisMinima;
    int* m_anAccelerometerAxisMaxima;
    int* m_anAccelerometerCalibrationValues;  // The calibration data for the accellerometer

  protected:
    Gamepad(Gamepad& roGamepad);  // No copy constructor.
    void Update();                // The internal updating routine that gets called periodically.
    bool LoadCalibrationData(int nAddress = 0);                                       // Load a descriptor from EEPROM

  public:
    // This constructor construct an instance for use with the Arduino Esplora.
    Gamepad();
    // This constructor constructs an instance using the descriptor provided.
    Gamepad(unsigned char nJoystickXAxisPin, int nJoystickXAxisMinimum, int nJoystickXAxisMaximum, unsigned char nJoystickYAxisPin, int nJoystickYAxisMinimum, int nJoystickYAxisMaximum,
            unsigned int nJoystickSensitivity, unsigned char  nButtonCount, unsigned char* anButtonPins, bool bButtonActiveState, unsigned char  nAccelerometerAxisCount,
            unsigned char* anAccelerometerAxisPins, int* anAccelerometerAxisMinima, int* anAccelerometerAxisMaxima);

    unsigned char* GetPostions();                                                                 // Get an array with two elements representing the X and Y positions of the joystick.
    bool* GetButtonStates(int& nSize);                                                   // Get an array with nSize elements representing the states of the buttons.

    void StoreCalibrationData(int nAddress = 0, bool bForce = false);  // Store a descriptor in EEPROM
  };

#endif
