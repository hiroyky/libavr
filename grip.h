/*
 * grip.h
 *
 * GRIP (Gifu university Robocon circle Interface Protocol)
 *
 * マイコン間シリアル通信のプロトコルを定義します。
 * Created: 2011/12/30 5:28:30
 *  Author: Gifu university Robocon circle
 */



#ifndef GRIP_H_
#define GRIP_H_

#include <avr/io.h>

/************************************************************************/
/* コレクタロボットのアドレス設定
/************************************************************************/
/** コレクタロボット：足回り前方モータドライバ */
static const int COLLECTOR_FRONT_ADDRESS = 0x12;

/** コレクタロボット：足回り後方モータドライバ */
static const int COLLECTOR_REAR_ADDRESS = 0x11;

/** コレクタロボット：サーボモータドライバ */
static const int COLLECTOR_SERVOMOTOR_ADDRESS = 0x13;

/** コレクタロボット：センサドライバ */
static const int COLLECTOR_SENSOR_ADDRESS = 0x17;

/** コレクタロボット：ライントレースセンサ */
static const int COLLECTOR_LINETRACER_ADDRESS = 0x19;

/** コレクタロボット:立ち上がった状態でのライントレースセンサ */
static const int COLLECTOR_STANDUP_LINETRACER_ADDRESS = 0x18;

/** コレクタロボット:ロータリエンコーダ */
static const int COLLECTOR_ROTARY_ENCORDER_ADDRESS = 0x16;

/** コレクタロボット: バンズアームモータドライバ */
static const int COLLECTOR_BUNS_ARM_ADDRESS = 0x14;

/** コレクタロボット: 上下機構モータドライバ */
static const int COLLECTOR_UPDOWN_ADDRESS = 0x15;


/************************************************************************/
/* 自動ロボットのアドレス設定
/************************************************************************/
/** 自動ロボット足回りのモータドライバ */
static const int AUTO_FOOT_MOTORDRIVER_ADDRESS = 0x20;

/** アーム動作のセンサドライバ */
static const int AUTO_ARM_SENSOR_ADDRESS = 0x21;

/** ライントレースセンサ・前 */
static const int AUTO_FRONT_LINETRACER_ADDRESS = 0x23;

/** ライントレースセンサ・後 */
static const int AUTO_REAR_LINETRACER_ADDRESS = 0x22;

/** サーボモータドライバ */
static const int AUTO_SERVOMOTOR_ADDRESS = 0x24;

/** ロータリーエンコーダと90度ラインセンサ */
static const int AUTO_ROTARYENCODER_ADDRESS = 0x25;

/** アームのモータドライバ */
static const int AUTO_ARM_MOTORDRIVER_ADDRESS = 0x26;

/** 演出率 */
#ifndef PI
//#define PI 3.14159265
#define PI 3.14
#endif


/**
 * 割り込みを許可をする or しない
 */
typedef enum InterruptSwitch {
	/** 割り込みを許可しない */
	INTERRUPT_OFF = 0,
	/** 割り込みを許可する */
	INTERRUPT_ON = 1
} InterruptSwitch;

/**
 * 進行方向
 */
typedef enum MovementDirection {
	FORWARD = 0,
	BACKWARD = 1,
	LEFT_ROTATION = 2,
	RIGHT_ROTATION = 3,
	STOP = 4
} MovementDirection;

/**
 * 左右
 */
typedef enum TurnDirection {
    RIGHT = 0,
    LEFT = 1
} TurnDirection;


/**
 * 上下
 */
typedef enum VerticalDirection {
    UPPER = 0,
    LOWER = 1
} VerticalDirection;

/**
 * 正負
 */
typedef enum PlusMinus {
    PLUS = 0,
    MINUS = 1
} PlusMinus;

/**
 * オン・オフ
 */
typedef enum OnOff {
	OFF = 0,
	ON = 1
} OnOff;

/**
* 動作フラグ
*/
typedef enum Action {
	/** 未動作 */
	STILLNESS = 0,
	/** 動作中 */
	ACTIVE = 1,
	/** 動作完了*/
	COMPLETE = 2
} Action;

/**
 * タッチされている・タッチされていない
*/
typedef enum Touch {
	NO_TOUCHED = 0,
	TOUCHED = 1
} Touch;

/**
* 明るい・暗い
*/
typedef enum Brightness {
	DARK = 0,
	BRIGHT = 1
} Brightness;

/**
* 真偽値
*/
typedef enum Boolean {
	FALSE = 0,
	TRUE = 1
} Boolean;

/**
 * モータドライバに伝えるモータの回転方向とスピード
 * direction: 回転方向(FORWARD or BACKWARD)(UPPER or LOWER)など
 * speed: スピード(7bitで)
 */
typedef union MotorSignal {
	uint8_t key: 8;
	struct {
	    MovementDirection direction: 1;
		uint8_t speed: 7;
	};
} MotorSignal;

/**
* モータドライバに送る順番
*/
typedef enum MotorOrder {
	RIGHT_MOTOR = 1,
	LEFT_MOTOR = 0
} MotorOrder;

/**
 * 回転
 * direction: 右回転 or 左回転
 * speed: スピード(0-127)
 */
typedef union TurnSignal {
	TurnDirection direction: 1;
	uint8_t speed: 7;
} TurnSignal;

/**
* ロータリエンコーダからの入力値のための型
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
/* コレクタロボットの独自プロトコル・定義
/************************************************************************/
/**
* タッチセンサの入力値
*/
typedef union Collector_SensorSignal {
	uint8_t key: 8;
	struct {
		Touch updownTouchValue: 1;
		Touch footTouchValue: 1;
		Touch armLimitTouchValue: 1;
		Touch fotSensor: 1;  //編集(山口)
	};
} Collector_SensorSignal;

/************************************************************************/
/* 自動ロボットの独自プロトコル・定義
/************************************************************************/
/**
* 十字ラインセンサの値
*/
typedef union Auto_CrossSensor {
	uint8_t key: 8;
	struct {
		uint8_t left: 1;
		uint8_t right: 1;
	};
} Auto_CrossSensor;


/**
* アームの動作
*/
typedef enum Auto_ArmMovement {
	Auto_ARM_STOP = 0,
	Auto_ARM_UP = 1,
	Auto_ARM_DOWN = 2
} Auto_ArmMovement;

/**
* アームのタッチセンサの値
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