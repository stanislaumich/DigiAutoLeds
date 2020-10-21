#ifndef defsh
#define defsh
// под что компилируем
#define digi
// наномега 328
#ifdef nano328
#define PIN 13        
#define leftpin 12
#define rightpin 11
#define stoppin 10
#endif
// дигиспарк
#ifdef digi
#define PIN 4        
#define leftpin 2
#define stoppin 1
#define rightpin 0
#endif
// цвета
#define red  0xFF0000
#define yel  0xFFA500
#define blue  0x0000FF
#define green  0x00FF00
#define black  0x000000

// число диодов
#define NUM_LEDS 30   

#endif