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
 * PS�R���g���[��NHK���{�R��2012��H�����ɓ��o�͂����������܂�
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
 * PS�R���g���[���̓��͂���Ă���L�[���擾����
 * @return  ���͂��ꂽ�l
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
* �R�}���h�𓊂��ăf�[�^��Ⴄ�B
* @param    cmd    PS�R���g���[���ɑ���R�}���h
* @return   PS�R���g���[������̐M��
* */

int rcvdat(int cmd)
{
    int dat=0,i;
    *psPin.port |= _BV(psPin.clk);  // �N���b�N���g�ɂ��Ă���

    // �N���b�N������ŏo�́A�����オ��œ���
    for(i=0;i<8;i++)
    {		
        if((cmd & ~_BV(i)) == cmd) {    // i�Ԗڂ̃r�b�g��0���ǂ����̔���
            *psPin.port &= ~_BV(psPin.cmd);
        } else{
            *psPin.port |= _BV(psPin.cmd);
        }
       

        // �N���b�N���k��
        *psPin.port &= ~_BV(psPin.clk);

        if(bit_is_set(*psPin.pin, psPin.dat)) {
            dat |= _BV(i);
        } else {
            dat &= ~_BV(i);
        }
        
        // �N���b�N��i�߂�
        *psPin.port |= _BV(psPin.clk);		
		waitMicrosec(5);
    }

    // CMD���g��
    *psPin.port |= _BV(psPin.cmd);
    return dat;
}
