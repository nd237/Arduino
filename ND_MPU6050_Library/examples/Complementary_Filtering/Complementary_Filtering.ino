#include <mpu6050.h>

#include <Wire.h>
TwoWire wire;
mpu6050 mpu(wire);

void setup() 
{
  
   Serial.begin(9600);
   mpu.set_up();
   
}

void loop() 
{
   mpu.read_data();
  

   Serial.print(mpu.pitch_acc);
   Serial.print(" ");
   Serial.print(mpu.pitch);
   Serial.print(" ");
   Serial.print(mpu.roll_acc);
   Serial.print(" ");
   Serial.println(mpu.roll);

   
  
 
}
