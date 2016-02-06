/*
 * PWM.c
 *
 * Created: 2012/03/07 18:04:08
 *  Author: hirokazu
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "PWM.h"

/**
 * タイマー0をPWM用に初期化します。
 * @param wgm タイマーの動作モード(wgm2,wgm1,wgm0)
 * @param p プリンスケーラ
 * @param matchA 出力Aのモード
 * @param matchB 出力Bのモード
 */
void PWM_initTimer0(unsigned char wgm, PWM_Prescaler p, 
                    PWM_MatchModeA matchA, PWM_MatchModeB matchB) {
	DDRD |= (_BV(PD5) | _BV(PD6));	
	OCR0A = 0x00;
	OCR0B = 0x00;
    TCCR0A = (matchA << 6) | (matchB << 4) | (wgm & 0b0011);	
	TCCR0B = ((wgm & 0b0100) << 1) | p;	
}

/**
 * タイマー1をPWM用に初期化します。
 * @param wgm タイマーの動作モード(wgm3,wgm2,wgm1,wgm0)
 * @param p プリンスケーラ
 * @param matchA 出力Aのモード
 * @param matchB 出力Bのモード
 */
void PWM_initTimer1(unsigned char wgm, PWM_Prescaler p, 
                    PWM_MatchModeA matchA, PWM_MatchModeB matchB) {
    DDRB |= (_BV(PB1) | _BV(PB2));
	OCR1A = 0x00;
	OCR1B = 0x00;
	TCCR1A = (matchA << 6) | (matchB << 4) | (wgm & 0b0011);	
	TCCR1B = (wgm & 0b1100) << 1 | p;	
}

/**
 * タイマー2をPWM用に初期化します。
 * @param wgm タイマーの動作モード(wgm2,wgm1,wgm0)
 * @param p プリンスケーラ
 * @param matchA 出力Aのモード
 * @param matchB 出力Bのモード
 */
void PWM_initTimer2(unsigned char wgm, PWM_Prescaler p, 
                    PWM_MatchModeA matchA, PWM_MatchModeB matchB) {
    DDRB |= _BV(PB3);
	DDRD |= _BV(PD3);
	TCCR2A = (matchA << 6) | (matchB << 4) | (wgm & 0b0011);	
	TCCR2B = (wgm & 0b1100) << 1 | p;
	OCR2A = 0x00;
	OCR2B = 0x00;
}


void PWM_setDuty0A(unsigned char duty) {
	OCR0A = duty;
}

void PWM_setDuty0B(unsigned char duty) {
	OCR0B = duty;
}

void PWM_setDuty1A(unsigned int duty) {
	OCR1A = duty;
}

void PWM_setDuty1B(unsigned int duty) {
	OCR1B = duty;
}

void PWM_setDuty2A(unsigned char duty) {
	OCR2A = duty;
}

void PWM_setDuty2B(unsigned char duty) {
	OCR2B = duty;
}