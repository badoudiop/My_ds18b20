
#include <My_DS18b20.h>
#include "ds18b20_serial.h"
#include <util/delay.h>


//affichage sur moniteur série mais on peut utiliser les dizaines et 
//decimales pour un affichage sur lcd  par exemple . Ici ce sont des types int .
int dqq=A0 ; //I use atmega 1280 so this is 0 in the serie ANALOG IN 
My_DS18b20 ds18b20(dqq);//ici the_dq=2=pin 2 mais on peut changer avec par exemple: DS18b20 ds18b20(7);
uint8_t  dizaine , diz , unit , deci;

void setup(void)
{
Serial.begin(9600);
ds18b20.init();
_delay_ms(1);
}
void loop()
{

int16_t temperature=ds18b20.read_temp();//temperatures non négatives !! les négatives non traitées .

Serial.print(" temperature  : ");
dizaine=temperature/16;
deci=(temperature)&0x0F;
deci=decimales[deci];

Serial.print("  dizaines :   ");
Serial.print(dizaine);
Serial.print("  les decimales :   ");
Serial.println(deci);

Serial.print("  donc la temperature est  :  ");
Serial.print(dizaine); Serial.print("  ,  ");Serial.println(deci);  Serial.println("  degres  "); 
//**************************************
_delay_ms(2000);
}