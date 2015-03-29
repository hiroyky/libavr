/*
 * PlayStationControler.c
 *
 * Created: 2012/01/17 22:35:20
 *  Author: Chihiro
 */ 

#include "PlayStationControler.h"

/*
�ŏI�X�V 2010 01 20
*/
#if !defined PS_H
#define PS_H

#if !defined F_CPU
#define F_CPU 8000000UL
#endif
#include <util/delay.h>
#include <avr/io.h>
#include "PlayStationControler.h"

//�s���̃��x�����O
#define CLK  3     //�N���b�N     ���M	
#define SEL  4     //�ʐM�̊J�n ���M
#define CMD  2     //�R�}���h     ���M
#define DAT  5     //�f�[�^      ��M

//�|�[�g�̃��x�����O
#define PS_DDR  DDRD
#define PS_PORT PORTD
#define PS_PIN  PIND

//�֐��̐錾
void initPadPort(void);             //�|�[�g�̏�����
void connectPad(PadStatus *data);   //PS�R���g���[���̐ڑ��E�f�[�^����
int rcvdat(int cmd);                //�R�}���h�𓊂��ăf�[�^��Ⴄ
void outputCMD(unsigned char *cmd); //�ݒ�p�R�}���h���M
void setVibrationMode(void);        //
void waitFiveus(int i);

unsigned char changeBit(int i) {
  return 0x01 << i;
}

//pad�ڑ�
//�ԋp�l  
//����
void connectPad(PadStatus *data) {
	//int i;
	PS_PORT &= ~changeBit(SEL);           //SRL���k�ɂ��Đڑ����Ă鍇�}

	//�f�[�^�̂����
	rcvdat(0x01);
	data->byte.id	 = rcvdat(0x42);
	data->byte.chk = rcvdat(0x00);
	data->byte.key1 = ~rcvdat(data->byte.vib != 0 ? 0x01 : 0x00);	//��U��
	data->byte.key2 = ~rcvdat(data->byte.vib);	//���k���@�U�����x���w���
	data->byte.stickR1 = rcvdat(0x00);
	data->byte.stickR2 = rcvdat(0x00);
	data->byte.stickL1 = rcvdat(0x00);
	data->byte.stickL2 = rcvdat(0x00);
  /*
	for(i = 0; i < 10; i++) {
		rcvdat(0x00);
	}
  */
	PS_PORT |= changeBit(SEL);            //SEL���g�ɂ��āA�ʐM�͏I��̍��}
}

//pad�ɃR�}���h�𓊂���
//�N���b�N������ŏo�́A�����オ��œ���
//�ԋp�l  �P�o�C�g�f�[�^
//����    �P�o�C�g�R�}���h
int rcvdat(int cmd) {
	int dat = 0;
  int i = 0;
  
	PS_PORT |= changeBit(CLK);	                //�N���b�N���g�ɂ��Ă���
	for(; i < 8; i++) {                         //�P�o�C�g���̌J��Ԃ�
		if((cmd & ~changeBit(i)) == cmd)		      //i�Ԗڂ̃r�b�g��0���ǂ����̔���
			{	PS_PORT &= ~changeBit(CMD);	}
		else
			{	PS_PORT |= changeBit(CMD);	}
		PS_PORT &= ~changeBit(CLK);               //�N���b�N���k��
		if(PS_PIN & changeBit(DAT))
			{	dat |=  changeBit(i); }
		else
			{	dat &= ~changeBit(i); }
		PS_PORT |= changeBit(CLK);                //�N���b�N��i�߂�
	}
	PS_PORT |= changeBit(CMD);                  //CMD���g��
     waitFiveus(2);
	return dat;
}

//pad�p�|�[�g�̏����� ���o�͂̐ݒ�
void initPadPort(void) {
	PS_PORT |= changeBit(CLK) | changeBit(SEL) | changeBit(CMD) | changeBit(DAT);
	PS_DDR  |= changeBit(CLK) | changeBit(SEL) | changeBit(CMD);
	PS_DDR  &= ~changeBit(DAT);
}

//�o�C�u���[�V�����̐ݒ�
void setVibrationMode(void) {	
  //�R�}���h�ꗗ
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

//�ݒ�p�R�}���h���M
//�߂�l  �Ȃ�
//����    �R�}���h�̔z����w���|�C���^
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
