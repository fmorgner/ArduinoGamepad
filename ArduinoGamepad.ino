#include <Esplora.h>
#include <CJoystick.h>

  
  boolean mouseIsActive = false;    // whether or not to control the mouse
  int lastSwitchState = LOW;        // previous switch state
  
  void setup() {
   // take control of the mouse:
    Mouse.begin();
    Serial.begin(9600);
  }
  
  void loop() {

    Serial.println(Esplora.readJoystickY());
    
    // read the switch:
    int switchState = Esplora.readButton(SWITCH_1);
  
    // if it's changed and it's high, toggle the mouse state:
    if (switchState != lastSwitchState) {
      if (switchState == LOW) {
        mouseIsActive = !mouseIsActive;
        // turn on LED to indicate mouse state:
      Esplora.writeGreen((int)mouseIsActive*255);
      } 
    }
    // save switch state for next comparison:
    lastSwitchState = switchState;
  
    // read and scale the two axes:
    int xReading = map(Esplora.readJoystickX()-6, -512, 511,  48, -48);
    int yReading = map(Esplora.readJoystickY()+15, -512, 511, -48,  48);
  
    // if the mouse control state is active, move the mouse:
    if (mouseIsActive) {
      Mouse.move(xReading, yReading, 0);
    }  
  
    // read the mouse button and click or not click:
    // if the mouse button is pressed:
    if (Esplora.readButton(SWITCH_2) == LOW) {
      // if the mouse is not pressed, press it:
      if (!Mouse.isPressed(MOUSE_LEFT)) {
        Mouse.press(MOUSE_LEFT); 
      }
    } 
    // else the mouse button is not pressed:
    else {
      // if the mouse is pressed, release it:
      if (Mouse.isPressed(MOUSE_LEFT)) {
        Mouse.release(MOUSE_LEFT); 
      }
    }
  
    delay(5);
  }
  
  /*
    reads an axis (0 or 1 for x or y) and scales the 
   analog input range to a range from 0 to <range>
   */
  // 
  

