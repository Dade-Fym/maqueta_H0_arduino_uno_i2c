/*prouecto para 13 desvios, algunos con salida para que un rele cambie un semaforo
 Se pueden colocar hasta 16 en este modulo e incluso añadir mas modulos, soldando los pines A0-A3
 del modulo. en este caso los tendriais que añadir en el sket tras haber averiguado su direccion I2C
 Adafruit_PWMServoDriver servos = Adafruit_PWMServoDriver(0x40); direccion por defecto sin soldar pines
La libreria <Adafruit_PWMServoDriver.h> la podeis descargar de Ide de arduino
no utiliceis los pines 0 y 1 como entrada, no funcionan correctamente en este sket
el modulo PCA9685 necesita alimentecion independiente de 5v !no lo enchufeis a los 5V del 
arduino que se quema! ademas El GND del arduino y el modulo deben estar unidos o ser el mismo
os recomiendo utilizar una resistencia de 4,7K para poner en los pines de entrada a GNG para evitar exceso de consumo
Tanto en la placa mega como en la uno tambien os sugiero colocar un fusiblr de 0,5A para evitar el exceso de consumo
Este sket ademas lleva añadida una pantalla de 16x2 para escribir informacion asi como he creado el caracter de la barra 
oblicua en el sentido contrario del teclad, que no funciona escrita directamente
funcion escritura brarra creada 
ESPERO QUE OS GUSTE*/

#include <Adafruit_PWMServoDriver.h>  //libreria modulo PCA9685
#include <Wire.h>                  //libreria I2C
#include <LCD.h>                  //libreria propia lcd
#include <LiquidCrystal_I2C.h>    //libreria lcd para I2C
#define I2C_ADDR1    0x27         //direccion I2C pantalla
LiquidCrystal_I2C             lcd1(I2C_ADDR1,2, 1, 0, 4, 5, 6, 7);  //añadir el display

byte barra[8] =
 {
 0b10000000,
 0b01000000,
 0b00100000,
 0b00010000,
 0b00001000,
 0b00000100,
 0b00000010,
 0b00000001
 };
Adafruit_PWMServoDriver servos = Adafruit_PWMServoDriver(0x40);  //direccion I2C PCA9685

unsigned int pos0=172; // ancho de pulso en cuentas para pocicion 0°  (configuracion de la libreria servos)
unsigned int pos180=565; // ancho de pulso en cuentas para la pocicion 180°  (configuracion de la libreria servos)

int estadoboton1 = 0;           //guarda el estado del boton
int estadoanteriorboton1  = 0;  //guarda el estado anterior del boton
int estadoboton2 = 0;           //guarda el estado del boton2
int estadoanteriorboton2  = 0;
int estadoboton3 = 0;           //guarda el estado del boton
int estadoanteriorboton3  = 0;
int estadoboton4 = 0;           //guarda el estado del boton
int estadoanteriorboton4  = 0;
int estadoboton5 = 0;           //guarda el estado del boton
int estadoanteriorboton5  = 0;
int estadoboton6 = 0;           //guarda el estado del boton
int estadoanteriorboton6  = 0;
int estadoboton7 = 0;           //guarda el estado del boton
int estadoanteriorboton7  = 0;
int estadoboton8 = 0;           //guarda el estado del boton
int estadoanteriorboton8  = 0;
int estadoboton9 = 0;           //guarda el estado del boton
int estadoanteriorboton9  = 0;
int estadoboton10 = 0;           //guarda el estado del boton
int estadoanteriorboton10  = 0;
int estadoboton11 = 0;           //guarda el estado del boton
int estadoanteriorboton11  = 0;
int estadoboton12 = 0;           //guarda el estado del boton
int estadoanteriorboton12  = 0;
int estadoboton13 = 0;           //guarda el estado del boton
int estadoanteriorboton13  = 0;

