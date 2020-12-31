

#include <BluetoothSerial.h>



//BluetoothSerial SerialBT;

char recibido;

void setup() {
  Serial.begin(115200);
 // SerialBT.begin("Cerveceria");


}

void loop() {
 /*if(SerialBT.available()){
  recibido=SerialBT.read();

  Serial.println(recibido);
  SerialBT.println ("caracter recibido");
  Serial.write(recibido);
 }
*/

for(int i=1;i<11;i++){
  Serial.println(i);
  delay(2000);
}
}
