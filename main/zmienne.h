#include <LiquidCrystal.h>
#include "Timers.h" 

//****************************************************************************************
//***************     Deklaracja zmiennych użytych w programie        ********************
//****************************************************************************************

#define TEMP_0_PIN         13   // Analog Input
#define TEMP_1_PIN         15   // Analog Input
#define TEMP_BED_PIN       14   // Analog Input
#define a -5.30377404285076e-07
#define b 0.000913895174164941
#define c -0.619287460375456
#define d 250.544163050966


#include <stdlib.h>
#define X_STEP_PIN         54
#define X_DIR_PIN          55
#define X_ENABLE_PIN       38
#define X_CS_PIN           53

#define Y_STEP_PIN         60
#define Y_DIR_PIN          61
#define Y_ENABLE_PIN       56
#define Y_CS_PIN           49

#define Z_STEP_PIN         46
#define Z_DIR_PIN          48
#define Z_ENABLE_PIN       62
#define Z_CS_PIN           40

#define E0_STEP_PIN        26
#define E0_DIR_PIN         28
#define E0_ENABLE_PIN      24
#define E0_CS_PIN          42

#define E1_STEP_PIN        36
#define E1_DIR_PIN         34
#define E1_ENABLE_PIN      30
#define E1_CS_PIN          44

#define X_MIN_PIN           3
#ifndef X_MAX_PIN
#define X_MAX_PIN         2
#endif

#define Y_MIN_PIN          14
#define Y_MAX_PIN          15

#define Z_MIN_PIN          18
#define Z_MAX_PIN          19

#ifndef MOSFET_D_PIN
#define MOSFET_D_PIN     -1
#endif

#ifndef RAMPS_D8_PIN
#define RAMPS_D8_PIN      8
#endif

#ifndef RAMPS_D9_PIN
#define RAMPS_D9_PIN      9
#endif

#ifndef RAMPS_D10_PIN
#define RAMPS_D10_PIN    10
#endif

#define HEATER_0_PIN       RAMPS_D10_PIN

String a2;
int i = 0, krok1 = 0, krok2 = 0, krok3 = 0, kroki = 0;
bool kierunek1 = HIGH, kierunek2 = HIGH, kierunek3 = HIGH;
bool kierunek = HIGH;
bool x1, y1, z1;
bool start = LOW;
bool okr = 0;

int temp;
double pomiar;
double x;
int czas = 0;
bool raz = 0;
bool raz2 = 0;
bool raz3 = 0;
bool raz4=0;
bool raz5=0;

int sr = 0;



bool praca = 0;
bool grzej = 0;
bool przesun = 0;
bool poz0 = 0;
bool startup = 0;
bool stop = 0;
bool gotowy = 0;
bool awaria = 0;
bool dol = 0;
int bkrok = 7500;



Timer wyswietl_temp;        // inicjacja timera uzytego w celu sprawdzania temperatury glowicy w przerwaniu
                            // zamiast uzywania delaya spowalniajacego predkosc silnikow



LiquidCrystal lcd(16, 17, 23, 25, 27, 29);
//************************************************************************************
//***************     przypisanie wejsc i wyjsc użytych w programie     **************
//************************************************************************************

void setup()
{
  lcd.begin(20, 4);
  pinMode(HEATER_0_PIN, OUTPUT);
  Serial.begin(115200);
  pinMode(X_ENABLE_PIN, OUTPUT);
  digitalWrite(X_ENABLE_PIN, LOW);
  pinMode(X_DIR_PIN, OUTPUT);
  digitalWrite(X_DIR_PIN, LOW);
  pinMode(X_STEP_PIN, OUTPUT);
  digitalWrite(X_STEP_PIN, HIGH);

  pinMode(Y_ENABLE_PIN, OUTPUT);
  digitalWrite(Y_ENABLE_PIN, LOW);
  pinMode(Y_DIR_PIN, OUTPUT);
  digitalWrite(Y_DIR_PIN, LOW);
  pinMode(Y_STEP_PIN, OUTPUT);
  digitalWrite(Y_STEP_PIN, HIGH);

  pinMode(Z_ENABLE_PIN, OUTPUT);
  digitalWrite(Z_ENABLE_PIN, LOW);
  pinMode(Z_DIR_PIN, OUTPUT);
  digitalWrite(Z_DIR_PIN, LOW);
  pinMode(Z_STEP_PIN, OUTPUT);
  digitalWrite(Z_STEP_PIN, HIGH);

  pinMode(X_MAX_PIN, INPUT_PULLUP);
  pinMode(Y_MAX_PIN, INPUT_PULLUP);
  pinMode(Z_MAX_PIN, INPUT_PULLUP);

 Serial.println("By umozliwic wybor trybu pracy wpisz 'gotowy'");
  wyswietl_temp.begin(10);

}
