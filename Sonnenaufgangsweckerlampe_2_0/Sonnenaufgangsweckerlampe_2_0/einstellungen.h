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
	Sekunden = 0;
	WochenTag=6;
	WStunden[0]=5;
	WMinuten[0]=35;
	WStunden[1]=7;
	WMinuten[1]=35;
//	einsweck();
//	einstzeit();
	einst(4);
//	einst(1); //Noch keinen Kalender, da er in den Einstellungen zu komplex ist
	einst(0);
	sekoffset=1;
}

void init(){
	//LCD einstellen und erste Ausgabe
	lcd_init();
	aus(1,4);
	//lcd_string("Wecker");
	//lcd_setcursor( 0, 2 );
	//lcd_string("Start!");
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
	PORTD |= (1<<PD2) | (1<<PD3) | (1<<PD4);
	
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
	aus(1,0);
	aus(2,0);
	lcd_string(NAME(WochenTag));
	while(!debounce(&PIND,3)){
		/*if (debounce(&PIND,2))
		{
			WochenTag++;
			if (WochenTag==7)
			{
				WochenTag=0;
			}
			aus(1,0);
			aus(2,0);
			lcd_string(NAME(WochenTag));
		}*/
		erhoehen(&WochenTag,7,0,NAME(WochenTag));
		
	}
	aus(1,0);
	aus(2,0);
	lcd_string(NAME(Stunden));
	while(!debounce(&PIND,3)){
		if (debounce(&PIND,2))
		{
			Stunden++;
			if (Stunden==24)
			{
				Stunden=0;
			}
			aus(1,0);
			aus(2,0);
			lcd_string(NAME(Stunden));
		}
		
	}
	aus(1,0);
	aus(2,0);
	lcd_string(NAME(Minuten));
	while(!debounce(&PIND,3)){
		if (debounce(&PIND,2))
		{
			Minuten++;
			if (Minuten==60)
			{
				Minuten=0;
			}
			aus(1,0);
			aus(2,0);
			lcd_string(NAME(Minuten));
		}
		
	}
	aus(1,0);
	aus(2,0);
	lcd_string(NAME(Sekunden));
	while(!debounce(&PIND,3)){
		if (debounce(&PIND,2))
		{
			Sekunden++;
			if (Sekunden==60)
			{
				Sekunden=0;
			}
			aus(1,0);
			aus(2,0);
			lcd_string(NAME(Sekunden));
		}
		
	}
}

void einsweck(){
	lcd_clear();
	lcd_home();
	aus(1,5);
	aus(2,0);
	lcd_string(NAME(WStunden[0]));
	while(!debounce(&PIND,3)){
		if (debounce(&PIND,2))
		{
			WStunden[0]++;
			if (WStunden[0]==24)
			{
				WStunden[0]=0;
			}
			aus(1,5);
			aus(2,0);
			lcd_string(NAME(WStunden[0]));
		}
	}
	
	aus(1,5);
	aus(2,0);
	lcd_string(NAME(WMinuten[0]));
	while(!debounce(&PIND,3)){
		if (debounce(&PIND,2))
		{
			WMinuten[0]++;
			if (WMinuten[0]==60)
			{
				WMinuten[0]=0;
			}
			aus(1,5);
			aus(2,0);
			lcd_string(NAME(WMinuten[0]));
		}
		
	}
	
}

//Funktion um eine Variable, die mit Adreesse uebergeben wird zu erhoehen
//erhoeht wird erst, wenn die richtige Taste gedrueckt wird
void erhoehen(uint8_t *var, uint8_t obergrenze, uint8_t pos, const char *data){
	if(debounce(&PIND,2))
	{
		*var +=1 ;
		if(*var>=obergrenze){
			*var=0;
		}
		aus(1,pos);
		aus(2,0);
		while( *data != '\0' )
		lcd_data( *data++ );
		
	}
}


//return 0 fuer kein Problem
//return 1 fuer falsche Eingabe

