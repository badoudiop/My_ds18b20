/*tres important : relier le DQ du ds1820 au GND à travers une diode et un condensateur comme indiqué
dans le datasheet ,sinon le ds1820 s'arrete 
, c'est ce qui arrive chez moi en tout cas .
*/

#include "My_DS18b20.h"

#include "Arduino.h"

int dq  ;



//***************************
#define _NOP() asm("nop")
//************************************

//********************************
void mydelay(unsigned int da);
void init(void);
void high(void);
void low(void);
unsigned char init1(void);

void delay480(void);
void delay120(void);
void delay60(void);
void delay15(void);
unsigned char read_bit(void);
void write_bit0(void);
void write_bit1(void);
//***********************************



My_DS18b20::My_DS18b20(int a)
{
  dq=a;
_DQdata=a;
}

void delay480(void)
{
//delayMicroseconds(480);
mydelay(271);
_NOP();
}

void delay15(void)
{
//delayMicroseconds(15);

mydelay(5);
_NOP();

}

void delay60(void)
{
//delayMicroseconds(60);

mydelay(30);
_NOP();
_NOP();
_NOP();
_NOP();
_NOP();
_NOP();

}

void delay120(void)
{
//delayMicroseconds(120);

mydelay(65);
_NOP();

}
//***************

void high(void)
{
pinMode(dq,INPUT);
//digitalWrite(dq,HIGH);
}

void low(void)
{
pinMode(dq,OUTPUT);
digitalWrite(dq,LOW);
}

void My_DS18b20::release(void)
{
high();
}

void write_bit0(void)
{
low();
delay60();
high();
delay15();
}

void write_bit1(void)
{
low();
mydelay(1);
high();
delay60();
}

unsigned char read_bit(void)
{
unsigned char caca1=0;
low();
mydelay(2);
high();
delay15();
high();
caca1=(digitalRead(dq))&0x01;
delay60();
return caca1;
}

unsigned char init1(void)
{
unsigned caca1=0;
high();
delay15();
low();
delay480();
high();
delay60();
caca1=(digitalRead(dq))&0x01;//just parenthee
delay480();
//PORTA=255-30;
return caca1;
}


unsigned char My_DS18b20::init(void)
{
return init1();
}

void write_byte1(unsigned char data)
{
for(unsigned int wb=0;wb<8;wb++)
{
if(data&(1<<wb)) write_bit1();
else write_bit0();
}
}

void My_DS18b20::write_byte(unsigned char data)
{
write_byte1(data);
}

unsigned char read_byte1(void)
{
unsigned char mimi=0;
for(unsigned int rb=0;rb<8;rb++)
{
if(read_bit()) mimi|=(1<<rb);
}
return mimi;
}
unsigned char My_DS18b20::read_byte(void)
{
return read_byte1();
}
//********** ce read temp nouv donne des décimales qui varient 

uint16_t My_DS18b20::read_temp(void)
{
unsigned char get[2];//envoie un résultat sur 9 bytes(chars)
uint16_t temp_read ;

while(init1());
write_byte1(0xCC);
write_byte1(0x44);
while(!read_bit()) ;//on attend le 1 de fin de conversion .
while(init1());
write_byte1(0xCC);
write_byte1(0xBE);
for(unsigned char gt=0;gt<2;gt++) get[gt]=read_byte1();
_delay_ms(10);

temp_read=get[0]+get[1]*256;
//temperature=(temp_read>>4)&0b01111111;
//decimale=get[0]&0x0F;

return temp_read ;
}


//**********************************
void mydelay(unsigned int da)
{
while(da--) _delay_us(1);
}
void pause(unsigned int x)
{
while(x--) _delay_us(10);
}

