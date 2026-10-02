#include <Arduino.h>

bool modBlink = false;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void blink() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);

  digitalWrite(LED_BUILTIN, LOW);
  delay(10000);
}

void loop() {

  if (Serial.available() > 0) {
    int sentByte = Serial.read();

    Serial.print("Am receptionat caracterul cu codul ascii: ");
    Serial.println(sentByte);

    if (sentByte == 49) {
      modBlink = false;
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("pornit");
    }

    else if (sentByte == 50) {
      modBlink = false;
      digitalWrite(LED_BUILTIN, LOW);
      Serial.println("oprit");
    }

    else if (sentByte == 51) {
      modBlink = true;
      Serial.println("blink");
    }
  }

  if (modBlink) {
    blink();
  }
}