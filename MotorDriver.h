/*
 * MotorDriver.h
 *
 * Created: 2012/03/07 23:34:19
 *  Author: hirokazu
 */ 


#ifndef MOTORDRIVER_H_
#define MOTORDRIVER_H_

#include "grobo.h"



/**
 * �^�C�}�E�J�E���^0�����[�^�h���C�o��PWM������
 * ��r�l��v��Low, 8bit����PWM,�v�����X�P�[��8����
 */
void MotorDriver_init0();

/**
 * �^�C�}�E�J�E���^1�����[�^�h���C�o��PWM������
 * ��r�l��v��Low, 8bit����PWM,�v�����X�P�[��8���� 
 */
void MotorDriver_init1();

/**
 * �^�C�}�E�J�E���^2�����[�^�h���C�o��PWM������
 * ��r�l��v��Low, 8bit����PWM,�v�����X�P�[��8����
 */
void MotorDriver_init2();


/**
 * �^�C�}�E�J�E���^0�̃��[�^�̑������w�肵�܂��B
 * @param motorSignal ���[�^�����M��
 */
void MotorDriver_run0(MotorSignal motorSignal);

/**
 * �^�C�}�E�J�E���^1�̃��[�^�̑������w�肵�܂��B
 * @param motorSignal ���[�^�����M��
 */
void MotorDriver_run1(MotorSignal motorSignal);

#endif /* MOTORDRIVER_H_ */