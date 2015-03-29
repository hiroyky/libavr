/*
 * ServoMotor.c
 *
 * Created: 2012/03/08 0:00:03
 *  Author: hirokazu
 */ 

#include <avr/io.h>
#include "timer.h"
#include "ServoMotor.h"


static uint8_t ServoMotor_getAngleDuty0(uint8_t angle);
static uint16_t ServoMotor_getAngleDuty1(uint8_t angle);

static float ServoMotor_proportionalConstant0 = 0.13;
static float ServoMotor_proportionalConstant1 = 8;
static uint16_t ServoMotor_maxPulse0 = 32;
static uint16_t ServoMotor_minPulse0 = 10;
static uint16_t ServoMotor_maxPulse1 = 2200;
static uint16_t ServoMotor_minPulse1 = 500;



/**
 * �T�[�{���[�^�̓d�����I���ɂ��܂��B
 */
void ServoMotor_onPower() {
	DDRD |= _BV(PD0);
	PORTD |= _BV(PD0);
}
	
/**
 * �T�[�{���[�^�̓d�����I�t�ɂ��܂��B
 */	
void ServoMotor_offPower() {
	PORTD &= ~_BV(PD0);
}
	
	
/**
 * �^�C�}�E�J�E���^0���T�[�{���[�^�����ɏ��������܂��B
 * ���S�̂��߂ɏ���������O�ɃT�[�{���[�^�̊p�x��ServoMotor_turn0A()
 * �y��ServoMotor_turn0B()�Ŏw�肵�Ă��炱������s���Ă��������B
 *
 * @param s �T�[�{���[�^�����ɏ���������^�C�}�E�J�E���^���w��
 * @param min �p�x0�x�ɂ�����p���X��High�̕�(�}�C�N���b)
 * @param max �p�x180�x�ɂ�����p���X��High�̕�(�}�C�N���b)
 * @param p �p�x(0�x����180�x)����o�͂���f���[�e�B�[����v�Z����Ƃ��ɕK�v�Ȕ��萔(8bit��)
 */
void ServoMotor_init0(ServoMotor_Selector0 s, uint16_t min, uint16_t max, float p) {
	// �ʑ�PWM,64������
	switch(s) {
		case ServoMotor_0A:
		    Timer0_init(Timer_A_LOW_AT_COMPARE_MATCH, Timer_B_NONE,
	                    Timer0_8BIT_FIRST_PWM, Timer_PRESCALER_64);
		    break;
		case ServoMotor_0B:
		    Timer0_init(Timer_A_NONE, Timer_B_LOW_AT_COMPARE_MATCH,
	                    Timer0_8BIT_FIRST_PWM, Timer_PRESCALER_64);
		    break;
		case ServoMotor_0A | ServoMotor_0B:
		    Timer0_init(Timer_A_LOW_AT_COMPARE_MATCH, Timer_B_LOW_AT_COMPARE_MATCH,
	                    Timer0_8BIT_FIRST_PWM, Timer_PRESCALER_64);
		    break;
	}

	// �^�C�}�E�J�E���^0��64�����œ��삳���邽��64�Ŋ������l��ێ�����B
    ServoMotor_maxPulse0 = max >> 6;
	ServoMotor_minPulse0 = min >> 6;
	ServoMotor_proportionalConstant0 = p;
}


/**
 * �T�[�{���[�^�����Ƀ^�C�}�P�����������܂��B
 * ���S�̂��߂ɏ���������O�ɃT�[�{���[�^�̊p�x��ServoMotor_turn1A()
 * �y��ServoMotor_turn1B()�Ŏw�肵�Ă��炱������s���Ă��������B
 *
 * @param s PWM���삳����^�C�}�P�o�̓s��(ServoMotor_1A, ServoMotor_1B)
 * @param min �p�x0�x�ɂ�����p���X��High�̕�(�}�C�N���b)
 * @param max �p�x180�x�ɂ�����p���X��High�̕�(�}�C�N���b)
 * @param p �p�x(0�x����180�x)����o�͂���f���[�e�B�[����v�Z����Ƃ��ɕK�v�Ȕ��萔(8bit��)
 */
