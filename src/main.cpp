#include <Arduino.h>
#include "defs.h"
/*
RAM:   [=         ]  11.7% (used 60 bytes from 512 bytes)
Flash: [=====     ]  46.7% (used 2810 bytes from 6012 bytes)
надо будет
лево\право\стоп\(зад) это 3-4 провода
1 провод на управление 7805 на диоды и отдельно дигиспарк у него свой 7805 
диодный делитель 2 к 1, это 10к и 5к, 5 к массе, 10 к 12 вольтам, средняя точка на пин
вопрос где взять постоянный плюс остается открытым
*/

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
int psl = 0; //left
int psr = 0; //right
int pss = 0; //stop


long prevm;
long currm;
long del = 50;
int cntl = 0;

void getcmd() {
  psl = sl; 
  psr = sr; 
  pss = ss;
  
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
  #ifndef test
  pinMode(leftpin, INPUT);
  pinMode(rightpin, INPUT);
  pinMode(stoppin, INPUT);
  #endif
  #ifdef test
   pinMode(pinled,OUTPUT);  
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
  #ifdef test
  while (1){
   digitalWrite(pinled,1);
   delay(1000);
   digitalWrite(pinled,0);
   delay(1000);
  }
  #endif
  #ifndef test
  getcmd();
  workt(sl, sr, ss);
  currm = millis();
  if (currm - prevm > del) {
    prevm = currm;
    cntl++;
    if (cntl == 10) {
      cntl = 0;
    }
    strip.show();
  }
 #endif
}//.
