#ifndef __StationNumberMenu_H__
#define __StationNumberMenu_H__
#include <Arduino.h>
#include "AbstractState.h"
#include <LiquidCrystal.h>
#include "Settings.h"

class StationNumberMenu : public AbstractState 
{
  public:
    StationNumberMenu();
    virtual void Init() override;
    virtual AbstractState* Tick();
    virtual AbstractState* Select() override;
    virtual AbstractState* Up() override;
    virtual AbstractState* Down() override;
    virtual AbstractState* Left() override;
    virtual AbstractState* Right() override;
  private:
    uint16_t controlNumber;
    uint8_t position;
    void printControlNumber();
};

#endif // __StationNumberMenu_H__
