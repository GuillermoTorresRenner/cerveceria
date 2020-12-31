#include <LiquidCrystal_I2C.h>


#include <Wire.h>




#include <BluetoothSerial.h>


char recepcion;
BluetoothSerial SerialBT;
LiquidCrystal_I2C lcd (0x3f,20,4);

void setup() {
  SerialBT.begin("cerveceria");
  Serial.begin(115200);
  Wire.begin();
  lcd.begin(20,4);
  lcd.clear();
  lcd.backlight();
  
  

}

void loop() {
  lcd.setCursor(0,0);
  lcd.print("esperando Directiva");
 while(SerialBT.available()==0){
  
 }

 if(SerialBT.available()>0){
  recepcion=SerialBT.read();

switch(recepcion){
  case 'r':
  lcd.clear();
  lcd.print("desea prender led Rojo?");
  break;
  
}


  
  Wire.beginTransmission(1);
  Wire.write(recepcion);
  Wire.endTransmission();
  delay(1000);

 
 }

}
