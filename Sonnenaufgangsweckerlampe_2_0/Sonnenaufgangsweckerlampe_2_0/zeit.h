/*
 * zeit.h
 *
 * Created: 05.02.2015 07:12:54
 *  Author: Lüdemann
 */ 


#ifndef ZEIT_H_
#define ZEIT_H_

void Wecker(){
	if (WochenTag!=0 && WochenTag!=6)
	{
		if (Wan == 0 && Stunden==Licht1a[1]){
			if (Minuten==Licht1a[0]){
				Wan = 1;
				lichteinaus(4);
			}
		}
		if (Wan==1 && Stunden==WStunden[0])
		{
			if (Minuten==WMinuten[0])
			{
				Wan = 2;
				TCNT0 = (255-35);
				TIMSK |= (1<<TOIE0);
				TCCR0 = (1<<CS01) | (1<<CS00);	
			}
		}
	}
	else
	{
		if (Wan == 0 && Stunden==Licht1b[1]){
			if (Minuten==Licht1b[0]){
				Wan = 1;
				lichteinaus(4);
			}
		}
		if (Wan==1 && Stunden==WStunden[1])
		{
			if (Minuten==WMinuten[1])
			{
				Wan = 2;
				TCNT0 = (255-35);
				TIMSK |= (1<<TOIE0);
				TCCR0 = (1<<CS01) | (1<<CS00);	
			}
		}
	}
}

void lichteinaus(uint8_t pos){
	switch (pos)
	{
		case 0:
			PORTC &= ~((1<<PC5) | (1<<PC4) | (1<<PC3));
			break;
			
		case 1:
			PORTC |= (1<<PC5);
			break;
		
		case 2:
			PORTC |= (1<<PC4);
			break;
			
		case 3: 
			PORTC |= (1<<PC3);
			break;
		
		case 4:
			PORTC |= ((1<<PC5) | (1<<PC4) | (1<<PC3));
			break;
		
		case 5:
			PORTC |= ((1<<PC5) | (1<<PC4));
			break;
		
		default:
			break;
	}
}


void temperatur(){

	ADC_Read(0);
	volatile uint16_t adcval =(uint16_t) (ADC_Read(0)+ADC_Read(0))/2.0;
	volatile float span= (float)adcval*(5.0/1023.0);
	volatile float widerst = ((float)span*3300.0)/((float)(5-(float)span));	//Widerstand hat 3,3kOhm
	tempera = (100.0/1387.0)*widerst+(50+tempoffset-(100.0/1387.0)*2417.0);//-18; //-17,86 gemessen, nicht analytisch bestätigt
	if ((int8_t)(tempera*10)%10>=5) //richtiges Runden auf die erste Nachkommastelle
	{
		tempera+=1;
	}
}

void zeit(){
	sektemp=Sekunden;
	if (Sekunden >= 60){
		//Temperatur bestimmen
		//Da auf der Platine nicht eingebaut, wird es momentn ausgenommen
		temperatur();
		
		Sekunden = 0;
		Minuten++;
		if(Minuten >= 60){
			Minuten = 0;
			Stunden++;
		}
		if(Stunden >= 24){
			Stunden = 0;
			WochenTag++;
			if (WochenTag>=7)
			{
				WochenTag=0;
			}
			if (Wan!=0)
			{
				Wan=0;
			}
			Sekunden += sekoffset; //Ausgleich der VerlustSekunden
		}
	}
	
	if(Wan!=3)
	{
		Wecker();
	}
}



#endif /* ZEIT_H_ */
