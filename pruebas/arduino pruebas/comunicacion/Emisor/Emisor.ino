#include <SoftwareSerial.h>



SoftwareSerial mySerial(25,26);
void setup() {
  
 
 mySerial.begin(115200);
}

void loop() {
  
for(int i=1;i<11;i++){
  mySerial.write(i);
  delay(2000);

}
}
