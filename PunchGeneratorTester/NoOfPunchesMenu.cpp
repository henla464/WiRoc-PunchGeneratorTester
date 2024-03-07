#include "NoOfPunchesMenu.h"
#include "LCDStates.h"
#include "ModuleDefs.h"

NoOfPunchesMenu::NoOfPunchesMenu() : AbstractState()
{
}

void NoOfPunchesMenu::Init()
{
  AbstractState::Init();
  ClearScreen();
  lcd.setCursor(0,0);
  lcd.print("No. punches: ");
   
  noOfPunches = Settings::GetNoOfPunches();
  if (noOfPunches > 9999)
  {
    noOfPunches = 0;
    Settings::SetNoOfPunches(noOfPunches);
  }
  printScreen();
}

void NoOfPunchesMenu::printScreen()
{
   lcd.setCursor(13,0);
   lcd.print("   ");
   if (noOfPunches > 999) {
      lcd.setCursor(12,0);
   } else if (noOfPunches > 99) {
      lcd.setCursor(13,0);
   } else if (noOfPunches > 9) {
       lcd.setCursor(14,0);
   } else {
       lcd.setCursor(15,0);
   }
   
   lcd.print(noOfPunches);
   lcd.setCursor(12,1);
   lcd.print("    ");
   lcd.setCursor(15-position,1);
   lcd.print('^');
}

AbstractState* NoOfPunchesMenu::Tick()
{
   if (millis()-millisAtInit > 10000)
   {
      return (AbstractState*)&LCDStates::TheSenderMenu;
   }
   return NULL;
}

AbstractState* NoOfPunchesMenu::Select()
{
  resetTime();
  Settings::SetNoOfPunches(noOfPunches);
  LCDStates::TheSplashMenu.Init("Saved", (AbstractState*)&LCDStates::TheSenderMenu);
  return (AbstractState*)&LCDStates::TheSplashMenu;
}

AbstractState* NoOfPunchesMenu::Up()
{
  resetTime();
  if (position == 0 && noOfPunches < 999) {
    noOfPunches++;
  } else if (position == 1 && noOfPunches <= 989) {
    noOfPunches = noOfPunches + 10;
  } else if (position == 2 && noOfPunches <= 899) {
    noOfPunches = noOfPunches + 100;
  } else if (position == 3 && noOfPunches <= 8999) {
    noOfPunches = noOfPunches + 1000;
  }
  printScreen();

  return NULL;
}

AbstractState* NoOfPunchesMenu::Down()
{
  resetTime();
  if (position == 0 && noOfPunches > 1) {
    noOfPunches--;
  } else if (position == 1 && noOfPunches > 10) {
    noOfPunches = noOfPunches - 10;
  } else if (position == 2 && noOfPunches > 100) {
    noOfPunches = noOfPunches - 100;
  } else if (position == 3 && noOfPunches > 1000) {
    noOfPunches = noOfPunches - 1000;
  }
  printScreen();
  return NULL;
}

AbstractState* NoOfPunchesMenu::Left()
{ 
  if (position < 3) {
    position++;
    printScreen();
    return NULL;
  } else {
    return (AbstractState*)&LCDStates::TheSenderMenu;
  }
}

AbstractState* NoOfPunchesMenu::Right()
{
  if (position > 0) {
    position--;
    printScreen();
  }  
  return NULL;
}
