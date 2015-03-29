/** AD変換のためのライブラリです。AVR atmega88P, atmega168P互換のマイコン向けに作成
 * されています。
 *
 * @file ADCoverter.h
 *
 *  AD変換のライブラリ mega88p/mega168p向け
 *
 * @namespace ADC
 * @date 2012/01/01 20:49:53
 *  author hirokazu yokoyama, Gifu university Robocon circle
 */


#ifndef ADCOVERTER_H_
#define ADCOVERTER_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "grobo.h"

/**
 * ＡＤ変換の基準電圧を指定するための列挙体
 */
typedef enum ADC_ReferenceVoltage{
	/** AREFピンの外部電圧を基準にします。*/
	ADC_AREF = 0b00,
	/** AVCCの外部電圧を基準にします(AREFにデカップ用コンデンサ使用可) */
	ADC_AVCC = 0b01,
	/** 内部1.1Vを基準電圧にします(AREFにデカップ用コンデンサ使用可) */
	ADC_INNER = 0b11
} ADC_ReferenceVoltage;

/**
 * AD変換での入力値の揃えの列挙体
 */
typedef enum ADC_Align {
	/** 右寄せ */
	ADC_RIGHT = 0,
	/** 左寄せ */
	ADC_LEFT = 1
} ADC_Align;

/**
 * AD変換プリンスケーラ(分周値)の列挙体
 */
typedef enum ADC_Prescaler {
	/** clock / 2 */
	ADC_PRESCALER_2 = 0b001,
	/** clock / 4 */
	ADC_PRESCALER_4 = 0b010,
	/** clock / 8 */
	ADC_PRESCALER_8 = 0b011,
	/** clock / 16 */
	ADC_PRESCALER_16 = 0b100,
	/** clock / 32 */
	ADC_PRESCALER_32 = 0b101,
	/** clock / 64 */
	ADC_PRESCALER_64 = 0b110,
	/** clock / 128 */
	ADC_PRESCALER_128 = 0b111
} ADC_Prescaler;

/**
 * AD変換の自動実行の選択
 */
typedef enum ADC_LaunchedFrom {
	/** 連続変換動作 */
	ADC_CONTINUOUS = 0b000,
	/** アナログ比較器 */
	ADC_ANALOG_COMPARE = 0b001,
	/** 外部割り込み要求 */
	ADC_EXTERNAL_INTERRUPT = 0b010,
	/** タイマ・カウンタ0比較A一致*/
	ADC_TIMER0A_COMPARE = 0b011,
	/** タイマ・カウンタのオーバーフロー */
	ADC_TIMER0_OVERFLOW = 0b100,
	/** タイマ・カウンタ1比較B一致 */
	ADC_TIMER1B_COMPARE = 0b101,
	/** タイマ・カウンタ1オーバーフロー */
	ADC_TIMER1B_OVERFLOW = 0b110,
	/** タイマ・カウンタ1捕獲要求 */
	ADC_TIMER1B_CAPTURE = 0b111
} ADC_LaunchedFrom;

/**
 * AD変換用レジスタを初期化します。AD変換を開始するにはADC_start()または
 * ADC_startAutomaticLaunch()を実行してください。
 * @param usedPin AD変換に使用するピン(PC0からPC5の中から一つを指定)
 * @param rv 基準電圧をどれにするかを指定(ADC_ReferenceVoltage列挙体から一つを選択)
 * @param align 10bitの入力値を左寄せ(LEFT)にするか右寄せ(RIGHT)にするかを指定
 * @param is 割り込みを許可するかしないか(別途sei()で割り込み許可を剃る必要あり)
 * @param p プリスケーラ(分周比をADC_Prescaler列挙体の中から選択)
 */
void ADC_init(unsigned char usedPin, ADC_ReferenceVoltage rv, ADC_Align align,
                InterruptSwitch is, ADC_Prescaler p);


/**
 * AD変換を１回だけ行います。事前にADC_init()で初期化する必要があります。
 */
void ADC_start();

/**
 * AD変換の自動起動を設定します。事前にADC_init()で初期化する必要があります。
 * また自動起動を停止するにはADC_stopAutomaticLaunch()を実行してください。
 * @param launchedFrom 自動起動の開始元
 */
void ADC_startAutomaticLaunch(ADC_LaunchedFrom launchedFrom);

/**
 * AD変換の自動起動を停止します。再開するにはADC_startAutomaticLaunch()を実行してください。
 */
void ADC_stopAutomaticLaunch();


/**
 * AD変換による入力値の上位ビットを返します。
 */
unsigned char ADC_getADCH();

/**
 * AD変換による入力値の下位ビットを返します。
 */
unsigned char ADC_getADCL();

/**
 * AD変換完了時の割り込みで実行する関数を指定します。
 * @param *func 実行する関数のポインタ
 */
void ADC_setInterruptListener(void (*func)(void));


#endif /* ADCOVERTER_H_ */