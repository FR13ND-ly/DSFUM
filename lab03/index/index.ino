
#include <Arduino.h>

int pins[6] = {8, 9, 10, 11, 12, 13};

String animations[6] = {
  "off", "off", "blink", "off", "fadeinout", "off"
};

unsigned long tFade[6] = {1000, 1000, 1000, 1000, 1000, 1000};
unsigned long start[6] = {0};

int brightness[6] = {0};

int pPWM = 2000;
unsigned long tPWM = 0;

String command = "";

void processCommand(String cmd);

void setup() {
  Serial.begin(9600);

  for (byte i = 0; i < 6; i++) {
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i], LOW);
  }
}

void loop() {
  while (Serial.available()) {
    char c = Serial.read();

    if (c == '\n' || c == '\r') {
      if (command.length() > 0) {
        processCommand(command);
        command = "";
      }
    } else {
      command += c;
    }
  }

  unsigned long ms = millis();
  unsigned long us = micros();

  for (int i = 0; i < 6; i++) {
    unsigned long elapsed = ms - start[i];
    unsigned long d = tFade[i];

    if (animations[i] == "off") {
      brightness[i] = 0;
    }

    else if (animations[i] == "fadein") {

        brightness[i] = elapsed * 255UL / d;
    }

    else if (animations[i] == "fadeout") {
      if (elapsed >= d)
        brightness[i] = 0;
      else
        brightness[i] = 255 - elapsed * 255UL / d;
    }

    else if (animations[i] == "fadeinout") {
      unsigned long t = elapsed % d;
      unsigned long half = d / 2;

      if (t < half)
        brightness[i] = t * 255UL / half;
      else
        brightness[i] = (d - t) * 255UL / (d - half);
    }

    else if (animations[i] == "blink") {
      unsigned long t = elapsed % d;

      if (t < d / 2)
        brightness[i] = 255;
      else
        brightness[i] = 0;
    }
  }

  unsigned long elapsedPWM = us - tPWM;

  if (elapsedPWM >= pPWM) {
    tPWM += (elapsedPWM / pPWM) * pPWM;
    elapsedPWM = us - tPWM;
  }

  for (byte i = 0; i < 6; i++) {
    unsigned long onTime = (unsigned long)brightness[i] * pPWM / 255;

    digitalWrite(pins[i], elapsedPWM < onTime ? HIGH : LOW);
  }
}

void processCommand(String cmd) {
  cmd.trim();

  int p1 = cmd.indexOf(',');
  int p2 = cmd.indexOf(',', p1 + 1);

  if (p1 == -1 || p2 == -1) {
    Serial.println("Invalid command");
    return;
  }

  int pin = cmd.substring(0, p1).toInt();

  String anim = cmd.substring(p1 + 1, p2);
  anim.trim();

  String timeText = cmd.substring(p2 + 1);
  timeText.trim();

  if (pin < 8 || pin > 13) {
    Serial.println("Invalid pin");
    return;
  }

  if (anim != "off" &&
      anim != "fadein" &&
      anim != "fadeout" &&
      anim != "fadeinout" &&
      anim != "blink") {
    Serial.println("Invalid animation");
    return;
  }

  long time = timeText.toInt();

  if (anim != "off" &&
      (time == 0 ||
      (anim == "fadeinout" && time < 2) ||
      (anim == "blink" && time < 2))) {
    Serial.println("Invalid time");
    return;
  }

  byte i = pin - 8;

  animations[i] = anim;
  tFade[i] = anim == "off" ? 1 : time;
  start[i] = millis();

  Serial.print("LED ");
  Serial.print(pin);
  Serial.print(": ");
  Serial.println(anim);
}
