/*
 * wait.h
 *
 *  Created on: 2011/01/17
 *  @file   wait.h
 *  @author Hirokazu Yokoyama
 *  @date   2011/01/17
 */

#ifndef WAIT_H_
#define WAIT_H_

#ifndef F_CPU
#define F_CPU 8000000UL
#endif  /* F_CPU */

#include <util/delay.h>

void waitClock(unsigned clock) {
	while(clock) {
		--clock;
	}
}

/**
 * �}�C�N���b�ҋ@
 * @param   usec    �}�C�N���b
 * */
void waitMicrosec(unsigned int usec);

/***
 * �~���b�ҋ@
 * @param   msec    �~���b
 * */
void waitMillisec(unsigned int msec);



#endif /* WAIT_H_ */
