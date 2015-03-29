/*
 * grip.h
 *
 * GRIP (Gifu university Robocon circle Interface Protocol)
 *
 * �}�C�R���ԃV���A���ʐM�̃v���g�R�����`���܂��B
 * Created: 2011/12/30 5:28:30
 *  Author: Gifu university Robocon circle
 */



#ifndef GRIP_H_
#define GRIP_H_

#include <avr/io.h>

/************************************************************************/
/* �R���N�^���{�b�g�̃A�h���X�ݒ�
/************************************************************************/
/** �R���N�^���{�b�g�F�����O�����[�^�h���C�o */
static const int COLLECTOR_FRONT_ADDRESS = 0x12;

/** �R���N�^���{�b�g�F����������[�^�h���C�o */
static const int COLLECTOR_REAR_ADDRESS = 0x11;

/** �R���N�^���{�b�g�F�T�[�{���[�^�h���C�o */
static const int COLLECTOR_SERVOMOTOR_ADDRESS = 0x13;

/** �R���N�^���{�b�g�F�Z���T�h���C�o */
static const int COLLECTOR_SENSOR_ADDRESS = 0x17;

/** �R���N�^���{�b�g�F���C���g���[�X�Z���T */
static const int COLLECTOR_LINETRACER_ADDRESS = 0x19;

/** �R���N�^���{�b�g:�����オ������Ԃł̃��C���g���[�X�Z���T */
static const int COLLECTOR_STANDUP_LINETRACER_ADDRESS = 0x18;

/** �R���N�^���{�b�g:���[�^���G���R�[�_ */
static const int COLLECTOR_ROTARY_ENCORDER_ADDRESS = 0x16;

/** �R���N�^���{�b�g: �o���Y�A�[�����[�^�h���C�o */
static const int COLLECTOR_BUNS_ARM_ADDRESS = 0x14;

/** �R���N�^���{�b�g: �㉺�@�\���[�^�h���C�o */
static const int COLLECTOR_UPDOWN_ADDRESS = 0x15;


/************************************************************************/
/* �������{�b�g�̃A�h���X�ݒ�
/************************************************************************/
/** �������{�b�g�����̃��[�^�h���C�o */
static const int AUTO_FOOT_MOTORDRIVER_ADDRESS = 0x20;

/** �A�[������̃Z���T�h���C�o */
static const int AUTO_ARM_SENSOR_ADDRESS = 0x21;

/** ���C���g���[�X�Z���T�E�O */
static const int AUTO_FRONT_LINETRACER_ADDRESS = 0x23;

/** ���C���g���[�X�Z���T�E�� */
static const int AUTO_REAR_LINETRACER_ADDRESS = 0x22;

/** �T�[�{���[�^�h���C�o */
static const int AUTO_SERVOMOTOR_ADDRESS = 0x24;

/** ���[�^���[�G���R�[�_��90�x���C���Z���T */
static const int AUTO_ROTARYENCODER_ADDRESS = 0x25;

/** �A�[���̃��[�^�h���C�o */
static const int AUTO_ARM_MOTORDRIVER_ADDRESS = 0x26;

/** ���o�� */
#ifndef PI
//#define PI 3.14159265
#define PI 3.14
#endif


/**
 * ���荞�݂��������� or ���Ȃ�
 */
typedef enum InterruptSwitch {
	/** ���荞�݂������Ȃ� */
	INTERRUPT_OFF = 0,
	/** ���荞�݂������� */
	INTERRUPT_ON = 1
} InterruptSwitch;

/**
 * �i�s����
 */
typedef enum MovementDirection {
	FORWARD = 0,
	BACKWARD = 1,
	LEFT_ROTATION = 2,
	RIGHT_ROTATION = 3,
	STOP = 4
} MovementDirection;

/**
 * ���E
 */
typedef enum TurnDirection {
    RIGHT = 0,
    LEFT = 1
} TurnDirection;


