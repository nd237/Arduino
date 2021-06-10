#include <mpu6050.h>
#include <Wire.h>
#include <math.h>

TwoWire wire;
mpu6050 mpu(wire);


void setup() 
{
  Serial.begin(9600);
  mpu.set_up();
  Serial.println(mpu.off_set_pitch,4);
  Serial.println(mpu.off_set_roll,4);
  //Serial.println(mpu.off_set[2],4);

}

void loop() {
  mpu.read_data(1/8000.0);
 
  Serial.print(" FX: ");Serial.print(mpu.force[0],4);Serial.print(" FY: ");
  Serial.print(mpu.force[1],4);Serial.print(" FZ: ");Serial.print(mpu.force[2],4);
  Serial.print(" pitch: ");Serial.print(mpu.acc_pitch,4);Serial.print(" roll: ");Serial.println(mpu.acc_roll,4);
  delay(1000);
  



}
