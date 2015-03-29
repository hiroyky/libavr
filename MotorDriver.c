/*
 * MotorDriver.c
 *
 * Created: 2012/03/07 23:34:33
 *  Author: hirokazu
 */ 

#include <avr/io.h>
#include "MotorDriver.h"
#include "timer.h"

static const int MotorDriver_STOP = 255;

/**
 * �^�C�}�E�J�E���^0�����[�^�h���C�o��PWM������
 * ��r�l��v��Low, 8bit����PWM,�v�����X�P�[��8����
 */
void MotorDriver_init0() {
	Timer0_setTimerACriteria(MotorDriver_STOP);
	Timer0_setTimerBCriteria(MotorDriver_STOP);
	Timer0_init(Timer_A_HIGH_AT_COMPARE_MATCH, Timer_B_HIGH_AT_COMPARE_MATCH, Timer0_8BIT_FIRST_PWM, Timer_PRESCALER_NONE);	
}

/**
 * �^�C�}�E�J�E���^1�����[�^�h���C�o��PWM������
 * ��r�l��v��Low, 8bit����PWM,�v�����X�P�[��8���� 
 */
void MotorDriver_init1() {
	Timer1_setTimerACriteria(MotorDriver_STOP);
	Timer1_setTimerBCriteria(MotorDriver_STOP);
	Timer1_init(Timer_A_HIGH_AT_COMPARE_MATCH, Timer_B_HIGH_AT_COMPARE_MATCH, Timer1_8BIT_FIRST_PWM, Timer_PRESCALER_NONE);
}

/**
 * �^�C�}�E�J�E���^2�����[�^�h���C�o��PWM������
 * ��r�l��v��Low, 8bit����PWM,�v�����X�P�[��8����
 */
void MotorDriver_init2() {
	Timer2_setTimerACriteria(MotorDriver_STOP);
	Timer2_setTimerBCriteria(MotorDriver_STOP);
	Timer2_init(Timer_A_HIGH_AT_COMPARE_MATCH, Timer_B_HIGH_AT_COMPARE_MATCH, Timer2_8BIT_FIRST_PWM, Timer_PRESCALER_8);
}


/**
 * �^�C�}�E�J�E���^0�̃��[�^�̑������w�肵�܂��B
 * @param motorSignal ���[�^�����M��
 */
void MotorDriver_run0(MotorSignal motorSignal) {
	unsigned char duty = 255 - (motorSignal.speed * 2);
	if(duty > 255) {
	    duty = 255;
	}
	if(motorSignal.direction == FORWARD) {
		Timer0_setTimerACriteria(duty);
		Timer0_setTimerBCriteria(MotorDriver_STOP);
	} else if(motorSignal.direction == BACKWARD) {
		Timer0_setTimerBCriteria(duty);
		Timer0_setTimerACriteria(MotorDriver_STOP);
	}
}

/**
 * �^�C�}�E�J�E���^1�̃��[�^�̑������w�肵�܂��B
 * @param motorSignal ���[�^�����M��
 */
void MotorDriver_run1(MotorSignal motorSignal) {
	unsigned char duty = 255 - (motorSignal.speed * 2);
	if(duty > 255) {
	    duty = 255;
	}
	if(motorSignal.direction == FORWARD) {
		Timer1_setTimerACriteria(duty);
		Timer1_setTimerBCriteria(MotorDriver_STOP);
	} else if(motorSignal.direction == BACKWARD) {
		Timer1_setTimerBCriteria(duty);
		Timer1_setTimerACriteria(MotorDriver_STOP);
	}
}
