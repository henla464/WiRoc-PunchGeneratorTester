#ifndef __Settings_H__
#define __Settings_H__
#include <Arduino.h>


struct ControlSettings {
  uint8_t ControlNumber = 100;
  uint32_t SendIntervalMS = 10000;
  uint32_t RandomizeMS = 100;
  uint16_t NoOfPunches = 1;
  uint32_t StartSINumber = 500001;
  uint8_t RunMode = 0;  // 0= stopped, 1 = sending, 2=receiving
  uint16_t NoOfPunchesSent = 0;
  uint32_t LastSINumberSent;
};

class Settings
{
  public:
    static void Init();
    static uint8_t GetControlNumber();
    static void SetControlNumber(uint8_t controlNumber);
    static uint32_t GetIntervalMS();
    static void SetIntervalMS(uint32_t sendIntervalMS);
    static uint32_t GetRandomizeMS();
    static void SetRandomizeMS(uint32_t randomizeMS);
    static uint16_t GetNoOfPunches();
    static void SetNoOfPunches(uint16_t noOfPunches);
    static uint32_t GetStartSINumber();
    static void SetStartSINumber(uint32_t siNumber);
    static uint8_t GetRunMode();
    static void SetRunMode(uint8_t mode);
    static uint16_t GetNoOfPunchesSent();
    static void SetNoOfPunchesSent(uint16_t noOfPunches);
    static uint32_t GetLastSINumberSent();
    static void SetLastSINumberSent(uint32_t siNumber);

  private:
    static struct ControlSettings settings;
};

#endif // __Settings_H__
