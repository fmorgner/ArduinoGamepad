#include "CGamepad.h"
#include "EEPROM.h"

Gamepad::Gamepad(unsigned char nJoystickXAxisPin, int nJoystickXAxisMinimum, int nJoystickXAxisMaximum, unsigned char nJoystickYAxisPin, int nJoystickYAxisMinimum, int nJoystickYAxisMaximum,
  unsigned int nJoystickSensitivity, unsigned char  nButtonCount, unsigned char* anButtonPins, bool bButtonActiveState, unsigned char  nAccelerometerAxisCount,
  unsigned char* anAccelerometerAxisPins, int* anAccelerometerAxisMinima, int* anAccelerometerAxisMaxima)
  {
  m_nJoystickXAxisPin = nJoystickXAxisPin;
  m_nJoystickYAxisPin = nJoystickYAxisPin;

  for(byte nIteration = 0; nIteration < 8; ++nIteration)
    {
    m_nJoystickXAxisCalibrationValue += analogRead(m_nJoystickXAxisPin);
    m_nJoystickYAxisCalibrationValue += analogRead(m_nJoystickYAxisPin);
    }

  m_nJoystickXAxisCalibrationValue >>= 3;
  m_nJoystickYAxisCalibrationValue >>= 3;

  m_nJoystickXAxisMinimum = nJoystickXAxisMinimum;
  m_nJoystickXAxisMaximum = nJoystickXAxisMaximum;

  m_nJoystickYAxisMinimum = nJoystickYAxisMinimum;
  m_nJoystickYAxisMaximum = nJoystickYAxisMaximum;

  m_nJoystickSensitivity = nJoystickSensitivity;
  
  m_nJoystickXPosition = 0;
  m_nJoystickYPosition = 0;

  m_nButtonCount = nButtonCount;
  m_bButtonActiveState = bButtonActiveState;
  m_anButtonPins = anButtonPins;

  if(m_nButtonCount && m_nButtonCount != FEATURE_NOT_AVAILABLE)
    {
    m_abButtonStates = (bool*)malloc(m_nButtonCount*sizeof(bool));
    }
  
  m_nAccelerometerAxisCount = nAccelerometerAxisCount;
  
  if(m_nAccelerometerAxisCount && m_nAccelerometerAxisCount != FEATURE_NOT_AVAILABLE)
    {
    m_anAccelerometerCalibrationValues = (int*)malloc(m_nAccelerometerAxisCount*sizeof(int));

    for(int nAxis = 0; nAxis < m_nAccelerometerAxisCount; ++nAxis)
      {
      for(int nIteration = 0; nIteration < 8; ++nIteration)
        {
        m_anAccelerometerCalibrationValues[nAxis] += analogRead(m_anAccelerometerAxisPins[nAxis]);
        }

      m_anAccelerometerCalibrationValues[nAxis] >>= 3;
      }
    }

  }

Gamepad::Gamepad() : m_nJoystickXPosition(0), m_nJoystickYPosition(0)
  {

  }

byte* Gamepad::GetPostions()
  {
  
  }

bool* Gamepad::GetButtonStates(int& nSize)
  {
  
  }

void Gamepad::StoreCalibrationData(int nAddress, bool bForce)
  {
  char acMagicBytes[4] = {};
  
  acMagicBytes[0] = EEPROM.read(nAddress++);
  acMagicBytes[1] = EEPROM.read(nAddress++);
  acMagicBytes[2] = EEPROM.read(nAddress++);
  acMagicBytes[3] = EEPROM.read(nAddress++);

  nAddress -= 4;

  bool bMagicBytesFound = !memcmp(acMagicBytes, ".gpc", 4*sizeof(char));

  if(!bMagicBytesFound || bForce)
    {
    // write the header to identify the calibration in EEPROM
    EEPROM.write(nAddress++, '.');
    EEPROM.write(nAddress++, 'g');
    EEPROM.write(nAddress++, 'p');
    EEPROM.write(nAddress++, 'c');

    // write the joystick calibration data
    EEPROM.write(nAddress++, m_nJoystickXAxisCalibrationValue >> 8);
    EEPROM.write(nAddress++, m_nJoystickXAxisCalibrationValue);
    EEPROM.write(nAddress++, m_nJoystickYAxisCalibrationValue >> 8);
    EEPROM.write(nAddress++, m_nJoystickYAxisCalibrationValue);

    // write the accelerometer calibration data
    if(m_nAccelerometerAxisCount && m_nAccelerometerAxisCount != FEATURE_NOT_AVAILABLE)
      {
      for(byte nIteration = 0; nIteration < m_nAccelerometerAxisCount; nIteration++)
        {
        EEPROM.write(nAddress++, m_anAccelerometerCalibrationValues[nIteration] >> 8);
        EEPROM.write(nAddress++, m_anAccelerometerCalibrationValues[nIteration]);
        }
      }
    }
  }

bool Gamepad::LoadCalibrationData(int nAddress)
  {
  
  }
