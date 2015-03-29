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
 * マイクロ秒待機
 * @param   usec    マイクロ秒
 * */
void waitMicrosec(unsigned int usec);

/***
 * ミリ秒待機
 * @param   msec    ミリ秒
 * */
void waitMillisec(unsigned int msec);



#endif /* WAIT_H_ */
