#ifndef __SenderMenu_H__
#define __SenderMenu_H__
#include <Arduino.h>
#include "AbstractState.h"
#include <LiquidCrystal.h>

class SenderMenu : public AbstractState 
{
  public:
    SenderMenu();
    virtual void Init() override;
    virtual AbstractState* Select() override;
    virtual AbstractState* Tick() override;
    virtual AbstractState* Up() override;
    virtual AbstractState* Down() override;
    virtual AbstractState* Left() override;
    virtual AbstractState* Right() override;
  private:
    void printMenu();
    void printArrow();
    AbstractState* GetSelected();
    uint8_t cursorIndex;
    uint8_t firstRowIndex;
    static char SenderMenuItems[][15];
};

#endif // __SenderMenu_H__
