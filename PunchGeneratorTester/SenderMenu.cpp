#include "SenderMenu.h"
#include "LCDStates.h"

SenderMenu::SenderMenu() : AbstractState()
{
  cursorIndex = 0;
  firstRowIndex = 0;
}

char SenderMenu::SenderMenuItems[][15] {{"Send"},
                                            {"Control number"},
                                            {"Send interval"},
                                            {"Random. inter."},
                                            {"SI Number star"},
                                            {"No of punches"}
                                            };


void SenderMenu::Init()
{
  AbstractState::Init();
  printMenu();
  printArrow();
}

void SenderMenu::printMenu()
{
  ClearScreen();
  lcd.setCursor(2,0);
  lcd.print(SenderMenu::SenderMenuItems[firstRowIndex]);
  lcd.setCursor(2,1);
  lcd.print(SenderMenu::SenderMenuItems[firstRowIndex+1]);
}

void SenderMenu::printArrow()
{
  if (firstRowIndex == cursorIndex)
  {
    lcd.setCursor(0,0);
    lcd.print("> ");
    lcd.setCursor(0,1);
    lcd.print("  ");
  } 
  else 
  {
    lcd.setCursor(0,0);
    lcd.print("  ");
    lcd.setCursor(0,1);
    lcd.print("> ");  
  }
}


AbstractState* SenderMenu::Tick()
{
   if (millis()-millisAtInit > 10000)
   {
      return (AbstractState*)&LCDStates::TheSenderMenu;
   }
   return NULL;
}

AbstractState* SenderMenu::GetSelected()
{
  if (cursorIndex == 0) 
  {
    return (AbstractState*)&LCDStates::TheSendMenu;
  }
  else if (cursorIndex == 1) 
  {
    return (AbstractState*)&LCDStates::TheStationNumberMenu;
  } else if (cursorIndex == 2)
  {
    return (AbstractState*)&LCDStates::TheSendIntervalMenu;
  } else if (cursorIndex == 3)
  {
    return (AbstractState*)&LCDStates::TheRandomizeIntervalMenu;
  } else if (cursorIndex == 4)
  {
    return (AbstractState*)&LCDStates::TheSINumberMenu;
  } else if (cursorIndex == 5)
  {
    return (AbstractState*)&LCDStates::TheNoOfPunchesMenu;
  } 
  return NULL;
}

AbstractState* SenderMenu::Select()
{
  resetTime();
  return GetSelected();
}


AbstractState* SenderMenu::Down()
{
  resetTime();
  #define NUMBER_OF_MENUITEMS 6
  
  if (cursorIndex < NUMBER_OF_MENUITEMS-1)
  {
    if (cursorIndex > firstRowIndex)
    {
      firstRowIndex++;
      printMenu();
    }
    cursorIndex++;
    printArrow();
  }
  return NULL;
}

AbstractState* SenderMenu::Up()
{
  resetTime();
  if (cursorIndex > 0)
  {
    cursorIndex--;
    if (cursorIndex < firstRowIndex)
    {
      firstRowIndex--;
      printMenu();
    }
    printArrow();
  }
  return NULL;
}


AbstractState* SenderMenu::Left()
{
  resetTime();
  return (AbstractState*)&LCDStates::TheSenderMenu;
}

AbstractState* SenderMenu::Right()
{
  resetTime();
  return GetSelected();
}
