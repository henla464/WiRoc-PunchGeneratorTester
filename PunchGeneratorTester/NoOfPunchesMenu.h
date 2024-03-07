#ifndef __NoOfPunchesMenu_H__
#define __NoOfPunchesMenu_H__
#include <Arduino.h>
#include "AbstractState.h"
#include <LiquidCrystal.h>
#include "Settings.h"

class NoOfPunchesMenu : public AbstractState 
{
  public:
    NoOfPunchesMenu();
    virtual void Init() override;
    virtual AbstractState* Tick();
    virtual AbstractState* Select() override;
    virtual AbstractState* Up() override;
    virtual AbstractState* Down() override;
    virtual AbstractState* Left() override;
    virtual AbstractState* Right() override;
  private:
    void printScreen();
    uint16_t noOfPunches;
    uint8_t position;
};

#endif // __NoOfPunchesMenu_H__
