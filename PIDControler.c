/*
 * PIDControler.c
 *
 * Created: 2012/03/20 19:05:39
 *  Author: hirokazu
 */

#include "PIDControler.h"

static int difference[2];
//static float integral = 0;



int PID_control(int sensor, int target, int kp, int ki, int kd, int dtime, int _min, int _max) {
	difference[0] = difference[1];
	difference[1] = sensor - target;
	//integral += (difference[1] + difference[0]) / 2 * dtime;
	int p = kp * difference[1];
	//float i = ki * integral;
	int d = kd * (difference[1] - difference[0]) / dtime;
	//int val = p + i + d;
	int val = p + d;
	// ç≈ëÂílÅEç≈è¨ílì‡Ç…êßå¿Ç∑ÇÈ
	val = min(val, _min);
	val = max(val, _max);
	return val;
}

int abs(int val){
	if(val < 0) {
		val = val * -1;
	}
	return val;
}

int min(int val, int _min) {
	if(val < _min) {
		val = _min;
	}
	return val;
}

int max(int val, int _max) {
	if(val > _max) {
		val = _max;
	}
	return val;
}