
//TOF  setup 






//when we put our finger on the sensor we noticed that the min val of each sensor is different 
//so this was to make them equal 
//(we didn't use them this year so the numbers are wrong)
int front_error = 40;
int right1_error = 35;
int right2_error = 20;
int left1_error = 20;
int left2_error = 10;
int back_error = 20;




#define xshut_pinf 25
#define xshut_pinr1 26
#define xshut_pinr2 23
#define xshut_pinl1 27
#define xshut_pinl2 24
#define xshut_pinb 22

#define frontadd 0x04
#define right1add 0x05
#define right2add 0x06
#define left1add 0x07
#define left2add 0x08
#define backadd 0x09


VL53L0X Front;
VL53L0X Right1;
VL53L0X Right2;
VL53L0X Left1;
VL53L0X Left2;
VL53L0X Back;


// #define LONG_RANGE

inline void Tof_setup() {
  
  Front.setTimeout(500);
  Right1.setTimeout(500);
  Right2.setTimeout(500);
  Left1.setTimeout(500);
  Left2.setTimeout(500);
  Back.setTimeout(500);

  Serial.println("done pinmode1");

  pinMode(xshut_pinf, OUTPUT);
  digitalWrite(xshut_pinf,HIGH);
  delay(10);
  Front.setAddress(frontadd);
  pinMode(xshut_pinf, INPUT);

  pinMode(xshut_pinr1, OUTPUT);
  digitalWrite(xshut_pinr1,HIGH);
  delay(10);
  Right1.setAddress(right1add);
  pinMode(xshut_pinr1, INPUT);
  //
  pinMode(xshut_pinr2, OUTPUT);
  digitalWrite(xshut_pinr2,HIGH);
  delay(10);
  Right2.setAddress(right2add);
  pinMode(xshut_pinr2, INPUT);
  //Serial.println("done r set add");
  // //
   pinMode(xshut_pinl1, OUTPUT);
   digitalWrite(xshut_pinl1,HIGH);
   delay(10);
   Left1.setAddress(left1add);
   pinMode(xshut_pinl1,INPUT);
  // Serial.println("done l1 set add");
  // //
  pinMode(xshut_pinl2, OUTPUT);
  digitalWrite(xshut_pinl2,HIGH);
  delay(10);
  Left2.setAddress(left2add);
  pinMode(xshut_pinl2,INPUT);
  //Serial.println("done l2 set add");
  // //
  pinMode(xshut_pinb, OUTPUT);
  digitalWrite(xshut_pinb,HIGH);
   delay(10);
  Back.setAddress(backadd);
  pinMode(xshut_pinb,INPUT);
  
  Serial.println("done pinmode2");
  
  ////Serial.println("done setting address");
  // Right1.setTimeout(500);

  if (!Front.init()) Serial.println("Failed front");
  if (!Right1.init()) Serial.println("Failed right1");
  if (!Right2.init()) Serial.println("Failed right2");
  if (!Left1.init()) Serial.println("Failed left1");
  if (!Left2.init()) Serial.println("Failed left2");
  if (!Back.init()) Serial.println("Failed back");
  
  delay(1000);
  Serial.println("done tof initialization");
  
  Serial.println("done tof set timeout");

  // #if defined LONG_RANGE
  //   //  // lower the return signal rate limit (default is 0.25 MCPS)
  //   //Front.setSignalRateLimit(0.1);
  //   //Right1.setSignalRateLimit(0.1);
  //   Right2.setSignalRateLimit(0.1);
  //   Left1.setSignalRateLimit(0.1);
  //   Left2.setSignalRateLimit(0.1);
  //   Back.setSignalRateLimit(0.1);
  //   // increase laser pulse periods (defaults are 14 and 10 PCLKs)
  //   //Front.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
  //   //Front.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);
  //   //Right1.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
  //   //Right1.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);
  //   Right2.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
  //   Right2.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);
  //   ////  //
  //   Left1.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
  //   Left1.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);
  //   Left2.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
  //   Left2.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);
  //   Back.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
  //   Back.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);
  // #endif



  Front.startContinuous();
  Right1.startContinuous();
  Right2.startContinuous();
  Left1.startContinuous();
  Left2.startContinuous();
  Back.startContinuous();
}
