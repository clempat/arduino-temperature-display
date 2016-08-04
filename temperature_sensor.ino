/**
 * Sketch for temperature
 */

#define MY_DEBUG
#define MY_NODE_ID 1

#define MY_RADIO_NRF24
#include <SPI.h>
#include <MySensors.h>
#include <DallasTemperature.h>
#include <OneWire.h>

#define CHILD_ID_TEMP 0
#define TARGET_NODE_ID 2
#define SLEEP_TIME 5 * 60000 // 5 minutes

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(CHILD_ID_TEMP);
// Pass the oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

float lastTemperature;

MyMessage msg(0,V_TEMP);

void setup() {
  sensors.begin();
}

void loop() {
  sensors.requestTemperatures();

  int8_t resolution = sensors.getResolution();

  float temperature = static_cast<float>(static_cast<int>((sensors.getTempCByIndex(0) * 10.)) / 10.);
  

  #ifdef MY_DEBUG
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println("°C");
  #endif

  if (lastTemperature != temperature && temperature != -127.00 && temperature != 85.00) {
    // Send in the new temperature
    send(msg.setDestination(TARGET_NODE_ID).set(temperature,1));
    #ifdef MY_DEBUG
      Serial.println("Temperature sent...");
    #endif
    // Save new temperatures for next compare
    lastTemperature=temperature;
  }

  sleep(SLEEP_TIME);
}
