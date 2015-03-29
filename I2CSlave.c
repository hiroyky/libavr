/*
 * I2CSlave.c
 *
 * Created: 2012/03/07 22:26:05
 *  Author: hirokazu
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "I2CSlave.h"

static void (*I2CSlave_initEventListener)(uint8_t dat);
static void (*I2CSlave_receiveEventListener)(uint8_t dat);
static void (*I2CSlave_stopEventListener)(void);
static unsigned char (*I2CSlave_sendEventListener)(void);

static const uint8_t I2CSlave_ENABLE_ACK = (1<<TWEA)|(1<<TWEN);
static const uint8_t I2CSlave_CLEAR_TWINT = (1<<TWEA)|(1<<TWEN)|(1<<TWINT);

unsigned char I2CSlave_isTWINT();

/**
 * I2Cをスレーブで初期化します。
 * 割り込み処理を行う場合は、paramをINTERRUPT_ONを指定し、
 * 別途sei()で割り込み許可を行う必要があります。
 * @param address I2Cスレーブアドレス
 * @param param スレーブ動作を割り込み処理にする場合はINTERRUPT_ONを指定
 */
void I2CSlave_init(unsigned char address, InterruptSwitch param) {
	address <<= 1;
	// address |= 1;    // ジェネラル・コール・アドレス許可
	TWAR = address;
	
	switch(param) {
		case INTERRUPT_ON:
		    TWCR = I2CSlave_ENABLE_ACK | _BV(TWIE);
		    break;
		default:
			case INTERRUPT_OFF:
		    TWCR = I2CSlave_ENABLE_ACK;
		    break;
	}	
}


void I2CSlave_do() {
switch(TWSR) {
		case 0x60:  // CB(W)受信
		    // --- CB(W)受信 ---
            I2CSlave_initEventListener(TWDR);       // CB受信イベントハンドラ
			TWCR = I2CSlave_CLEAR_TWINT;            // INT要求フラグのクリア
		    break;

		case 0x80:  // データ受信
		    // --- スレーブ受信 ---
			I2CSlave_receiveEventListener(TWDR);    // 受信イベントハンドラ
			TWCR = I2CSlave_CLEAR_TWINT;            // INT要求フラグのクリア
		    break;
		 
		case 0xA8:  // CB(R)受信
		    // --- CB(R)受信 ----
			I2CSlave_initEventListener(TWDR);       // CB受信イベントハンドラ
			TWDR = I2CSlave_sendEventListener();    // スレーブ送信イベントハンドラ
			                                        // 送信データ取得
			TWCR = I2CSlave_CLEAR_TWINT;            // INT要求フラグのクリア
		    break;

		case 0xB8:  // データ送信(ACK受信)
		    TWDR = I2CSlave_sendEventListener();    // スレーブ送信イベントハンドラ
			                                        // 送信データ取得
			TWCR = I2CSlave_CLEAR_TWINT;            // INT要求フラグのクリア
		    break;

		case 0xC0:  // データ送信(NOACK受信)　採集データ　スレーブ送信終了

		case 0xA0:  // スレーブ受信中のストップコンディション
			I2CSlave_stopEventListener();
		    TWCR = I2CSlave_CLEAR_TWINT;            // INT要求フラグのクリア
		    break;
	}	
}

/**
 * I2C処理(メインループに入れる)
 * この関数を実行する前にそれぞれのイベントハンドラを設定してください。
 */
void I2CSlave_com() {
    if(!I2CSlave_isTWINT())	{		
		return;
	}    
    I2CSlave_do();	
}

/**
* 割り込み処理 TWSRレジスタが更新されたときに呼び出されます
*/
ISR(TWI_vect) {
	cli();
	I2CSlave_do();
	sei();
}


void I2CSlave_setInitEvent(void (*func)(uint8_t dat)) {
	I2CSlave_initEventListener = func;
}
void I2CSlave_setReceiveEvent(void (*func)(uint8_t dat)) {
	I2CSlave_receiveEventListener = func;
}
void I2CSlave_setStopEvent(void (*func)(void)) {
	I2CSlave_stopEventListener = func;
}
void I2CSlave_setSendEvent(unsigned char (*func)(void)) {
    I2CSlave_sendEventListener = func;
}

/**
 * TWCRレジスタのTWINTビットを返します
 * @return 1 or 0
*/
unsigned char I2CSlave_isTWINT() {
	if((TWCR & (1<<TWINT))) {
		return 1;
	} else {
		return 0;
	}
}