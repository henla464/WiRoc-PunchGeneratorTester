#include "LCDMachine.h"
#include "ModuleDefs.h"
#include <SoftwareSerial.h>
const byte rxPin = 3;
const byte txPin = 2;

// Set up a new SoftwareSerial object
SoftwareSerial usbSerial(rxPin, txPin);

const byte rxPinRS232 = 12;
const byte txPinRS232 = 11;
SoftwareSerial rs232Serial(rxPinRS232, txPinRS232);

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  //pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin( 115200 );
  usbSerial.begin(38400);
  rs232Serial.begin(38400);

  LCDMachine::Init(BUTTON_ADC_PIN, LCD_BACKLIGHT_PIN);
  LCDMachine::Tick();
  LCDMachine::ShowSplash("Punch generator / tester");
  delay(1000);
  LCDMachine::SetState(&LCDStates::TheSenderMenu);

  randomSeed(analogRead(A0));
  Serial.println("tick");
}

#define POLYNOM 0x8005

unsigned int calculateCRC(unsigned int uiCount,unsigned char *pucDat)
{
  short int iTmp;
  unsigned short int uiTmp,uiTmp1,uiVal;
  unsigned char *pucTmpDat;

  if (uiCount < 2) return(0);        // response value is "0" for none or one data byte
  pucTmpDat = pucDat;
  uiTmp1 = *pucTmpDat++;
  uiTmp1 = (uiTmp1<<8) + *pucTmpDat++;

  if (uiCount == 2) return(uiTmp1);   // response value is CRC for two data bytes
  for (iTmp=(int)(uiCount>>1);iTmp>0;iTmp--)
  {
    if (iTmp>1)
    {
      uiVal = *pucTmpDat++;
      uiVal= (uiVal<<8) + *pucTmpDat++;
    }
    else 
    {
      if (uiCount&1)               // odd number of data bytes, complete with "0"         
      {
        uiVal = *pucTmpDat;
        uiVal= (uiVal<<8);
      }
      else
      {
        uiVal=0; //letzte Werte mit 0
      }
    } 
    
    for (uiTmp=0;uiTmp<16;uiTmp++)
    {
      if (uiTmp1 & 0x8000)
      {
          uiTmp1  <<= 1;
          if (uiVal & 0x8000)uiTmp1++;
          uiTmp1 ^= POLYNOM;
      }
      else
      {
          uiTmp1  <<= 1;
          if (uiVal & 0x8000)uiTmp1++;
      }
      uiVal <<= 1;
    }
  }
  return(uiTmp1);
}

                        // stx   type  len    cn1   cn0   SN3  SN2   SN1   SN0    TD    TH    TL   TSS   MEM2   MEM1  MEM0   CRC1  CRC0   ETX
uint8_t PunchTemplate[] = {0x02, 0xD3, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x3F, 0x23, 0x00, 0x00, 0x00, 0x00,  0x00,  0x00, 0x03};
uint16_t seconds = 0;
uint32_t memoryAddr = 0;

void PreparePunch()
{
  uint8_t ctrlNo = Settings::GetControlNumber();
  PunchTemplate[4] = ctrlNo;

  uint32_t siNo = Settings::GetLastSINumberSent();
  PunchTemplate[5] = (siNo >> 24) & 0x000000FF;
  PunchTemplate[6] = (siNo >> 16) & 0x000000FF;
  PunchTemplate[7] = (siNo >> 8) & 0x000000FF;
  PunchTemplate[8] = siNo & 0x000000FF;

  PunchTemplate[10] = (seconds >> 8) & 0x00FF;
  PunchTemplate[11] = seconds & 0x00FF;
  seconds++;

  PunchTemplate[13] = (memoryAddr >> 16) & 0x000000FF;
  PunchTemplate[14] = (memoryAddr >> 8) & 0x000000FF;
  PunchTemplate[15] = memoryAddr & 0x000000FF;
  memoryAddr += 8;

  uint16_t crc = calculateCRC(15, (unsigned char *) (PunchTemplate+1));
  PunchTemplate[16] = (crc >> 8) & 0x00FF;
  PunchTemplate[17] = crc & 0x00FF;

}

void SendPunch()
{
  for (uint8_t i = 0; i < 19; i++)
  {
    usbSerial.write(PunchTemplate[i]);
  }
}

void SendPunchRS232()
{
  for (uint8_t i = 0; i < 19; i++)
  {
    rs232Serial.write(PunchTemplate[i]);
  }
}

// the loop function runs over and over again forever
void loop() {
  LCDMachine::Tick();
  uint8_t runMode = Settings::GetRunMode();
  if (runMode == 1) {
    Serial.println("Send punch");
    Settings::SetLastSINumberSent(Settings::GetLastSINumberSent() + 1);
    PreparePunch();
    SendPunch();
    SendPunchRS232();
    uint16_t noOfPunchesSent = Settings::GetNoOfPunchesSent() + 1;
    Settings::SetNoOfPunchesSent(noOfPunchesSent);
    if (noOfPunchesSent >= Settings::GetNoOfPunches()) {
      runMode = 0;
      Settings::SetRunMode(runMode);
      Serial.println(noOfPunchesSent);
      Serial.println("reached the no to send");
      return;
    }

    // DELAY
    uint32_t randomizeMs = Settings::GetRandomizeMS();
    Serial.println("random");
    Serial.println(randomizeMs);
    Serial.println("interval");
    uint32_t interval = Settings::GetIntervalMS();
    Serial.println(interval);
    
    int rand = random(0, randomizeMs) - randomizeMs/2;
    Serial.println("rand");
    Serial.println(rand);
    int64_t randInterval = interval + rand;
    if (randInterval <= 0) {
      randInterval = 0;
    }
    //Serial.println("randInterval");
    //Serial.println(randInterval);

    unsigned long timeBefore = millis();
    unsigned long timeAfter = timeBefore + randInterval;
    Serial.println(timeAfter);
    for (;;)
    {
      LCDMachine::Tick();
      if (runMode == 0 || millis() > timeAfter) {
        Serial.println("break.............:");
        break;
      }
    }
  }
}
