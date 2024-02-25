#include "MainMenu.h"
#include "LCDStates.h"
//#include "ModuleDefs.h"

MainMenu::MainMenu() : AbstractState()
{
  cursorIndex = 0;
  firstRowIndex = 0;
}

char MainMenu::MainMenuItems[][16] {{"Sender"},
                                    {"Receiver"}};

void MainMenu::Init()
{
  ClearScreen();
  printMenu();
  printArrow();
}

void MainMenu::printMenu()
{
  ClearScreen();
  lcd.setCursor(2,0);
  lcd.print(MainMenu::MainMenuItems[firstRowIndex]);
  lcd.setCursor(2,1);
  lcd.print(MainMenu::MainMenuItems[firstRowIndex+1]);
}

void MainMenu::printArrow()
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

AbstractState* MainMenu::Tick()
{
   return NULL;  
}

AbstractState* MainMenu::GetSelected()
{
  if (cursorIndex == 0) 
  {
    return (AbstractState*)&LCDStates::TheSenderMenu;
  } else if (cursorIndex == 1)
  {
    return NULL; //(AbstractState*)&LCDStates::ReceiverMenu;
  }
  return NULL;
}

AbstractState* MainMenu::Select()
{
    return GetSelected();
}


AbstractState* MainMenu::Down()
{
  #define NUMBER_OF_MENUITEMS 2
  
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

AbstractState* MainMenu::Up()
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

AbstractState* MainMenu::Right()
{
  resetTime();
  return GetSelected();
}
