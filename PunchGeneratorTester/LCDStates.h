#ifndef __LCDStates_H__
#define __LCDStates_H__
#include <Arduino.h>
#include "MainMenu.h"
#include "SplashMenu.h"
#include "SenderMenu.h"
#include "StationNumberMenu.h"
#include "SendIntervalMenu.h"
#include "RandomizeIntervalMenu.h"
#include "SendMenu.h"

class LCDStates {
    public:
        static MainMenu TheMainMenu;
        static SplashMenu TheSplashMenu;
        static SenderMenu TheSenderMenu;
        static StationNumberMenu TheStationNumberMenu;
        static SendIntervalMenu TheSendIntervalMenu;
        static RandomizeIntervalMenu TheRandomizeIntervalMenu;
        static SendMenu TheSendMenu;
};

#endif // __LCDStates_H__