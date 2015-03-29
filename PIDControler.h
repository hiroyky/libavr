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
* PID制御を行うための操作量を算出して返します。
* @param sensor センサ値(現状の値)
* @param tagret 目標値
* @param kp 比例制御の定数
* @param ki 積分制御の定数
* @param kd 微分制御の定数
* @param dtime 処理周期
* @param _min 最小値
* @param _max 最大値
* @return 操作量
*/
int PID_control(int sensor, int target, int kp, int ki, int kd, int dtime, int _min, int _max);

#endif /* PIDCONTROLER_H_ */