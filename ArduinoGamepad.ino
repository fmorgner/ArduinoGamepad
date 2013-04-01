#include "CGamepad.h"
#include <EEPROM.h>
#include <Esplora.h>

bool bMouseIsActive   = false;
bool bLastSwitchState = LOW;
int  anAxisRange[2]   = {0, 1023};
byte anButtonPins[4]  = {1,2,3,4};
byte anAxisPins[3]    = {A2,A3,A4};

void setup()
  {
//  Gamepad::StoreDescriptor(stTestDescriptor);

  Mouse.begin();
  }

void loop()
  {

  bool bSwitchState = Esplora.readButton(SWITCH_1);

  if (bSwitchState != bLastSwitchState)
    {
    if (bSwitchState == LOW)
      {
      bMouseIsActive = !bMouseIsActive;
      Esplora.writeRed((int)bMouseIsActive * 255);
      } 
    }

  bLastSwitchState = bSwitchState;


  int xReading = map(Esplora.readJoystickX()-6, -512, 511,  48, -48);
  int yReading = map(Esplora.readJoystickY()+15, -512, 511, -48,  48);


  if (bMouseIsActive)
    {
    Mouse.move(xReading, yReading, 0);
    }

  if (Esplora.readButton(SWITCH_2) == LOW)
    {
    if (!Mouse.isPressed(MOUSE_LEFT))
      {
      Mouse.press(MOUSE_LEFT); 
      }
    }

  else
    {
    if (Mouse.isPressed(MOUSE_LEFT))
      {
      Mouse.release(MOUSE_LEFT); 
      }
    }
  
  delay(10);
  }

