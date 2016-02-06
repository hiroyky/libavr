/*
 * pspad.c
 *
 * Created: 2012/02/26 2:50:59
 *  Author: hirokazu
 */ 
#include <avr/io.h>
#include "pspad.h"
#include "wait.h"

static PsPin psPin;
int rcvdat(int cmd);

/**
 * PSコントローラNHKロボコン2012回路向けに入出力を初期化します
 */
void PS_init() {
	DDRD += 0b11011111;
	PORTD += 0b00100000;
	psPin.port = &PORTD;
	psPin.pin = &PIND;	
	psPin.dat = PIND5;
	psPin.cmd = PIND2;
	psPin.sel = PIND4;	
	psPin.clk = PIND3;
}

/**
 * PSコントローラの入力されているキーを取得する
 * @return  入力された値
 * */
PsPad connectPad(PsPin *pin) {
    psPin = *pin;
    PsPad pad;
    *psPin.port &= ~_BV(psPin.sel);
    waitMicrosec(5);

    rcvdat(0x01);
    pad.id = rcvdat(0x42);
    pad.chk = rcvdat(0x00);
    pad.key1.byteKey = ~rcvdat(0x00);
    pad.key2.byteKey = ~rcvdat(0x00);
    pad.analogRightSide = rcvdat(0x00);
    pad.analogRightHide = rcvdat(0x00);
    pad.analogLeftSide = rcvdat(0x00);
    pad.analogLeftHide = rcvdat(0x00);
    
    *psPin.port |= _BV(psPin.sel);
    waitMicrosec(5);

    

    return pad;
}


/**
* コマンドを投げてデータを貰う。
* @param    cmd    PSコントローラに送るコマンド
* @return   PSコントローラからの信号
* */

int rcvdat(int cmd)
{
    int dat=0,i;
    *psPin.port |= _BV(psPin.clk);  // クロックをＨにしておく

    // クロック立下りで出力、立ち上がりで入力
    for(i=0;i<8;i++)
    {		
        if((cmd & ~_BV(i)) == cmd) {    // i番目のビットが0かどうかの判別
            *psPin.port &= ~_BV(psPin.cmd);
        } else{
            *psPin.port |= _BV(psPin.cmd);
        }
       

        // クロックをＬに
        *psPin.port &= ~_BV(psPin.clk);

        if(bit_is_set(*psPin.pin, psPin.dat)) {
            dat |= _BV(i);
        } else {
            dat &= ~_BV(i);
        }
        
        // クロックを進める
        *psPin.port |= _BV(psPin.clk);		
		waitMicrosec(5);
    }

    // CMDをＨに
    *psPin.port |= _BV(psPin.cmd);
    return dat;
}
