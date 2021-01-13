//--------------------------------------------------------------Librerías---------------------------------------------------------------------------------------------------------
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>



#include <BluetoothSerial.h>

//--------------------------------------------------------------Definición de variables-------------------------------------------------------------------------------------------
#define botonAceptar 26
#define botonCancelar 25
#define flujometro1 17
#define flujometro2 16
#define trig 27
#define eco 14
#define termometros 12
#define ledBT 13
#define ledDirectiva 5
#define ledResistencia 23
#define buzzer 19
//queda el pin 18 vacante


//Declración de variables globales auxiliares del programa
String comando="";
char caracter=0;
bool nuevaLinea=false;
String recepcion;
char operacion;
String parametro;


//Declaración de objetos inherentes a las librerías de clases utilizadas
BluetoothSerial SerialBT;
LiquidCrystal_I2C lcd (0x3f,20,4);
OneWire oneWire (termometros);
DallasTemperature temperatura(&oneWire);


//--------------------------------------------------------------Inicialización-----------------------------------------------------------------------------------------------------
void setup() {
  //Inicio BT
  SerialBT.begin("Cerveceria");
  
  //Inicio Monitor Serial
  Serial.begin(115200);

  //Inicio Comunicación I2C
  Wire.begin();

  //Inicio de sensores de temperatura
  temperatura.begin();

  //Inicio Pantalla LCD de 20x4
  lcd.begin(20,4);
  lcd.clear();
  lcd.backlight();
  
  //Inicio de pines de entrada
  pinMode(botonAceptar,INPUT);
  pinMode(botonCancelar,INPUT);
  pinMode(flujometro1,INPUT);
  pinMode(flujometro2,INPUT);
  pinMode(termometros,INPUT);
  pinMode(eco,INPUT);

  //Inicio de pines de Salida
  pinMode(trig, OUTPUT);
  pinMode(ledBT,OUTPUT);
  pinMode(ledBT,OUTPUT);
  pinMode(ledResistencia,OUTPUT);
  pinMode(buzzer,OUTPUT);
 
  
       
  
}

//--------------------------------------------------------------Programa----------------------------------------------------------------------------------------------------------
void loop() {


    /* Directivas si es que no se ha recibido ninguna instreucción por bluetoot*/
 while(SerialBT.available()==0){
  lcd.clear();
  lcd.print("Esperando Directiva");
  lcd.display();
  delay(500);
  lcd.noDisplay();
  delay(500);
 
 }





/*Directivas en caso de que se hayan recibido directivas Bluettoth*/
 while(SerialBT.available()>0){

  //algoritmo para concatenar los caracteres recibidos en una cadena de String, la cual posteriormente se procesará para extraer la operación solicitada y los parámetros asociados
    caracter=SerialBT.read();
    if(caracter=='\r'){
      continue;
      
    }else if(caracter=='\n'){
      nuevaLinea=true;
      break;
      
    }else{
      comando=comando+caracter;
    }
 }

 if(nuevaLinea){
      nuevaLinea=false;
      recepcion=comando;
      comando="";
      
    }


//comprobación prescindible inicio
Serial.print("comando: ");
Serial.println(comando);
Serial.print("recepción: ");
Serial.println(recepcion);
//comprobación prescindible fin
   
  //Tratamiento del String recibido para poder decodificar la información que éste trae asociada.
  operacion=recepcion.charAt(0);
  parametro=recepcion.substring(1);

//comprobación prescindible inicio
Serial.print("operacion: ");
Serial.println(operacion);
Serial.print("parámetro: ");
Serial.println(parametro);
//comprobación prescindible fin


//arbol de operaciones 

switch(operacion){

  
     case 'a': //ingreso de agua de red sin pasar por el filtro de carbon activado
               
                mensajePantalla("INGRESO","AGUA SIN FILTRAR "+parametro+ "L");
                esperarConfirmacion();
                confirmado();
                break;
                
                

      case 'b': //ingreso de agua a la planta desde el filtro de carbón activado.
                
                mensajePantalla("INGRESO","AGUA DECLORADA "+parametro+ "L");
                esperarConfirmacion();
                confirmado();
                break;

      case 'c': //succión desde el exterior por entrada anexa a la bomba
      
                mensajePantalla("INGRESO","SUCCION EXTERIOR "+parametro+ "L");
                esperarConfirmacion();
                confirmado();
                break;

      case 'd': // apertura de las válvulas de la olla de cocción y encendido de la bomba para trasegar por cañería principal
      
                mensajePantalla("TRASIEGO","OLLA COCCION");
                esperarConfirmacion();
                confirmado();
                break;

      case 'e': //  apertura de las válvulas del macerador y encendido de la bomba para trasegar por cañería principal
                mensajePantalla("TRASIEGO","MACERADOR");
                esperarConfirmacion();
                confirmado();
                break;

      case 'f': //rutina de macerado.
      
                mensajePantalla("MACERADO","");
                esperarConfirmacion();
                confirmado();
                break;

      case 'z': //proceso de parada de EMERGENCIA
                desactivar();
      break;

      case 'h': //refrigeración, apertura de las válvulas de la olla de cocción y pasaje de la cerveza por el intercambiador de calor hasta la salida del mismo al fermentador
                
                 mensajePantalla("INTERCAMBIADOR","");
                 esperarConfirmacion();
                 confirmado();
                 break;

      case 'i': //lectura de las temperaturas de ambos sensores.
      
                getTemperatura();
                break;

      case 'j'://Lectura de Volumen de liquido

                getVolumen();
               
                break;

      default:
              mensajePantalla("ERROR","DIRECTIVA DESCONOCIDA");
              delay(3000);
              break;
              
      
}









 



 

 
 }












