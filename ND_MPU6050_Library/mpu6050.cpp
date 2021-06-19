#include "mpu6050.h"
#include "math.h"

mpu6050::~mpu6050()
{}

mpu6050::mpu6050(TwoWire &w,byte cfg_pwr=0b00000000,byte cfg_acc=0b00000000,byte cfg_gyro=0b00000000)
{
    wire = &w;
    config_acc = cfg_acc;
    config_gyro = cfg_acc;
    config_PWR = cfg_pwr;
}

void mpu6050::set_up()
{
 wire->begin();
 wire->beginTransmission(MPU6050_ADDR);
 wire->write(PWR_MGMT_1_ADDR);
 wire->write(config_PWR);
 wire->endTransmission(); 
  delay(5);
  
 wire->begin();
 wire->beginTransmission(MPU6050_ADDR);
 wire->write(ACCEL_CONFIG_ADDR);
 wire->write(config_acc);
 wire->endTransmission(); 
  delay(5);

 wire->begin();
 wire->beginTransmission(MPU6050_ADDR);
 wire->write(GYRO_CONFIG_ADDR);
 wire->write(config_gyro);
 wire->endTransmission(); 
  delay(5);

  calibrate_roll_pitch();

  Serial.println("Offset:----------------");
  Serial.print("roll: "); Serial.println(roll_offset,4);
  Serial.print("pitch: "); Serial.println(pitch_offset,4);
  Serial.println("------------------------");
  

}

void mpu6050::calibrate_roll_pitch()
{
  roll_offset = 0; pitch_offset = 0;
  for(int i=0; i<3000;++i)
  {
    wire->beginTransmission(MPU6050_ADDR);
    wire->write(ACCEL_ADDR);
    wire->endTransmission(); 
    wire->requestFrom(MPU6050_ADDR,6);

    int16_t raw_off1  = wire->read() << 8 | wire->read() ;
    int16_t raw_off2  = wire->read() << 8 | wire->read() ;
    int16_t raw_off3  = wire->read() << 8 | wire->read() ;

   float f1[3] = {((float)raw_off1)*0.0006, ((float)raw_off2)*0.0006, ((float)raw_off3)*0.0006};
   float Total_force = sqrt(f1[0]*f1[0] + f1[1]*f1[1] + f1[2]*f1[2]);

    roll_offset += atan2(f1[1],f1[2])*57.325;
    pitch_offset += asin(f1[0] / Total_force)*57.325;
    delay(5);
  }

  roll_offset /= 3000.0;
  pitch_offset /= 3000.0;

}

void mpu6050::read_data()
{
 wire->beginTransmission(MPU6050_ADDR);
 wire->write(ACCEL_ADDR);
 wire->endTransmission(); 
 wire->requestFrom(MPU6050_ADDR,14);
 raw_acc[0]  = wire->read() << 8 | wire->read() ;
 raw_acc[1]  = wire->read() << 8 | wire->read() ;
 raw_acc[2]  = wire->read() << 8 | wire->read() ;

 raw_temp    = wire->read() << 8 | wire->read() ;

 raw_gyro[0] = wire->read() << 8 | wire->read() ;
 raw_gyro[1] = wire->read() << 8 | wire->read() ;
 raw_gyro[2] = wire->read() << 8 | wire->read() ;

 // compute roll pitch acceleration

 float f1[3] = {((float)raw_acc[0])*0.0006, ((float)raw_acc[1])*0.0006, ((float)raw_acc[2])*0.0006};
 float Total_force = sqrt(f1[0]*f1[0] + f1[1]*f1[1] + f1[2]*f1[2]);
 
 roll_acc  = atan2(f1[1],f1[2])*57.325  - roll_offset;
 pitch_acc = asin(f1[0] / Total_force)*57.325  - pitch_offset;

 // compute p, q and r from gyro

  pg = (float)raw_gyro[0] / 131.0 ; // °/s
  qg = (float)raw_gyro[1] / 131.0;
  rg = (float)raw_gyro[2] / 131.0;

 // complementary filter
  float DT = 0.0004; //4ms
  

  pitch = 0.02*pitch_acc + 0.98*(pitch + DT*qg); //gama = 0.98
  roll = 0.25*roll_acc + 0.75*(roll + DT*pg); // gama = 0.8
 //pitch = (1.0 - gama)*pitch_acc + gama*(pitch + DT*qg);


}