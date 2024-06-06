

//unsigned char decimales[]={0,6,12,18,25,31,37,43,50,56,62,68,75,81,87,93};// la decimale de temperature 
//est donnée par pas de  0,0625 et
//est donnée sur b3b2b1b0 comme chiffre entre 0 et 15 ; on multiple ce chiffre par 0,0625 pour obtenir la décimale .
// le résultat de la multiplication est dans le tableau decimale ; pour une valeur x de b3b2b1b0 la decimales 
//donnée par decimales[x] .

#ifndef My_DS18b20_h
#define My_DS18b20_h

#include <Arduino.h>

#if ARDUINO >= 100
#include <Arduino.h>       // for delayMicroseconds, digitalPinToBitMask, etc
#else
#include "WProgram.h"      // for delayMicroseconds
#endif
//******************************


//***************************

class My_DS18b20{

public:

My_DS18b20(int dq_number);
void release(void);
unsigned char init(void);
void write_byte(unsigned char data);
unsigned char read_byte(void);
uint16_t read_temp(void);
int8_t read_int(void);
int toto=30;

private:
int _DQdata;

};

#endif






