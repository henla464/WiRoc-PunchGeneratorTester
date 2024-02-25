#ifndef __RandomizeIntervalMenu_H__
#define __RandomizeIntervalMenu_H__
#include <Arduino.h>
#include "AbstractState.h"
#include <LiquidCrystal.h>
#include "Settings.h"

class RandomizeIntervalMenu : public AbstractState 
{
  public:
    RandomizeIntervalMenu();
    virtual void Init() override;
    virtual AbstractState* Tick();
    virtual AbstractState* Select() override;
    virtual AbstractState* Up() override;
    virtual AbstractState* Down() override;
    virtual AbstractState* Left() override;
    virtual AbstractState* Right() override;
  private:
    uint32_t randomizeMS;
    uint8_t position;
    void printRandomizeMS();
};

#endif // __RandomizeIntervalMenu_H__
