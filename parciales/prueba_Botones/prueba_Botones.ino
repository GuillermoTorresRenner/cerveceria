#define btn 26
int contador=1;

void setup() {
 pinMode(btn,INPUT);
 Serial.begin(115200);

}

void loop() {
 if(digitalRead(btn)==LOW){
 delay(200);
    Serial.print("Boton presionado" );
     Serial.println(contador );
     contador++;
 }

}
