
char rx;

void setup() {

Serial.begin(115200);
}

void loop() {

 if(Serial.available()>0){
  rx=Serial.read();
  Serial.print(rx);
 }

}
