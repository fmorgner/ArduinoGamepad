#ifndef __CJOYSTICK_H
#define __CJOYSTICK_H

#define NOT_AVAILABLE 255

#include <Arduino.h>

#ifdef ESPLORA
#include <Esplora.h>
#endif


class Gamepad
  {
  public:
    typedef char sbyte;

    typedef struct 
      {
      byte nXAxisPin;
      byte nYAxisPin;
      int  anXAxisLimits[2];
      int  anYAxisLimits[2];
      
      byte nButton1Pin;
      byte nButton2Pin;
      byte nButton3Pin;
      byte nButton4Pin;
      boolean bButtonActiveState;
      } gamepad_descriptor_t;

  protected:
    sbyte m_nXPosition;  // The current X position of the joystick (calibrated)
    sbyte m_nYPosition;  // The current Y position of the joystick (calibrated)
    sbyte m_nXOffset;    // The calibration offset from the ideal center of the X axis
    sbyte m_nYOffset;    // The calibration offset from the ideal center of the Y axis
    
    int m_anXLimits[2];  // The minimum and maximum reading of the X axis
    int m_anYLimits[2];  // The minimum and maximum reading of the Y axis
    
    boolean m_bLeftMouseButtonIsClicked;   // Is the left mouse button clicked?
    boolean m_bRightMouseButtonIsClicked;  // Is the right mouse button clicked?
    boolean m_bMouseButtonActiveState;     // The state that signals a pushed button (LOW of HIGH)
    
  protected:
    Gamepad(Gamepad& roGamepad);  // No copy construction
    Gamepad();  // No default construction
    
    void Update(); // The internal updating routine
  
  public:
    Gamepad(byte nXAxisPin, byte nYAxisPin, int anXLimits[2], int anYLimits[2], byte nLeftMouseButtonPin, byte nRightMouseButtonPin, boolean nMouseButtonActiveState);
    
    byte* GetPostions();

    boolean LeftMouseButtonIsDown() { return m_bLeftMouseButtonIsClicked; }
    boolean RightMouseButtonIsDown() { return m_bRightMouseButtonIsClicked; }
  };

#endif
