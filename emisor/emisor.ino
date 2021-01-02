//--------------------------------------------------------------Librerías---------------------------------------------------------------------------------------------------------
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <BluetoothSerial.h>

//--------------------------------------------------------------Definición de variables-------------------------------------------------------------------------------------------
#define botonAceptar 26
#define botonCancelar 25
#define buzzer 17
#define termometro1 16
#define termometro2 27
#define flujometro1 14
#define flujometro2 12
char recepcion;
char directiva;
bool error=false;
BluetoothSerial SerialBT;
LiquidCrystal_I2C lcd (0x3f,20,4);

//--------------------------------------------------------------Inicialización-----------------------------------------------------------------------------------------------------
void setup() {
  SerialBT.begin("Cerveceria");
  Serial.begin(115200);
  Wire.begin();
  lcd.begin(20,4);
  lcd.clear();
  lcd.backlight();

  pinMode(botonAceptar,OUTPUT);
  pinMode(botonCancelar,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(termometro1,INPUT);
  pinMode(termometro2,INPUT);
  pinMode(flujometro1,INPUT);
  pinMode(flujometro2,INPUT);
       
  
}

//--------------------------------------------------------------Programa----------------------------------------------------------------------------------------------------------
void loop() {
    
 while(SerialBT.available()==0){
  lcd.clear();
  lcd.print("Esperando Directiva");
  lcd.display();
  delay(500);
  lcd.noDisplay();
  delay(500);
 }

 if(SerialBT.available()>0){
  recepcion=SerialBT.read();

   switch(recepcion){
   
      case  'a': mensajePantalla("INGRESO","AGUA SIN FILTRAR");
                   
      break;

      case 'b':mensajePantalla("INGRESO","AGUA DECLORADA");
      break;

      case 'c':mensajePantalla("INGRESO","SUCCION EXTERIOR");
      break;

      case 'd':mensajePantalla("TRASIEGO","OLLA COCCION");
      break;

      case 'e':mensajePantalla("TRASIEGO","MACERADOR");
      break;

      case 'f':mensajePantalla("MACERADO","");
      break;

      case 'z'://desactivar();
      break;

      case 'h':
      break;

      case 'i':
      break;

      case 'j':
      break;

      default: 
              mensajePantalla("DIRECTIVA", "DESCONOCIDA");
              delay(5000);
              error=true;
              
      break;



}

while(digitalRead(botonAceptar)==LOW || digitalRead(botonCancelar)==LOW || error==false){
  
}

  if(digitalRead(botonAceptar)==HIGH){
  Wire.beginTransmission(1);
  Wire.write(recepcion);
  Wire.endTransmission();
  delay(1000);
}

if(digitalRead(botonCancelar)==HIGH){
  recepcion='z';
  Wire.beginTransmission(1);
  Wire.write('z');
  Wire.endTransmission();
  delay(1000);
  
}


 

 
 }

}

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
