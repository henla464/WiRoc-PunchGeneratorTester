#include "SendIntervalMenu.h"
#include "LCDStates.h"
#include "ModuleDefs.h"

SendIntervalMenu::SendIntervalMenu() : AbstractState()
{
  sendIntervalMS = 10000;
  Settings::SetIntervalMS(sendIntervalMS);
  position = 0;
}

void SendIntervalMenu::Init()
{
  AbstractState::Init();
  ClearScreen();
  lcd.setCursor(0,0);
  lcd.print("inter: ");
  lcd.setCursor(0,1);
  lcd.print("ms");

  sendIntervalMS = Settings::GetIntervalMS();
  if (sendIntervalMS > 999990)
  {
    sendIntervalMS = 0;
    Settings::SetIntervalMS(sendIntervalMS);
  }
  printSendIntervalMS();
}

void SendIntervalMenu::printSendIntervalMS()
{
   lcd.setCursor(7,0);
   lcd.print("       ");
   lcd.setCursor(7,1);
   lcd.print("       ");
   if (sendIntervalMS > 99999) 
   {
     lcd.setCursor(7,0); 
   } else if (sendIntervalMS > 9999) 
   {
     lcd.setCursor(8,0); 
   } else if (sendIntervalMS > 999) 
   {
     lcd.setCursor(9,0); 
   } else if (sendIntervalMS > 99) 
   {
     lcd.setCursor(10,0); 
   } else {
     lcd.setCursor(11,0); 
   }
   lcd.print(sendIntervalMS);
   lcd.setCursor(11-position,1);
   lcd.print('^');
}

AbstractState* SendIntervalMenu::Tick()
{
   if (millis()-millisAtInit > 10000)
   {
      return (AbstractState*)&LCDStates::TheMainMenu;
   }
   return NULL;
}

AbstractState* SendIntervalMenu::Select()
{
  resetTime();
  Settings::SetIntervalMS(sendIntervalMS);
  LCDStates::TheSplashMenu.Init("Saved", (AbstractState*)&LCDStates::TheSenderMenu);
  return (AbstractState*)&LCDStates::TheSplashMenu;
}

AbstractState* SendIntervalMenu::Up()
{
  resetTime();
  if (position == 0 && sendIntervalMS < 999990) {
    sendIntervalMS = sendIntervalMS + 10;
  } else if (position == 1 && sendIntervalMS <= 999890) {
    sendIntervalMS = sendIntervalMS + 100;
  } else if (position == 2 && sendIntervalMS <= 998990) {
    sendIntervalMS = sendIntervalMS + 1000;
  } else if (position == 3 && sendIntervalMS <= 989990) {
    sendIntervalMS = sendIntervalMS + 10000;
  } else if (position == 4 && sendIntervalMS <= 899990) {
    sendIntervalMS = sendIntervalMS + 100000;
  }
  printSendIntervalMS();
  return NULL;
}

AbstractState* SendIntervalMenu::Down()
{
  resetTime();
  if (position == 0 && sendIntervalMS > 100) {
    sendIntervalMS = sendIntervalMS - 10;
  } else if (position == 1 && sendIntervalMS >= 200) {
    sendIntervalMS = sendIntervalMS - 100;
  } else if (position == 2 && sendIntervalMS >= 1100) {
    sendIntervalMS = sendIntervalMS - 1000;
  } else if (position == 3 && sendIntervalMS >= 10100) {
    sendIntervalMS = sendIntervalMS - 10000;
  } else if (position == 4 && sendIntervalMS >= 100100) {
    sendIntervalMS = sendIntervalMS - 100000;
  }
  printSendIntervalMS();
  
  return NULL;
}

AbstractState* SendIntervalMenu::Left()
{ 
  if (position < 4) {
    position++;
    printSendIntervalMS();
    return NULL;
  } else {
    return (AbstractState*)&LCDStates::TheSenderMenu;
  }
}

AbstractState* SendIntervalMenu::Right()
{
  if (position > 0) {
    position--;
    printSendIntervalMS();
  }  
  return NULL;
}