int salida1 = 0;           //estado inicial del rele 0=apagado, 1= encendido
int salida2 = 0;
int salida3 = 0;
int salida4 = 0;
int salida5 = 0;
int salida6 = 0;
int salida7 = 0;
int salida8 = 0;
int salida9 = 0;
int salida10 = 0;
int salida11 = 0;
int salida12 = 0;
int salida13 = 0;


const int tiempoantirebote=250;  //funcion para el antirebote del boton
boolean antirebote(int pin){
  int contador=0;
  boolean estado;
  boolean estadoanterior;

  do{
    estado=digitalRead(pin);
    if(estado!=estadoanterior)
    {
      contador=0;
      estadoanterior=estado;
      }
    else{
      contador=contador+1;
      }
      delay(1);
      }while(contador<tiempoantirebote);
      return estado;
  }

void setup() {
  servos.begin();  
  servos.setPWMFreq(60); //Frecuecia PWM de 60Hz o T=16,66ms
  lcd1.begin (16,2);    // Inicializar el display con 16 caraceres 2 lineas
  lcd1.setBacklightPin(3,POSITIVE);
  lcd1.setBacklight(HIGH);
  lcd1.createChar(1, barra);
  lcd1.home ();                   // go home
 
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);      //PIN  PARA BOTON ENTRADA
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(9,  INPUT);
  pinMode(10, INPUT);      //PIN  PARA BOTON ENTRADA
  pinMode(2,  INPUT);       //PIN  PARA BOTON ENTRADA
  pinMode(3,  INPUT);
  pinMode(4,  INPUT);
  pinMode(5,  INPUT);
  pinMode(6,  INPUT);
  pinMode(7,  INPUT);
  pinMode(8,  INPUT);
  
  pinMode(0, OUTPUT); //PIN  PARA LED SALIDA
  pinMode(1, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);     //PIN  PARA LED SALIDA
 
}
void setServo(uint8_t n_servo, int angulo) {
  int duty;
  duty=map(angulo,0,180,pos0, pos180);
  servos.setPWM(n_servo, 0, duty);  
}

