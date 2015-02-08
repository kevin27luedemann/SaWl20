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
uint8_t WStunden = 0;
uint8_t WMinuten = 0;
uint8_t Wan = 0;
uint8_t sektemp=0;
double tempera;
uint8_t sekoffset=0;
uint8_t tempoffset = 2;
uint8_t Tag = 5;
uint8_t Monat = 10;
uint8_t Jahr = 15;
char Buffer[20];

#define NAME(x) #x

//Funktionen
void zeit();
inline uint8_t debounce(volatile uint8_t *port, uint8_t pin);
void sende (uint8_t zahl);
void zeitsetzen();
void init();
void Wecker();
void ausgabe(uint8_t pos);
void einstzeit();
void einsweck();
void init();
void zeitsetzen();
uint16_t ADC_Read( uint8_t channel );
uint16_t ADC_Read_Avg( uint8_t channel, uint8_t nsamples );
uint8_t einst(uint8_t posit);
void erhoehen(uint8_t *var, uint8_t obergrenze, uint8_t pos, const char *data);
void wtag(uint8_t numm);
void aus(uint8_t zeile, uint8_t pos);
void Kalenderaus();
void zeitaus(uint8_t pos);


#endif /* DEFINITIONEN_H_ */

inline uint8_t debounce(volatile uint8_t *port, uint8_t pin)
{
	if ( !(*port & (1 << pin)) )
	{
		/* Pin wurde auf Masse gezogen, 100ms warten   */
		_delay_ms(50);   // Maximalwert des Parameters an _delay_ms
		//_delay_ms(50);   // beachten, vgl. Dokumentation der avr-libc
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

void sende (uint8_t zahl){
	//PORTC |= (1<<PC2);
	PORTC |= (1<<PC1);
	while(!(SPSR & (1<<SPIF))){}
	SPDR=zahl;
	while(!(SPSR & (1<<SPIF))){}
	PORTB |= (1<<PB2);
	PORTB &= ~(1<<PB2);
	_delay_ms(500);
	PORTC &= ~(1<<PC1);
	//PORTC &= ~(1<<PC2);
	_delay_ms(500);
}