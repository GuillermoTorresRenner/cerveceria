#include <OneWire.h>

#include <DallasTemperature.h>

#define temp 26

OneWire oneWire (temp);

DallasTemperature temp1(&oneWire);

void setup() {
 Serial.begin(115200);
 temp1.begin();

}

void loop() {
 temp1.requestTemperatures();
 Serial.print("Tempertura Olla: ");
 Serial.println(temp1.getTempCByIndex(0));
 Serial.print("Tempertura Macerador: ");
 Serial.println(temp1.getTempCByIndex(1));
 delay(3000);

}
