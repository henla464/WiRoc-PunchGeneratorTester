#include "SendMenu.h"
#include "LCDStates.h"
#include "ModuleDefs.h"

SendMenu::SendMenu() : AbstractState()
{
  LastRunMode = Settings::GetRunMode();
}

void SendMenu::Init()
{
  AbstractState::Init();
  LastNoOfPunchesSent = 0;
  ClearScreen();
  lcd.setCursor(0,0);
  lcd.print("No sent:");
  lcd.setCursor(0,1);
  lcd.print("Last si:");
  printScreen();
}

void SendMenu::printScreen()
{
   lcd.setCursor(8,0);
   lcd.print("        ");
   lcd.setCursor(8,0);
   lcd.print(Settings::GetNoOfPunchesSent());
   lcd.setCursor(15,0);
   if (Settings::GetRunMode() == 1) {
    lcd.print("S");
   }
   lcd.setCursor(8,1);
   lcd.print("        ");
   if (Settings::GetLastSINumberSent() >= Settings::GetStartSINumber())
   {
    lcd.setCursor(8,1);
    lcd.print(Settings::GetLastSINumberSent());
   }
}

AbstractState* SendMenu::Tick()
{
  if (Settings::GetNoOfPunchesSent() != LastNoOfPunchesSent ||
      LastRunMode != Settings::GetRunMode())
  {
    LastNoOfPunchesSent = Settings::GetNoOfPunchesSent();
    LastRunMode = Settings::GetRunMode();
    printScreen();
  }
  return NULL;
}

AbstractState* SendMenu::Select()
{
  resetTime();
  // start sending
  if (Settings::GetRunMode() == 0) {
    Settings::SetRunMode(1);
    Settings::SetLastSINumberSent(Settings::GetStartSINumber()-1);
    Settings::SetNoOfPunchesSent(0);
  } else if (Settings::GetRunMode() == 1) {
    Settings::SetRunMode(0);
  }

  printScreen();
  //LCDStates::TheSplashMenu.Init("Saved", (AbstractState*)&LCDStates::TheSenderMenu);
  return (AbstractState*)&LCDStates::TheSendMenu;
}

AbstractState* SendMenu::Up()
{
  resetTime();
  printScreen();
  return NULL;
}

AbstractState* SendMenu::Down()
{
  resetTime();
  printScreen();
  return NULL;
}


AbstractState* SendMenu::Left()
{
  return (AbstractState*)&LCDStates::TheSenderMenu;
}
