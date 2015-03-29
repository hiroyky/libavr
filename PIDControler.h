/*
 * PIDControler.h
 *
 * Created: 2012/03/20 19:05:28
 *  Author: hirokazu
 */


#ifndef PIDCONTROLER_H_
#define PIDCONTROLER_H_

#include <avr/io.h>
#include "grobo.h"

int abs(int val);
int min(int val, int _min);
int max(int val, int _max);

/**
* PID������s�����߂̑���ʂ��Z�o���ĕԂ��܂��B
* @param sensor �Z���T�l(����̒l)
* @param tagret �ڕW�l
* @param kp ��ᐧ��̒萔
* @param ki �ϕ�����̒萔
* @param kd ��������̒萔
* @param dtime ��������
* @param _min �ŏ��l
* @param _max �ő�l
* @return �����
*/
int PID_control(int sensor, int target, int kp, int ki, int kd, int dtime, int _min, int _max);

#endif /* PIDCONTROLER_H_ */