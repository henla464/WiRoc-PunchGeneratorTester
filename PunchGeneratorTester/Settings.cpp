#include "Settings.h"
#include <Arduino.h>


struct ControlSettings Settings::settings;

void Settings::Init()
{
}


uint8_t Settings::GetControlNumber()
{
  return settings.ControlNumber;
}

void Settings::SetControlNumber(uint8_t controlNumber)
{
  settings.ControlNumber = controlNumber;
}

uint32_t Settings::GetIntervalMS()
{
  return settings.SendIntervalMS;
}

void Settings::SetIntervalMS(uint32_t sendIntervalMS)
{
  settings.SendIntervalMS = sendIntervalMS;
}

uint32_t Settings::GetRandomizeMS()
{
  return settings.RandomizeMS;
}

void Settings::SetRandomizeMS(uint32_t randomizeMS)
{
  settings.RandomizeMS = randomizeMS;
}

uint16_t Settings::GetNoOfPunches()
{
  return settings.NoOfPunches;
}

void Settings::SetNoOfPunches(uint16_t noOfPunches)
{
  settings.NoOfPunches = noOfPunches;
}

uint32_t Settings::GetStartSINumber()
{
  return settings.StartSINumber;
}

void Settings::SetStartSINumber(uint32_t siNumber)
{
  settings.StartSINumber = siNumber;
}

uint8_t Settings::GetRunMode()
{
  return settings.RunMode;
}

void Settings::SetRunMode(uint8_t mode)
{
  settings.RunMode = mode;
}

uint16_t Settings::GetNoOfPunchesSent()
{
  return settings.NoOfPunchesSent;
}

void Settings::SetNoOfPunchesSent(uint16_t noOfPunches)
{
  settings.NoOfPunchesSent = noOfPunches;
}

uint32_t Settings::GetLastSINumberSent()
{
  return settings.LastSINumberSent;
}

void Settings::SetLastSINumberSent(uint32_t siNumber)
{
  settings.LastSINumberSent = siNumber;
}
