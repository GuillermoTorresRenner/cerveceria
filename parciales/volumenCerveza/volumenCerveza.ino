#define eco 26
# define trig 25
double duracion;
double distancia;
double alturaOlla=4.5; //en decimetros
double radioOlla=2.25; //en decimetros
double distanciaVacio;;
double volumenLiquido;

void setup() {
 pinMode(trig, OUTPUT);
 pinMode(eco,INPUT);
 Serial.begin(115200);

}

void loop() {
  digitalWrite(trig,HIGH);
  delay(1);
  digitalWrite(trig,LOW);
  duracion= pulseIn(eco,HIGH);
  distanciaVacio=duracion/582;
  volumenLiquido= (alturaOlla - distanciaVacio)*(3.14*radioOlla*radioOlla);

 Serial.print("Altura de líquido: ");
 Serial.println(alturaOlla - distanciaVacio);
 Serial.print ("Volumen (l): ");
 Serial.println(volumenLiquido);
  delay(2000);

}
