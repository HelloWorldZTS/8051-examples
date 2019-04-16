#include "mpu6050.h"

void mpu6050_init(MPU6050 *mpu6050)
{
  iic_single_byte_write(mpu6050 -> deviceAddress, PWR_MGMT_1, 0x00);
  iic_single_byte_write(mpu6050 -> deviceAddress, SMPLRT_DIV, 0x07);
  iic_single_byte_write(mpu6050 -> deviceAddress, CONFIG, 0x06);
  iic_single_byte_write(mpu6050 -> deviceAddress, GYRO_CONFIG, 0x18);
  iic_single_byte_write(mpu6050 -> deviceAddress, ACCEL_CONFIG, 0x01);
}
