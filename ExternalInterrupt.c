/*
 * ExternalInterrupt.c
 *
 * Created: 2012/02/07 20:46:14
 *  Author: hirokazu
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "ExternalInterrupt.h"


// 外部割り込み発生時に実行される関数
static void (*External_INT0handler)(void);
static void (*External_INT1handler)(void);
static void (*External_PCINT0handler)(void);
static void (*External_PCINT1handler)(void);
static void (*External_PCINT2handler)(void);

/**
 * INT0(PD2)外部割り込みのために初期化します。
 * ただし、別途sei()で割り込みを許可する必要があります。
 * また、External_setINT0Event(*func)で外部割り込み時に実行する関数を設定してください。
 * @param c 割り込みの発生条件
 */
void External_initINT0(External_Condition c) {
	EICRA |= c & 0b0011;
	EIMSK |= _BV(INT0);
}

/**
 * INT1(PD3)外部割り込みのために初期化します。
 * ただし、別途sei()で割り込みを許可する必要があります。
 * また、External_setINT1Event(*func)で外部割り込み時に実行する関数を設定してください。
 * @param c 割り込みの発生条件
 */
void External_initINT1(External_Condition c) {
	EICRA |= c << 2;
	EIMSK |= _BV(INT1);
}

/**
 * PCINT0(PCINT0~PCINT7)の外割り込み(変化時に割り込み)のために初期化します。
 * PCINT0からPCINT7の内、割り込みを許可するピンをパラメータに指定します。
 * また、External_setPCINT0Handler(*func)で割り込み時に実行する関数を指定してください。
 * @param mask 割り込み許可するピンを1にする
 *              [PCINT7|PCINT6|PCINT5|PCINT4|PCINT3|PCINT2|PCINT1|PCINT0|]
 */
void External_initPCINT0(unsigned char mask) {
	PCICR |= _BV(PCIE0);
	PCMSK0 = mask;
}

/**
 * PCINT1(PCINT8~PCINT14)の外部割り込み(変化時に割り込み)のために初期化します。
 * PCINT8からPCINT14の内、割り込みを許可するピンをパラメータに指定します。
 * また、External_setPCINT1Handler(*func)で割り込み時に実行する関数を指定してください。
 * @param mask 割り込み許可するピンを1にする
 *              [-|PCINT14|PCINT13|PCINT12|PCINT11|PCINT10|PCINT9|PCINT8|]
 */
void External_initPCINT1(unsigned char mask) {
	PCICR |= _BV(PCIE1);
	PCMSK1 = mask;
}

/**
 * PCINT2(PCINT16~PCINT23)の外部割り込み(変化時に割り込み)のために初期化します。
 * PCINT16からPCINT23の内、割り込みを許可するピンをパラメータに指定します。
 * また、External_setPCINT2Handler(*func)で割り込み時に実行する関数を指定してください。
 * @param mask 割り込み許可するピンを1にする
 *              [PCINT23|PCINT22|PCINT21|PCINT20|PCINT19|PCINT18|PCINT17|PCINT16|]
 */
void External_initPCINT2(unsigned char mask) {
	PCICR |= _BV(PCIE2);
	PCMSK2 = mask;
}

/**
 * INT0外部割り込み時に実行する関数を設定します。
 * @param *func 実行する関数のポインタ
 */
void External_setINT0Handler(void (*func)(void)) {
	External_INT0handler = func;
}

/**
 * INT1外部割り込み時に実行する関数を設定します。
 * @param *func 実行する関数のポインタ
 */
void External_setINT1Handler(void (*func)(void)) {
	External_INT1handler = func;
}

/**
 * PCINT0外部割り込み時に実行する関数を設定します。
 * @param *func 実行する関数のポインタ
 */
void External_setPCINT0Handler(void (*func)(void)) {
	External_PCINT0handler = func;
}

/**
 * PCINT1外部割り込み時に実行する関数を設定します。
 * @param *func 実行する関数のポインタ
 */
void External_setPCINT1Handler(void (*func)(void)) {
	External_PCINT1handler = func;
}

/**
 * PCINT2外部割り込み時に実行する関数を設定します。
 * @param *func 実行する関数のポインタ
 */
void External_setPCINT2Handler(void (*func)(void)) {
	External_PCINT2handler = func;
}

/**
 * INT0が切り替わった時の割り込み動作
 */
ISR(INT0_vect){
    External_INT0handler();
}

/**
 * INT1が切り替わった時の割り込み動作
 */
ISR(INT1_vect) {
	External_INT1handler();
}

/**
 * PCINT0~PCINT7のいずれかが切り替わった時の割り込み動作
 */
ISR(PCINT0_vect) {
	External_PCINT0handler();
}

/**
 * PCINT8~PCINT14のいずれかが切り替わった時の割り込み動作
 */
ISR(PCINT1_vect) {
	External_PCINT1handler();
}

/**
 * PCINT16~PCINT23のいずれかが切り替わった時の割り込み動作
 */
ISR(PCINT2_vect) {
	External_PCINT2handler();
}
