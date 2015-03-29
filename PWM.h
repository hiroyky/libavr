/*
 * pwm.h
 *
 * 主にPWMを出力するためのライブラリです。
 * Created: 2011/12/26 15:12:08
 *  Author: hirokazu yokoyama, Gifu University Robocon Cirkle
 */ 
#ifndef PWM_H_
#define PWM_H_

#include "grobo.h"

// タイマのプリンスケーラ(分周比)
typedef enum PWM_Prescaler {
	PWM_PRESCALER_NONE = 0b001,         // 分周なし
    PWM_PRESCALER_8 = 0b010,               // 8分周
    PWM_PRESCALER_64 = 0b011,              // 64分周
    PWM_PRESCALER_256 = 0b100,             // 256分周
    PWM_PRESCALER_1024 = 0b101,            // 1024分周
    PWM_PRESCALER_OUTSIDE_UNDER = 0b110,   // 外部クロック(下降)
    PWM_PRESCALER_OUTSIDE_OVER = 0b111     // 外部クロック(上昇)	
} PWM_Prescaler;

typedef enum PWM_MatchModeA {
	// Low, High交互出力
	PWMA_ALTERNATE = 0b01,  
	// 比較一致でLow, BOTTOMでHigh          
	PWMA_BOTTOM_HIGH = 0b10,
	// 比較一致でHigh, BOTTOMでLow
	PWMA_BOTTOM_LOW = 0b11
} PWM_MatchModeA;

typedef enum PWM_MatchModeB {
	// 比較一致でLow, BOTTOMでHigh
	PWMB_BOTTOM_HIGH = 0b10,
	// 比較一致でHigh, BOTTOMでLow	
	PWMB_BOTTOM_LOW = 0b11
} PWM_MatchModeB;

/**
 * タイマー0をPWM用に初期化します。
 * @param wgm タイマーの動作モード(wgm2,wgm1,wgm0)
 * @param p プリンスケーラ
 * @param matchA 出力Aのモード
 * @param matchB 出力Bのモード
 */
void PWM_initTimer0(unsigned char wgm, PWM_Prescaler p, 
                    PWM_MatchModeA matchA, PWM_MatchModeB matchB);

/**
 * タイマー1をPWM用に初期化します。
 * @param wgm タイマーの動作モード(wgm3,wgm2,wgm1,wgm0)
 * @param p プリンスケーラ
 * @param matchA 出力Aのモード
 * @param matchB 出力Bのモード
 */
void PWM_initTimer1(unsigned char wgm, PWM_Prescaler p, 
                    PWM_MatchModeA matchA, PWM_MatchModeB matchB);

/**
 * タイマー2をPWM用に初期化します。
 * @param wgm タイマーの動作モード(wgm2,wgm1,wgm0)
 * @param p プリンスケーラ
 * @param matchA 出力Aのモード
 * @param matchB 出力Bのモード
 */
void PWM_initTimer2(unsigned char wgm, PWM_Prescaler p, 
                    PWM_MatchModeA matchA, PWM_MatchModeB matchB);

void PWM_setDuty0A(unsigned char duty);

void PWM_setDuty0B(unsigned char duty);

void PWM_setDuty1A(unsigned int duty);

void PWM_setDuty1B(unsigned int duty);

void PWM_setDuty2A(unsigned char duty);

void PWM_setDuty2B(unsigned char duty);

#endif /* PWM_H_ */