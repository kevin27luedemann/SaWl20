/*
 * einstellungen.h
 *
 * Created: 05.02.2015 07:07:08
 *  Author: Lüdemann
 */ 


#ifndef EINSTELLUNGEN_H_
#define EINSTELLUNGEN_H_

void zeitsetzen(){
	Minuten = 34;
	Stunden	= 5;
	Sekunden = 50;
	WochenTag=6;
	WStunden=5;
	WMinuten=35;
	einsweck();
	einstzeit();
}

void init(){
	//LCD einstellen und erste Ausgabe
	lcd_init();
	lcd_string("Wecker");
	lcd_setcursor( 0, 2 );
	lcd_string("Start!");
	_delay_ms(1500);
	lcd_clear();
	
	//SPI
	//SPCR = (1<<SPE) | (1<<MSTR) | (1<<DORD);
	//SPSR = (1<<SPI2X);
	//SPDR = 0;
	
	//ADC
	ADMUX = (1<<REFS0);
	ADCSRA = (1<<ADPS1) | (1<<ADPS0);
	ADCSRA |= (1<<ADEN);
	ADCSRA |= (1<<ADSC);
	while (ADCSRA & (1<<ADSC) ) {
	}
	(void) ADCW;
	
	//Eingänge
	PORTD |= (1<<PD2) | (1<<PD3);
	
	//Ausgänge
	DDRC = (1<<PC5);
	
	//erste zeiteinstellung
	zeitsetzen();
	
	//Timer 1 Einstelungen
	TCNT1H = 0b11110001;
	TCNT1L = 0b11110000;
	TIMSK = (1<<TOIE1);
	TCCR1B = (1<<CS10) | (1<<CS12);
	
	//Interupts aktivieren
	sei();
	
	//Wecker einschalten
	Wan=0;
	
}

void einstzeit(){
	ausgabe(0);
	lcd_string(NAME(WochenTag));
	while(!debounce(&PIND,3)){
		if (debounce(&PIND,2))
		{
			WochenTag++;
			if (WochenTag==7)
			{
				WochenTag=0;
			}
			ausgabe(0);
			lcd_string(NAME(WochenTag));
		}
		
	}
	ausgabe(0);
	lcd_string(NAME(Stunden));
	while(!debounce(&PIND,3)){
		if (debounce(&PIND,2))
		{
			Stunden++;
			if (Stunden==24)
			{
				Stunden=0;
			}
			ausgabe(0);
			lcd_string(NAME(Stunden));
		}
		
	}
	ausgabe(0);
	lcd_string(NAME(Minuten));
	while(!debounce(&PIND,3)){
		if (debounce(&PIND,2))
		{
			Minuten++;
			if (Minuten==60)
			{
				Minuten=0;
			}
			ausgabe(0);
			lcd_string(NAME(Minuten));
		}
		
	}
	ausgabe(0);
	lcd_string(NAME(Sekunden));
	while(!debounce(&PIND,3)){
		if (debounce(&PIND,2))
		{
			Sekunden++;
			if (Sekunden==60)
			{
				Sekunden=0;
			}
			ausgabe(0);
			lcd_string(NAME(Sekunden));
		}
		
	}
}

void einsweck(){
	lcd_clear();
	lcd_home();
	ausgabe(2);
	lcd_string(NAME(WStunden));
	while(!debounce(&PIND,3)){
		if (debounce(&PIND,2))
		{
			WStunden++;
			if (WStunden==24)
			{
				WStunden=0;
			}
			ausgabe(2);
			lcd_string(NAME(WStunden));
		}
	}
	
	ausgabe(2);
	lcd_string(NAME(WMinuten));
	while(!debounce(&PIND,3)){
		if (debounce(&PIND,2))
		{
			WMinuten++;
			if (WMinuten==60)
			{
				WMinuten=0;
			}
			ausgabe(2);
			lcd_string(NAME(WMinuten));
		}
		
	}
	
}

//Funktion um eine Variable, die mit Adreesse uebergeben wird zu erhoehen
//erhoeht wird erst, wenn die richtige Taste gedrueckt wird
void erhoehen(uint8_t *var, uint8_t obergrenze){
	if(debounce(&PIND,3))
	{
		*var+=1;
		if(*var>=obergrenze){
			*var=0;
		}
	}
}


//return 0 fuer kein Problem
//return 1 fuer falsche Eingabe

uint8_t einst(uint8_t posit){
	uint8_t temp=0;
	//abfrage wass eingestellt werden soll
	switch (posit){
	case 0:
		//Einstellen Zeit
		//alles einstellen bis auf Sekunden
		//diese werden auf 0 gesetzt
	
		while(temp<3);
		{
			if(debounce(&PIND,2));{
				temp++;
			}
			if(Sekunden!=sektemp){
				zeit();
				ausgabe(0);
			}
			switch (temp){
			case 0:
				erhoehen(&Stunden,60);
				break;
			case 1:
				erhoehen(&Minuten,60);
				break;
			default:
				break;
			}
		}
		return 0;
		break;
	case 1:
		//Einstellen der Tage
		temp = 0;
		while(temp< 3);
		{
			if(debounce(&PIND,2));{
				temp++;
			}
			if(Sekunden!=sektemp){
				zeit();
				ausgabe(0);
			}
			switch (temp){
			case 0:
				erhoehen(&Tag,10);
				break;
			case 1:
				erhoehen(&Monat,12);
				break;
			case 2:
				erhoehen(&Jahr,30);
				break;
			default:
				break;
			}
		}
		return 0;
		break;
	case 2:
		//Einstellen Sekundenoffset
		//default =0
		while(debounce(&PIND,3));
		{
			if(Sekunden!=sektemp){
				zeit();
				ausgabe(0);
			}
			if(debounce(&PIND,2)){
				erhoehen(&sekoffset,10);	
			}
		}
		return 0;
		break;
	case 3:
		//Einstellen Temperaturoffset
		//default = 0;
		while(debounce(&PIND,3));
		{
			if(Sekunden!=sektemp){
				zeit();
				ausgabe(0);
			}
			erhoehen(&tempoffset,10);
		}
		return 0;
		break;
//	case //alle einstellungen der Wecker
//		return 0;
//		break;
	default:
		return 1;
		break;
	}
}



#endif /* EINSTELLUNGEN_H_ */