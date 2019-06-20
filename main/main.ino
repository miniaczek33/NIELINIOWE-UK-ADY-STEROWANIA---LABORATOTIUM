#include "zmienne.h"

//******************************************************************************************
//********************         glowna petla programu           *****************************
//******************************************************************************************

void loop()
{
  while(startup == 0){
  sprawdz();
  if(gotowy == 1) {
    start_programu();
  }
  }
  
  /*digitalWrite(X_STEP_PIN, LOW);
  digitalWrite(Y_STEP_PIN, LOW);
  digitalWrite(Z_STEP_PIN, LOW);
  delayMicroseconds(100);*/
  
  while(dol == 1) {               // wykonanie trybu jazdy w dol
    jazda_dol();
    sprawdz_temp();
    sprawdz();
  }

 while(poz0 == 1) {              // wykonanie trybu pozycja zerowa
    poz_0();
    sprawdz_temp();
    sprawdz();
  }

  while(przesun==1){             // wywolanie trybu przesuwania silnikow o zadane wartosci
  przesun_o();
  sprawdz_temp();
  sprawdz();
  }

  while(grzej == 1)               // wywolanie trybu grzania grzalki
  {
    grzalka_on();
    sprawdz_temp();
    sprawdz();
  }
  
  while(praca == 1) {            // wywolanie trybu jazdy silnika gora dol
    silnik_gora_dol();
    sprawdz_temp();
    sprawdz();
  }
  
   sprawdz_temp();              // sprawdzenie temperatury glowicy
   sprawdz();                   // sprawdzenie czy nie zostal zmieniony tryb pracy, badz tryb awaryjny
}
