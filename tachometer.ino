/* 
  *   
  *  Modul yang digunakan  
  *  
  *  - Arduino Nano 
  *  - IR Distance Sensor
  *  - 7 Segment 7"
  *  
  */

// =========== Librari ===========

  #include <TimerOne.h>
  #include "Wire.h"

// =========== INISIALISASI ==========

  #define LATCH   6
  #define CLK     5
  #define DATA    4

// =========== Byte Display ===========

byte digit[10]= {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xf8,0x80,0x90}; //negatif
//byte digit[10]= {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x7, 0x7F, 0x6F};
// =========== Variabel ===========

  float value=0;  
  float rev=0;

  int i,j,k,l;
  int rpm;
  int patokanwaktu=0;
  int time;

  int pembagi = 1 ;               // Jumlah Ruas yang terbaca

// =========== Program Utama ===========

void RPM() {
  rev++;
}

void CalculateRPM(){

  Timer1.detachInterrupt();         //stop the timer

  rpm = ((rev/pembagi) * 60 );      //kalkulasi rpm
  
  Serial.print("Counted : ");
  Serial.println(rev);
  Serial.print("RPM : ");
  Serial.println(rpm);

  rev=0;

  Timer1.attachInterrupt( CalculateRPM );  // enable the timer
  
}

void setup(){
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(7, INPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(DATA, OUTPUT);


  Timer1.initialize(1000000);               // set timer freeze, patokan 100000 = 1sec
  attachInterrupt(0, RPM, FALLING);  
  Timer1.attachInterrupt( CalculateRPM );  // enable the timer

  }

void loop(){
  
  if (digitalRead(7) == HIGH){
    
    Serial.print("RPM terbaca : ");
    Serial.println(rpm);

//Digit 1 Dihilangkan
    

    l = ((rpm/10)%10);
    k = ((rpm/100)%10);
    j = ((rpm/1000)%10);
    i = ((rpm/10000)%10);


/*
  //Digit 1 dibaca
   
    l = (rpm%10);
    k = ((rpm/10)%10);
    j = ((rpm/100)%10);
    i = ((rpm/1000)%10);
*/    
 

    
          Serial.print("i = ");
          Serial.println(i);
          Serial.print("j = ");
          Serial.println(j);
          Serial.print("l = ");
          Serial.println(k);
          Serial.print("l = ");
          Serial.println(l);
  
      digitalWrite (LATCH, LOW);
      
        shiftOut(DATA, CLK, MSBFIRST, ~digit[l]); // digitempat
        shiftOut(DATA, CLK, MSBFIRST, ~digit[k]); // digittiga
        shiftOut(DATA, CLK, MSBFIRST, ~digit[j]); // digitdua
        shiftOut(DATA, CLK, MSBFIRST, ~digit[i]); // digitsatu
      
      digitalWrite(LATCH, HIGH);
      delay(1000);

  }
  
}
