/*
 * ServoMotor.h
 *
 * Created: 2012/03/07 23:59:43
 *  Author: hirokazu
 */ 


#ifndef SERVOMOTOR_H_
#define SERVOMOTOR_H_

#include <avr/io.h>

typedef enum ServoMotor_Selector0 {
	ServoMotor_0A = 1,
	ServoMotor_0B = 2
} ServoMotor_Selector0;


typedef enum ServoMotor_Selector1 {
	ServoMotor_1A = 1,
	ServoMotor_1B = 2
} ServoMotor_Selector1;



/** �T�[�{���[�^�����o�͂̂P�����J�E���g�l */
static const uint16_t ServoMotor_ICR_TOP = 18000;

/** GWS Micro 2BBMG�T�[�{���[�^�̍ő�p�x�̃p���X�� */
static const uint16_t ServoMotor_GWSMICRO_2BBMG_MAX = 2050;
/** GWS Micro 2BBMG�T�[�{���[�^�̍ŏ��p�x�̃p���X�� */
static const uint16_t ServoMotor_GWSMICRO_2BBMG_MIN = 470;
/** GWS Micro 2BBMG�T�[�{���[�^�����̔��萔(16bit�^�C�}����) */
static const float ServoMotor_GWSMICRO_2BBMG_CONSTANT = 8.7;
/** GWS Micro 2BBMG�T�[�{���[�^�����̔��萔(8bit�^�C�}����) */
static const float ServoMotor_GWSMICRO_2BBMG_CONSTANT_8BIT = 0.13;


/** TowerPro MG995�T�[�{���[�^�̍ő�p�x�̃p���X�� */
static const uint16_t ServoMotor_MG995_MAX = 2940;
/** TowerPro MG995�T�[�{���[�^�̍ŏ��p�x�̃p���X�� */
static const uint16_t ServoMotor_MG995_MIN = 750;
/** TowerPro MG995�T�[�{���[�^�����̔��萔(16bit�^�C�}����) */
static const float ServoMotor_MG995_CONSTANT = 10.4;
/** TowerPro MG995�T�[�{���[�^�����̔��萔(8bit�^�C�}����) */
static const float ServoMotor_MG995_CONSTANT_8BIT = 0.16;


/** GWS PICO STD�T�[�{���[�^�̍ő�p�x�̃p���X�� */
static const uint16_t ServoMotor_GWSPICO_STD_MAX = 2160;
/** GWS PICO STD�T�[�{���[�^�̍ŏ��p�x�̃p���X�� */
static const uint16_t ServoMotor_GWSPICO_STD_MIN = 760;
/** GWS PICO STD�T�[�{���[�^�̍ő�p�x�̃p���X�� */
static const float ServoMotor_GWSPICO_STD_CONSTANT = 7.7;
/** GWS PICO STD�T�[�{���[�^�̍ő�p�x�̃p���X�� */
static const float ServoMotor_GWSPICO_STD_CONSTANT_8BIT = 0.12;


/**
 * �T�[�{���[�^�̓d�����I���ɂ��܂��B
 */
void ServoMotor_onPower();
	
/**
 * �T�[�{���[�^�̓d�����I�t�ɂ��܂��B
 */	
void ServoMotor_offPower();
	
	
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
void ServoMotor_init0(ServoMotor_Selector0 s, uint16_t min, uint16_t max, float p);


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
void ServoMotor_init1(ServoMotor_Selector1 s, uint16_t min, uint16_t max, float p);



/**
 * �^�C�}0A�̃T�[�{���[�^����]�����܂��B�p�x�w��
 * @param angle �p�x(�O�x����P�W�O�x)
 *
 * @return �o�͂����p���X�̃f���[�e�B��
 */
uint8_t ServoMotor_turn0A(uint8_t angle);

/**
 * �^�C�}0B�̃T�[�{���[�^����]�����܂��B�p�x�w��
 * @param angle �p�x(�O�x����P�W�O�x)
 * @return �o�͂����p���X�̃f���[�e�B��
 */
uint8_t ServoMotor_turn0B(uint8_t angle);

/**
 * �^�C�}1A�̃T�[�{���[�^����]�����܂��B�p�x�w��
 * @param angle �p�x(0-180)
 * @return �o�͂����f���[�e�B��
 */
uint16_t ServoMotor_turn1A(uint8_t angle);

/**
 * �^�C�}1B�̃T�[�{���[�^����]�����܂��B�p�x�w��
 * @param angle �p�x(0-180)
 * @return �o�͂����f���[�e�B��
 */
uint16_t ServoMotor_turn1B(uint8_t angle);



#endif /* SERVOMOTOR_H_ */