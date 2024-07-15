/*
  Nombre del Archivo: Matriz_led_8_8
  Descripción: manejo de matriz LeD sin librerias con ARDUINO MEGA, conexion directa.


  Autor: jose heriberto marquez diaz
  Fecha: 14 de julio 2024

  Notas:
  - Ninguna
*/

#include <stdio.h>

String mensaje = "";
bool flag_data = false;
int flag = 1;
int numero = 0;
uint8_t count = 0;
int pines[2][8] = {{4, 5, 6, 7, 8, 9, 10, 11}, {22, 23, 24, 25, 26, 27, 28, 29}}; // columnas , filas

bool data[8][25] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0},
                    {0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0},
                    {0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0},
                    {0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

void setup()
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  for (size_t j = 0; j < 2; j++)
  {
    for (size_t i = 0; i < 8; i++)
    {
      pinMode(pines[j][i], OUTPUT);
      digitalWrite(pines[j][i], 1 - j);
      // Serial.println(pines[j][i]); // exploracion de los pines
    }
  }
}

void loop()
{
  for (size_t k = 0; k < 25; k++)
  {
    for (size_t x = 0; x < 15; x++)
    {
      for (size_t i = 0; i < 8; i++)
      {
        for (size_t j = 0; j < 8; j++)
        {
          if (j + k < 25)
          {
            digitalWrite(pines[0][j], 1 - data[i][j + k]);
          }
          else
          {
            digitalWrite(pines[0][j], 1 - data[i][(j + k) - 25]);
          }
        }

        digitalWrite(pines[1][i], 1);
        delay(15 / 8);
        digitalWrite(pines[1][i], 0);
      }
    }
  }

  if (flag_data == true)
  {
    numero = atoi(mensaje.c_str());
    toogle(numero);
    Serial.println(String(numero) + " " + String(digitalRead(numero)));

    mensaje = "";
    flag_data = false;
  }
}

void toogle(uint8_t pin)
{
  if (digitalRead(pin) == 0)
  {
    digitalWrite(pin, HIGH);
  }
  else
  {
    digitalWrite(pin, LOW);
  }
}

void serialEvent()
{
  while (Serial.available())
  {
    char data = Serial.read();
    if (data == '\n')
    {
      flag_data = true;
    }
    else
    {
      mensaje += data;
    }
  }
}
