#include "SendMenu.h"
#include "LCDStates.h"
#include "ModuleDefs.h"

SendMenu::SendMenu() : AbstractState()
{
  controlNumber = 1;
}

void SendMenu::Init()
{
  AbstractState::Init();
  ClearScreen();
  lcd.setCursor(0,0);
  lcd.print("Node number: ");
   
  controlNumber = Settings::GetControlNumber();
  if (controlNumber > 255)
  {
    controlNumber = 0;
    Settings::SetControlNumber(controlNumber);
  }
  printSendIntervalNumber();
}

void SendMenu::printSendIntervalNumber()
{
   lcd.setCursor(13,0);
   lcd.print("  ");
   lcd.setCursor(13,0);
   lcd.print(controlNumber);
}

AbstractState* SendMenu::Tick()
{
   if (millis()-millisAtInit > 10000)
   {
      return (AbstractState*)&LCDStates::TheMainMenu;
   }
   return NULL;
}

AbstractState* SendMenu::Select()
{
  resetTime();
  Settings::SetControlNumber(controlNumber);
  LCDStates::TheSplashMenu.Init("Saved", (AbstractState*)&LCDStates::TheSenderMenu);
  return (AbstractState*)&LCDStates::TheSplashMenu;
}

AbstractState* SendMenu::Up()
{
  resetTime();
  if (controlNumber < 255)
  {
    controlNumber++;
    printSendIntervalNumber();
  }
  return NULL;
}

AbstractState* SendMenu::Down()
{
  resetTime();
  if (controlNumber > 1)
  {
    controlNumber--;
    printSendIntervalNumber();
  }
  return NULL;
}

AbstractState* SendMenu::Left()
{
  return (AbstractState*)&LCDStates::TheSenderMenu;
}