//--------------------------------------------------------------Métodos Adicionales----------------------------------------------------------------------------------------------------------

/* El siguiente método sirve para estandarizar los mensajes que serán mostrados en la pnatalla LCD con un formato definido para cada operación que se solicite*/
void mensajePantalla(String operacion,String mensaje){
  lcd.clear();
                   lcd.display();
                   int l= (20 - operacion.length())/2;
                   lcd.setCursor(l,0);
                   lcd.print(operacion);
                   l= (20 - mensaje.length())/2;
                   lcd.setCursor(l,1);
                   lcd.print(mensaje);
                   lcd.setCursor(1,2);
                   lcd.print("VERDE --> ACEPTAR");
                   lcd.setCursor(1,3);
                   lcd.print("ROJO  --> CANCELAR");
 
}

/*Metodo  para realizar una parada de emergencia de todos los componentes electrónicos asociados */
void desactivar(){
  Wire.beginTransmission(1);
  Wire.write('z');
  Wire.endTransmission();
  delay(1000);
}


/*Metodo utilizado para quedar a la espera de la confirmación on cancelación de la operación enviada por BT*/
void esperarConfirmacion(){
  while(digitalRead(botonAceptar)==LOW && digitalRead(botonCancelar)==LOW && operacion!='z'){
 
  digitalWrite(buzzer,HIGH);
  digitalWrite(ledBT,LOW);
  delay(500);
  
  digitalWrite(buzzer,LOW);
  digitalWrite(ledBT,HIGH);
  delay(3000);
}
}


/*Metodo para transmitir la operación deseada al Arduino receptor */
void confirmado(){
  
  if(digitalRead(botonAceptar)==HIGH){
  digitalWrite(buzzer,LOW);
  digitalWrite(ledBT,LOW);
  Wire.beginTransmission(1);
  Wire.write(operacion);
  Wire.endTransmission();
  delay(1000);
}else if(digitalRead(botonCancelar)==HIGH ||operacion=='z'){
  digitalWrite(buzzer,LOW);
  digitalWrite(ledBT,LOW); 
  lcd.clear();
  lcd.display();
  lcd.setCursor(1,0);
  lcd.print("OPERACION CANCELADA ");
  delay(5000);
  
}

}


/*Metodo  para obtener las lecturas de temperatura de los dos sensores y mostrarlas por pantalla*/
void getTemperatura(){
 do{
     temperatura.requestTemperatures();
     


      lcd.clear();
      lcd.display();
                   
      lcd.setCursor(4,0);
      lcd.print("TEMPERATURAS");

      lcd.setCursor(0,1);
      lcd.print("____________________");
      
  
      lcd.setCursor(0,2);
      lcd.print("Temp OLLA: ");
      lcd.print(temperatura.getTempCByIndex(0));
  
      
  
      lcd.setCursor(0,3);
      lcd.print("Temp MACERADO: ");
      lcd.print(temperatura.getTempCByIndex(1));

      delay(3000);
      
  } while(digitalRead(botonAceptar)==LOW && digitalRead(botonCancelar)==LOW);

}

void getVolumen(){
  
}
