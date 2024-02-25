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


