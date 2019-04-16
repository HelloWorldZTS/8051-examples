#include "iic.h"
#include "delay.h"
#include "stdio.h"
#include "serial.h"
#include "mpu6050.h"
#include <mcs51/8051.h>

int putchar(int c)
{
	while(!(SCON & 0x02));
	SCON &= ~0x02;
	SBUF = (char)c;
  return c;
}

void main()
{
  uint8_t data_h;
  uint8_t data_l;
  uint16_t data;
  MPU6050 mpu6050;
  mpu6050.deviceAddress = 0xD0;

  serial_init();
  mpu6050_init(&mpu6050);
  delay_ms(1000);

  while(1)
  {
    iic_single_byte_read(mpu6050.deviceAddress, GYRO_XOUT_H, &data_h);
    iic_single_byte_read(mpu6050.deviceAddress, GYRO_XOUT_H+1, &data_l);

    data = ((uint16_t)data_h) << 8 | ((uint16_t)data_l);

    printf("data is %d\n", data);

    delay_ms(1);
  }
}