void loop() {
   estadoboton1 = digitalRead(A0);  //lee el estado del boton
  if((estadoboton1 == HIGH)&&(estadoanteriorboton1 == LOW)){  //si estado de boton cambia
    if(antirebote(A0)){//El numero del antirebote debe coincidir con el numero del pin leido digitalread
    salida1 = 1 - salida1;                          //cambiamos el estado del boton
  } 
  }
    estadoanteriorboton1 = estadoboton1;                      //guarda el estado del boton
    
    if(salida1 == 1){
      setServo(1,55);   //cambia el servo para cambiar la aguja
                        //funcion de llamada para servo= 
                       // setServo(numero de servo en la placa, posicion en grados);
      lcd1.setCursor(12,1);
      lcd1.print("1>V2");
    }
    else{
      setServo(1,20);     //deja el servo al encender
      lcd1.setCursor(12,1);
      lcd1.print("1>V1");
    }
  
  estadoboton2 = digitalRead(A1);  //lee el estado del boton
  if((estadoboton2 == HIGH)&&(estadoanteriorboton2 == LOW)){  //si estado de boton cambia
    if(antirebote(A1)){    //El numero del antirebote debe coincidir con el numero del pin leido digitalread
    salida2 = 1 - salida2;                          //cambiamos el estado del boton
  } 
  }
    estadoanteriorboton2 = estadoboton2;                      //guarda el estado del boton
    
    if(salida2 == 1){
      setServo(2,8);   //mueve el servo para cambiar la aguja
      lcd1.setCursor(12,0);
      lcd1.print("2>V2");
    }
    else{
      setServo(2,40);     //deja el servo al encender
      lcd1.setCursor(12,0);
      lcd1.print("2>V1");
    }

   estadoboton3 = digitalRead(A2);  //lee el estado del boton
  if((estadoboton3 == HIGH)&&(estadoanteriorboton3 == LOW)){  //si estado de boton cambia
    if(antirebote(A2)){   //El numero del antirebote debe coincidir con el numero del pin leido digitalread
    salida3 = 1 - salida3;                          //cambiamos el estado del boton
  }
  }
  
    estadoanteriorboton3 = estadoboton3;                      //guarda el estado del boton
    
    if(salida3 == 1){  //en este caso muevo dos servos a la vez
     setServo(3,45);  //mueve el servo para cambiar la aguja
     setServo(4,22);
     lcd1.setCursor(7,0);
     lcd1.print("3>V2");
      }
    else{
     setServo(3,20);                        //mueve el servo para cambiar la aguja
     setServo(4,50);
     lcd1.setCursor(7,0);                   //no es necesario mover el desvio 2
      lcd1.print("3>V3");
    }
  estadoboton4 = digitalRead(A3);  //lee el estado del boton
  if((estadoboton4 == HIGH)&&(estadoanteriorboton4 == LOW)){  //si estado de boton cambia
    if(antirebote(A3)){     //El numero del antirebote debe coincidir con el numero del pin leido digitalread
    salida4 = 1 - salida4; //cambiamos el estado del led
  }
  }
    estadoanteriorboton4 = estadoboton4;                      //guarda el estado del boton
    
    if(salida4 == 1){
     setServo(11,20);
      digitalWrite(0, HIGH);
      lcd1.setCursor(0,1);
      lcd1.print("4>V3");
    }
    else{
      setServo(11,55);
       digitalWrite(0, LOW);
       lcd1.setCursor(0,1);
      lcd1.print("4>V2");
    }
  estadoboton5 = digitalRead(2);  //lee el estado del boton
  if((estadoboton5 == HIGH)&&(estadoanteriorboton5 == LOW)){  //si estado de boton cambia
    if(antirebote(2)){   //El numero del antirebote debe coincidir con el numero del pin leido digitalread
    salida5 = 1 - salida5; //cambiamos el estado del boton
  }
  }
    estadoanteriorboton5 = estadoboton5;                      //guarda el estado del boton
    
    if(salida5 == 1){
      setServo(5,56);                        //mueve el servo para cambiar la aguja
      lcd1.setCursor(7,1);
      lcd1.print("5>V2");
    }
    else{
      setServo(5,15);                          //posicion aguja de reposo
    lcd1.setCursor(7,1);
      lcd1.print("5>V3");
    }
     estadoboton6 = digitalRead(3);  //lee el estado del boton
  if((estadoboton6 == HIGH)&&(estadoanteriorboton6 == LOW)){  //si estado de boton cambia
    if(antirebote(3)){   //El numero del antirebote debe coincidir con el numero del pin leido digitalread
    salida6 = 1 - salida6; //cambiamos el estado del boton
  }
  }
    estadoanteriorboton6 = estadoboton6;                      //guarda el estado del boton
    
    if(salida6 == 1){
      setServo(6,45);                        //mueve el servo para cambiar la aguja
    }
    else{
      setServo(6,10);                          //posicion aguja de reposo
    }
   estadoboton7 = digitalRead(4);  //lee el estado del boton
  if((estadoboton7 == HIGH)&&(estadoanteriorboton7 == LOW)){  //si estado de boton cambia
    if(antirebote(4)){  //El numero del antirebote debe coincidir con el numero del pin leido digitalread
    salida7 = 1 - salida7; //cambiamos el estado del led
  }
  }
    estadoanteriorboton7 = estadoboton7;                      //guarda el estado del boton
    
    if(salida7 == 1){
      setServo(7,77);                        //mueve el servo para cambiar la aguja
    }
    else{
      setServo(7,29);                          //posicion aguja de reposo
    }
     estadoboton8 = digitalRead(5);  //lee el estado del boton
  if((estadoboton8 == HIGH)&&(estadoanteriorboton8 == LOW)){  //si estado de boton cambia
    if(antirebote(5)){    //El numero del antirebote debe coincidir con el numero del pin leido digitalread
    salida8 = 1 - salida8; //cambiamos el estado del boton
  }
  }
    estadoanteriorboton8 = estadoboton8;                      //guarda el estado del boton
    
    if(salida8 == 1){
      digitalWrite(11, HIGH);                    //encendemos el led
      setServo(8,7);                        //mueve el servo para cambiar la aguja
    }
    else{
      digitalWrite(11, LOW);                       //apaga el led
      setServo(8,42);                          //posicion aguja de reposo
    }
   estadoboton9 = digitalRead(6);  //lee el estado del boton
  if((estadoboton9 == HIGH)&&(estadoanteriorboton9 == LOW)){  //si estado de boton cambia
    if(antirebote(6)){    //El numero del antirebote debe coincidir con el numero del pin leido digitalread
    salida9 = 1 - salida9; //cambiamos el estado del boton
  }
  }
    estadoanteriorboton9 = estadoboton9;                      //guarda el estado del boton
    
    if(salida9 == 1){
      digitalWrite(12, HIGH);                    //encendemos el led
      setServo(9,50);   //mueve el servo para cambiar la aguja
    }
    else{
      digitalWrite(12, LOW);                       //apaga el led
      setServo(9,5);    //posicion aguja de reposo
    }
   estadoboton10 = digitalRead(7);  //lee el estado del boton
  if((estadoboton10 == HIGH)&&(estadoanteriorboton10 == LOW)){  //si estado de boton cambia
    if(antirebote(7)){     //El numero del antirebote debe coincidir con el numero del pin leido digitalread
    salida10 = 1 - salida10; //cambiamos el estado del boton
  }
  } 
    estadoanteriorboton10 = estadoboton10;                      //guarda el estado del boton
    
    if(salida10 == 1){
      digitalWrite(13, HIGH);                    //encendemos el led
     setServo(10,10);
    }
    else{
      digitalWrite(13, LOW);                       //apaga el led
      setServo(10,38);
    }
      estadoboton11 = digitalRead(10);  //lee el estado del boton
  if((estadoboton11 == HIGH)&&(estadoanteriorboton11 == LOW)){  //si estado de boton cambia
    if(antirebote(10)){   //El numero del antirebote debe coincidir con el numero del pin leido digitalread
    salida11 = 1 - salida11; //cambiamos el estado del boton
  }
  }
    estadoanteriorboton11 = estadoboton11;                      //guarda el estado del boton

    if(salida11 == 1){}

    else{}
    
   //linea vacia a falta de utilizar  corresponde a boton negro de la izquierda

   
      estadoboton12 = digitalRead(8);  //lee el estado del boton
  if((estadoboton12 == HIGH)&&(estadoanteriorboton12 == LOW)){  //si estado de boton cambia
    if(antirebote(8)){     //El numero del antirebote debe coincidir con el numero del pin leido digitalread
    salida12 = 1 - salida12; //cambiamos el estado del boton
   }
  }
    estadoanteriorboton12 = estadoboton12;                      //guarda el estado del boton
    
    if(salida12 == 1){
     setServo(12,7);
      digitalWrite(1, HIGH);
      lcd1.setCursor(0,0);
      lcd1.print("12>TAL");
    }
    else{
      setServo(12,43);
       digitalWrite(1, LOW);
       lcd1.setCursor(0,0);
      lcd1.print("12>V1 ");
    }
      estadoboton13 = digitalRead(9);  //lee el estado del boton
  if((estadoboton13 == HIGH)&&(estadoanteriorboton13 == LOW)){  //si estado de boton cambia
    if(antirebote(9)){     //El numero del antirebote debe coincidir con el numero del pin leido digitalread
    salida13 = 1 - salida13; //cambiamos el estado del botom
  }
  }
    estadoanteriorboton13 = estadoboton13;                      //guarda el estado del boton
    
    if(salida13 == 1){
     setServo(13,40);
     
    }
    else{
      setServo(13,6);
      
    }   
  }
 
