#include <Wire.h>
#define ENDER_ESCRAVO 9
#define TAM_MSG 1

int motorPin = 2;
int motorState = 0;
int temp = 0;
char c;
void receiveEvent(int nb)
{
  byte i = 0;
  while (Wire.available() && (i < nb))
  {
    c = (char)Wire.read();
    i++;
  }
  digitalWrite (motorPin, HIGH);
  motorState = digitalRead(motorPin);
  temp = c;
  if (motorState == 1) {
    Serial.print("VALVULA LIGADA POR ");
    Serial.print(temp * 10);
    Serial.print(" SEGUNDOS!");
    Serial.println("");
  }

  delay(temp * 1000);

  digitalWrite (motorPin, LOW);
  motorState = digitalRead(motorPin);
  if (motorState == 0) {
    Serial.println("VALVULA DESLIGADA!");
  }
  Serial.println();
}
void requestEvent(void)
{
  Wire.write(1);
}
void setup()
{
  pinMode(motorPin, OUTPUT);
  Wire.begin(ENDER_ESCRAVO);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  Serial.begin(9600);
}

void loop()
{
  delay(500);
}