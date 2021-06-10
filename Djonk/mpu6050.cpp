#include "mpu6050.h"
#include "math.h"

mpu6050::mpu6050(TwoWire &w)
{
    wire = &w;
}

mpu6050::~mpu6050()
{
}

void mpu6050::calibration()
{
    int N_cal = 3000;
    for (int ii = 0; ii < N_cal; ii++)
    {
        if(ii % 200 == 0){Serial.println("calibration-----");}
		wire->beginTransmission(MPU6050_ADDR);
        wire->write(ACCEL_ADDR);//0x43
        wire->endTransmission();
        wire->requestFrom(MPU6050_ADDR,14);
 
         while(wire->available() < 14);

        off_set[0] += (((wire->read() << 8 | wire->read())));//-off_set[3] ;
        off_set[1] += (((wire->read() << 8 | wire->read())));//-off_set[4] ;
        off_set[2] += (((wire->read() << 8 | wire->read())));//-off_set[5] ;
        off_set[3] += (((wire->read() << 8 | wire->read())));//-off_set[3] ;
        off_set[4] += (((wire->read() << 8 | wire->read())));//-off_set[4] ;
        off_set[5] += (((wire->read() << 8 | wire->read())));//-off_set[5] ;
        off_set[6] += (((wire->read() << 8 | wire->read())));//-off_set[5] ;

        delay(3);
	}
    
    off_set[0] = (float)(off_set[0]/ N_cal );
	off_set[1] = (float)(off_set[1]/ N_cal );
	off_set[2] = (float)(off_set[2]/ N_cal );

    off_set[0] *= 0.0005987; //  unit m/s^2
    off_set[1] *= 0.0005987;
    off_set[2] *= 0.0005987;

 
 float grav = sqrt(off_set[0]*off_set[0] + off_set[1]*off_set[1] + off_set[2]*off_set[2]);

 off_set_pitch = asin( -off_set[0]/grav); // rad
 off_set_roll = asin(  off_set[1]/ (grav*cos(off_set_pitch))  ); // rad

  off_set_pitch *= 57.3248; // degree
  off_set_roll  *= 57.3248; // degree
      
}

void mpu6050::read_data(float Dt)
{
  wire->beginTransmission(MPU6050_ADDR);
  wire->write(ACCEL_ADDR);//0x3B
  wire->endTransmission();
  wire->requestFrom(MPU6050_ADDR,6);

 force[0] = (float)( (wire->read() << 8 | wire->read()) );// LSB 
 force[1] = (float)( (wire->read() << 8 | wire->read()) );// LSB 
 force[2] = (float)( (wire->read() << 8 | wire->read()) );// LSB

    //1g = 9.81m/s^2
    //9.81/16384 = 0.0005987;

 force[0] *= 0.0005987; //  unit m/s^2
 force[1] *= 0.0005987;
 force[2] *= 0.0005987;

 
 float grav = sqrt(force[0]*force[0] + force[1]*force[1] + force[2]*force[2]);

 acc_pitch = asin( -force[0]/grav); // rad
 acc_roll = asin(  force[1]/ (grav*cos(acc_pitch))  ); // rad

  acc_pitch *= 57.3248; // degree
  acc_roll  *= 57.3248; // degree

  acc_pitch -= off_set_pitch;
  acc_roll  -= off_set_roll;

}

void mpu6050::set_up()
{
    config(PWR_MGMT_1_ADDR,0b00000000);
    config(GYRO_CONFIG_ADDR,0x08);
    config(ACCEL_CONFIG_ADDR,0b00000000);
    delay(1000);

     off_set[0] = 0.0;
     off_set[1] = 0.0;
     off_set[2] = 0.0;
     off_set[3] = 0.0;
     off_set[4] = 0.0;
     off_set[5] = 0.0;
     off_set[6] = 0.0;

     calibration();
}

void mpu6050::config(byte reg,byte data)
{ 
 wire->beginTransmission(MPU6050_ADDR);
 wire->write(reg);
 wire->write(data);
 wire->endTransmission();
}