#ifndef __SINumberMenu_H__
#define __SINumberMenu_H__
#include <Arduino.h>
#include "AbstractState.h"
#include <LiquidCrystal.h>
#include "Settings.h"

class SINumberMenu : public AbstractState 
{
  public:
    SINumberMenu();
    virtual void Init() override;
    virtual AbstractState* Tick();
    virtual AbstractState* Select() override;
    virtual AbstractState* Up() override;
    virtual AbstractState* Down() override;
    virtual AbstractState* Left() override;
    virtual AbstractState* Right() override;
  private:
    uint32_t siNumber;
    uint8_t position;
    void printScreen();
};

#endif // __SINumberMenu_H__
