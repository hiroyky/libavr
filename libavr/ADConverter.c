/** 
 * ADConverter.c
 *
 * Created: 2012/02/07 20:24:08
 *  Author: hirokazu
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "ADCoverter.h"

static void (*ADC_interruptListener)(void);

void ADC_init(unsigned char usedPin, ADC_ReferenceVoltage rv, ADC_Align align,
                InterruptSwitch is, ADC_Prescaler p) {
    // AD変換に使用するピンを入力にする
	DDRC &= ~_BV(usedPin);
	PORTC &= ~_BV(usedPin);

    ADMUX = (rv << 6) | (align << 5) | (usedPin & 0x0F);
	ADCSRA = _BV(ADEN) | (is << 3) | p;
}


void ADC_start() {
	ADCSRA |= _BV(ADSC);
}

void ADC_startAutomaticLaunch(ADC_LaunchedFrom launchedFrom) {
	launchedFrom &= 0b111;
	ADCSRB |= launchedFrom;
	ADCSRA |= _BV(ADATE);
}


void ADC_stopAutomaticLaunch() {
	ADCSRA &= ~_BV(ADATE);
}


unsigned char ADC_getADCH() {
	return ADCH;
};

unsigned char ADC_getADCL() {
    return ADCL;
};

void ADC_setInterruptListener(void (*func)(void)) {
	ADC_interruptListener = func;
}

/**
 * ＡＤ変換の割り込み動作
 */
ISR(ADC_vect) {
	ADC_interruptListener();

	// リセット処理(次回の再スタートのため)
	ADCSRA |= _BV(ADSC);
	ADCSRA |= _BV(ADIF);
}