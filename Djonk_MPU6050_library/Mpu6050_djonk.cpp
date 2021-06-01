#include "Mpu6050_djonk.h"
#include "Arduino.h"

MPU::Mpu6050_djonk::~Mpu6050_djonk()
{
}

MPU::Mpu6050_djonk::Mpu6050_djonk(TwoWire &w)
{
 
 lsb_acc = lsb[0];
 lsb_gyro = lsb[4];
 cfg_data[0] = 0b00000000;
 cfg_data[1] = 0b00000000;
 wire = &w;
}


void MPU::Mpu6050_djonk::set_up()
{
 
 config(PWR_MGMT_1_ADDR,0b00000000);
 config(GYRO_CONFIG_ADDR,cfg_data[1]);
 config(ACCEL_CONFIG_ADDR,cfg_data[0]);
 Serial.println(lsb_acc);
 Serial.println(lsb_gyro);
 delay(2000);
}

float MPU::Mpu6050_djonk::get_temp1()
{
 wire->beginTransmission(MPU6050_ADDR);
 wire->write(TEMPERATURE_ADDR);//0x41
 wire->endTransmission();
 wire->requestFrom(MPU6050_ADDR,2);
 float raw_temp = (wire->read() << 8 | wire->read()) ;
 return (raw_temp /340) + 36.53;
}

float* MPU::Mpu6050_djonk::get_acc()
{
 wire->beginTransmission(MPU6050_ADDR);
 wire->write(ACCEL_ADDR);//0x3B
 wire->endTransmission();
 wire->requestFrom(MPU6050_ADDR,6);

 acc[0] = ((float)(wire->read() << 8 | wire->read()))/lsb_acc ;
 acc[1] = ((float)(wire->read() << 8 | wire->read()))/lsb_acc ;
 acc[2] = ((float)(wire->read() << 8 | wire->read()))/lsb_acc ;
 
 return acc;
}


float* MPU::Mpu6050_djonk::get_angular_speed()
{
 wire->beginTransmission(MPU6050_ADDR);
 wire->write(GYRO_ADDR);//0x43
 wire->endTransmission();
 wire->requestFrom(MPU6050_ADDR,6);

 gyro[0] = ((float)(wire->read() << 8 | wire->read()))/lsb_gyro ;
 gyro[1] = ((float)(wire->read() << 8 | wire->read()))/lsb_gyro ;
 gyro[2] = ((float)(wire->read() << 8 | wire->read()))/lsb_gyro ;
 
 return gyro;
}



void MPU::Mpu6050_djonk::set_config_data(byte ac,byte gyr)
{
  cfg_data[0] = ac;
  cfg_data[1] = gyr;

  if(cfg_data[0] == 0b00000000){lsb_acc = lsb[0];}
  else if(cfg_data[0] == 0b00000001){lsb_acc = lsb[1];}
  else if(cfg_data[0] == 0b00000010){lsb_acc = lsb[2];}
  else if(cfg_data[0] == 0b00000011){lsb_acc = lsb[3];}else{lsb_acc = lsb[0]; cfg_data[0] = 0b00000000;}

  if(cfg_data[1] == 0b00000000){lsb_gyro = lsb[4];}
  else if(cfg_data[1] == 0b00000001){lsb_gyro = lsb[5];}
  else if(cfg_data[1] == 0b00000010){lsb_gyro = lsb[6];}
  else if(cfg_data[1] == 0b00000011){lsb_gyro = lsb[7];}else{lsb_gyro = lsb[4];cfg_data[1] = 0b00000000;}
    //lsb_gyro = lsb[4];
}

void MPU::Mpu6050_djonk::config(byte reg,byte data )
{

 wire->beginTransmission(MPU6050_ADDR);
 wire->write(reg);
 wire->write(data);
 wire->endTransmission();
}























