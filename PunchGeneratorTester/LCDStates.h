#ifndef __LCDStates_H__
#define __LCDStates_H__
#include <Arduino.h>
#include "MainMenu.h"
#include "SplashMenu.h"
#include "SenderMenu.h"
#include "StationNumberMenu.h"
#include "SendIntervalMenu.h"
#include "RandomizeIntervalMenu.h"
#include "NoOfPunchesMenu.h"
#include "SendMenu.h"
#include "SINumberMenu.h"

class LCDStates {
    public:
        static MainMenu TheMainMenu;
        static SplashMenu TheSplashMenu;
        static SenderMenu TheSenderMenu;
        static StationNumberMenu TheStationNumberMenu;
        static SendIntervalMenu TheSendIntervalMenu;
        static RandomizeIntervalMenu TheRandomizeIntervalMenu;
        static NoOfPunchesMenu TheNoOfPunchesMenu;
        static SendMenu TheSendMenu;
        static SINumberMenu TheSINumberMenu;
};

#endif // __LCDStates_H__