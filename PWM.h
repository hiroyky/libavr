/*
 * pwm.h
 *
 * ���PWM���o�͂��邽�߂̃��C�u�����ł��B
 * Created: 2011/12/26 15:12:08
 *  Author: hirokazu yokoyama, Gifu University Robocon Cirkle
 */ 
#ifndef PWM_H_
#define PWM_H_

#include "grobo.h"

// �^�C�}�̃v�����X�P�[��(������)
typedef enum PWM_Prescaler {
	PWM_PRESCALER_NONE = 0b001,         // �����Ȃ�
    PWM_PRESCALER_8 = 0b010,               // 8����
    PWM_PRESCALER_64 = 0b011,              // 64����
    PWM_PRESCALER_256 = 0b100,             // 256����
    PWM_PRESCALER_1024 = 0b101,            // 1024����
    PWM_PRESCALER_OUTSIDE_UNDER = 0b110,   // �O���N���b�N(���~)
    PWM_PRESCALER_OUTSIDE_OVER = 0b111     // �O���N���b�N(�㏸)	
} PWM_Prescaler;

typedef enum PWM_MatchModeA {
	// Low, High���ݏo��
	PWMA_ALTERNATE = 0b01,  
	// ��r��v��Low, BOTTOM��High          
	PWMA_BOTTOM_HIGH = 0b10,
	// ��r��v��High, BOTTOM��Low
	PWMA_BOTTOM_LOW = 0b11
} PWM_MatchModeA;

typedef enum PWM_MatchModeB {
	// ��r��v��Low, BOTTOM��High
	PWMB_BOTTOM_HIGH = 0b10,
	// ��r��v��High, BOTTOM��Low	
	PWMB_BOTTOM_LOW = 0b11
} PWM_MatchModeB;

/**
 * �^�C�}�[0��PWM�p�ɏ��������܂��B
 * @param wgm �^�C�}�[�̓��샂�[�h(wgm2,wgm1,wgm0)
 * @param p �v�����X�P�[��
 * @param matchA �o��A�̃��[�h
 * @param matchB �o��B�̃��[�h
 */
void PWM_initTimer0(unsigned char wgm, PWM_Prescaler p, 
                    PWM_MatchModeA matchA, PWM_MatchModeB matchB);

/**
 * �^�C�}�[1��PWM�p�ɏ��������܂��B
 * @param wgm �^�C�}�[�̓��샂�[�h(wgm3,wgm2,wgm1,wgm0)
 * @param p �v�����X�P�[��
 * @param matchA �o��A�̃��[�h
 * @param matchB �o��B�̃��[�h
 */
void PWM_initTimer1(unsigned char wgm, PWM_Prescaler p, 
                    PWM_MatchModeA matchA, PWM_MatchModeB matchB);

/**
 * �^�C�}�[2��PWM�p�ɏ��������܂��B
 * @param wgm �^�C�}�[�̓��샂�[�h(wgm2,wgm1,wgm0)
 * @param p �v�����X�P�[��
 * @param matchA �o��A�̃��[�h
 * @param matchB �o��B�̃��[�h
 */
void PWM_initTimer2(unsigned char wgm, PWM_Prescaler p, 
                    PWM_MatchModeA matchA, PWM_MatchModeB matchB);

void PWM_setDuty0A(unsigned char duty);

void PWM_setDuty0B(unsigned char duty);

void PWM_setDuty1A(unsigned int duty);

void PWM_setDuty1B(unsigned int duty);

void PWM_setDuty2A(unsigned char duty);

void PWM_setDuty2B(unsigned char duty);

#endif /* PWM_H_ */