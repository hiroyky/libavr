/*
 * wait.c
 *
 * Created: 2012/03/07 22:58:47
 *  Author: hirokazu
 */ 


#include "wait.h"

/**
 * マイクロ秒待機
 * @param   usec    マイクロ秒
 * */
void waitMicrosec(unsigned int usec) {
    while(--usec) {
        _delay_us(1);
    }
}

/***
 * ミリ秒待機
 * @param   msec    ミリ秒
 * */
void waitMillisec(unsigned int msec) {
    while(--msec) {
        _delay_ms(1);
    }
}
