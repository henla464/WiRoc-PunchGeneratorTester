#include "StationNumberMenu.h"
#include "LCDStates.h"
#include "ModuleDefs.h"

StationNumberMenu::StationNumberMenu() : AbstractState()
{
}

void StationNumberMenu::Init()
{
  AbstractState::Init();
  ClearScreen();
  lcd.setCursor(0,0);
  lcd.print("Control no: ");
   
  controlNumber = Settings::GetControlNumber();
  if (controlNumber > 999)
  {
    controlNumber = 100;
    Settings::SetControlNumber(controlNumber);
  }
  printControlNumber();
}

void StationNumberMenu::printControlNumber()
{
   lcd.setCursor(13,0);
   lcd.print("   ");
   if (controlNumber > 99) {
      lcd.setCursor(13,0);
   } else if (controlNumber > 9) {
       lcd.setCursor(14,0);
   } else {
       lcd.setCursor(15,0);
   }
   
   lcd.print(controlNumber);
   lcd.setCursor(13,1);
   lcd.print("   ");
   lcd.setCursor(15-position,1);
   lcd.print('^');
}

AbstractState* StationNumberMenu::Tick()
{
   if (millis()-millisAtInit > 10000)
   {
      return (AbstractState*)&LCDStates::TheSenderMenu;
   }
   return NULL;
}

AbstractState* StationNumberMenu::Select()
{
  resetTime();
  Settings::SetControlNumber(controlNumber);
  LCDStates::TheSplashMenu.Init("Saved", (AbstractState*)&LCDStates::TheSenderMenu);
  return (AbstractState*)&LCDStates::TheSplashMenu;
}

AbstractState* StationNumberMenu::Up()
{
  resetTime();
  if (position == 0 && controlNumber < 999) {
    controlNumber++;
  } else if (position == 1 && controlNumber <= 989) {
    controlNumber = controlNumber + 10;
  } else if (position == 2 && controlNumber <= 899) {
    controlNumber = controlNumber + 100;
  }
  printControlNumber();

  return NULL;
}

AbstractState* StationNumberMenu::Down()
{
  resetTime();
  if (position == 0 && controlNumber > 1) {
    controlNumber--;
  } else if (position == 1 && controlNumber > 10) {
    controlNumber = controlNumber - 10;
  } else if (position == 2 && controlNumber > 100) {
    controlNumber = controlNumber - 100;
  }
  printControlNumber();
  return NULL;
}

AbstractState* StationNumberMenu::Left()
{ 
  if (position < 2) {
    position++;
    printControlNumber();
    return NULL;
  } else {
    return (AbstractState*)&LCDStates::TheSenderMenu;
  }
}

AbstractState* StationNumberMenu::Right()
{
  if (position > 0) {
    position--;
    printControlNumber();
  }  
  return NULL;
}
