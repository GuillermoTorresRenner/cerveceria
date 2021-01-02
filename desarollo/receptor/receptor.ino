
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
#define bomba 9 //salida 1 relay 4 canales
#define bombaLavado 10 //salida 2 relay 4 canales
#define macerador 11 //salida 3 relay 4 canales

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
   
      case 'a':entradaAguaSinFiltrar();
      break;

      case 'b':entradaAguaFiltrada();
      break;

      case 'c':entradaExterior();
      break;

      case 'd':trasiegoOlla();
      break;

      case 'e':trasiegoMacerador();
      break;

      case 'f':calentar();
      break;

      case 'g':
      break;

      case 'h':
      break;

      case 'i':
      break;

      case 'j':
      break;

      case 'k':
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

void entradaAguaSinFiltrar(){
  desactivar();
  delay(3000);
  digitalWrite(entradaAguaDirecta, LOW) ;

}

void entradaAguaFiltrada(){
  desactivar();
  delay(3000);
  digitalWrite(entradaAguaFiltro, LOW) ;

}

void entradaExterior(){
  desactivar(); 
  delay(3000);
  digitalWrite(entradaExterna, LOW) ;
  delay(3000);
  digitalWrite(salidaGeneral, LOW) ;
  delay(3000);
  digitalWrite(bomba,LOW);

}

void trasiegoOlla(){
  desactivar(); 
  delay(3000);
  digitalWrite(salidaOlla, LOW) ;
  delay(3000);
  digitalWrite(salidaGeneral, LOW) ;
  delay(3000);
  digitalWrite(bomba,LOW);

}

void trasiegoMacerador(){
  desactivar(); 
  delay(3000);
  digitalWrite(salidaMacerador, LOW) ;
  delay(3000);
  digitalWrite(salidaGeneral, LOW) ;
  delay(3000);
  digitalWrite(bomba,LOW);

}

void refrigererar(){
  desactivar(); 
  delay(3000);
  entradaAguaSinFiltrar();
  delay(10000);
  digitalWrite(salidaIntercambiador, LOW) ;
  delay(3000);
  digitalWrite(bomba,LOW);
  
}

void calentar(){
  desactivar(); 
  delay(3000);
  digitalWrite(macerador, LOW);
  
}
