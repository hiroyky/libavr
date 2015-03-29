/*
 * MotorDriver.h
 *
 * Created: 2012/03/07 23:34:19
 *  Author: hirokazu
 */ 


#ifndef MOTORDRIVER_H_
#define MOTORDRIVER_H_

#include "grobo.h"



/**
 * タイマ・カウンタ0をモータドライバのPWM初期化
 * 比較値一致でLow, 8bit高速PWM,プリンスケーラ8分周
 */
void MotorDriver_init0();

/**
 * タイマ・カウンタ1をモータドライバのPWM初期化
 * 比較値一致でLow, 8bit高速PWM,プリンスケーラ8分周 
 */
void MotorDriver_init1();

/**
 * タイマ・カウンタ2をモータドライバのPWM初期化
 * 比較値一致でLow, 8bit高速PWM,プリンスケーラ8分周
 */
void MotorDriver_init2();


/**
 * タイマ・カウンタ0のモータの速さを指定します。
 * @param motorSignal モータ向け信号
 */
void MotorDriver_run0(MotorSignal motorSignal);

/**
 * タイマ・カウンタ1のモータの速さを指定します。
 * @param motorSignal モータ向け信号
 */
void MotorDriver_run1(MotorSignal motorSignal);

#endif /* MOTORDRIVER_H_ */