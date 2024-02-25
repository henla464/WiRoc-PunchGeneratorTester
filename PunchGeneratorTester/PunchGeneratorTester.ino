#include "LCDMachine.h"
#include "ModuleDefs.h"

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  //pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin( 115200 );


  LCDMachine::Init(BUTTON_ADC_PIN, LCD_BACKLIGHT_PIN);
  LCDMachine::Tick();
  LCDMachine::ShowSplash("Punch generator / tester");
  delay(1000);
  LCDMachine::SetState(&LCDStates::TheMainMenu);

  Serial.println("tick");
}

// the loop function runs over and over again forever
void loop() {
  //digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  //delay(500);                      // wait for a second
  //digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  //delay(500);     
  
  LCDMachine::Tick();
}
