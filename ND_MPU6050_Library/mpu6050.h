#ifndef _MPU6050_
#define _MPU6050_
#include "Arduino.h"
#include "Wire.h"

//2021/06/16 --> configure the mpu6050 sensor

// Registries
const byte MPU6050_ADDR = 0x68;
const byte PWR_MGMT_1_ADDR = 0x6B;
const byte GYRO_CONFIG_ADDR = 0x1B;
const byte ACCEL_CONFIG_ADDR = 0x1C;
const byte ACCEL_ADDR = 0x3B;
const byte GYRO_ADDR = 0x43;
const byte TEMPERATURE_ADDR = 0x41;

class mpu6050
{
private:
    TwoWire *wire;
    byte config_acc,config_gyro,config_PWR; 
    int16_t raw_acc[3],raw_gyro[3],raw_temp;
    float roll_offset,pitch_offset;
    float pg,qg,rg;
    void calibrate_roll_pitch();
    
public:
    mpu6050(TwoWire &w,byte cfg_pwr=0b00000000,byte cfg_acc=0b00000000,byte cfg_gyro=0b00000000);
    ~mpu6050();
    void set_up();
    void read_data();
    float roll_acc,pitch_acc,roll=0,pitch=0;;
    
};



#endif