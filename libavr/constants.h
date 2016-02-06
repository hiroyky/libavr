/*
 * constants.h
 *
 * Created: 2/6/2016 8:26:03 PM
 *  Author: hirokazu
 */ 


#ifndef CONSTANTS_H_
#define CONSTANTS_H_

/**
 * 割り込みを許可をする or しない
 */
typedef enum InterruptSwitch {
	/** 割り込みを許可しない */
	INTERRUPT_OFF = 0,
	/** 割り込みを許可する */
	INTERRUPT_ON = 1
} InterruptSwitch;




#endif /* CONSTANTS_H_ */