/**
 * �㉺
 */
typedef enum VerticalDirection {
    UPPER = 0,
    LOWER = 1
} VerticalDirection;

/**
 * ����
 */
typedef enum PlusMinus {
    PLUS = 0,
    MINUS = 1
} PlusMinus;

/**
 * �I���E�I�t
 */
typedef enum OnOff {
	OFF = 0,
	ON = 1
} OnOff;

/**
* ����t���O
*/
typedef enum Action {
	/** ������ */
	STILLNESS = 0,
	/** ���쒆 */
	ACTIVE = 1,
	/** ���슮��*/
	COMPLETE = 2
} Action;

/**
 * �^�b�`����Ă���E�^�b�`����Ă��Ȃ�
*/
typedef enum Touch {
	NO_TOUCHED = 0,
	TOUCHED = 1
} Touch;

/**
* ���邢�E�Â�
*/
typedef enum Brightness {
	DARK = 0,
	BRIGHT = 1
} Brightness;

/**
* �^�U�l
*/
typedef enum Boolean {
	FALSE = 0,
	TRUE = 1
} Boolean;

/**
 * ���[�^�h���C�o�ɓ`���郂�[�^�̉�]�����ƃX�s�[�h
 * direction: ��]����(FORWARD or BACKWARD)(UPPER or LOWER)�Ȃ�
 * speed: �X�s�[�h(7bit��)
 */
typedef union MotorSignal {
	uint8_t key: 8;
	struct {
	    MovementDirection direction: 1;
		uint8_t speed: 7;
	};
} MotorSignal;

/**
* ���[�^�h���C�o�ɑ��鏇��
*/
typedef enum MotorOrder {
	RIGHT_MOTOR = 1,
	LEFT_MOTOR = 0
} MotorOrder;

/**
 * ��]
 * direction: �E��] or ����]
 * speed: �X�s�[�h(0-127)
 */
typedef union TurnSignal {
	TurnDirection direction: 1;
	uint8_t speed: 7;
} TurnSignal;

/**
* ���[�^���G���R�[�_����̓��͒l�̂��߂̌^
*/
typedef union RotaryEncoderSignal {
	signed long pulse;
	struct {
		uint8_t val0: 8;
		uint8_t val1: 8;
		uint8_t val2: 8;
		signed char val3: 8;
	};
} RotaryEncoderSignal;

/************************************************************************/
/* �R���N�^���{�b�g�̓Ǝ��v���g�R���E��`
/************************************************************************/
/**
* �^�b�`�Z���T�̓��͒l
*/
typedef union Collector_SensorSignal {
	uint8_t key: 8;
	struct {
		Touch updownTouchValue: 1;
		Touch footTouchValue: 1;
		Touch armLimitTouchValue: 1;
		Touch fotSensor: 1;  //�ҏW(�R��)
	};
} Collector_SensorSignal;

/************************************************************************/
/* �������{�b�g�̓Ǝ��v���g�R���E��`
/************************************************************************/
/**
* �\�����C���Z���T�̒l
*/
typedef union Auto_CrossSensor {
	uint8_t key: 8;
	struct {
		uint8_t left: 1;
		uint8_t right: 1;
	};
} Auto_CrossSensor;


/**
* �A�[���̓���
*/
typedef enum Auto_ArmMovement {
	Auto_ARM_STOP = 0,
	Auto_ARM_UP = 1,
	Auto_ARM_DOWN = 2
} Auto_ArmMovement;

/**
* �A�[���̃^�b�`�Z���T�̒l
*/
typedef union {
	unsigned char key;
	struct{
		unsigned char basketsensor :1;
		unsigned char arm_up_sensor :1;
		unsigned char arm_down_sensor :1;
		unsigned char AUTO_restart: 1;
		unsigned char collecter_robot_start :1;		
	};
} Auto_ArmTouchSensor;

#endif /* GRIP_H_ */