#include "RandomizeIntervalMenu.h"
#include "LCDStates.h"
#include "ModuleDefs.h"

RandomizeIntervalMenu::RandomizeIntervalMenu() : AbstractState()
{
  randomizeMS = 100;
  Settings::SetRandomizeMS(randomizeMS);
}

void RandomizeIntervalMenu::Init()
{
  AbstractState::Init();
  ClearScreen();
  lcd.setCursor(0,0);
  lcd.print("random.: ");
  lcd.setCursor(0,1);
  lcd.print("ms");

  randomizeMS = Settings::GetRandomizeMS();
  if (randomizeMS > 999990)
  {
    randomizeMS = 100;
    Settings::SetRandomizeMS(randomizeMS);
  }
  printRandomizeMS();
}

void RandomizeIntervalMenu::printRandomizeMS()
{
  lcd.setCursor(7,0);
  lcd.print("       ");
  lcd.setCursor(7,1);
  lcd.print("       ");
  if (randomizeMS > 99999) 
  {
    lcd.setCursor(7,0); 
  } else if (randomizeMS > 9999) 
  {
    lcd.setCursor(8,0); 
  } else if (randomizeMS > 999) 
  {
    lcd.setCursor(9,0); 
  } else if (randomizeMS > 99) 
  {
    lcd.setCursor(10,0); 
  } else {
    lcd.setCursor(11,0); 
  }
  lcd.print(randomizeMS);
  lcd.setCursor(11-position,1);
  lcd.print('^');
}

AbstractState* RandomizeIntervalMenu::Tick()
{
   if (millis()-millisAtInit > 10000)
   {
      return (AbstractState*)&LCDStates::TheMainMenu;
   }
   return NULL;
}

AbstractState* RandomizeIntervalMenu::Select()
{
  resetTime();
  Settings::SetRandomizeMS(randomizeMS);
  LCDStates::TheSplashMenu.Init("Saved", (AbstractState*)&LCDStates::TheSenderMenu);
  return (AbstractState*)&LCDStates::TheSplashMenu;
}

AbstractState* RandomizeIntervalMenu::Up()
{
  resetTime();
  if (position == 0 && randomizeMS < 999990) {
    randomizeMS = randomizeMS + 10;
  } else if (position == 1 && randomizeMS <= 999890) {
    randomizeMS = randomizeMS + 100;
  } else if (position == 2 && randomizeMS <= 998990) {
    randomizeMS = randomizeMS + 1000;
  } else if (position == 3 && randomizeMS <= 989990) {
    randomizeMS = randomizeMS + 10000;
  } else if (position == 4 && randomizeMS <= 899990) {
    randomizeMS = randomizeMS + 100000;
  }
  printRandomizeMS();
  return NULL;
}

AbstractState* RandomizeIntervalMenu::Down()
{
  resetTime();
  if (position == 0 && randomizeMS > 100) {
    randomizeMS = randomizeMS - 10;
  } else if (position == 1 && randomizeMS >= 200) {
    randomizeMS = randomizeMS - 100;
  } else if (position == 2 && randomizeMS >= 1100) {
    randomizeMS = randomizeMS - 1000;
  } else if (position == 3 && randomizeMS >= 10100) {
    randomizeMS = randomizeMS - 10000;
  } else if (position == 4 && randomizeMS >= 100100) {
    randomizeMS = randomizeMS - 100000;
  }
  printRandomizeMS();
  
  return NULL;
}

AbstractState* RandomizeIntervalMenu::Left()
{ 
  if (position < 4) {
    position++;
    printRandomizeMS();
    return NULL;
  } else {
    return (AbstractState*)&LCDStates::TheSenderMenu;
  }
}

AbstractState* RandomizeIntervalMenu::Right()
{
  if (position > 0) {
    position--;
    printRandomizeMS();
  }  
  return NULL;
}
