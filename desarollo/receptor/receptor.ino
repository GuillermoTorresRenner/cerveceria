
//--------------------------------------------------------------Librerías---------------------------------------------------------------------------------------------------------
#include <Wire.h>
//--------------------------------------------------------------Definición de variables-------------------------------------------------------------------------------------------

/*Las siguientes variables refieren a los pines que manejan los diferentes canales del relay 8 que manejarán las electroválvulas que funcionan a 12V*/

#define entradaAguaDirecta 2 //salida 1 relay 8 canales
#define entradaAguaFiltro 3 //salida 2 relay 8 canales
#define entradaExterna 4 //salida 4 relay 8 canales
#define salidaOlla 5 //salida 5 relay 8 canales
#define salidaMacerador 6 //salida 6 relay 8 canales
#define salidaGeneral 7 //salida 7 relay 8 canales
#define salidaIntercambiador 8 //salida 8 relay 8 canales

/*Las siguientes variables refieren a los pines que manejan los canales del relay 4 los cuales funcionarán a 220V manejando la bomba, la resistencia del macerador y el motor  de la moledora */
#define bomba 9
#define molino 10
#define macerador 11

/*Definición de variables auxiliares*/
char recepcion;
bool estado=false;



//--------------------------------------------------------------Inicialización-----------------------------------------------------------------------------------------------------
void setup() {
  Serial.begin(115200);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);

 digitalWrite(2,HIGH);
 digitalWrite(3,HIGH);
 digitalWrite(4,HIGH);
 digitalWrite(5,HIGH);
 digitalWrite(6,HIGH);
 digitalWrite(7,HIGH);
 digitalWrite(8,HIGH);
 digitalWrite(9,HIGH);
 digitalWrite(10,HIGH);
 digitalWrite(11,HIGH);
 


  Wire.begin(1);
  Wire.onReceive(receiveEvent);

}


//--------------------------------------------------------------Programa----------------------------------------------------------------------------------------------------------
void loop() {




}



//--------------------------------------------------------------Métodos----------------------------------------------------------------------------------------------------------
void receiveEvent(int howMany){
  if(Wire.available()>0){
     recepcion=Wire.read();
  switch(recepcion){
    case 'r':
      digitalWrite(2,HIGH);
      digitalWrite(3,LOW);
      digitalWrite(4,LOW);
      break;

      case 'a':
      digitalWrite(2,LOW);
      digitalWrite(3,HIGH);
      digitalWrite(4,LOW);
      break;

      case 'v':
      digitalWrite(2,LOW);
      digitalWrite(3,LOW);
      digitalWrite(4,HIGH);
      break;

       case 'n':
      digitalWrite(2,LOW);
      digitalWrite(3,LOW);
      digitalWrite(4,LOW);
      break;

       case 't':
      digitalWrite(2,HIGH);
      digitalWrite(3,HIGH);
      digitalWrite(4,HIGH);
      break;
  
}
  }
}




void comprobacionRelay(){
delay(5000);
for(int i=2;i<=11;i++){
  digitalWrite(i,LOW);
  delay(1000);
}
for(int i=11;i>=2;i--){
  digitalWrite(i,HIGH);
  delay(1000);
}
}


void desactivar(){
   digitalWrite(2,HIGH);
 digitalWrite(3,HIGH);
 digitalWrite(4,HIGH);
 digitalWrite(5,HIGH);
 digitalWrite(6,HIGH);
 digitalWrite(7,HIGH);
 digitalWrite(8,HIGH);
 digitalWrite(9,HIGH);
 digitalWrite(10,HIGH);
 digitalWrite(11,HIGH);
}

void entradaAgua(){
  
  
}
