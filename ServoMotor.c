/*
 * ServoMotor.c
 *
 * Created: 2012/03/08 0:00:03
 *  Author: hirokazu
 */ 

#include <avr/io.h>
#include "timer.h"
#include "ServoMotor.h"


static uint8_t ServoMotor_getAngleDuty0(uint8_t angle);
static uint16_t ServoMotor_getAngleDuty1(uint8_t angle);

static float ServoMotor_proportionalConstant0 = 0.13;
static float ServoMotor_proportionalConstant1 = 8;
static uint16_t ServoMotor_maxPulse0 = 32;
static uint16_t ServoMotor_minPulse0 = 10;
static uint16_t ServoMotor_maxPulse1 = 2200;
static uint16_t ServoMotor_minPulse1 = 500;



/**
 * サーボモータの電源をオンにします。
 */
void ServoMotor_onPower() {
	DDRD |= _BV(PD0);
	PORTD |= _BV(PD0);
}
	
/**
 * サーボモータの電源をオフにします。
 */	
void ServoMotor_offPower() {
	PORTD &= ~_BV(PD0);
}
	
	
/**
 * タイマ・カウンタ0をサーボモータ向けに初期化します。
 * 安全のために初期化する前にサーボモータの角度をServoMotor_turn0A()
 * 及びServoMotor_turn0B()で指定してからこれを実行してください。
 *
 * @param s サーボモータ向けに初期化するタイマ・カウンタを指定
 * @param min 角度0度におけるパルスのHighの幅(マイクロ秒)
 * @param max 角度180度におけるパルスのHighの幅(マイクロ秒)
 * @param p 角度(0度から180度)から出力するデューティー比を計算するときに必要な比例定数(8bit時)
 */
void ServoMotor_init0(ServoMotor_Selector0 s, uint16_t min, uint16_t max, float p) {
	// 位相PWM,64分周比
	switch(s) {
		case ServoMotor_0A:
		    Timer0_init(Timer_A_LOW_AT_COMPARE_MATCH, Timer_B_NONE,
	                    Timer0_8BIT_FIRST_PWM, Timer_PRESCALER_64);
		    break;
		case ServoMotor_0B:
		    Timer0_init(Timer_A_NONE, Timer_B_LOW_AT_COMPARE_MATCH,
	                    Timer0_8BIT_FIRST_PWM, Timer_PRESCALER_64);
		    break;
		case ServoMotor_0A | ServoMotor_0B:
		    Timer0_init(Timer_A_LOW_AT_COMPARE_MATCH, Timer_B_LOW_AT_COMPARE_MATCH,
	                    Timer0_8BIT_FIRST_PWM, Timer_PRESCALER_64);
		    break;
	}

	// タイマ・カウンタ0を64分周で動作させるため64で割った値を保持する。
    ServoMotor_maxPulse0 = max >> 6;
	ServoMotor_minPulse0 = min >> 6;
	ServoMotor_proportionalConstant0 = p;
}


/**
 * サーボモータ向けにタイマ１を初期化します。
 * 安全のために初期化する前にサーボモータの角度をServoMotor_turn1A()
 * 及びServoMotor_turn1B()で指定してからこれを実行してください。
 *
 * @param s PWM動作させるタイマ１出力ピン(ServoMotor_1A, ServoMotor_1B)
 * @param min 角度0度におけるパルスのHighの幅(マイクロ秒)
 * @param max 角度180度におけるパルスのHighの幅(マイクロ秒)
 * @param p 角度(0度から180度)から出力するデューティー比を計算するときに必要な比例定数(8bit時)
 */
void ServoMotor_init1(ServoMotor_Selector1 s, uint16_t min, uint16_t max, float p) {
	Timer1_setTimerCaptureCriteria(ServoMotor_ICR_TOP);

	switch (s) {
		case ServoMotor_1A:
		    Timer1_init(Timer_A_LOW_AT_COMPARE_MATCH, Timer_B_NONE, Timer1_FIRST_PWM_ICR, Timer_PRESCALER_NONE);
			break;
		case ServoMotor_1B:
		    Timer1_init(Timer_A_NONE, Timer_B_LOW_AT_COMPARE_MATCH, Timer1_FIRST_PWM_ICR, Timer_PRESCALER_NONE);
			break;
		case ServoMotor_1A | ServoMotor_1B:
		    Timer1_init(Timer_A_LOW_AT_COMPARE_MATCH, Timer_B_LOW_AT_COMPARE_MATCH, Timer1_FIRST_PWM_ICR, Timer_PRESCALER_NONE);
			break;
        default:
		    // タイマ停止
		    Timer1_init(Timer_A_NONE, Timer_B_NONE, Timer1_PULSE_NONE, Timer_PRESCALER_NONE);
	}
	ServoMotor_maxPulse1 = max;
	ServoMotor_minPulse1 = min;
	ServoMotor_proportionalConstant1 = p;
}



/**
 * タイマ0Aのサーボモータを回転させます。角度指定
 * @param angle 角度(０度から１８０度)
 *
 * @return 出力したパルスのデューティ比
 */
uint8_t ServoMotor_turn0A(uint8_t angle) {
	uint8_t duty = ServoMotor_getAngleDuty0(angle);
	Timer0_setTimerACriteria(duty);
	return duty;
}

/**
 * タイマ0Bのサーボモータを回転させます。角度指定
 * @param angle 角度(０度から１８０度)
 * @return 出力したパルスのデューティ比
 */
uint8_t ServoMotor_turn0B(uint8_t angle) {
	uint8_t duty = ServoMotor_getAngleDuty0(angle);
	Timer0_setTimerBCriteria(duty);
	return duty;
}


/**
 * タイマ1Aのサーボモータを回転させます。角度指定
 * @param angle 角度(0-180)
 * @return 出力したデューティ比
 */
uint16_t ServoMotor_turn1A(uint8_t angle) {
	uint16_t duty = ServoMotor_getAngleDuty1(angle);
	Timer1_setTimerACriteria(duty);
	return duty;
}

/**
 * タイマ1Bのサーボモータを回転させます。角度指定
 * @param angle 角度(0-180)
 * @return 出力したデューティ比
 */
uint16_t ServoMotor_turn1B(uint8_t angle) {
	uint16_t duty = ServoMotor_getAngleDuty1(angle);
	Timer1_setTimerBCriteria(duty);
	return duty;
}

/**
 *
 */
static uint8_t ServoMotor_getAngleDuty0(uint8_t angle) {
	if(angle > 180) {
		angle = 180;
	}
    uint8_t p = angle * ServoMotor_proportionalConstant0 + ServoMotor_minPulse0;

	// 閾値内に収まっているかを確認
	if(p > ServoMotor_maxPulse0) {
        p = ServoMotor_maxPulse0;
	} else if (p < ServoMotor_minPulse0){
        p = ServoMotor_minPulse0;
	}
	return p;
}

/**
 * パラーメタで指定された角度を実現するタイマ・カウンタ1から出力すべきデューティを返
 * します。
 * @param 角度(0-180)
 * @return デューティ比
 */
static uint16_t ServoMotor_getAngleDuty1(uint8_t angle) {
	if(angle > 180) {
		angle = 180;
	}
    uint16_t p = angle * ServoMotor_proportionalConstant1 + ServoMotor_minPulse1;

	// 閾値内に収まっているかを確認
	if(p > ServoMotor_maxPulse1) {
        p = ServoMotor_maxPulse1;
	} else if (p < ServoMotor_minPulse1){
        p = ServoMotor_minPulse1;
	}
	return p;
}