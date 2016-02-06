/*
 * ServoMotor.h
 *
 * Created: 2012/03/07 23:59:43
 *  Author: hirokazu
 */ 


#ifndef SERVOMOTOR_H_
#define SERVOMOTOR_H_

#include <avr/io.h>

typedef enum ServoMotor_Selector0 {
	ServoMotor_0A = 1,
	ServoMotor_0B = 2
} ServoMotor_Selector0;


typedef enum ServoMotor_Selector1 {
	ServoMotor_1A = 1,
	ServoMotor_1B = 2
} ServoMotor_Selector1;



/** サーボモータ向け出力の１周期カウント値 */
static const uint16_t ServoMotor_ICR_TOP = 18000;

/** GWS Micro 2BBMGサーボモータの最大角度のパルス幅 */
static const uint16_t ServoMotor_GWSMICRO_2BBMG_MAX = 2050;
/** GWS Micro 2BBMGサーボモータの最小角度のパルス幅 */
static const uint16_t ServoMotor_GWSMICRO_2BBMG_MIN = 470;
/** GWS Micro 2BBMGサーボモータ向けの比例定数(16bitタイマ向け) */
static const float ServoMotor_GWSMICRO_2BBMG_CONSTANT = 8.7;
/** GWS Micro 2BBMGサーボモータ向けの比例定数(8bitタイマ向け) */
static const float ServoMotor_GWSMICRO_2BBMG_CONSTANT_8BIT = 0.13;


/** TowerPro MG995サーボモータの最大角度のパルス幅 */
static const uint16_t ServoMotor_MG995_MAX = 2940;
/** TowerPro MG995サーボモータの最小角度のパルス幅 */
static const uint16_t ServoMotor_MG995_MIN = 750;
/** TowerPro MG995サーボモータ向けの比例定数(16bitタイマ向け) */
static const float ServoMotor_MG995_CONSTANT = 10.4;
/** TowerPro MG995サーボモータ向けの比例定数(8bitタイマ向け) */
static const float ServoMotor_MG995_CONSTANT_8BIT = 0.16;


/** GWS PICO STDサーボモータの最大角度のパルス幅 */
static const uint16_t ServoMotor_GWSPICO_STD_MAX = 2160;
/** GWS PICO STDサーボモータの最小角度のパルス幅 */
static const uint16_t ServoMotor_GWSPICO_STD_MIN = 760;
/** GWS PICO STDサーボモータの最大角度のパルス幅 */
static const float ServoMotor_GWSPICO_STD_CONSTANT = 7.7;
/** GWS PICO STDサーボモータの最大角度のパルス幅 */
static const float ServoMotor_GWSPICO_STD_CONSTANT_8BIT = 0.12;


/**
 * サーボモータの電源をオンにします。
 */
void ServoMotor_onPower();
	
/**
 * サーボモータの電源をオフにします。
 */	
void ServoMotor_offPower();
	
	
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
void ServoMotor_init0(ServoMotor_Selector0 s, uint16_t min, uint16_t max, float p);


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
void ServoMotor_init1(ServoMotor_Selector1 s, uint16_t min, uint16_t max, float p);



/**
 * タイマ0Aのサーボモータを回転させます。角度指定
 * @param angle 角度(０度から１８０度)
 *
 * @return 出力したパルスのデューティ比
 */
uint8_t ServoMotor_turn0A(uint8_t angle);

/**
 * タイマ0Bのサーボモータを回転させます。角度指定
 * @param angle 角度(０度から１８０度)
 * @return 出力したパルスのデューティ比
 */
uint8_t ServoMotor_turn0B(uint8_t angle);

/**
 * タイマ1Aのサーボモータを回転させます。角度指定
 * @param angle 角度(0-180)
 * @return 出力したデューティ比
 */
uint16_t ServoMotor_turn1A(uint8_t angle);

/**
 * タイマ1Bのサーボモータを回転させます。角度指定
 * @param angle 角度(0-180)
 * @return 出力したデューティ比
 */
uint16_t ServoMotor_turn1B(uint8_t angle);



#endif /* SERVOMOTOR_H_ */