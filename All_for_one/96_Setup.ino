 void setup() {
  // put your setup code here, to run once:
   delay(1000);
  Serial.begin(9600);
  Wire.begin();
  Wire.setWireTimeout(500,1);


  pinMode(M1A, OUTPUT);
  pinMode(M1B, OUTPUT);
  pinMode(M1En, OUTPUT);
  pinMode(M1PWM, OUTPUT);

  pinMode(M2A, OUTPUT);
  pinMode(M2B, OUTPUT);
  pinMode(M2En, OUTPUT);
  pinMode(M2PWM, OUTPUT);

  pinMode(52,OUTPUT);
  pinMode(53,INPUT_PULLUP);
  digitalWrite(52 , 1);


   digitalWrite(M1En,1);
   digitalWrite(M2En,1);
     //analogWrite(A12,1023);

  Serial.println("begin setup");
  Tof_setup();
  Serial.println("done tof setup") ;
  //IMU_setup();
  //Serial.println("done imu setup");
  //BnW_setup();
  //temp_setup();
  //rescue_setup();
  Serial.println("done setup");

//while(1) Serial.println("done");

}
