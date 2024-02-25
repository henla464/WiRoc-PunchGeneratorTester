#ifndef __MainMenu_H__
#define __MainMenu_H__
#include <Arduino.h>
#include "AbstractState.h"
#include <LiquidCrystal.h>
//#include "Settings.h"

class MainMenu : public AbstractState 
{
  public:
    MainMenu();
    virtual void Init() override;
    virtual AbstractState* Select() override;
    virtual AbstractState* Tick() override;
    virtual AbstractState* Up() override;
    virtual AbstractState* Down() override;
    virtual AbstractState* Right() override;
  private:
    void printMenu();
    void printArrow();
    AbstractState* GetSelected();
    uint8_t cursorIndex;
    uint8_t firstRowIndex;
    static char MainMenuItems[][16];
};

#endif // __MainMenu_H__
