/** TWI(I2C�ʐM)�ŃX���[�u��������邽�߂̊֐��Q�������C�u�����ł��B
 * I2CSlave.h
 * I2C�X���[�u�̃w�b�_�[�t�@�C���A�l�[���X�y�[�X�Ƃ���I2CSlave_�Ŏn�܂�܂��B
 * ���ӁF���荞�ݓ��삪�ł��܂���I
 *
 * Created: 2011/12/07 17:18:39
 * @author Hirokazu Yokoyama, Gifu university Robocon circle
 *
 */

/**
 * @example �g���� (��
 * �}�X�^�[����擾�����f�[�^��PORTD�ɏo�͂��܂��B�܂��A1bit�V�t�g�����l��Ԃ��܂�
 *
 * #include <avr/io.h>
 * #include "I2CSlave.h"
 *
 * // �X���[�u�A�h���X
 * static const unsigned char ADDRESS = 0x20;
 *
 * // �X���[�u�E�C�x���g�n���h��
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
 * 	// ���o�͂̏�����
 * 	DDRD = 0xFF;
 * 	PORTD = 0x00;
 * 
 * 	// I2C�X���[�u���������܂��B�X���[�u�A�h���X��n���܂��B
 * 	I2CSlave_init(ADDRESS);
 * 
 * 	// �X���[�u�����̃C�x���g��ݒ�
 *  I2CSlave_setInitEvent(slaveInitHandler);        // �������C�x���g
 * 	I2CSlave_setReceiveEvent(slaveRecieveHandler);  // ��M���C�x���g
 * 	I2CSlave_setStopEvent(slaveStopHandler);        // ��~���C�x���g
 *  I2CSlave_setSendEvent(slaveSendHandler);        // ���M���C�x���g

 *  while(1)
 *  {
 * 		// �X���[�u������s��
 * 		I2CSlave_com();	
 *  }
 * }

 * /** 8bit�̐����1bit���ɂ��炵�A8bit�ڂ̒l��1bit�ڂɓ���܂��B
 *  * @param dat 8bit�̐���
 *  * @return 1bit�V�t�g�����l    
 * unsigned char shift(unsigned char dat) {
 *     unsigned topBit = ((dat>>7) & 0x01);
 * 	return ((dat<<1)|topBit);
 * }
 * 
 * 
 * void slaveInitHandler(uint8_t dat) {
 * 	// ��
 * }

 * // ��M���C�x���g�A�}�X�^�[�����M�����l��PORTD�ɏo�͂��܂��B
 * void slaveRecieveHandler(uint8_t dat) {
 *  PORTD = dat;
 * }
 * 
 * // ���M���C�x���g�A�}�X�^�[�ɑ���f�[�^��return���܂��B
 * unsigned char slaveSendHandler(void) {
 *     return shift(PIND);
 * }
 * 
 * // �ʐM��~���̃C�x���g
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
 * I2C���X���[�u�ŏ��������܂��B
 * ���荞�ݏ������s���ꍇ�́Aparam��INTERRUPT_ON���w�肵�A
 * �ʓrsei()�Ŋ��荞�݋����s���K�v������܂��B
 * @param address I2C�X���[�u�A�h���X
 * @param param �X���[�u��������荞�ݏ����ɂ���ꍇ��INTERRUPT_ON���w��
 */
void I2CSlave_init(unsigned char address, InterruptSwitch param);


void I2CSlave_do();

/**
 * I2C����(���C�����[�v�ɓ����)
 * ���̊֐������s����O�ɂ��ꂼ��̃C�x���g�n���h����ݒ肵�Ă��������B
 */
void I2CSlave_com();



void I2CSlave_setInitEvent(void (*func)(uint8_t dat));
void I2CSlave_setReceiveEvent(void (*func)(uint8_t dat));
void I2CSlave_setStopEvent(void (*func)(void));
void I2CSlave_setSendEvent(unsigned char (*func)(void));

/**
 * TWCR���W�X�^��TWINT�r�b�g��Ԃ��܂�
 * @return 1 or 0
*/
unsigned char I2CSlave_isTWINT();


#endif /* I2CSLAVE_H_ */
