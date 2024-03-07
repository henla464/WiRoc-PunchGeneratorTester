#include "SINumberMenu.h"
#include "LCDStates.h"
#include "ModuleDefs.h"

SINumberMenu::SINumberMenu() : AbstractState()
{
  position = 0;
}

void SINumberMenu::Init()
{
  AbstractState::Init();
  ClearScreen();
  lcd.setCursor(0,0);
  lcd.print("sino: ");

  siNumber = Settings::GetStartSINumber();
  if (siNumber > 999999)
  {
    siNumber = 500001;
    Settings::SetStartSINumber(siNumber);
  }
  printScreen();
}

void SINumberMenu::printScreen()
{
   lcd.setCursor(6,0);
   lcd.print("        ");
   lcd.setCursor(6,1);
   lcd.print("        ");
   if (siNumber > 99999) 
   {
     lcd.setCursor(6,0); 
   } else if (siNumber > 9999) 
   {
     lcd.setCursor(7,0); 
   } else if (siNumber > 999) 
   {
     lcd.setCursor(8,0); 
   } else if (siNumber > 99) 
   {
     lcd.setCursor(9,0); 
   } else {
     lcd.setCursor(10,0); 
   }
   lcd.print(siNumber);
   lcd.setCursor(11-position,1);
   lcd.print('^');
}

AbstractState* SINumberMenu::Tick()
{
   if (millis()-millisAtInit > 10000)
   {
      return (AbstractState*)&LCDStates::TheSenderMenu;
   }
   return NULL;
}

AbstractState* SINumberMenu::Select()
{
  resetTime();
  Settings::SetStartSINumber(siNumber);
  LCDStates::TheSplashMenu.Init("Saved", (AbstractState*)&LCDStates::TheSenderMenu);
  return (AbstractState*)&LCDStates::TheSplashMenu;
}

AbstractState* SINumberMenu::Up()
{
  resetTime();
  if (position == 0 && siNumber < 999999) {
    siNumber = siNumber + 1;
  } else if (position == 1 && siNumber <= 999989) {
    siNumber = siNumber + 10;
  } else if (position == 2 && siNumber <= 999899) {
    siNumber = siNumber + 100;
  } else if (position == 3 && siNumber <= 998999) {
    siNumber = siNumber + 1000;
  } else if (position == 4 && siNumber <= 989999) {
    siNumber = siNumber + 10000;
  } else if (position == 5 && siNumber <= 899999) {
    siNumber = siNumber + 100000;
  }
  printScreen();
  return NULL;
}

AbstractState* SINumberMenu::Down()
{
  resetTime();
  if (position == 0 && siNumber > 1) {
    siNumber = siNumber - 1;
  } else if (position == 1 && siNumber >= 11) {
    siNumber = siNumber - 10;
  } else if (position == 2 && siNumber >= 101) {
    siNumber = siNumber - 100;
  } else if (position == 3 && siNumber >= 1001) {
    siNumber = siNumber - 1000;
  } else if (position == 4 && siNumber >= 10001) {
    siNumber = siNumber - 10000;
  } else if (position == 5 && siNumber > 100001) {
    siNumber = siNumber - 100000;
  }
  printScreen();
  
  return NULL;
}

AbstractState* SINumberMenu::Left()
{ 
  if (position < 5) {
    position++;
    printScreen();
    return NULL;
  } else {
    return (AbstractState*)&LCDStates::TheSenderMenu;
  }
}

AbstractState* SINumberMenu::Right()
{
  if (position > 0) {
    position--;
    printScreen();
  }  
  return NULL;
}
