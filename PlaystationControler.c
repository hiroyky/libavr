/*
 * PlayStationControler.c
 *
 * Created: 2012/01/17 22:35:20
 *  Author: Chihiro
 */ 

#include "PlayStationControler.h"

/*
最終更新 2010 01 20
*/
#if !defined PS_H
#define PS_H

#if !defined F_CPU
#define F_CPU 8000000UL
#endif
#include <util/delay.h>
#include <avr/io.h>
#include "PlayStationControler.h"

//ピンのラベリング
#define CLK  3     //クロック     送信	
#define SEL  4     //通信の開始 送信
#define CMD  2     //コマンド     送信
#define DAT  5     //データ      受信

//ポートのラベリング
#define PS_DDR  DDRD
#define PS_PORT PORTD
#define PS_PIN  PIND

//関数の宣言
void initPadPort(void);             //ポートの初期化
void connectPad(PadStatus *data);   //PSコントローラの接続・データ授受
int rcvdat(int cmd);                //コマンドを投げてデータを貰う
void outputCMD(unsigned char *cmd); //設定用コマンド送信
void setVibrationMode(void);        //
void waitFiveus(int i);

unsigned char changeBit(int i) {
  return 0x01 << i;
}

//pad接続
//返却値  
//引数
void connectPad(PadStatus *data) {
	//int i;
	PS_PORT &= ~changeBit(SEL);           //SRLをＬにして接続してる合図

	//データのやり取り
	rcvdat(0x01);
	data->byte.id	 = rcvdat(0x42);
	data->byte.chk = rcvdat(0x00);
	data->byte.key1 = ~rcvdat(data->byte.vib != 0 ? 0x01 : 0x00);	//弱振動
	data->byte.key2 = ~rcvdat(data->byte.vib);	//強震動　振動レベル指定可
	data->byte.stickR1 = rcvdat(0x00);
	data->byte.stickR2 = rcvdat(0x00);
	data->byte.stickL1 = rcvdat(0x00);
	data->byte.stickL2 = rcvdat(0x00);
  /*
	for(i = 0; i < 10; i++) {
		rcvdat(0x00);
	}
  */
	PS_PORT |= changeBit(SEL);            //SELをＨにして、通信は終りの合図
}

//padにコマンドを投げる
//クロック立下りで出力、立ち上がりで入力
//返却値  １バイトデータ
//引数    １バイトコマンド
int rcvdat(int cmd) {
	int dat = 0;
  int i = 0;
  
	PS_PORT |= changeBit(CLK);	                //クロックをＨにしておく
	for(; i < 8; i++) {                         //１バイト分の繰り返し
		if((cmd & ~changeBit(i)) == cmd)		      //i番目のビットが0かどうかの判別
			{	PS_PORT &= ~changeBit(CMD);	}
		else
			{	PS_PORT |= changeBit(CMD);	}
		PS_PORT &= ~changeBit(CLK);               //クロックをＬに
		if(PS_PIN & changeBit(DAT))
			{	dat |=  changeBit(i); }
		else
			{	dat &= ~changeBit(i); }
		PS_PORT |= changeBit(CLK);                //クロックを進める
	}
	PS_PORT |= changeBit(CMD);                  //CMDをＨに
     waitFiveus(2);
	return dat;
}

//pad用ポートの初期化 入出力の設定
void initPadPort(void) {
	PS_PORT |= changeBit(CLK) | changeBit(SEL) | changeBit(CMD) | changeBit(DAT);
	PS_DDR  |= changeBit(CLK) | changeBit(SEL) | changeBit(CMD);
	PS_DDR  &= ~changeBit(DAT);
}

//バイブレーションの設定
void setVibrationMode(void) {	
  //コマンド一覧
  unsigned char enterCon[]    = { 0x01, 0x43, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00 };
  //const unsigned char exitCon[]     = { 0x01, 0x43, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
  unsigned char mode[]        = { 0x01, 0x44, 0x00, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00 };
  unsigned char vibration[]   = { 0x01, 0x4D, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF };
  //const unsigned char pres_enable[] = { 0x01, 0x4F, 0x00, 0xFF, 0xFF, 0x03, 0x00, 0x00, 0x00 };
  //const unsigned char pres[]        = { 0x01, 0x43, 0x00, 0x00, 0x5A, 0x5A, 0x5A, 0x5A, 0x5A };
  
  outputCMD(enterCon);
  outputCMD(mode);
  outputCMD(vibration);
}

//設定用コマンド送信
//戻り値  なし
//引数    コマンドの配列を指すポインタ
void outputCMD(unsigned char *cmd) {
  int i = 0;
  PS_PORT &= ~changeBit(SEL);
  while(i < 10) {
    rcvdat(cmd[i]);
    i++;
  }
  PS_PORT |= changeBit(SEL);
}

void waitFiveus(int i) {
  for(;i;i--) _delay_us(5);
}

void vibrationON(uint8_t intensity, PadStatus *psdata){
	psdata->byte.vib = intensity;
}

void vibrationOFF(PadStatus *psdata){
	psdata->byte.vib = 0;
}

#endif
