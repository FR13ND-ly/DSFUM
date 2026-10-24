
const int exercitiu = 2;
const int N = 10;

byte digits[10] = {
  0b00000011, // 0
  0b11110011, // 1
  0b00100101, // 2
  0b01100001, // 3
  0b11010001, // 4
  0b01001001, // 5
  0b00001001, // 6
  0b11100011, // 7
  0b00000001, // 8
  0b01000001  // 9
};

byte positions[4] = {
  0b10000000,
  0b01000000,
  0b00100000,
  0b00010000
};

const byte A = 0b00010000;
const byte B = 0b00001000;
const byte C = 0b00000100;
const byte D = 0b10000000;
const byte E = 0b01000000;
const byte F = 0b00100000;
const byte G = 0b00000010;

unsigned long records[N] = {0};
int numbers[N] = {0};
int iteration = 0;

int counter = 0;
bool oldButtons[3] = {HIGH, HIGH, HIGH};
unsigned long lastPress[3] = {0};

String mesaj = "    dECEbAL_Si_FiUL_SAU_LOCUiESC_PE_PLAiUL_dACiEi    ";
int offset = 0;
bool pauza = false;
unsigned long lastMove = 0;

void setup() {
  Serial.begin(9600);

  pinMode(4, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);

  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);

  randomSeed(analogRead(A0));
}

void loop() {
  if (exercitiu == 1) ex1();
  if (exercitiu == 2) ex2();
  if (exercitiu == 3) ex3();
  if (exercitiu == 4) ex4();
  if (exercitiu == 5) ex5();
}

void afiseazaValoare(byte valoare, byte segment) {
  digitalWrite(4, LOW);
  shiftOut(8, 7, LSBFIRST, valoare);
  shiftOut(8, 7, LSBFIRST, segment);
  digitalWrite(4, HIGH);
}

void ex1() {
  for (int i = 0; i < 10; i++) {
    afiseazaValoare(digits[i], positions[0]);
    delay(1000);
  }
}

void ex2() {
  if (iteration >= N) return;

  String command = "";
  int numarCitit = -1;

  int nr = random(1000, 10000);

  int cifre[4] = {
    nr % 10,
    nr / 10 % 10,
    nr / 100 % 10,
    nr / 1000
  };

  unsigned long start = millis();

  while (numarCitit != nr) {
    for (int i = 0; i < 4; i++) {
      afiseazaValoare(digits[cifre[i]], positions[i]);
      delay(2);
    }

    while (Serial.available()) {
      char c = Serial.read();

      if (c == '\n' || c == '\r') {
        if (command.length() > 0) {
          numarCitit = command.toInt();
          command = "";

          if (numarCitit != nr) {
            Serial.println("Wrong");
          }
        }
      } else {
        command += c;
      }
    }
  }

  records[iteration] = millis() - start;
  numbers[iteration] = nr;

  Serial.print("Timp: ");
  Serial.print(records[iteration]);
  Serial.println(" ms");

  iteration++;

  if (iteration == N) {
    statistici();
    afiseazaValoare(255, 0);
  }
}

void statistici() {
  unsigned long minT = records[0];
  unsigned long maxT = records[0];
  unsigned long suma = 0;

  int minNr = numbers[0];
  int maxNr = numbers[0];

  for (int i = 0; i < N; i++) {
    suma += records[i];

    if (records[i] < minT) {
      minT = records[i];
      minNr = numbers[i];
    }

    if (records[i] > maxT) {
      maxT = records[i];
      maxNr = numbers[i];
    }
  }

  Serial.print("Minim: ");
  Serial.print(minT);
  Serial.print(" ms, numar: ");
  Serial.println(minNr);

  Serial.print("Maxim: ");
  Serial.print(maxT);
  Serial.print(" ms, numar: ");
  Serial.println(maxNr);

  Serial.print("Media: ");
  Serial.print(suma / (float)N);
  Serial.println(" ms");
}

void ex3() {
  int buttons[3] = {A1, A2, A3};

  for (int i = 0; i < 3; i++) {
    bool state = digitalRead(buttons[i]);

    if (state == LOW && oldButtons[i] == HIGH &&
        millis() - lastPress[i] > 150) {

      if (i == 0 && counter < 9999) counter++;
      if (i == 1 && counter > 0) counter--;
      if (i == 2) counter = 0;

      lastPress[i] = millis();
    }

    oldButtons[i] = state;
  }

  int nr = counter;

  for (int i = 0; i < 4; i++) {
    int cifra = nr % 10;

    if (nr > 0 || i == 0) {
      afiseazaValoare(digits[cifra], positions[i]);
    } else {
      afiseazaValoare(255, positions[i]);
    }

    nr /= 10;
    delay(2);
  }
}

byte litera(byte segmente) {
  return ~segmente;
}

byte caracter(char ch) {
  switch (ch) {
    case 'A': return litera(A | B | C | E | F | G);
    case 'b': return litera(C | D | E | F | G);
    case 'C': return litera(A | D | E | F);
    case 'd': return litera(B | C | D | E | G);
    case 'E': return litera(A | D | E | F | G);
    case 'F': return litera(A | E | F | G);

    case '_': return litera(D);
    case 'L': return litera(D | E | F);
    case 'i': return litera(C);
    case 'J': return litera(B | C | D | E);
    case 'O': return litera(A | B | C | D | E | F);
    case 'P': return litera(A | B | E | F | G);
    case 'S': return litera(A | C | D | F | G);
    case 'U': return litera(B | C | D | E | F);

    default: return 255;
  }
}

byte roteste(byte val) {
  byte result = val;

  result = (result & ~(A | D));
  if (val & A) result |= D;
  if (val & D) result |= A;

  result = (result & ~(B | E));
  if (val & B) result |= E;
  if (val & E) result |= B;

  result = (result & ~(C | F));
  if (val & C) result |= F;
  if (val & F) result |= C;

  return result;
}

// Exercitiul 4

void ex4() {
  char letters[6] = {'A', 'b', 'C', 'd', 'E', 'F'};

  for (int i = 0; i < 6; i++) {
    byte val = roteste(caracter(letters[i]));
    unsigned long start = millis();

    while (millis() - start < 5000) {
      afiseazaValoare(val, positions[3]);
      delay(2);
    }
  }
}

void ex5() {
  int buttons[3] = {A1, A2, A3};

  for (int i = 0; i < 3; i++) {
    bool state = digitalRead(buttons[i]);

    if (state == LOW && oldButtons[i] == HIGH &&
        millis() - lastPress[i] > 200) {
      pauza = !pauza;
      lastPress[i] = millis();
    }

    oldButtons[i] = state;
  }

  for (int i = 0; i < 4; i++) {
    char ch = mesaj[offset + i];

    byte val = roteste(caracter(ch));
    afiseazaValoare(val, positions[3 - i]);

    delay(2);
  }

  if (!pauza && millis() - lastMove >= 350) {
    offset++;
    lastMove = millis();

    if (offset > (int)mesaj.length() - 4) {
      offset = 0;
    }
  }
}
