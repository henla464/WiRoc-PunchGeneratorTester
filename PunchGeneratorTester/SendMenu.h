#ifndef __SendMenu_H__
#define __SendMenu_H__
#include <Arduino.h>
#include "AbstractState.h"
#include <LiquidCrystal.h>
#include "Settings.h"

class SendMenu : public AbstractState 
{
  public:
    SendMenu();
    virtual void Init() override;
    virtual AbstractState* Tick();
    virtual AbstractState* Select() override;
    virtual AbstractState* Up() override;
    virtual AbstractState* Down() override;
    virtual AbstractState* Left() override;
  private:
    uint16_t LastNoOfPunchesSent;
    uint8_t LastRunMode;
    void printScreen();
};

#endif // __SendMenu_H__