uint8_t einst(uint8_t posit){
	uint8_t temp=0;
	//abfrage wass eingestellt werden soll
	switch (posit)
	{
	case 0:
		//Einstellen Zeit
		//alles einstellen bis auf Sekunden
		//diese werden auf 0 gesetzt
		aus(1,6);
		aus(2,0);
		lcd_string(NAME(Stunden));
		while(temp<3)
		{
			if(debounce(&PIND,3))
			{
				temp++;
				lcd_clear();
				aus(1,6);
				aus(2,0);
				switch (temp)
				{
					case 0:
						lcd_string(NAME(Stunden));
						break;
					case 1:
						lcd_string(NAME(Minuten));
						break;
					case 2:
						lcd_string(NAME(WochenTag));
						break;
					default:
						break;
				}
			}
			/*if(Sekunden!=sektemp){
				zeit();
				//ausgabe(0);
				//Es muss eine richtge Ausgabe speziell fuer dieses Einstellung geschrieben werden
				//besonders wichtig ist, dass die alte Ausgaba ersetzt werden muss
			}*/
			switch (temp)
			{
			case 0:
				erhoehen(&Stunden,60,6,NAME(Stunden));
				break;
			case 1:
				erhoehen(&Minuten,60,6,NAME(Minuten));
				break;
			case 2:
				//nur jetzt WochenTag
				erhoehen(&WochenTag,7,6,NAME(WochenTag));
				break;
			default:
				break;
			}
		}
		Sekunden=0;
		return 0;
		break;
	case 1:
		//Einstellen der Lampenstärke
		//default=1
		temp = 0;
		lcd_clear();
		lcd_home();
		lcd_string("Lampenstärke:");
		aus(2,0);
		itoa(lampenstaerke,Buffer,10);
		lcd_string(Buffer);
		if(Sekunden!=sektemp){
			zeit();
		}
		if(debounce(&PIND,2))
		{
			lampenstaerke++;
			lcd_clear();
			lcd_home();
			lcd_string("Lampenstärke:");
			aus(2,0);
			itoa(lampenstaerke,Buffer,10);
			lcd_string(Buffer);
			
			if (lampenstaerke>=3)
			{
				lampenstaerke=1;
			}
			
		}
		return 0;
		break;
	case 2:
		//Einstellen Sekundenoffset
		//default =0
		lcd_clear();
		lcd_home();
		lcd_string("Sekundenoffset:");
		aus(2,0);
		itoa(sekoffset,Buffer,10);
		lcd_string(Buffer);
		if(Sekunden!=sektemp){
			zeit();
		}
		if(debounce(&PIND,2))
		{
			sekoffset++;
			lcd_clear();
			lcd_home();
			lcd_string("Sekundenoffset:");
			aus(2,0);
			itoa(sekoffset,Buffer,10);
			lcd_string(Buffer);
			
			if (sekoffset>=5)
			{
				sekoffset=-5;
			}
				
		}
		
		return 0;
		break;
	case 3:
		//Einstellen Temperaturoffset
		//default = 0;
		lcd_clear();
		lcd_home();
		lcd_string("Temperaturoffset:");
		aus(2,0);
		itoa(tempoffset,Buffer,10);
		lcd_string(Buffer);
		
		if(Sekunden!=sektemp){
			zeit();
		}
		if(debounce(&PIND,2))
		{
			tempoffset++;
			lcd_clear();
			lcd_home();
			lcd_string("Temperaturoffset:");
			aus(2,0);
			itoa(tempoffset,Buffer,10);
			lcd_string(Buffer);
			
			if (tempoffset>=10)
			{
				tempoffset=-10;
			}
			
		}
		
		return 0;
		break;
	case 4: //Wecker einstellen
		temp = 0;
		aus(1,5);
		aus(2,0);
		lcd_string(NAME(WStunden[0]));
		while (temp<2)
		{
			if (Sekunden!=sektemp)
			{
				zeit();
			}
			if(debounce(&PIND,3))
			{
				temp++;
				aus(1,5);
				aus(2,0);
				switch (temp)
				{
					case 0:
						lcd_string(NAME(WStunden[0]));
						break;
					case 1:
						lcd_string(NAME(WMinuten[0]));
						break;
					default:
						break;
				}
			}
			switch (temp)
			{
				case 0:
					erhoehen(&WStunden[0],24,5,NAME(WStunden[0]));
					break;
				case 1:
					erhoehen(&WMinuten[0],60,5,NAME(WMinuten[0]));
					break;
			}
			
		}
		return 0;
		break;

	case 5:
		temp = 0;
		aus(1,5);
		aus(2,0);
		lcd_string(NAME(WStunden[1]));
		while (temp<2)
		{
			if (Sekunden!=sektemp)
			{
				zeit();
			}
			if(debounce(&PIND,3))
			{
				temp++;
				aus(1,5);
				aus(2,0);
				switch (temp)
				{
					case 0:
					lcd_string(NAME(WStunden[1]));
					break;
					case 1:
					lcd_string(NAME(WMinuten[1]));
					break;
					default:
					break;
				}
			}
			switch (temp)
			{
				case 0:
				erhoehen(&WStunden[1],24,5,NAME(WStunden[1]));
				break;
				case 1:
				erhoehen(&WMinuten[1],60,5,NAME(WMinuten[1]));
				break;
			}
			
		}
		return 0;
		break;

	default:
		return 1;
		break;
	}
}



#endif /* EINSTELLUNGEN_H_ */