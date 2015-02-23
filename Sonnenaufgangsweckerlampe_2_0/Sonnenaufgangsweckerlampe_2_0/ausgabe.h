/*
 * ausgabe.h
 *
 * Created: 06.02.2015 07:07:47
 *  Author: Lüdemann
 */ 


#ifndef AUSGABE_H_
#define AUSGABE_H_

void wtag(uint8_t numm){
	switch (numm)
	{
		case 0:
		lcd_string("So ");
		break;
		
		case 1:
		lcd_string("Mo ");
		break;
		
		case 2:
		lcd_string("Di ");
		break;
		
		case 3:
		lcd_string("Mi ");
		break;
		
		case 4:
		lcd_string("Do ");
		break;
		
		case 5:
		lcd_string("Fr ");
		break;
		
		case 6:
		lcd_string("Sa ");
		break;
		
		default:
		break;
	}
}

void aus(uint8_t zeile, uint8_t pos){
	
	switch (zeile)
	{
		case 1:
			lcd_clear();
			lcd_home();
			switch (pos)
			{
				case 0:
					//Alles ohne Sekunden
					wtag(WochenTag);
					lcd_string(" ");
					zeitaus(0);
					
					break;
					
				case 1:
					//Alles
					wtag(WochenTag);
					lcd_string(" ");
					zeitaus(1);
					
					break;
				case 2:
					//Nur Kalender
					wtag(WochenTag);
					
					break;
				case 3:
					//Nur Zeit mit Sekunden mit WDAY
					wtag(WochenTag);
					zeitaus(1);
					
					break;
					
				case 4:
					lcd_string("Guten Tag");
					lcd_setcursor(0,2);
					lcd_string("Wecker start");
					
					break;
				
				case 5:
					//Wecker
					lcd_string("Weckzeit: ");
					itoa(WStunden[0],Buffer,10);
					lcd_string(Buffer);
					lcd_string(":");
					itoa(WMinuten[0],Buffer,10);
					lcd_string(Buffer);
					
					break;
					
				case 6:
					//Zeit ohne Sekunden mit WDAY
					wtag(WochenTag);
					zeitaus(0);
					
					break;
			}
			break;
			
		case 2:
			lcd_setcursor(0,2);
				switch (pos)
				{
					case 0:
						//blanko
					
						break;
						
					case 1:
						//Temperatur
						dtostrf(tempera,2,2,Buffer);
						lcd_string(Buffer);
						lcd_data(0b11011111); //°
						lcd_data(0b01000011); //C
						
						break;
				}
			break;
	}
}

void zeitaus(uint8_t pos){
	switch (pos)
	{
		case 0:
			itoa( Stunden, Buffer, 10 );
			lcd_string(Buffer);
			lcd_string(":");
			itoa( Minuten, Buffer, 10);
			lcd_string(Buffer);
			
			break;
		
		case 1:
			itoa( Stunden, Buffer, 10 );
			lcd_string(Buffer);
			lcd_string(":");
			itoa( Minuten, Buffer, 10);
			lcd_string(Buffer);
			lcd_string(":");
			itoa(Sekunden, Buffer,10);
			lcd_string(Buffer);
			
			break;
	}
}


#endif /* AUSGABE_H_ */