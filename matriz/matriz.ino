/*
  Nombre del Archivo: OLED_64_128
  Descripción: manejo de matriz SSD1306 sin librerias.
   

  Autor: jose heriberto marquez diaz
  Fecha: 27 de junio 2024

  Notas:
  - Ninguna
*/

#include <stdio.h>

String mensaje = "";
bool flag_data = false;
int numero = 0;
int pines[2][8] = {{4,5,6,7,8,9,10,11},{22,23,24,25,26,27,28,29}};


void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN,OUTPUT);
  digitalWrite(LED_BUILTIN,LOW);
  for (size_t j = 0; j < 2; j++)
  {
    for (size_t i = 0; i < 8; i++)
    {
      pinMode(pines[j][i], OUTPUT);
      digitalWrite(pines[j][i], 1-j);
      // Serial.println(pines[j][i]); // exploracion de los pines
    }
  }
  
  
}

void loop() {
    

    if (flag_data == true)
    {
      numero = atoi(mensaje.c_str());
      toogle(numero);
      Serial.println(String(numero) + " " + String(digitalRead(numero)));

      mensaje = "";
      flag_data = false;
      
    }
}

void toogle(uint8_t pin){
    if (digitalRead(pin)==0)
    {
        digitalWrite(pin,HIGH);
    }
    else
    {
        digitalWrite(pin,LOW);
    }
}


void serialEvent() {
  while (Serial.available())
  {
    char data = Serial.read();
    if (data == '\n')
    {
      flag_data = true;
    }
    else
    {
      mensaje+=data;
    }
    
  }
}
