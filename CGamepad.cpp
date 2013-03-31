#include "CGamepad.h"

Gamepad::Gamepad(gamepad_descriptor_t* pstDescriptor) : m_pstDescriptor(pstDescriptor), m_nXPosition(0), m_nYPosition(0), m_abButtonStates(NULL)
  {
  if(pstDescriptor == NULL)
    return;
    
  int nXBuffer = 0, nYBuffer = 0;
  
  for(byte nIteration = 0; nIteration < 8; ++nIteration)
    {
    nXBuffer += analogRead(m_pstDescriptor->nJoystickXAxisPin);
    nYBuffer += analogRead(m_pstDescriptor->nJoystickYAxisPin);
    }
  
  m_pstDescriptor->anJoystickCalibrationData[0] = (nXBuffer >> 3);
  m_pstDescriptor->anJoystickCalibrationData[1] = (nYBuffer >> 3);
  
  if(m_pstDescriptor->nButtonsCount && m_pstDescriptor->nButtonsCount != FEATURE_NOT_AVAILABLE)
    {
    m_abButtonStates = (bool*)malloc(pstDescriptor->nButtonsCount*sizeof(bool));
    }
  
  byte nAcceleromterAxisCount = 0;
  
  if(m_pstDescriptor->nAccelerometerAxisCount && m_pstDescriptor->nAccelerometerAxisCount != FEATURE_NOT_AVAILABLE)
    {
    m_pstDescriptor->anAccelerometerCalibrationData = (int*)malloc(m_pstDescriptor->nAccelerometerAxisCount*sizeof(int));

    for(int nAxis = 0; nAxis < m_pstDescriptor->nAccelerometerAxisCount; ++nAxis)
      {
      for(int nIteration = 0; nIteration < 8; ++nIteration)
        {
        m_pstDescriptor->anAccelerometerCalibrationData[nAxis] += analogRead(m_pstDescriptor->anAccelerometerAxisPins[nAxis]);
        }

      m_pstDescriptor->anAccelerometerCalibrationData[nAxis] >>= 3;
      }
    }
  }

Gamepad::Gamepad() : m_nXPosition(0), m_nYPosition(0), m_abButtonStates(NULL)
  {
  m_pstDescriptor = (gamepad_descriptor_t*)malloc(sizeof(gamepad_descriptor_t));
  
  if(!m_pstDescriptor)
    return;
  
  
  }

byte* Gamepad::GetPostions()
  {
  
  }

bool* Gamepad::GetButtonStates(int& nSize)
  {
  
  }

void Gamepad::StoreDescriptor(gamepad_descriptor_t* pstDescriptor)
  {
  
  }

gamepad_descriptor_t* Gamepad::LoadDescriptor()
  {
  
  }
