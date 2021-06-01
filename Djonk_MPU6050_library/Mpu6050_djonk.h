#ifndef _MPU6050_DJONK_
#define _MPU6050_DJONK_

#include "Arduino.h"
#include "Wire.h"

const byte MPU6050_ADDR = 0x68;
const byte PWR_MGMT_1_ADDR = 0x6B;
const byte GYRO_CONFIG_ADDR = 0x1B;
const byte ACCEL_CONFIG_ADDR = 0x1C;
const byte ACCEL_ADDR = 0x3B;
const byte GYRO_ADDR = 0x43;
const byte TEMPERATURE_ADDR = 0x41;

const float lsb[8] = {16384,8192,4096,2048,131,65.5,32.8,16.4};
const float fs_sel[4]={0,1,2,3};


/*
 acceleration full scale selector                Sensitivity
 0-> 2g                                          16384
 1-> 4g                                           8192
 2-> 8g                                           4096
 3-> 16g                                          2048

 gyroscope full scale selector                   Sensitivity
 0-> 250°/s                                        131
 1-> 500°/s                                        65.5
 2-> 1000°/s                                       32.8
 3-> 2000°/s                                       16.4

*/
namespace MPU
{


 class Mpu6050_djonk
 {
 private:
    float acc[3],gyro[3];
    TwoWire *wire;
    float lsb_acc,lsb_gyro;
    void config(byte reg,byte data );
     byte cfg_data[2];
  public:
    Mpu6050_djonk(TwoWire &w);
    ~Mpu6050_djonk();
    float* get_acc();
    float get_temp1();
    float* get_angular_speed();
    void set_up();
    void set_config_data(byte ac,byte gyr);
   
 };




}
#endif
