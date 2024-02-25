#ifndef __Settings_H__
#define __Settings_H__
#include <Arduino.h>


struct ControlSettings {
  uint8_t ControlNumber;
  uint32_t SendIntervalMS;
  uint32_t RandomizeMS;
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
    
  private:
    static struct ControlSettings settings;
};

#endif // __Settings_H__
