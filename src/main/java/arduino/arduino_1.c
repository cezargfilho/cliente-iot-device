#include <Wire.h>
#define ENDER_ESCRAVO 9
#define TAM_MSG 1

const int sensorTempPino = A0;
const int pinoSensor = A1;
const int pinoSolar = A2;

int umidadeSolo = 0;
int temp = 0;
int tempIrrigacao = 0;
int sol = 0;

void setup()
{
  Wire.begin(ENDER_ESCRAVO);
  Serial.begin(9600);
}

void loop()
{
  int msg = 0;
  Wire.beginTransmission(ENDER_ESCRAVO);

  Serial.print("UMIDADE ");

  umidadeSolo = analogRead(pinoSensor);
  //transforma p/ representacao em porcentagem
  umidadeSolo = map(umidadeSolo, 1023, 0, 100, 0);

  Serial.println(umidadeSolo);


  Serial.print("TEMPERATURA ");

  float voltage = analogRead(sensorTempPino) * 5.0;
  voltage /= 1024.0;

  float temp = (voltage - 0.5) * 100 ;

  Serial.println(temp);

  sol = analogRead(pinoSolar);
  //transforma p/ representacao em porcentagem
  sol = map(sol, 134, 0, 100, 0);
  Serial.print("RADIACAO ");
  Serial.println(sol);


  if (umidadeSolo < 70) {

    if (umidadeSolo > 60) {
      if (sol < 30) {
        Wire.write(2);
        Wire.endTransmission();
        Serial.println("IRRIGACAO 20");

      } else if (sol >= 30 && sol <= 55) {
        Wire.write(3);
        Wire.endTransmission();
        Serial.println("IRRIGACAO 30");
      } else if (sol > 55) {
        Wire.write(4);
        Wire.endTransmission();
        Serial.println("IRRIGACAO 40");
      }
      msg = 1;

    } else if (umidadeSolo > 50) {

      if (sol < 30) {
        Wire.write(4);
        Wire.endTransmission();
        Serial.println("IRRIGACAO 40");
      } else if (sol >= 30 && sol <= 55) {
        Wire.write(5);
        Wire.endTransmission();
        Serial.println("IRRIGACAO 50");
      } else if (sol > 55) {
        Wire.write(6);
        Wire.endTransmission();
        Serial.println("IRRIGACAO 60");
      }
      msg = 1;

    } else if (umidadeSolo > 40) {

      if (sol < 30) {
        Wire.write(6);
        Wire.endTransmission();
        Serial.println("IRRIGACAO 60");
      } else if (sol >= 30 && sol <= 55) {
        Wire.write(7);
        Wire.endTransmission();
        Serial.println("IRRIGACAO 70");
      } else if (sol > 55) {
        Wire.write(8);
        Wire.endTransmission();
        Serial.println("IRRIGACAO 80");
      }
      msg = 1;
    } else if (umidadeSolo > 30) {

      if (sol < 30) {
        Wire.write(8);
        Wire.endTransmission();
        Serial.println("IRRIGACAO 80");
      } else if (sol >= 30 && sol <= 55) {
        Wire.write(9);
        Wire.endTransmission();
        Serial.println("IRRIGACAO 90");
      } else if (sol > 55) {
        Wire.write(10);
        Wire.endTransmission();
        Serial.println("IRRIGACAO 100");
      }
      msg = 1;

    } else if (umidadeSolo > 20) {

      if (sol < 30) {
        Wire.write(10);
        Wire.endTransmission();
        Serial.println("IRRIGACAO 100");
      } else if (sol >= 30 && sol <= 55) {
        Wire.write(11);
        Wire.endTransmission();
        Serial.println("IRRIGACAO 110");
      } else if (sol > 55) {
        Wire.write(12);
        Wire.endTransmission();
        Serial.println("IRRIGACAO 120");
      }
      msg = 1;


    } else if (umidadeSolo > 10) {

      if (sol < 30) {
        Wire.write(12);
        Wire.endTransmission();
        Serial.println("IRRIGACAO 120");
      } else if (sol >= 30 && sol <= 55) {
        Wire.write(13);
        Wire.endTransmission();
        Serial.println("IRRIGACAO 130");
      } else if (sol > 55) {
        Wire.write(14);
        Wire.endTransmission();
        Serial.println("IRRIGACAO 140");
      }
      msg = 1;

    } else if (umidadeSolo >= 0) {

      if (sol < 30) {
        Wire.write(14);
        Wire.endTransmission();
        Serial.println("IRRIGACAO 140");
      } else if (sol >= 30 && sol <= 55) {
        Wire.write(15);
        Wire.endTransmission();
        Serial.println("IRRIGACAO 150");
      } else if (sol > 55) {
        Wire.write(16);
        Wire.endTransmission();
        Serial.println("IRRIGACAO 160");
      }
      msg = 1;

    }
  } else if (temp > 21) {
    if (sol < 30) {
      Serial.println("IRRIGACAO 0");
      delay(3 * 1000);
    } else if (sol >= 30 && sol <= 55) {
      Serial.println("IRRIGACAO 0");
      delay(2 * 1000);
    } else if (sol > 55) {
      Serial.println("IRRIGACAO 0");
      delay(1 * 1000);
    }
    Serial.println();
  } else {
    if (sol < 30) {
      Serial.println("IRRIGACAO 0");
      delay(6 * 1000);
    } else if (sol >= 30 && sol <= 55) {
      Serial.println("IRRIGACAO 0");
      delay(5 * 1000);
    } else if (sol > 55) {
      Serial.println("IRRIGACAO 0");
      delay(4 * 1000);
    }
    Serial.println();
  }
  if (msg > 0) {
    Wire.requestFrom(ENDER_ESCRAVO, TAM_MSG);
    char b;
    while (Wire.available()) {
      b = Wire.read();
    }
    Serial.println();
    delay(2000);
  }
}