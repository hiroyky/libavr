/*
 * PlayStationControler.h
 *
 * Created: 2012/01/17 22:36:06
 *  Author: Chihiro
 *
 * �f���A���V���b�N2�Q�̂ݑΉ�
 */ 


#ifndef PLAYSTATIONCONTROLER_H_
#define PLAYSTATIONCONTROLER_H_

#include <avr/io.h>

//data�i�[�p�\���̌^�̐錾
typedef struct {
  unsigned id : 8;
  unsigned chk : 8;
  unsigned stickR1 : 8; //| �E�����  ���E  ��:00h,���S:80h,�E:FFh |
  unsigned stickR2 : 8; //| �E�����  �㉺  ��:00h,���S:80h,��:FFh |
  unsigned stickL1 : 8; //| �������  ���E  ��:00h,���S:80h,�E:FFh |
  unsigned stickL2 : 8; //| �������  �㉺  ��:00h,���S:80h,��:FFh |
  unsigned vib : 8;               //               �U���̋���
  unsigned key1 : 8;    //| �� | �� | �E | �� |����| R3 | L3 |�ڸ�|
  unsigned key2 : 8;    //| �� | �~ | �� | �� | R1 | L1 | R2 | L2 |
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

//�֐��̐錾
void initPadPort(void);             //�|�[�g�̏�����
void connectPad(PadStatus *data);   //PS�R���g���[���̐ڑ��E�f�[�^����
void setVibrationMode(void);        //
void vibrationON(uint8_t intensity, PadStatus *psdata);
void vibrationOFF(PadStatus *psdata);


#endif /* PLAYSTATIONCONTROLER_H_ */