/*
 * definitionen.h
 *
 * Created: 05.02.2015 07:08:04
 *  Author: Lüdemann
 */ 


#ifndef DEFINITIONEN_H_
#define DEFINITIONEN_H_

#define F_CPU 3686400

//Include
#include <avr/interrupt.h>
#include <stdint.h>
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>


//Variablen
uint8_t Sekunden = 0;
uint8_t Minuten = 0;
uint8_t Stunden = 0;
uint8_t WochenTag = 0;
uint8_t WStunden[2] = {0,0};
uint8_t WMinuten[2] = {0,0};
uint8_t Licht1[2] = {0,0};
uint8_t Licht2[2] = {0,0};
uint8_t Licht3[2] = {0,0};
uint8_t Wan = 0;
uint8_t sektemp=0;
double tempera;
int8_t sekoffset=0;
int8_t tempoffset = 2;
uint8_t lampenstaerke = 1;
char Buffer[20];

#define NAME(x) #x

//Funktionen
void zeit();
inline uint8_t debounce(volatile uint8_t *port, uint8_t pin);
void zeitsetzen();
void init();
void Wecker();
void init();
void zeitsetzen();
uint16_t ADC_Read( uint8_t channel );
uint16_t ADC_Read_Avg( uint8_t channel, uint8_t nsamples );
uint8_t einst(uint8_t posit);
void erhoehen(uint8_t *var, uint8_t obergrenze, uint8_t pos, const char *data);
void wtag(uint8_t numm);
void aus(uint8_t zeile, uint8_t pos);
void zeitaus(uint8_t pos);
uint8_t menu();
void temperatur(uint8_t);

#endif /* DEFINITIONEN_H_ */

inline uint8_t debounce(volatile uint8_t *port, uint8_t pin)
{
	if ( !(*port & (1 << pin)) )
	{
		/* Pin wurde auf Masse gezogen, 100ms warten   */
		_delay_ms(50);   // Maximalwert des Parameters an _delay_ms
		_delay_ms(10);   // beachten, vgl. Dokumentation der avr-libc
		if ( !(*port & (1 << pin)) )
		{
			/* Anwender Zeit zum Loslassen des Tasters geben */
			//_delay_ms(50);
			//_delay_ms(50);
			return 1;
		}
	}
	return 0;
}
