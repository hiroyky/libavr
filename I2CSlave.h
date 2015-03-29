/** TWI(I2C通信)でスレーブ動作をするための関数群を持つライブラリです。
 * I2CSlave.h
 * I2Cスレーブのヘッダーファイル、ネームスペースとしてI2CSlave_で始まります。
 * 注意：割り込み動作ができません！
 *
 * Created: 2011/12/07 17:18:39
 * @author Hirokazu Yokoyama, Gifu university Robocon circle
 *
 */

/**
 * @example 使い方 (例
 * マスターから取得したデータをPORTDに出力します。また、1bitシフトした値を返します
 *
 * #include <avr/io.h>
 * #include "I2CSlave.h"
 *
 * // スレーブアドレス
 * static const unsigned char ADDRESS = 0x20;
 *
 * // スレーブ・イベントハンドラ
 * void slaveInitHandler(uint8_t dat);
 * void slaveRecieveHandler(uint8_t dat);
 * void slaveStopHandler(void);
 * unsigned char slaveSendHandler(void);
 * 
 * unsigned char shift(unsigned char dat);
 * 
 * 
 * int main(void)
 * {
 * 	// 入出力の初期化
 * 	DDRD = 0xFF;
 * 	PORTD = 0x00;
 * 
 * 	// I2Cスレーブ初期化します。スレーブアドレスを渡します。
 * 	I2CSlave_init(ADDRESS);
 * 
 * 	// スレーブ処理のイベントを設定
 *  I2CSlave_setInitEvent(slaveInitHandler);        // 初期化イベント
 * 	I2CSlave_setReceiveEvent(slaveRecieveHandler);  // 受信時イベント
 * 	I2CSlave_setStopEvent(slaveStopHandler);        // 停止時イベント
 *  I2CSlave_setSendEvent(slaveSendHandler);        // 送信時イベント

 *  while(1)
 *  {
 * 		// スレーブ動作を行う
 * 		I2CSlave_com();	
 *  }
 * }

 * /** 8bitの数列を1bit左にずらし、8bit目の値を1bit目に入れます。
 *  * @param dat 8bitの数列
 *  * @return 1bitシフトした値    
 * unsigned char shift(unsigned char dat) {
 *     unsigned topBit = ((dat>>7) & 0x01);
 * 	return ((dat<<1)|topBit);
 * }
 * 
 * 
 * void slaveInitHandler(uint8_t dat) {
 * 	// 空白
 * }

 * // 受信時イベント、マスターから受信した値をPORTDに出力します。
 * void slaveRecieveHandler(uint8_t dat) {
 *  PORTD = dat;
 * }
 * 
 * // 送信時イベント、マスターに送るデータをreturnします。
 * unsigned char slaveSendHandler(void) {
 *     return shift(PIND);
 * }
 * 
 * // 通信停止時のイベント
 * void slaveStopHandler(void) {
 * }

*/

#ifndef I2CSLAVE_H_
#define I2CSLAVE_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "grobo.h"

//typedef InterruptSwitch I2CSlave_Interrupt;



/**
 * I2Cをスレーブで初期化します。
 * 割り込み処理を行う場合は、paramをINTERRUPT_ONを指定し、
 * 別途sei()で割り込み許可を行う必要があります。
 * @param address I2Cスレーブアドレス
 * @param param スレーブ動作を割り込み処理にする場合はINTERRUPT_ONを指定
 */
void I2CSlave_init(unsigned char address, InterruptSwitch param);


void I2CSlave_do();

/**
 * I2C処理(メインループに入れる)
 * この関数を実行する前にそれぞれのイベントハンドラを設定してください。
 */
void I2CSlave_com();



void I2CSlave_setInitEvent(void (*func)(uint8_t dat));
void I2CSlave_setReceiveEvent(void (*func)(uint8_t dat));
void I2CSlave_setStopEvent(void (*func)(void));
void I2CSlave_setSendEvent(unsigned char (*func)(void));

/**
 * TWCRレジスタのTWINTビットを返します
 * @return 1 or 0
*/
unsigned char I2CSlave_isTWINT();


#endif /* I2CSLAVE_H_ */
