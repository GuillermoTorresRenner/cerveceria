//--------------------------------------------------------------Librerías---------------------------------------------------------------------------------------------------------
#include <LiquidCrystal_I2C.h>
#include <Wire.h>




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

//--------------------------------------------------------------Inicialización-----------------------------------------------------------------------------------------------------
void setup() {
  //Inicio BT
  SerialBT.begin("Cerveceria");
  
  //Inicio Monitor Serial
  Serial.begin(115200);

  //Inicio Comunicación I2C
  Wire.begin();

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

  
     case 'a': 
               
                mensajePantalla("INGRESO","AGUA SIN FILTRAR "+parametro+ "L");
                break;
                

      case 'b':
                
                mensajePantalla("INGRESO","AGUA DECLORADA "+parametro+ "L");
                break;

      case 'c':
                mensajePantalla("INGRESO","SUCCION EXTERIOR "+parametro+ "L");
                break;

      case 'd':
                mensajePantalla("TRASIEGO","OLLA COCCION");
                break;

      case 'e':
                mensajePantalla("TRASIEGO","MACERADOR");
                break;

      case 'f':
                mensajePantalla("MACERADO","");
                break;

      case 'z':
                desactivar();
      break;

      case 'h':
                mensajePantalla("OPERACION","NO DEFINIDA");
          break;

      case 'i':mensajePantalla("TRASIEGO","MACERADOR");
      break;

      case 'j':mensajePantalla("TRASIEGO","MACERADOR");
      break;

      default:
              mensajePantalla("ERROR","DIRECTIVA DESCONOCIDA");
              
      
}










while(digitalRead(botonAceptar)==LOW && digitalRead(botonCancelar)==LOW && operacion!='z'){
 
  digitalWrite(buzzer,HIGH);
  digitalWrite(ledBT,LOW);
  delay(500);
  
  digitalWrite(buzzer,LOW);
  digitalWrite(ledBT,HIGH);
  delay(3000);
}

 

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

void desactivar(){
  Wire.beginTransmission(1);
  Wire.write('z');
  Wire.endTransmission();
  delay(1000);
}
