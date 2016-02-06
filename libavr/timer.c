/**
 * timer.c
 *
 * Created: 2012/02/07 19:58:18
 *  Author: hirokazu
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"

static void (*Timer0_compAMatchHandler)(void);
static void (*Timer0_compBMatchHandler)(void);
static void (*Timer0_overflowHandler)(void);
static void (*Timer1_compAMatchHandler)(void);
static void (*Timer1_compBMatchHandler)(void);
static void (*Timer1_overflowHandler)(void);
static void (*Timer1_captureHandler)(void);
static void (*Timer2_compAMatchHandler)(void);
static void (*Timer2_compBMatchHandler)(void);
static void (*Timer2_overflowHandler)(void);

void Timer0_init(Timer_MatchModeA matchA, Timer_MatchModeB matchB,
                    Timer0_PulseMode wgm, Timer_Prescaler p)  {
	TCCR0A = (matchA << 6) | (matchB << 4) | (wgm & 0b0011);
	TCCR0B = ((wgm & 0b0100) << 1) | p;
	if(matchA != Timer_A_NONE) {
		DDRD |= _BV(PD6);
	}
	if(matchB != Timer_B_NONE) {
		DDRD |= _BV(PD5);
	}
}

void Timer1_init(Timer_MatchModeA matchA, Timer_MatchModeB matchB,
                    Timer1_PulseMode wgm, Timer_Prescaler p) {
	TCCR1A = (matchA << 6) | (matchB << 4) | (wgm & 0b0011);
	TCCR1B = ((wgm & 0b1100) << 1) | p;
	if(matchA != Timer_A_NONE) {
		DDRB |= _BV(PB1);
	}
	if(matchB != Timer_B_NONE) {
		DDRB |= _BV(PB2);
	}
}

void Timer2_init(Timer_MatchModeA matchA, Timer_MatchModeB matchB,
                    Timer2_PulseMode wgm, Timer_Prescaler p) {
	TCCR2A = (matchA << 6) | (matchB << 4) | (wgm & 0b0011);
	TCCR2B = ((wgm & 0b0100) << 1) | p;
	if(matchA != Timer_A_NONE) {
		DDRB |= _BV(PB3);
	}
	if(matchB != Timer_B_NONE) {
		DDRD |= _BV(PD3);
	}
}

void Timer0_setTimerInterruptEnable(Timer0_InterruptMask mask) {
	TIMSK0 = mask;
}

void Timer1_setTimerInterruptEnable(Timer1_InterruptMask mask) {
	TIMSK1 = mask;
}

void Timer2_setTimerInterruptEnable(Timer2_InterruptMask mask) {
	TIMSK2 = mask;
}

void Timer0_setTimerCounter(uint8_t count) {
	TCNT0 = count;
}

void Timer1_setTimerCounter(uint16_t count) {
	TCNT1 = count;
}

void Timer2_setTimerCounter(uint8_t count) {
	TCNT2 = count;
}

void Timer0_setTimerACriteria(uint8_t criteriaValue) {
	OCR0A = criteriaValue;
}

void Timer0_setTimerBCriteria(uint8_t criteriaValue) {
	OCR0B = criteriaValue;
}

void Timer1_setTimerACriteria(uint16_t criteriaValue) {
	OCR1AH = (criteriaValue >> 8) &0x00FF;
	OCR1AL = criteriaValue &0x00FF;
}

void Timer1_setTimerBCriteria(uint16_t criteriaValue) {
	OCR1BH = (criteriaValue >> 8) &0x00FF;
	OCR1BL = criteriaValue &0x00FF;
}

void Timer1_setTimerCaptureCriteria(uint16_t criteriaValue) {
	ICR1 = criteriaValue;
}

void Timer2_setTimerACriteria(uint8_t criteriaValue) {
	OCR2A = criteriaValue;
}

void Timer2_setTimerBCriteria(uint8_t criteriaValue) {
	OCR2B = criteriaValue;
}

void Timer0_setOverflowHandler(void (*func)(void)) {
	Timer0_overflowHandler = func;
}

void Timer0_setMatchAHandler(void (*func)(void)) {
	Timer0_compAMatchHandler = func;
}

void Timer0_setMatchBHandler(void (*func)(void)) {
	Timer0_compBMatchHandler = func;
}

void Timer1_setOverflowHandler(void (*func)(void)) {
	Timer1_overflowHandler = func;
}

void Timer1_setMatchAHandler(void (*func)(void)) {
	Timer1_compAMatchHandler = func;
}

void Timer1_setMatchBHandler(void (*func)(void)) {
	Timer1_compBMatchHandler = func;
}

void Timer1_setCaptureHandler(void (*func)(void)) {
	Timer1_captureHandler = func;
}

void Timer2_setOverflowHandler(void (*func)(void)) {
	Timer2_overflowHandler = func;
}

void Timer2_setMatchAHandler(void (*func)(void)) {
	Timer2_compAMatchHandler = func;
}

void Timer2_setMatchBHandler(void (*func)(void)) {
	Timer2_compBMatchHandler = func;
}

ISR(TIMER0_OVF_vect) {
	Timer0_overflowHandler();	
}

ISR(TIMER0_COMPA_vect) {
	Timer0_compAMatchHandler();
}

ISR(TIMER0_COMPB_vect) {
	Timer0_compBMatchHandler();
}

ISR(TIMER1_OVF_vect) {
	Timer1_overflowHandler();
}
ISR(TIMER1_COMPA_vect) {
	Timer1_compAMatchHandler();
}
ISR(TIMER1_COMPB_vect) {
	Timer1_compBMatchHandler();
}
ISR(TIMER1_CAPT_vect) {
	Timer1_captureHandler();
}

ISR(TIMER2_OVF_vect) {
	Timer2_overflowHandler();
}

ISR(TIMER2_COMPA_vect) {
	Timer2_compAMatchHandler();
}

ISR(TIMER2_COMPB_vect) {
	Timer2_compBMatchHandler();
}