#ifndef defsh
#define defsh

#define digi

#ifdef nano// nanomega 328
#define PIN 13        // пин DI
#define leftpin 12
#define rightpin 11
#define stoppin 10
#endif
#ifdef digi// digispark
#define PIN 13        // пин DI
#define leftpin 12
#define rightpin 11
#define stoppin 10
#endif

#define red  0xFF0000
#define yel  0xFFA500
#define blue  0x0000FF
#define green  0x00FF00
#define black  0x000000

#define NUM_LEDS 30   // число диодов

#endif