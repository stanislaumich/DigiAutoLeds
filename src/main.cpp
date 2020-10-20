#include <Arduino.h>
#include "defs.h"
/*
с сериалом это будет 5830 байт, если выкинуть сериал то 4510 из приблизно 6000
после ещё доработки стало 3828, если анализировать пины 12 вольт
то можно прицепить к дигиспарку
надо будет
лево\право\стоп\(зад) это 3-4 провода
1 провод на управление
7812 на диоды и от неё же дигиспарк

*/

#undef serialon
#include "Adafruit_NeoPixel.h"

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

//
int ld[NUM_LEDS];
int k;
int cl = -1;
// statuses 1 0
int sl = 0; //left
int sr = 0; //right
int ss = 0; //stop
//int st = 0; //test
int psl = 0; //left
int psr = 0; //right
int pss = 0; //stop


long prevm;
long currm;
long del = 50;
int cntl = 0;

void getcmd() {
  char ch;
  int a = 0;
  psl = sl; psr = sr; pss = ss;
  String s ;

  #ifdef serialon
  while (Serial.available()) {
    ch = Serial.read();
    if (ch != '\n') {
      s.concat(ch);
    }
  }
  
  s == "1" ? ss = 1 : a = 0;// stop on
  s == "2" ? ss = 0 : a = 0;// stop off
  s == "3" ? sl = 1 : a = 0;// left on
  s == "4" ? sl = 0 : a = 0;// left off
  s == "5" ? sr = 1 : a = 0;// right on
  s == "6" ? sr = 0 : a = 0;// right off
  if (s == "7") {//leftright on
    sr = 1;
    sl = 1;
  }
  if (s == "8") {// leftrighoff
    sr = 0;
    sl = 0;
  }
  if (s == "9") {// all on
    sr = 1;
    sl = 1;
    ss = 1;
  }
  if (s == "0") {// all off
    sr = 0;
    sl = 0;
    ss = 0;
  }
   Serial.println(s);
  #endif
  sr=rightpin==1;
  sl=leftpin==1;
  ss=stoppin==1;
}

void start() {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor( i, red);
  }
  strip.show();
  delay(500);
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, blue);
  }
  strip.show();
  delay(500);
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, green);
  }
  strip.show();
  delay(500);
  strip.clear();
  strip.show();
}

void workt(int isl, int isr, int iss) {
  if (isr == 1) {// right 30
    if (psr == 0) {
      psr = 1;
      cntl = 0;
    }
    strip.setPixelColor(cntl + NUM_LEDS/3*2, yel);
  } else {
    if (psr == 1) {
      psr = 0;
      cntl = 0;
    }
    strip.setPixelColor(cntl + NUM_LEDS/3*2, black);
  }
  if (isl == 1) {// left 1
    if (psl == 0) {
      psl = 1;
      cntl = 0;
    }
    strip.setPixelColor(NUM_LEDS / 3 - cntl - 1, yel);
  } else {
    if (psl == 1) {
      psl = 0;
      cntl = 0;
    }
    strip.setPixelColor(NUM_LEDS / 3 - cntl - 1, black);
  }
  if (iss == 1) {// stop
    if (pss == 0) {
      pss = 1;
      cntl = 0;
    }
    strip.setPixelColor(15 + cntl / 2, red);
    strip.setPixelColor(14 - cntl / 2, red);
  } else {
    if (pss == 1) {
      pss = 0;
      cntl = 0;
    }
    strip.setPixelColor(19 - cntl / 2, black);
    strip.setPixelColor(10 + cntl / 2, black);
  }
}

void setup() {
  //pinMode(leftpin, INPUT);
  //digitalWrite(leftpin, LOW);  
  //pinMode(rightpin, INPUT);
  //digitalWrite(rightpin, LOW);
  //pinMode(stoppin, INPUT);
  //digitalWrite(stoppin, LOW);
  #ifdef serialon
   Serial.begin(9600);
  #endif 
  strip.begin();
  strip.setBrightness(250);
  strip.clear();
  strip.show();
  start();
  k = 0;
}
int ee;
void loop() {
  getcmd();
  workt(sl, sr, ss);
  //ee=digitalRead(leftpin);
  currm = millis();
  if (currm - prevm > del) {
    prevm = currm;
    cntl++;
    if (cntl == 10) {
      cntl = 0;
    }
    strip.show();
  }
  #ifdef serialon
   ee==1?Serial.write("1"):Serial.write("0");
  #endif
}//.
