/** PS1用コントローラを使用するためのライブラリ
 * pspad.h
 *
 * @file    pspad.h
 * @author  Hirokazu Yokoyama, Gifu university Robocon circle
 * @date    12/28/2010
 * */

#ifndef PSPAD_H_
#define PSPAD_H_


typedef struct PsPin {
    volatile uint8_t *port;
    volatile uint8_t *pin;
    unsigned int dat : 8;
    unsigned int cmd : 8;
    unsigned int sel : 8;
    unsigned int clk : 8;
} PsPin;

typedef union PsPadKey1 {
    unsigned int byteKey : 8;
    struct {
        unsigned int select : 1;
        unsigned int l3 : 1;
        unsigned int r3 : 1;
        unsigned int start : 1;
        unsigned int up : 1;
        unsigned int right : 1;
        unsigned int down : 1;
        unsigned int left : 1;
    };
} PsPadKey1;


typedef union PsPadKey2 {
    unsigned int byteKey : 8;
    struct {
        unsigned int l2 : 1;
        unsigned int r2 : 1;
        unsigned int l1 : 1;
        unsigned int r1 : 1;
        unsigned int triangle : 1;
        unsigned int circle : 1;
        unsigned int cross : 1;
        unsigned int square : 1;
    };
} PsPadKey2;

/**
 * PSコントローラから取得する値
 * */
typedef struct PsPad {
    // コントローラの種類
    unsigned int id : 8;
    unsigned int chk : 8;
    // | 左 | 下 | 右 | 上 | START | SELECT | R3 | L3 | SELECT |
    PsPadKey1 key1;
    // | □ | × | ○ | △ | R1 | L1 | R2 | L2 |
    PsPadKey2 key2;
    unsigned int analogRightSide : 8;
    unsigned int analogRightHide : 8;
    unsigned int analogLeftSide : 8;
    unsigned int analogLeftHide : 8;
} PsPad;

typedef enum PS_Event {
	DOWN,
	UP,
	PRESS_1SEC,
	PRESS_2SEC
} PS_Event;

PsPad connectPad(PsPin *pin);

//void setEvent(void (*func)(void), PsPadKey1 key1, PsPadKey2 key2, PS_Event event);



#endif /* PSPAD_H_ */

