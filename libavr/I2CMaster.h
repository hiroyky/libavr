/*
 * I2CMaster.h
 *
 * Created: 2011/12/07 17:18:24
 *  Author: Hirokazu Yokoyama
 */


#ifndef I2CMASTER_H_
#define I2CMASTER_H_


static const uint8_t I2CMaster_PRESCALER_1 = 0x00;    // TWIプリスケーラ分周値1
static const uint8_t I2CMaster_PRESCALER_4 = 0x01;    // TWIプリスケーラ分周値4
static const uint8_t I2CMaster_PRESCALER_16 = 0x02;   // TWIプリスケーラ分周値16
static const uint8_t I2CMaster_PRESCALER_64 = 0x03;   // TWIプリスケーラ分周値64


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
 * I2Cを初期化します。ここで通信の速度を設定します。通信のクロック数は
 * [ クロック = (CPUクロック周波数) / (16 + 2 * bitRate * prescaler) ]で設定されます。
 * @param bitRate TWIの速度の分周値
 * @param prescaler TWIのビット速度の前置分周値
 * = 参考例 =
 *  - クロック8MHz動作時、bitRate = 2, prescaler = I2CMaster_PRESCALER_16
 */
void I2CMaster_init(uint8_t bitRate, uint8_t prescaler);

/**
 * スタートコンディションを発行し、スレーブのアドレスを送信します。
 * (送信の場合でもビットシフトしたスレーブアドレスを渡す必要はありません)
 * @param address 通信するスレーブアドレス
 * @param mode  送信:WRITE(0) or 受信:READ(1)を指定
 */
void I2CMaster_start(unsigned char address, I2CMode mode);

/**
 * ストップコンディションを発行します。
 */
void I2CMaster_stop();

/**
 * データを送信します。
 * @param dat 送信するデータ
 * @return 1:ACK / 0:NOACK
 */
unsigned char I2CMaster_write(unsigned char dat);

/**
 * データを受信します
 * @param ack
 * @return 受信データ
 */
unsigned char I2CMaster_read(unsigned char ack);

/**
 * TWCRレジスタのTWINTの値を返します。
 * @return TWINTが1なら1, 0なら0
 */
unsigned char I2CMaster_isTWINT();

unsigned char I2CMaster_isACK();
#endif /* I2CMASTER_H_ */