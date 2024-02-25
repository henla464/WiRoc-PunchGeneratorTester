#ifndef __SendIntervalMenu_H__
#define __SendIntervalMenu_H__
#include <Arduino.h>
#include "AbstractState.h"
#include <LiquidCrystal.h>
#include "Settings.h"

class SendIntervalMenu : public AbstractState 
{
  public:
    SendIntervalMenu();
    virtual void Init() override;
    virtual AbstractState* Tick();
    virtual AbstractState* Select() override;
    virtual AbstractState* Up() override;
    virtual AbstractState* Down() override;
    virtual AbstractState* Left() override;
    virtual AbstractState* Right() override;
  private:
    uint32_t sendIntervalMS;
    uint8_t position;
    void printSendIntervalMS();
};

#endif // __SendIntervalMenu_H__
