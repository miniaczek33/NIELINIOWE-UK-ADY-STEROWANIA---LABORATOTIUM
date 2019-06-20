//********************************************************************************************
//*************************  Wybor trybu pracy przez serial read  ****************************
//********************************************************************************************

void sprawdz() {
  while (Serial.available()){
    a2 = Serial.readStringUntil('\n');
    Serial.println(a2);
    if(a2 == "grzej" && awaria==0 && gotowy == 1) {
      praca = 0;
      grzej = 1;
      okr = 0;
      dol = 0;
      poz0 = 0;
      przesun = 0;
    }
    if(a2 == "praca" && awaria==0 && gotowy == 1) {
      praca = 1;
      grzej = 0;
      przesun = 0;
      okr = 0;
      dol = 0;
      poz0 = 0;
      gotowy = 0;
    }
    if(a2 == "a") {
      awaria = 1;
      praca = 0;
      grzej = 0;
      okr = 0;
      dol = 0;
      poz0 = 0;
      gotowy = 0;
      przesun = 0;
      Serial.println("Program zostal zatrzymany...");
      Serial.println("By wznowic program wpisz 'gotowy'...");
    }

    if(a2 == "gotowy" && (awaria==0 || startup == 0)) {
      gotowy = 1;
      okr = 0;
      przesun = 0;
      praca = 0;
      grzej = 0;
      dol = 0;
      poz0 = 0;
      awaria = 0;

      raz = 0;
      bkrok = 7500;
    }
    
    if(a2 == "okrag" && awaria==0 && gotowy == 1) {
      praca = 0;
      grzej = 0;
      okr = 1;
      dol = 0;
      poz0 = 0;
      gotowy = 0;
      przesun = 0;
    }
    if(a2 == "zero" && awaria==0 && gotowy == 1) {
      praca = 0;
      grzej = 0;
      okr = 0;
      dol = 0;
      poz0 = 1;
      gotowy = 0;
      przesun = 0;
    }
    if(a2 == "dol" && awaria==0 && gotowy == 1) {
      praca = 0;
      grzej = 0;
      okr = 0;
      dol = 1;
      poz0 = 0;
      gotowy = 0;
      przesun = 0;
    }


    if(a2 == "przesun" && awaria == 0 && gotowy == 1){
     praca = 0;
      grzej = 0;
      okr = 0;
      dol = 0;
      poz0 = 0;
      gotowy = 0;
      przesun = 1;
    }

     if(a2 == "stop" && awaria == 0 && gotowy == 1){
      praca = 0;
      grzej = 0;
      okr = 0;
      dol = 0;
      poz0 = 0;
      gotowy = 1;
      przesun = 0;
      
      raz = 0;
      raz2 = 0;
      raz4=0;
      bkrok =7500;
      raz5=0;
    }
  }
}

//********************************************************************************************
//***********************          tryb pracy gora/dol         *******************************
//***********************  Silniki co 500 krokow zmieniajace   *******************************
//***********************            kierunek jazdy            *******************************
//********************************************************************************************

void silnik_gora_dol() {
if(raz4==0){
  Serial.println("\t\t\tgora/dol - by zakonczyc wpisz stop...");
  raz4=1;
}
  if (kroki < 500)
  {
    digitalWrite(X_STEP_PIN, HIGH);
  }

  if (kroki < 500)
  {
    digitalWrite(Y_STEP_PIN, HIGH);
  }

  if (kroki < 500)
  {
    digitalWrite(Z_STEP_PIN, HIGH);
  }
  kroki++;
  delayMicroseconds(100);
  if (kroki == 500)
  {
    
    digitalWrite(X_DIR_PIN, kierunek);
    digitalWrite(Y_DIR_PIN, kierunek);
    digitalWrite(Z_DIR_PIN, kierunek);
    kierunek = !kierunek;
    kroki = 0;
  }
}


//******************************************************************************************
//*************************  sprawdzanie temperatury głowicy  ******************************
//******************************************************************************************

void sprawdz_temp() {
  if (wyswietl_temp.available())
  {
    temp = analogRead(13);
    x = (double) temp;
    pomiar = a * x * x * x + b * x * x + c * x + d;
    lcd.setCursor(0, 0);
    lcd.print(pomiar);
    wyswietl_temp.restart();
  }
}


//******************************************************************************************
//***********************  ustawianie pozycji zerowej drukarki 3d  *************************
//******************************************************************************************

void poz_0() {
  if(raz2==0){
    Serial.println("Ustawianie pozycji zerowej ");
    raz2=1;
  }
  
  digitalWrite(X_DIR_PIN, !kierunek);             // SPRAWDZIC I WPISAC NA SZTYWNO!!!!
  digitalWrite(Y_DIR_PIN, !kierunek);             // SPRAWDZIC I WPISAC NA SZTYWNO!!!!
  digitalWrite(Z_DIR_PIN, !kierunek);             // SPRAWDZIC I WPISAC NA SZTYWNO!!!!

  digitalWrite(X_STEP_PIN, LOW);
  digitalWrite(Y_STEP_PIN, LOW);
  digitalWrite(Z_STEP_PIN, LOW);
  delayMicroseconds(100);

  x1 = digitalRead(X_MAX_PIN);
  y1 = digitalRead(Y_MAX_PIN);
  z1 = digitalRead(Z_MAX_PIN);

  if (x1 == LOW && kierunek == HIGH)
  {
    digitalWrite(X_STEP_PIN, HIGH);
  }

  if (y1 == LOW && kierunek == HIGH)
  {
    digitalWrite(Y_STEP_PIN, HIGH);
  }

  if (z1 == LOW && kierunek == HIGH)
  {
    digitalWrite(Z_STEP_PIN, HIGH);
  }

if (x1 == HIGH && y1 == HIGH && z1 == HIGH){
  Serial.println("pozycja zerowa ustawiona, podaj nastepna komende:");
  gotowy = 1;
  raz2 = 0;
  poz0 = 0;
}

}

