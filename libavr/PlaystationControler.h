/*
 * PlayStationControler.h
 *
 * Created: 2012/01/17 22:36:06
 *  Author: Chihiro
 *
 * デュアルショック2２のみ対応
 */ 


#ifndef PLAYSTATIONCONTROLER_H_
#define PLAYSTATIONCONTROLER_H_

#include <avr/io.h>

//data格納用構造体型の宣言
typedef struct {
  unsigned id : 8;
  unsigned chk : 8;
  unsigned stickR1 : 8; //| 右ﾊﾝﾄﾞﾙ  左右  左:00h,中心:80h,右:FFh |
  unsigned stickR2 : 8; //| 右ﾊﾝﾄﾞﾙ  上下  上:00h,中心:80h,下:FFh |
  unsigned stickL1 : 8; //| 左ﾊﾝﾄﾞﾙ  左右  左:00h,中心:80h,右:FFh |
  unsigned stickL2 : 8; //| 左ﾊﾝﾄﾞﾙ  上下  上:00h,中心:80h,下:FFh |
  unsigned vib : 8;               //               振動の強さ
  unsigned key1 : 8;    //| 左 | 下 | 右 | 上 |ｽﾀｰﾄ| R3 | L3 |ｾﾚｸﾄ|
  unsigned key2 : 8;    //| □ | × | ○ | △ | R1 | L1 | R2 | L2 |
} Byte;

typedef struct{
	unsigned a :8;
	unsigned b :8;
	unsigned c :8;
	unsigned d :8;
	unsigned e :8;
	unsigned f :8;
	unsigned g :8;
	
	unsigned SERECT : 1;
	unsigned L3 : 1;
	unsigned R3 : 1;
  unsigned START : 1;
  unsigned UP : 1;
	unsigned RIGHT : 1;
	unsigned DOWN : 1;
	unsigned LEFT : 1;
	
	unsigned L2 : 1;
	unsigned R2 : 1;
	unsigned L1 : 1;
	unsigned R1 : 1;
	unsigned /*Y*/ triangle : 1;
	unsigned /*A*/ circle : 1;
	unsigned /*B*/ cross: 1;
	unsigned /*X*/ square: 1;
  
}Bit;

typedef union{
  Byte byte;
  Bit bit;
}PadStatus;

//関数の宣言
void initPadPort(void);             //ポートの初期化
void connectPad(PadStatus *data);   //PSコントローラの接続・データ授受
void setVibrationMode(void);        //
void vibrationON(uint8_t intensity, PadStatus *psdata);
void vibrationOFF(PadStatus *psdata);


#endif /* PLAYSTATIONCONTROLER_H_ */