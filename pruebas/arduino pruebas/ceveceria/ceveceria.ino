
//Declaración de variables

//Relay 8
#define entradaAguaFiltro 2
#define entradaAguaDirecta 3
#define salidaOlla 4
#define salidaMacerador 5
#define salidaGeneral 6
#define salidaEnfriador 7
#define entradaExterna 8

//Relay 4
#define bombaGeneral 9
#define bombaLavado 10
#define resistencia 11
#define molino 12


char comando;

void setup() {
//Inicialización de variables

//Inicialización serial
Serial.begin(9600);

//Inicialización de pines

pinMode(entradaAguaFiltro,OUTPUT);
pinMode(entradaAguaDirecta,OUTPUT);
pinMode(salidaOlla,OUTPUT);
pinMode(salidaMacerador,OUTPUT);
pinMode(salidaGeneral,OUTPUT);
pinMode(salidaEnfriador,OUTPUT);
pinMode(entradaExterna,OUTPUT);
pinMode(bombaGeneral,OUTPUT);
pinMode(bombaLavado,OUTPUT);
pinMode(resistencia,OUTPUT);
pinMode(molino,OUTPUT);

//Puesta a cero de las funciones

digitalWrite(entradaAguaFiltro,HIGH);
digitalWrite(entradaAguaDirecta,HIGH);
digitalWrite(salidaOlla,HIGH);
digitalWrite(salidaMacerador,HIGH);
digitalWrite(salidaGeneral,HIGH);
digitalWrite(salidaEnfriador,HIGH);
digitalWrite(entradaExterna,HIGH);
digitalWrite(bombaGeneral,HIGH);
digitalWrite(bombaLavado,HIGH);
digitalWrite(resistencia,HIGH);
digitalWrite(molino,HIGH);


  

}

void loop() {
Serial.println("Esperando Directiva");
while(Serial.available()==0){
  
}


 if(Serial.available()>0){
  comando=Serial.read();
  digitalWrite(5,LOW);
 
   switch(comando){
    case 'a':activar(entradaAguaFiltro, false,"¿Desea comenzar el llenado con agua filtrada?");
    break;

    case 'b':activar(entradaAguaDirecta, false,"¿Desea comenzar el llenado con agua SIN filtrar?");
    break;

    case 'c': activar(salidaOlla, true,"¿Desea evacuar la Olla de cocción?");
    break;

     case 'd': activar(salidaMacerador, true,"¿Desea evacuar el macerador?");
    break;

    
  }
 
 
 
  
 
 }
}















void activar(int electroValvula,bool bomba, String mensaje ){
  Serial.println(mensaje);
  
 
 
    if(bomba){
      digitalWrite(electroValvula,LOW);
      digitalWrite(bombaGeneral,LOW);
     }else{
       digitalWrite(electroValvula,LOW);
     }

    
       if(bomba){
      digitalWrite(electroValvula,HIGH);
      digitalWrite(bombaGeneral,HIGH);
     }else{
       digitalWrite(electroValvula,HIGH);
     }
      
     }
      


void pararTodo(){
digitalWrite(entradaAguaFiltro,HIGH);
digitalWrite(entradaAguaDirecta,HIGH);
digitalWrite(salidaOlla,HIGH);
digitalWrite(salidaMacerador,HIGH);
digitalWrite(salidaGeneral,HIGH);
digitalWrite(salidaEnfriador,HIGH);
digitalWrite(entradaExterna,HIGH);
digitalWrite(bombaGeneral,HIGH);
digitalWrite(bombaLavado,HIGH);
digitalWrite(resistencia,HIGH);
digitalWrite(molino,HIGH);

}
