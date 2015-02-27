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
		if(Stunden==WStunden[0]){
			if(Minuten==WMinuten[0]){
				Wan = 1;
				PORTC |= (1<<PC5);
			}
		}
	}
	else
	{
		if(Stunden==WStunden[1]){
			if(Minuten==WMinuten[1]){
				Wan = 1;
				PORTC |= (1<<PC5);
			}
		}
	}
}

void weckereinaus(uint8_t pos){
	


}


void temperatur(){
	ADC_Read(0);
	uint16_t adcval = ADC_Read(0);
	double span= (double)adcval*(5.0/1024.0);
	double widerst = ((double)span*2700.0)/((double)(5-(double)span));
	tempera = (100.0/1387.0)*widerst+(50+tempoffset-(100.0/1387.0)*2417.0);
}

void zeit(){
	sektemp=Sekunden;
	if (Sekunden >= 60){
		//Temperatur bestimmen
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
			Sekunden += sekoffset; //Ausgleich der VerlustSekunden
		}
	}
	
	if(Wan==0)
	{
		Wecker();
	}
}



#endif /* ZEIT_H_ */
