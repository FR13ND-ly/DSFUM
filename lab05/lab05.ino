#define p_tip 4
#define p_gnd 7

#define PAUZA 0

#define Si3 247
#define Do4 262
#define Re4 294
#define Mi4 330
#define Fa_diez4 370
#define Sol4 392
#define La4 440
#define Si4 494

#define Do5 523
#define Re5 587
#define Mi5 659
#define Fa_diez5 740

int tempo = 500;

int inceput[] = {
  Si3, 4
};

int partea1[] = {
  Mi4, 3,
  Fa_diez4, 1,
  Sol4, 2,
  La4, 2,

  Si4, 2,
  Mi4, 2,
  Mi4, 2,

  Do5, 3,
  Si4, 1,
  La4, 2,
  La4, 2,

  Re5, 3,
  Si4, 1,
  Si4, 2,
  Si4, 2
};

int partea2[] = {
  Mi5, 3,
  Re5, 1,
  Do5, 1,
  Si4, 1,
  La4, 2,

  Si4, 2,
  Sol4, 4,
  La4, 2,

  Si4, 3,
  La4, 1,
  Sol4, 2,
  Fa_diez4, 2
};

int partea3[] = {
  Mi4, 3,
  Fa_diez4, 1,
  Sol4, 2,
  La4, 2,

  Mi5, 2,
  Re5, 2,
  Re5, 2,

  Mi5, 3,
  Re5, 1,
  Do5, 1,
  Si4, 1,
  La4, 2,

  Re5, 2,
  Do5, 2,
  Si4, 2,
  Si4, 2
};

int partea4[] = {
  Mi5, 3,
  Re5, 1,
  Do5, 1,
  Si4, 1,
  La4, 2,

  Si4, 2,
  Sol4, 4,
  La4, 2,

  Si4, 3,
  La4, 1,
  Sol4, 2,
  Fa_diez4, 2
};

int finalStrofa[] = {
  Sol4, 2,
  La4, 2,
  Si4, 2,
  La4, 1,
  Sol4, 1,
  Fa_diez4, 2,
  Sol4, 2,
  Mi4, 6
};

void canta(int melodie[], int lungime) {
  for (int i = 0; i < lungime; i += 2) {

    int frecventa = melodie[i];
    int durata = tempo * melodie[i + 1] / 2;

    if (frecventa == PAUZA) {
      noTone(p_tip);
      delay(durata);
    } else {
      tone(p_tip, frecventa);

      delay(durata * 0.95);

      noTone(p_tip);
      delay(durata * 0.05);
    }
  }
}

void cantaStrofa() {
  canta(partea1, sizeof(partea1) / sizeof(int));
  canta(partea2, sizeof(partea2) / sizeof(int));
  canta(partea3, sizeof(partea3) / sizeof(int));
  canta(partea4, sizeof(partea4) / sizeof(int));
  canta(finalStrofa, sizeof(finalStrofa) / sizeof(int));
}

void setup() {
  pinMode(p_tip, OUTPUT);
  pinMode(p_gnd, OUTPUT);

  digitalWrite(p_gnd, LOW);

  canta(inceput, sizeof(inceput) / sizeof(int));

  cantaStrofa();
  delay(800);

  cantaStrofa();
  delay(800);

  cantaStrofa();

  noTone(p_tip);
}

void loop() {
}