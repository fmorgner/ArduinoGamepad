#ifndef __CJOYSTICK_H
#define __CJOYSTICK_H

#include <Arduino.h>
#include <Esplora.h>

#define FEATURE_NOT_AVAILABLE 255
#define BUTTON_PRESSED  true
#define BUTTON_RELEASED false

class Gamepad
  {
  public:
    struct gamepad_descriptor_t
      {
      byte nJoystickXAxisPin;               // The pin to which the X-axis is connected
      byte nJoystickYAxisPin;               // The pin to which the Y-axis is connected
      int  anJoystickXAxisRange[2];         // The range of input values of the joysticks x-axis.
      int  anJoystickYAxisRange[2];         // The range of input values of the joysticks y-axis
      char anJoystickCalibrationData[2];    // The calibration data for the joystick
      char nJoystickSensitivity;            // The sensitivity of the joystick
      
      byte* anButtonPins;                   // The pins to which the buttons are connected to
      byte  nButtonsCount;                  // The number of buttons on the gamepad
      bool  bButtonActiveState;             // The states that singals a pushed button (LOW or HIGH)
      
      byte* anAccelerometerAxisPins;        // The pin to wich the X-axis of the accelerometer is connected
      byte nAccelerometerAxisCount;         // The pin to wich the Y-axis of the accelerometer is connected
      int* anAccelerometerCalibrationData;  // The calibration data for the accellerometer
      };

  protected:
    gamepad_descriptor_t* m_pstDescriptor;  // The descriptor for the gamepad

    char m_nXPosition;                      // The current calibrated and scaled X position of the joystick
    char m_nYPosition;                      // The current calibrated and scaled Y position of the joystick

    bool*  m_abButtonStates;                // The states of the connected buttons
    
  protected:
    Gamepad(Gamepad& roGamepad);  // No copy constructor.
    void Update();                // The internal updating routine that gets called periodically.
  
  public:
    Gamepad();                                                         // Default constructor construct an instance for use with the Arduino Esplora.
    Gamepad(gamepad_descriptor_t* stDescriptor);                       // This constructor constructs an instance using the descriptor provided.

    byte* GetPostions();                                               // Get an array with two elements representing the X and Y positions of the joystick.
    bool* GetButtonStates(int& nSize);                                 // Get an array with nSize elements representing the states of the buttons.

    static void StoreDescriptor(gamepad_descriptor_t* pstDescriptor);  // Store a descriptor in EEPROM
    static gamepad_descriptor_t* LoadDescriptor();                     // Load a descriptor from EEPROM
  };

#endif
