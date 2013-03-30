#include "CGamepad.h"

Gamepad::Gamepad(byte nXAxisPin, byte nYAxisPin,  int anXLimits[2], int anYLimits[2], byte nLeftMouseButtonPin, byte nRightMouseButtonPin, boolean nMouseButtonActiveState)
  : m_bLeftMouseButtonIsClicked(false),
    m_bRightMouseButtonIsClicked(false),
    m_nXOffset(0),
    m_nYOffset(0)
  {
  #ifdef ESPLORA
    for(byte nIteration = 0; nIteration < 5; nIteration++)
      {
      m_nXOffset += Esplora.readJoystickX();
      m_nYOffset += Esplora.readJoystickY();
      }
  #else

  #endif
  }
    
byte* Gamepad::GetPostions()
  {
    
  }
