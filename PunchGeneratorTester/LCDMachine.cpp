#include "LCDMachine.h"

AbstractState* LCDMachine::CurrentMenu;

uint8_t LCDMachine::BacklightPin;
uint8_t LCDMachine::ButtonPin;
bool LCDMachine::backlightOn = true;
uint8_t LCDMachine::buttonJustPressed = false;
uint8_t LCDMachine::buttonJustReleased = false;
uint8_t LCDMachine::buttonWas = BUTTON_NONE;
uint8_t LCDMachine::buttonReleased = BUTTON_NONE;
uint32_t LCDMachine::millisLastTick = 0;
uint32_t LCDMachine::millisLastButtonPress = 0;

void LCDMachine::Init(uint8_t buttonPin, uint8_t backlightPin)
{
   ButtonPin = buttonPin;
   BacklightPin = backlightPin;
   backlightOn = true;
   
    //button adc input
   pinMode( ButtonPin, INPUT );         //ensure A0 is an input
   digitalWrite( ButtonPin, LOW );      //ensure pullup is off on A0
   pinMode( BacklightPin, OUTPUT );
   digitalWrite( BacklightPin, LOW );  // Set to low then control with setting it as input or output as workaround hw bug
   TurnBacklightOn();
  
   AbstractState::lcd.begin(16,2);
   CurrentMenu = (AbstractState*)&LCDStates::TheSenderMenu;
   CurrentMenu->Init();
}

void LCDMachine::TurnBacklightOn()
{
  digitalWrite( BacklightPin, HIGH);
}

void LCDMachine::TurnBacklightOff()
{
  digitalWrite( BacklightPin, LOW);
}

void LCDMachine::ShowSplash(String txt, AbstractState* returnToMenu)
{
  if (returnToMenu == NULL)
  {
    if (CurrentMenu == &LCDStates::TheSplashMenu)
    {
      LCDStates::TheSplashMenu.Init(txt, LCDStates::TheSplashMenu.rtnToMenu);
    } else
    {
      LCDStates::TheSplashMenu.Init(txt, CurrentMenu);
    }
  } else {
    LCDStates::TheSplashMenu.Init(txt, returnToMenu);  
  }
  CurrentMenu = &LCDStates::TheSplashMenu;
  CurrentMenu->Init();
}

void LCDMachine::SetState(AbstractState *newMenu)
{
  CurrentMenu = newMenu;
  CurrentMenu->Init();
  CurrentMenu->Tick();
  millisLastTick = millis();
  Serial.println("set state");
}

void LCDMachine::Tick()
{
  // no need to run too often
  if (millis() - millisLastTick < 100)
  {
    return;
  }
  millisLastTick = millis();

  if (CurrentMenu == (AbstractState*)&LCDStates::TheSenderMenu)
  {
    if (millis() - millisLastButtonPress > 20000 && !backlightOn)
    {
      backlightOn = false;
      TurnBacklightOff();
    }
  }

  
  
  uint8_t button = ReadButtons();

  AbstractState* newState = NULL;
  if (CurrentMenu) 
  {
    //Serial.println("tick");
    newState = CurrentMenu->Tick();
  }
   //show text label for the button pressed
   if (buttonJustPressed  == false && buttonJustReleased == true)
   {
     if (buttonReleased != BUTTON_NONE)
     {
        millisLastButtonPress = millis();
        backlightOn = true;
        TurnBacklightOn();
     }
     switch( buttonReleased )
     {
        case BUTTON_RIGHT:
        {
           newState = CurrentMenu->Right();
           Serial.println("right");
           break;
        }
        case BUTTON_UP:
        {
           newState = CurrentMenu->Up();
           Serial.println("up");
           break;
        }
        case BUTTON_DOWN:
        {
           newState = CurrentMenu->Down();
           Serial.println("down");
           break;
        }
        case BUTTON_LEFT:
        {
          newState = CurrentMenu->Left();
          Serial.println("left");
          break;
       }
       case BUTTON_SELECT:
       {
          newState = CurrentMenu->Select(); 
          Serial.println("select"); 
          break;
       }
     }
   }
   buttonJustPressed = false;
   buttonJustReleased = false;

   if (newState) {
     millisLastButtonPress = millis();
     CurrentMenu = newState;
     newState = NULL;
     CurrentMenu->Init();
   }
}


/*--------------------------------------------------------------------------------------
  ReadButtons()
  Detect the button pressed and return the value
  Uses static class values buttonWas, buttonJustPressed, buttonJustReleased.
--------------------------------------------------------------------------------------*/
uint8_t LCDMachine::ReadButtons()
{
   unsigned int buttonVoltage;
   byte button = BUTTON_NONE;   // return no button pressed if the below checks don't write to btn
   
   //read the button ADC pin voltage
   buttonVoltage = analogRead( ButtonPin );
   //Serial.println(buttonVoltage);
   //sense if the voltage falls within valid voltage windows
   if( buttonVoltage < ( RIGHT_10BIT_ADC + BUTTONHYSTERESIS ) )
   {
      button = BUTTON_RIGHT;
   }
   else if(   buttonVoltage >= ( UP_10BIT_ADC + BUTTONLEVELADJUSTMENT - BUTTONHYSTERESIS )
           && buttonVoltage <= ( UP_10BIT_ADC + BUTTONLEVELADJUSTMENT + BUTTONHYSTERESIS ) )
   {
      button = BUTTON_UP;
   }
   else if(   buttonVoltage >= ( DOWN_10BIT_ADC + BUTTONLEVELADJUSTMENT - BUTTONHYSTERESIS )
           && buttonVoltage <= ( DOWN_10BIT_ADC + BUTTONLEVELADJUSTMENT + BUTTONHYSTERESIS ) )
   {
      button = BUTTON_DOWN;
   }
   else if(   buttonVoltage >= ( LEFT_10BIT_ADC + BUTTONLEVELADJUSTMENT - BUTTONHYSTERESIS )
           && buttonVoltage <= ( LEFT_10BIT_ADC + BUTTONLEVELADJUSTMENT + BUTTONHYSTERESIS ) )
   {
      button = BUTTON_LEFT;
   }
   else if(   buttonVoltage >= ( SELECT_10BIT_ADC + BUTTONLEVELADJUSTMENT - BUTTONHYSTERESIS )
           && buttonVoltage <= ( SELECT_10BIT_ADC + BUTTONLEVELADJUSTMENT + BUTTONHYSTERESIS ) )
   {
      button = BUTTON_SELECT;
   }
   //handle button flags for just pressed and just released events
   if( ( buttonWas == BUTTON_NONE ) && ( button != BUTTON_NONE ) )
   {
      //the button was just pressed, set buttonJustPressed, this can optionally be used to trigger a once-off action for a button press event
      //it's the duty of the receiver to clear these flags if it wants to detect a new button change event
      buttonJustPressed  = true;
      buttonJustReleased = false;
   }
   if( ( buttonWas != BUTTON_NONE ) && ( button == BUTTON_NONE ) )
   {
      buttonJustPressed  = false;
      buttonJustReleased = true;
   }
      
   //save the latest button value, for change event detection next time round
   buttonReleased = buttonWas;
   buttonWas = button;
   
   return( button );
}
