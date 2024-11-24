#include "AbstractState.h"

//LiquidCrystal AbstractState::lcd( 8, A1, 3, 5, 6, 7 );   //Pins for the freetronics 16x2 LCD shield. LCD: ( RS, E, LCD-D4, LCD-D5, LCD-D6, LCD-D7 )
const int rs = 8;  // Register Select pin
const int enable = 9;  // Enable pin
const int d4 = 4;  // Data pin 4
const int d5 = 5;  // Data pin 5
const int d6 = 6;  // Data pin 6
const int d7 = 7;  // Data pin 7


// Create the LiquidCrystal object
LiquidCrystal AbstractState::lcd(rs, enable, d4, d5, d6, d7);

AbstractState::AbstractState()
{
}

void AbstractState::Init()
{
   resetTime();
}

void AbstractState::resetTime()
{
   millisAtInit = millis();
}

void AbstractState::ClearScreen()
{
   lcd.setCursor(0,0);
   lcd.print("                ");
   lcd.setCursor(0,1);
   lcd.print("                ");
}

AbstractState* AbstractState::Select()
{
    return NULL;
}

AbstractState* AbstractState::Left()
{
    return NULL;  
}


AbstractState* AbstractState::Right()
{
    return NULL; 
}


AbstractState* AbstractState::Up()
{
    return NULL; 
}


AbstractState* AbstractState::Down()
{
    return NULL; 
}


AbstractState* AbstractState::Tick()
{
    return NULL; 
}

