#include <Arduino.h>

bool modBlink = false;
bool ledAprins = false;
unsigned long lastBlink = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void blink() {
  if (!modBlink)
    return;

  if (ledAprins && millis() - lastBlink >= 1000) {
    digitalWrite(LED_BUILTIN, LOW);
    ledAprins = false;
    lastBlink = millis();
  }

  else if (!ledAprins && millis() - lastBlink >= 10000) {
    digitalWrite(LED_BUILTIN, HIGH);
    ledAprins = true;
    lastBlink = millis();
  }
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
      lastBlink = millis();
      Serial.println("blink");
    }
  }

  if (modBlink) {
    blink();
  }
}