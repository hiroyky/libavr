/** 外部割り込みをかんたんに行うためのライブラリです。AVR atmega88P,atmega168P互換
 * のマイコン向けに作成されています。
 *
 * @file ExternalInterrupt.h
 * 外部割り込みのためのライブラリ
 *
 * mega88p/mega168p向け
 *
 * @namespace External
 * @date 2012/01/06 22:41:56
 * @author hirokazu yokoyama
 */


#ifndef EXTERNALINTERRUPT_H_
#define EXTERNALINTERRUPT_H_

/**
 * INT0,INT1外部割り込みの発生条件
 */
typedef enum External_Condition {
	/** Lowレベルで発生 */
	External_LOW = 0b00,
	/** 変化時に発生 */
	External_CHANGE = 0b01,
	/** 下降端で発生 */
	External_FALLING_EDGE = 0b10,
	/** 上昇端で発生 */
    External_RISING_EDGE = 0b11
} External_Condition;

/**
 * INT0(PD2)外部割り込みのために初期化します。
 * このINT0ピンとINT1ピンの外部割り込みは割り込みの発生条件を設定できます
 * 発生条件をExternal_Condtion列挙体で定義された値を引数で与えてください。
 * この関数を実行してINT0を外部割り込みのために初期化すると共に、
 * External_setINT0Event(*func)でINT0外部割り込み時に実行する関数を設定してください。
 * そして、割り込みを実行するには別途sei()で割り込みを許可する必要があります。 
 * @param c 割り込みの発生条件
 *
 * *-- 使用例 --*
 *
 * // INT0外部割り込みを立ち上がりに実行で初期化する
 * External_init0(External_RISING_EDGE);
 *
 * // INT0外部割り込み発生時に実行する関数funcを設定する
 * External_setINT0Event(*func);
 *
 * //割り込みを許可
 * sei();
 */
void External_initINT0(External_Condition c);


/**
 * INT1(PD3)外部割り込みのために初期化します。
 * このINT0ピンとINT1ピンの外部割り込みは割り込みの発生条件を設定できます
 * 発生条件をExternal_Condtion列挙体で定義された値を引数で与えてください。
 * この関数を実行してINT1を外部割り込みのために初期化すると共に、
 * External_setINT1Event(*func)でINT0外部割り込み時に実行する関数を設定してください。
 * そして、割り込みを実行するには別途sei()で割り込みを許可する必要があります。 
 * @param c 割り込みの発生条件
 *
 * *-- 使用例 --*
 *
 * // INT1外部割り込みを立ち上がりに実行で初期化する
 * External_init1(External_RISING_EDGE);
 *
 * // INT0外部割り込み発生時に実行する関数funcを設定する
 * External_setINT1Event(*func);
 *
 * //割り込みを許可
 * sei();
 */
void External_initINT1(External_Condition c);


/**
 * PCINT0(PCINT0~PCINT7)の外割り込み(変化時に割り込み)のために初期化します。
 * PCINT0からPCINT7の内、割り込みを許可するピンを引数に指定します。
 * PCINTxの外部割り込みは割り込みの発生条件を設定することはできません。
 * PCINTxの外部割り込みは立ち上がり、立下りの両方で発生します。
 * この関数を実行してPCINT0外部割り込みを初期化すると共に、
 * External_setPCINT0Handler(*func)で割り込み時に実行する関数を指定してください。
 * (PCINT0~PCINT7の割り込み時の動作は共通になります。個別に指定することはできません)
 * また、割り込みを実行するには別途sei()で割り込みを許可する必要があります。
 * @param mask 割り込み許可するピンを1にする
 *              [PCINT7|PCINT6|PCINT5|PCINT4|PCINT3|PCINT2|PCINT1|PCINT0|]
 */
void External_initPCINT0(unsigned char mask);


/**
 * PCINT1(PCINT8~PCINT14)の外部割り込み(変化時に割り込み)のために初期化します。
 * PCINT8からPCINT14の内、割り込みを許可するピンをパラメータに指定します。
 * PCINTxの外部割り込みは割り込みの発生条件を設定することはできません。
 * PCINTxの外部割り込みは立ち上がり、立下りの両方で発生します。
 * この関数を実行してPCINT1外部割り込みを初期化すると共に、
 * External_setPCINT1Handler(*func)で割り込み時に実行する関数を指定してください。
 * (PCINT8~PCINT14の割り込み時の動作は共通になります。個別に指定することはできません)
 * また、割り込みを実行するには別途sei()で割り込みを許可する必要があります。

 * @param mask 割り込み許可するピンを1にする
 *              [-|PCINT14|PCINT13|PCINT12|PCINT11|PCINT10|PCINT9|PCINT8|]
 */
void External_initPCINT1(unsigned char mask);


/**
 * PCINT2(PCINT16~PCINT23)の外部割り込み(変化時に割り込み)のために初期化します。
 * PCINT16からPCINT23の内、割り込みを許可するピンをパラメータに指定します。
 * PCINTxの外部割り込みは割り込みの発生条件を設定することはできません。
 * PCINTxの外部割り込みは立ち上がり、立下りの両方で発生します。
 * この関数を実行してPCINT2外部割り込みを初期化すると共に、
 * External_setPCINT2Handler(*func)で割り込み時に実行する関数を指定してください。
 * (PCINT16~PCINT23の割り込み時の動作は共通になります。個別に指定することはできません)
 * また、割り込みを実行するには別途sei()で割り込みを許可する必要があります。
 * @param mask 割り込み許可するピンを1にする
 *              [PCINT23|PCINT22|PCINT21|PCINT20|PCINT19|PCINT18|PCINT17|PCINT16|]
 */
void External_initPCINT2(unsigned char mask);


/**
 * INT0外部割り込み時に実行する関数を設定します。
 * @param *func 実行する関数のポインタ
 */
void External_setINT0Handler(void (*func)(void));


/**
 * INT1外部割り込み時に実行する関数を設定します。
 * @param *func 実行する関数のポインタ
 */
void External_setINT1Handler(void (*func)(void));


/**
 * PCINT0外部割り込み時に実行する関数を設定します。
 * @param *func 実行する関数のポインタ
 */
void External_setPCINT0Handler(void (*func)(void));


/**
 * PCINT1外部割り込み時に実行する関数を設定します。
 * @param *func 実行する関数のポインタ
 */
void External_setPCINT1Handler(void (*func)(void));


/**
 * PCINT2外部割り込み時に実行する関数を設定します。
 * @param *func 実行する関数のポインタ
 */
void External_setPCINT2Handler(void (*func)(void));


#endif /* EXTERNALINTERRUPT_H_ */