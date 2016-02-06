/**
 * usart.h  AVR AtMega88P / AtMega168P向け
 *
 * USART通信及びFT232RLを使ったPCとのUSBインターフェイスのライブラリ
 * @author Hirokazu Yokoyama
 * @namespace USART
 *
 * Created: 2011/12/23 15:51:38
 *  Author: hirokazu
 */
#ifndef USART_H_
#define USART_H_

#include <avr/io.h>
#include <avr/interrupt.h>

typedef enum USART_InitMode {
	// 通常USART通信
	NOMAL = 0,
	// 送信割り込みを許可でUSART通信初期化
	ALLOW_SEND_INTERRUPT = 1,
	// 受信割り込みを許可でUSART通信初期化
	ALLOW_RECIEVE_INTERRUPT = 2,
	// 送信受信共に割り込みを許可でUSART通信初期化
	ALLOW_SEND_AND_RECIEVE_INTERRUPT = 3
} USART_InitMode;


/**
* USARTを初期化します。
* 必要に応じてUSART_sendBaudrate()でボーレートを設定する必要があります
* @param mode 割り込みを行うかどうかを指定します。
*/
void USART_init(USART_InitMode mode);

/**
* 通信におけるボーレートを指定します。
* レジスタUBRR0H及びUBRR0Lに入力します。値はデータシートを参考にしてください。
* @param highBit UBRR0Hの値
* @param lobBit UBRR0Lの値
* 参考値
*  1MHz動作時：highBit = 0, lowBit = 12
*  8MHz動作時：highBit = 0, lowBit = 104
*/
void USART_setBaudrate(uint8_t highBit, uint8_t lowBit);

void USART_sendData(uint8_t data);

uint8_t USART_recieveData();



void USART_binaryPrintf(unsigned char dat);

void USART_setSendInterruptListener(void (*func)(void));

void USART_setRecieveInterruptListener(void (*func)(uint8_t data));





#endif /* USART_H_ */