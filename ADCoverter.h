/** AD�ϊ��̂��߂̃��C�u�����ł��BAVR atmega88P, atmega168P�݊��̃}�C�R�������ɍ쐬
 * ����Ă��܂��B
 *
 * @file ADCoverter.h
 *
 *  AD�ϊ��̃��C�u���� mega88p/mega168p����
 *
 * @namespace ADC
 * @date 2012/01/01 20:49:53
 *  author hirokazu yokoyama, Gifu university Robocon circle
 */


#ifndef ADCOVERTER_H_
#define ADCOVERTER_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "grobo.h"

/**
 * �`�c�ϊ��̊�d�����w�肷�邽�߂̗񋓑�
 */
typedef enum ADC_ReferenceVoltage{
	/** AREF�s���̊O���d������ɂ��܂��B*/
	ADC_AREF = 0b00,
	/** AVCC�̊O���d������ɂ��܂�(AREF�Ƀf�J�b�v�p�R���f���T�g�p��) */
	ADC_AVCC = 0b01,
	/** ����1.1V����d���ɂ��܂�(AREF�Ƀf�J�b�v�p�R���f���T�g�p��) */
	ADC_INNER = 0b11
} ADC_ReferenceVoltage;

/**
 * AD�ϊ��ł̓��͒l�̑����̗񋓑�
 */
typedef enum ADC_Align {
	/** �E�� */
	ADC_RIGHT = 0,
	/** ���� */
	ADC_LEFT = 1
} ADC_Align;

/**
 * AD�ϊ��v�����X�P�[��(�����l)�̗񋓑�
 */
typedef enum ADC_Prescaler {
	/** clock / 2 */
	ADC_PRESCALER_2 = 0b001,
	/** clock / 4 */
	ADC_PRESCALER_4 = 0b010,
	/** clock / 8 */
	ADC_PRESCALER_8 = 0b011,
	/** clock / 16 */
	ADC_PRESCALER_16 = 0b100,
	/** clock / 32 */
	ADC_PRESCALER_32 = 0b101,
	/** clock / 64 */
	ADC_PRESCALER_64 = 0b110,
	/** clock / 128 */
	ADC_PRESCALER_128 = 0b111
} ADC_Prescaler;

/**
 * AD�ϊ��̎������s�̑I��
 */
typedef enum ADC_LaunchedFrom {
	/** �A���ϊ����� */
	ADC_CONTINUOUS = 0b000,
	/** �A�i���O��r�� */
	ADC_ANALOG_COMPARE = 0b001,
	/** �O�����荞�ݗv�� */
	ADC_EXTERNAL_INTERRUPT = 0b010,
	/** �^�C�}�E�J�E���^0��rA��v*/
	ADC_TIMER0A_COMPARE = 0b011,
	/** �^�C�}�E�J�E���^�̃I�[�o�[�t���[ */
	ADC_TIMER0_OVERFLOW = 0b100,
	/** �^�C�}�E�J�E���^1��rB��v */
	ADC_TIMER1B_COMPARE = 0b101,
	/** �^�C�}�E�J�E���^1�I�[�o�[�t���[ */
	ADC_TIMER1B_OVERFLOW = 0b110,
	/** �^�C�}�E�J�E���^1�ߊl�v�� */
	ADC_TIMER1B_CAPTURE = 0b111
} ADC_LaunchedFrom;

/**
 * AD�ϊ��p���W�X�^�����������܂��BAD�ϊ����J�n����ɂ�ADC_start()�܂���
 * ADC_startAutomaticLaunch()�����s���Ă��������B
 * @param usedPin AD�ϊ��Ɏg�p����s��(PC0����PC5�̒��������w��)
 * @param rv ��d�����ǂ�ɂ��邩���w��(ADC_ReferenceVoltage�񋓑̂�����I��)
 * @param align 10bit�̓��͒l������(LEFT)�ɂ��邩�E��(RIGHT)�ɂ��邩���w��
 * @param is ���荞�݂������邩���Ȃ���(�ʓrsei()�Ŋ��荞�݋�����K�v����)
 * @param p �v���X�P�[��(�������ADC_Prescaler�񋓑̂̒�����I��)
 */
void ADC_init(unsigned char usedPin, ADC_ReferenceVoltage rv, ADC_Align align,
                InterruptSwitch is, ADC_Prescaler p);


/**
 * AD�ϊ����P�񂾂��s���܂��B���O��ADC_init()�ŏ���������K�v������܂��B
 */
void ADC_start();

/**
 * AD�ϊ��̎����N����ݒ肵�܂��B���O��ADC_init()�ŏ���������K�v������܂��B
 * �܂������N�����~����ɂ�ADC_stopAutomaticLaunch()�����s���Ă��������B
 * @param launchedFrom �����N���̊J�n��
 */
void ADC_startAutomaticLaunch(ADC_LaunchedFrom launchedFrom);

/**
 * AD�ϊ��̎����N�����~���܂��B�ĊJ����ɂ�ADC_startAutomaticLaunch()�����s���Ă��������B
 */
void ADC_stopAutomaticLaunch();


/**
 * AD�ϊ��ɂ����͒l�̏�ʃr�b�g��Ԃ��܂��B
 */
unsigned char ADC_getADCH();

/**
 * AD�ϊ��ɂ����͒l�̉��ʃr�b�g��Ԃ��܂��B
 */
unsigned char ADC_getADCL();

/**
 * AD�ϊ��������̊��荞�݂Ŏ��s����֐����w�肵�܂��B
 * @param *func ���s����֐��̃|�C���^
 */
void ADC_setInterruptListener(void (*func)(void));


#endif /* ADCOVERTER_H_ */