void ServoMotor_init1(ServoMotor_Selector1 s, uint16_t min, uint16_t max, float p) {
	Timer1_setTimerCaptureCriteria(ServoMotor_ICR_TOP);

	switch (s) {
		case ServoMotor_1A:
		    Timer1_init(Timer_A_LOW_AT_COMPARE_MATCH, Timer_B_NONE, Timer1_FIRST_PWM_ICR, Timer_PRESCALER_NONE);
			break;
		case ServoMotor_1B:
		    Timer1_init(Timer_A_NONE, Timer_B_LOW_AT_COMPARE_MATCH, Timer1_FIRST_PWM_ICR, Timer_PRESCALER_NONE);
			break;
		case ServoMotor_1A | ServoMotor_1B:
		    Timer1_init(Timer_A_LOW_AT_COMPARE_MATCH, Timer_B_LOW_AT_COMPARE_MATCH, Timer1_FIRST_PWM_ICR, Timer_PRESCALER_NONE);
			break;
        default:
		    // �^�C�}��~
		    Timer1_init(Timer_A_NONE, Timer_B_NONE, Timer1_PULSE_NONE, Timer_PRESCALER_NONE);
	}
	ServoMotor_maxPulse1 = max;
	ServoMotor_minPulse1 = min;
	ServoMotor_proportionalConstant1 = p;
}



/**
 * �^�C�}0A�̃T�[�{���[�^����]�����܂��B�p�x�w��
 * @param angle �p�x(�O�x����P�W�O�x)
 *
 * @return �o�͂����p���X�̃f���[�e�B��
 */
uint8_t ServoMotor_turn0A(uint8_t angle) {
	uint8_t duty = ServoMotor_getAngleDuty0(angle);
	Timer0_setTimerACriteria(duty);
	return duty;
}

/**
 * �^�C�}0B�̃T�[�{���[�^����]�����܂��B�p�x�w��
 * @param angle �p�x(�O�x����P�W�O�x)
 * @return �o�͂����p���X�̃f���[�e�B��
 */
uint8_t ServoMotor_turn0B(uint8_t angle) {
	uint8_t duty = ServoMotor_getAngleDuty0(angle);
	Timer0_setTimerBCriteria(duty);
	return duty;
}


/**
 * �^�C�}1A�̃T�[�{���[�^����]�����܂��B�p�x�w��
 * @param angle �p�x(0-180)
 * @return �o�͂����f���[�e�B��
 */
uint16_t ServoMotor_turn1A(uint8_t angle) {
	uint16_t duty = ServoMotor_getAngleDuty1(angle);
	Timer1_setTimerACriteria(duty);
	return duty;
}

/**
 * �^�C�}1B�̃T�[�{���[�^����]�����܂��B�p�x�w��
 * @param angle �p�x(0-180)
 * @return �o�͂����f���[�e�B��
 */
uint16_t ServoMotor_turn1B(uint8_t angle) {
	uint16_t duty = ServoMotor_getAngleDuty1(angle);
	Timer1_setTimerBCriteria(duty);
	return duty;
}

/**
 *
 */
static uint8_t ServoMotor_getAngleDuty0(uint8_t angle) {
	if(angle > 180) {
		angle = 180;
	}
    uint8_t p = angle * ServoMotor_proportionalConstant0 + ServoMotor_minPulse0;

	// 臒l���Ɏ��܂��Ă��邩���m�F
	if(p > ServoMotor_maxPulse0) {
        p = ServoMotor_maxPulse0;
	} else if (p < ServoMotor_minPulse0){
        p = ServoMotor_minPulse0;
	}
	return p;
}

/**
 * �p���[���^�Ŏw�肳�ꂽ�p�x����������^�C�}�E�J�E���^1����o�͂��ׂ��f���[�e�B���
 * ���܂��B
 * @param �p�x(0-180)
 * @return �f���[�e�B��
 */
static uint16_t ServoMotor_getAngleDuty1(uint8_t angle) {
	if(angle > 180) {
		angle = 180;
	}
    uint16_t p = angle * ServoMotor_proportionalConstant1 + ServoMotor_minPulse1;

	// 臒l���Ɏ��܂��Ă��邩���m�F
	if(p > ServoMotor_maxPulse1) {
        p = ServoMotor_maxPulse1;
	} else if (p < ServoMotor_minPulse1){
        p = ServoMotor_minPulse1;
	}
	return p;
}