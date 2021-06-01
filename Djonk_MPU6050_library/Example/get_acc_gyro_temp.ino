#include <Mpu6050_djonk.h>
#include <Wire.h>
using MPU::Mpu6050_djonk;
float *acc, *ang_speed;
TwoWire wire;
Mpu6050_djonk mpu(wire);
void setup() 
{
   
  Serial.begin(9600);
   mpu.set_config_data(0b00000000,0b00000000);
   mpu.set_up();

  //delay(5000);
  
}

void loop() 
{ acc = mpu.get_acc();
  ang_speed = mpu.get_angular_speed();
  
  Serial.print("temp: ");    Serial.print(mpu.get_temp1());
  Serial.print(" | accx: "); Serial.print(*acc,4);
  Serial.print(" | accy: "); Serial.print(*(acc+1),4);
  Serial.print(" | accz: "); Serial.print(*(acc+2),4);

  Serial.print(" | gyrox: "); Serial.print(*ang_speed,4);
  Serial.print(" | gyroy: "); Serial.print(*(ang_speed+1),4);
  Serial.print(" | gyroz: "); Serial.println(*(ang_speed+2),4);
  
}
