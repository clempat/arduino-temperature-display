/**
 * Sketch for display temperature
 */

#define MY_DEBUG
#define MY_NODE_ID 2

#define MY_RADIO_NRF24
#include <SPI.h>
#include <MySensors.h>
#include <Wire.h>
#include <LiquidCrystal.h>

// Initialize display. Google the correct settings for your display. 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // initialize the lcd for 16 chars 2 lines and turn on backlight
  lcd.begin(16,2); 

  lcd.home();
  lcd.print("Temperature: ");
  lcd.print("N.C.");
}

void loop() {

}

void receive(const MyMessage &message) {
  if (message.type==V_TEMP) {
    float temperature = message.getFloat();
    #ifdef MY_DEBUG
      Serial.print("New Temperature received: ");
      Serial.print(temperature);
      Serial.println("°C");
    #endif
    lcd.home();
    lcd.print("Temperature: ");
    lcd.print(temperature);
    lcd.write(223);
    lcd.print("C");
  }
}

