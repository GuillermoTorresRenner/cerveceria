#include <SoftwareSerial.h>




SoftwareSerial myserial(2,3);
void setup() {
 Serial.begin(115200);

}

void loop() {
  if(Serial.available()>0){
    char recibido=Serial.read();
    Serial.print(recibido);
  }

}
