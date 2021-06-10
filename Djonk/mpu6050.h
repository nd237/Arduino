#ifndef _MPU6050_
#define _MPU6050_
#include "Arduino.h"
#include "Wire.h"

const byte MPU6050_ADDR = 0x68;
const byte PWR_MGMT_1_ADDR = 0x6B;
const byte GYRO_CONFIG_ADDR = 0x1B;
const byte ACCEL_CONFIG_ADDR = 0x1C;
const byte ACCEL_ADDR = 0x3B;
const byte GYRO_ADDR = 0x43;
const byte TEMPERATURE_ADDR = 0x41;

const float lsb[8] = {16384,8192,4096,2048,131,65.5,32.8,16.4};// 4 accx + 4 gyro lsb
const float fs_sel[4]={0,1,2,3};

//step1: configuration
//step2:set_up()

class mpu6050
{
private:
    TwoWire *wire;
    
    void config(byte reg,byte data);
    void calibration();
public:
     mpu6050(TwoWire &w);
    ~mpu6050();
    void set_up();
    void read_data(float Dt);
    float off_set[7];
    float force[3],acc_pitch,acc_roll,off_set_pitch,off_set_roll;
};









#endif
