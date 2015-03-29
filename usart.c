/*
 * usart.c
 *
 * Created: 2012/03/18 19:00:05
 *  Author: hirokazu
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "usart.h"

static uint8_t (*recieveInterruptListener)(uint8_t data);
static void (*sendInterruptListener)(void);

void USART_init(USART_InitMode mode) {
	// 倍速動作
    UCSR0A |= _BV(U2X0);

	// 送受信許可と割り込み許可設定
    switch (mode) {
		case ALLOW_RECIEVE_INTERRUPT:
		    UCSR0B = _BV(TXEN0) | _BV(RXCIE0) | _BV(RXEN0);
		    break;
		case ALLOW_SEND_INTERRUPT:
		    UCSR0B = _BV(TXEN0) | _BV(UDRIE0) | _BV(RXEN0);
		    break;
		case ALLOW_SEND_INTERRUPT + ALLOW_RECIEVE_INTERRUPT:
		    UCSR0B = _BV(TXEN0) | _BV(RXCIE0) | _BV(RXEN0) | _BV(UDRIE0);
		    break;
		default:
		    UCSR0B = _BV(TXEN0) | _BV(RXEN0);
		    break;
	}

	// ボーレート設定
    //UBRR0H = 0;
	//UBRR0L = 12;    /* 1MHzクロックにて9600bps */
	UBRR0H = 0;
	UBRR0L = 104;

	 //uint16_t b = (F_CPU / (16UL * baud)) - 1;
	 //UBRRH = (uint8_t)(b >> 8);
     //UBRRL = (uint8_t)b;
}

void USART_setBaudrate(uint8_t highBit, uint8_t lowBit) {
    UBRR0H = highBit;
	UBRR0L = lowBit;	
}

void USART_sendData(uint8_t data) {
    loop_until_bit_is_set(UCSR0A, UDRE0);   // UDRE0ビットが1になるまで待機
	UDR0 = data;
}

uint8_t USART_recieveData() {
    loop_until_bit_is_set(UCSR0A, RXC0);

	/*if ((UCSRA & _BV(FE)) || (UCSRA & _BV(DOR))) {
        return -1;
    }*/

	return UDR0;
}


void USART_binaryPrintf(unsigned char dat) {
    for(uint8_t i = 0;i < sizeof(dat);++i) {
        if(dat & 0x01 == 1) {
			printf("1");
		}
		dat >>= 1;
	}
	printf("\n");
}

void USART_setSendInterruptListener(void (*func)(void))  {
    recieveInterruptListener = func;
}

void USART_setRecieveInterruptListener(void (*func)(uint8_t data)) {
    recieveInterruptListener = func;
}

/**
 * 受信割り込み動作
 */
ISR(USART_RX_vect) {
    if(bit_is_clear(UCSR0A, FE0)) {
		//cli();
		recieveInterruptListener(UDR0);
		//sei();
	}
}

/**
 * 送信割り込み動作
 */
ISR(USART_UDRE_vect) {
    sendInterruptListener();
}