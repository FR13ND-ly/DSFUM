//ex1

// #include <Arduino.h>
// const byte pins[] = {8, 9, 10, 11, 12, 13};
// byte count = 0;
// unsigned long t = 0;

// void setup() {
//   for (byte i = 0; i < 6; i++) pinMode(pins[i], OUTPUT);
// }

// void loop() {
//   if (millis() - t >= 300) {
//     t = millis();
//     for (byte i = 0; i < 6; i++) {
//       digitalWrite(pins[i], bitRead(count, i));
//     }
//     count = (count + 1) % 64;
//   }
// }


//ex2

// #include <Arduino.h>
// const byte pins[] = {8, 9, 10, 11, 12, 13};

// void setup() {
//   Serial.begin(9600);
//   for (byte i = 0; i < 6; i++) pinMode(pins[i], OUTPUT);
// }

// void loop() {
//   if (Serial.available()) {
//     int val = Serial.parseInt();
//     for (byte i = 0; i < 6; i++) {
//       digitalWrite(pins[i], bitRead(val, i));
//     }
//   }
// }


//ex3

// #include <Arduino.h>
// const byte pin = 9;
// int val = 0, pas = 5;
// unsigned long t = 0;

// void setup() {
//   pinMode(pin, OUTPUT);
// }

// void loop() {
//   if (millis() - t >= 30) {
//     t = millis();
//     analogWrite(pin, val);
//     val += pas;
//     if (val <= 0 || val >= 255) pas = -pas;
//   }
// }


//ex4

// #include <Arduino.h>

// const byte pin = 9;

// int val = 0;
// int pas = 5;
// int viteza = 5;

// unsigned long t = 0;

// void setup() {
//   Serial.begin(9600);
//   pinMode(pin, OUTPUT);
// }

// void loop() {
//   if (Serial.available() > 0) {
//     int v = Serial.parseInt();

//     if (v >= 1 && v <= 100) {
//       viteza = v;
//     }

//     while (Serial.available()) {
//       Serial.read();
//     }
//   }

//   int interval = 100 / viteza;

//   if (millis() - t >= interval) {
//     t = millis();

//     analogWrite(pin, val);

//     val += pas;

//     if (val <= 0 || val >= 255) {
//       pas = -pas;
//     }
//   }
// }


//ex5

// #include <Arduino.h>

// const byte pin = 8;
// const unsigned long period = 2000;

// unsigned long onTime = 1000;
// unsigned long t = 0;

// void setup() {
//   Serial.begin(9600);
//   pinMode(pin, OUTPUT);

//   Serial.setTimeout(10);
//   Serial.println("Introdu o valoare intre 0 si 5:");
// }

// void loop() {
//   if (Serial.available() > 0) {
//     float volt = Serial.parseFloat();

//     while (Serial.available() > 0) {
//       Serial.read();
//     }

//     if (volt >= 0 && volt <= 5) {
//       onTime = (volt / 5.0) * period;

//       Serial.print("Valoare: ");
//       Serial.println(volt);
//     } else {
//       Serial.println("Eroare! Introdu o valoare intre 0 si 5.");
//     }
//   }

//   unsigned long elapsed = micros() - t;

//   if (elapsed >= period) {
//     t += (elapsed / period) * period;
//     elapsed = micros() - t;
//   }

//   digitalWrite(pin, elapsed < onTime ? HIGH : LOW);
// }



//ex7

// #include <Arduino.h>

// const byte pins[6] = {8, 9, 10, 11, 12, 13};

// int val[6] = {0, 0, 0, 0, 0, 0};
// int pas[6] = {5, 5, 5, 5, 5, 5};

// unsigned long interval[6] = {10, 20, 30, 40, 50, 60};

// unsigned long tFade[6] = {0};
// unsigned long tPWM = 0;

// const unsigned long perioada = 2000; 

// void setup() {
//   for (byte i = 0; i < 6; i++) {
//     pinMode(pins[i], OUTPUT);
//   }
// }

// void loop() {
//   unsigned long ms = millis();
//   unsigned long us = micros();

//   for (byte i = 0; i < 6; i++) {
//     if (ms - tFade[i] >= interval[i]) {
//       tFade[i] = ms;

//       val[i] += pas[i];

//       if (val[i] >= 255) {
//         val[i] = 255;
//         pas[i] = -5;
//       }

//       if (val[i] <= 0) {
//         val[i] = 0;
//         pas[i] = 5;
//       }
//     }
//   }

//   unsigned long elapsed = us - tPWM;

//   if (elapsed >= perioada) {
//     tPWM += (elapsed / perioada) * perioada;
//     elapsed = us - tPWM;
//   }

//   for (byte i = 0; i < 6; i++) {
//     unsigned long onTime =
//         (unsigned long)val[i] * perioada / 255;

//     digitalWrite(pins[i], elapsed < onTime ? HIGH : LOW);
//   }
// }