/*
 * I2CMaster.h
 *
 * Created: 2011/12/07 17:18:24
 *  Author: Hirokazu Yokoyama
 */


#ifndef I2CMASTER_H_
#define I2CMASTER_H_


static const uint8_t I2CMaster_PRESCALER_1 = 0x00;    // TWI�v���X�P�[�������l1
static const uint8_t I2CMaster_PRESCALER_4 = 0x01;    // TWI�v���X�P�[�������l4
static const uint8_t I2CMaster_PRESCALER_16 = 0x02;   // TWI�v���X�P�[�������l16
static const uint8_t I2CMaster_PRESCALER_64 = 0x03;   // TWI�v���X�P�[�������l64


typedef enum I2CMode {
    WRITE = 0,
	READ = 1
} I2CMode;

typedef enum Ack {
	ACK = 0,
	NOACK = 1
} Ack;

void I2CMaster_init(uint8_t bitRate, uint8_t prescaler);
void I2CMaster_start(unsigned char address, I2CMode mode);
void I2CMaster_stop();
unsigned char I2CMaster_write(unsigned char dat);
unsigned char I2CMaster_read(unsigned char ack);
unsigned char I2CMaster_isTWINT();
unsigned char I2CMaster_isACK();

/**
 * I2C�����������܂��B�����ŒʐM�̑��x��ݒ肵�܂��B�ʐM�̃N���b�N����
 * [ �N���b�N = (CPU�N���b�N���g��) / (16 + 2 * bitRate * prescaler) ]�Őݒ肳��܂��B
 * @param bitRate TWI�̑��x�̕����l
 * @param prescaler TWI�̃r�b�g���x�̑O�u�����l
 * = �Q�l�� =
 *  - �N���b�N8MHz���쎞�AbitRate = 2, prescaler = I2CMaster_PRESCALER_16
 */
void I2CMaster_init(uint8_t bitRate, uint8_t prescaler);

/**
 * �X�^�[�g�R���f�B�V�����𔭍s���A�X���[�u�̃A�h���X�𑗐M���܂��B
 * (���M�̏ꍇ�ł��r�b�g�V�t�g�����X���[�u�A�h���X��n���K�v�͂���܂���)
 * @param address �ʐM����X���[�u�A�h���X
 * @param mode  ���M:WRITE(0) or ��M:READ(1)���w��
 */
void I2CMaster_start(unsigned char address, I2CMode mode);

/**
 * �X�g�b�v�R���f�B�V�����𔭍s���܂��B
 */
void I2CMaster_stop();

/**
 * �f�[�^�𑗐M���܂��B
 * @param dat ���M����f�[�^
 * @return 1:ACK / 0:NOACK
 */
unsigned char I2CMaster_write(unsigned char dat);

/**
 * �f�[�^����M���܂�
 * @param ack
 * @return ��M�f�[�^
 */
unsigned char I2CMaster_read(unsigned char ack);

/**
 * TWCR���W�X�^��TWINT�̒l��Ԃ��܂��B
 * @return TWINT��1�Ȃ�1, 0�Ȃ�0
 */
unsigned char I2CMaster_isTWINT();

unsigned char I2CMaster_isACK();
#endif /* I2CMASTER_H_ */