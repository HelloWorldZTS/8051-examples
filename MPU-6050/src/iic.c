#include "iic.h"

/**
 * SDA change high to low when SCL is high
 */
void iic_start(void)
{
  IIC_SCL = 0;
  __nop(); __nop();
  IIC_SDA = 1;
  IIC_SCL = 1;
  __nop(); __nop();
  IIC_SDA = 0;
}

/**
 * SDA changes low to high when SCL is high
 */
void iic_stop(void)
{
  IIC_SCL = 0;
  __nop(); __nop();
  IIC_SDA = 0;
  IIC_SCL = 1;
  __nop(); __nop();
  IIC_SDA = 1;
}

void iic_ack(void)
{
  IIC_SCL = 0;
  __nop(); __nop();
  IIC_SDA = 0;
  __nop(); __nop();
  IIC_SCL = 1;
}

void iic_nack(void)
{
  IIC_SCL = 0;
  __nop(); __nop();
  IIC_SDA = 1;
  __nop(); __nop();
  IIC_SCL = 1;
}

uint8_t iic_read_ack(void)
{
  IIC_SCL = 0;
  __nop(); __nop();
  IIC_SCL = 1;
  __nop(); __nop();
  return IIC_SDA;
}

void iic_send_byte(uint8_t data)
{
  uint8_t i;
  for(i=0; i<8; i++)
  {
    IIC_SCL = 0;
    __nop(); __nop();
    IIC_SDA = (data << i) & 0x80;
    __nop(); __nop();
    IIC_SCL = 1;
  }
}

uint8_t iic_read_byte(void)
{
  uint8_t i;
  uint8_t data = 0x00;
  for(i=0; i<8; i++)
  {
    IIC_SCL = 0;
    __nop(); __nop();
    data <<= 1;
    IIC_SCL = 1;
    __nop(); __nop();
    data |= (uint8_t)IIC_SDA;
  }
  return data;
}

void iic_single_byte_read(uint8_t deviceAddress, uint8_t registerAddress, uint8_t *data)
{
  iic_start();
  iic_send_byte(deviceAddress);
  iic_read_ack();
  iic_send_byte(registerAddress);
  iic_read_ack();
  iic_start();
  iic_send_byte(deviceAddress | 0x01);
  iic_read_ack();
  *data = iic_read_byte();
  iic_nack();
  iic_stop();
}

void iic_single_byte_write(uint8_t deviceAddress, uint8_t registerAddress, uint8_t data)
{
  iic_start();
  iic_send_byte(deviceAddress);
  iic_read_ack();
  iic_send_byte(registerAddress);
  iic_read_ack();
  iic_send_byte(data);
  iic_read_ack();
  iic_stop();
}
