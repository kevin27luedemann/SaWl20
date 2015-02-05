﻿/*
 * ADC.h
 *
 * Created: 05.02.2015 07:05:40
 *  Author: Lüdemann
 */ 


#ifndef ADC_H_
#define ADC_H_

uint16_t ADC_Read( uint8_t channel )
{
	ADMUX = (ADMUX & ~(0x1F)) | (channel & 0x1F);
	ADCSRA |= (1<<ADSC);
	while (ADCSRA & (1<<ADSC) ) {
	}
	return ADCW;
}

uint16_t ADC_Read_Avg( uint8_t channel, uint8_t nsamples )
{
	uint32_t sum = 0;
	
	for (uint8_t i = 0; i < nsamples; ++i ) {
		sum += ADC_Read( channel );
	}
	
	return (uint16_t)( sum / nsamples );
}



#endif /* ADC_H_ */