/*
 * wait.c
 *
 * Created: 2012/03/07 22:58:47
 *  Author: hirokazu
 */ 


#include "wait.h"

/**
 * �}�C�N���b�ҋ@
 * @param   usec    �}�C�N���b
 * */
void waitMicrosec(unsigned int usec) {
    while(--usec) {
        _delay_us(1);
    }
}

/***
 * �~���b�ҋ@
 * @param   msec    �~���b
 * */
void waitMillisec(unsigned int msec) {
    while(--msec) {
        _delay_ms(1);
    }
}