//******************************************************************************************
//********************           jazda 7500 krokow w dol           *************************
//********************  z mozliwoscia zatrzymania w trakcie jazdy  *************************
//******************************************************************************************

void jazda_dol() {
  if(raz5 == 0){
    Serial.println("!! Wszystkie silniki jada w dol 7500 krokow !!");
  Serial.println("!! W razie awarii wpisz a, lub by zatrzymac jazde - stop !! ");
  raz5 = 1;
  }
  
  digitalWrite(X_DIR_PIN, HIGH);
  digitalWrite(Y_DIR_PIN, HIGH);
  digitalWrite(Z_DIR_PIN, HIGH);

  digitalWrite(X_STEP_PIN, LOW);
  digitalWrite(Y_STEP_PIN, LOW);
  digitalWrite(Z_STEP_PIN, LOW);
  delayMicroseconds(100);


  if (sr < 7500)
  {
    digitalWrite(X_STEP_PIN, HIGH);
    Serial.print("Pozostalo krokow: ");
    Serial.print(bkrok);
    bkrok--;
  }

  if (sr < 7500)
  {
    digitalWrite(Y_STEP_PIN, HIGH);
  }

  if (sr < 7500)
  {
    digitalWrite(Z_STEP_PIN, HIGH);

  }
  sr++;
  if(sr == 7500) {
    raz5 = 0;
    gotowy = 1;
    dol = 0;
    bkrok =7500;
  }
}

//******************************************************************************************
//********************          zalaczenie grzalki na t= 2S          ***********************
//******************************************************************************************

void grzalka_on() {
  if(raz3==0){
    Serial.println("grzanie ");
    raz3=1;
  }
  
  digitalWrite(HEATER_0_PIN, HIGH);
  if (czas < 200)
  {
    delay(10);
    sprawdz_temp();
    czas++;
  }
  else
  {
    raz3 = 0;
    digitalWrite(HEATER_0_PIN, LOW);
    Serial.println("grzanie skonczone, podaj nastepna komende:");
    grzej = 0;
  }
}

//******************************************************************************************
//********************          ruch silnikow o zadane wartosci      ***********************
//******************************************************************************************

void przesun_o(){
  if(raz == 0){
  Serial.println("Wpisz o ile krokow ma sie przesunac filnik w formacie a xkr b ykr c zkr");
  raz == 1;
  }
  while (Serial.available())
  {
      
      while(stop == 0){
      start = HIGH;
      a2 = Serial.readStringUntil('\n');
      if (a2 == "stop") {
      stop = 1;
      }
      else{
      sscanf(a2.c_str(), "a %d b %d c %d", &krok1, &krok2, &krok3);
      Serial.println(krok1);
      Serial.println(krok2);
      Serial.println(krok3);

      kierunek1 = krok1 < 0;
      digitalWrite(X_DIR_PIN, kierunek1);
      krok1 = krok1 > 0 ? krok1 : -krok1;

      kierunek2 = krok2 < 0;
      digitalWrite(Y_DIR_PIN, kierunek2);
      krok2 = krok2 > 0 ? krok2 : -krok2;

      kierunek3 = krok3 < 0;
      digitalWrite(Z_DIR_PIN, kierunek3);
      krok3 = krok3 > 0 ? krok3 : -krok3;

      if (krok1 == 0 && krok2 == 0 && krok3 == 0 && start == HIGH)
      {
        Serial.println("Wpisz nastepna komende - so wyboru:");
        Serial.print("stop");
        Serial.println("\t\ta xkr b ykr c zkr");
        start = LOW;

      }
      }
}
}
  if ((x1 == LOW || kierunek1 == LOW) && krok1 > 0)
    {
      digitalWrite(X_STEP_PIN, HIGH);
      krok1--;
    }

    if ((y1 == LOW || kierunek2 == LOW) && krok2 > 0)
    {
      digitalWrite(Y_STEP_PIN, HIGH);
      krok2--;
    }

    if ((z1 == LOW || kierunek3 == LOW) && krok3 > 0)
    {
      digitalWrite(Z_STEP_PIN, HIGH);
      krok3--;
    }
}

//******************************************************************************************
//*************************          startup menu programu      ****************************
//******************************************************************************************

void start_programu(){
  
  Serial.println("\t\t\tMozliwe tryby pracy:");
  Serial.println("praca - silnik gora dol");
  Serial.println("zero - ustaw pozycje zerowa");
  Serial.println("dol - ustaw (mniej wiecej) na srodku (do uzycia tylko w pozycji zerowej)");
  Serial.println("grzej - grzalka on na t = 2s");
  Serial.println("stop - zatrzymanie pracy, mozliwosc sredowania silnikami poprzez");
  Serial.println("\t\ta xkrokow b ykrokow c zkrokow");
  startup = 1;
}
