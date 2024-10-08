 void loop() {
  // put your main code here, to run repeatedly:
  // Serial.print("front : ");
  // Serial.print(Front.readRangeContinuousMillimeters());
  // Serial.print(" Right : ");
  // Serial.print(Right1.readRangeContinuousMillimeters());
  // Serial.print(" Right2 ");
  // Serial.print(Right2.readRangeContinuousMillimeters());
  // Serial.print(" Left1 : ");
  // Serial.print(Left1.readRangeContinuousMillimeters());
  // Serial.print(" Left2 : ");
  // Serial.print(Left2.readRangeContinuousMillimeters());
  // Serial.print(" Back : ");
  // Serial.print(Back.readRangeContinuousMillimeters());
  //mpu.update();
  //Serial.print("Angle : ");
  //Serial.println(mpu.getAngleZ());
  //while(1)Serial.println(color());

  //delay(500);
  //turn('L');
  //delay(5000);
  //delay_turn('R');
  //delay(2000);  
  //Serial.println();
  //e3dell();
  //front_one_tile();
  //rescue_kit(2);
  //back_one_tile();
  //delay(3000);
  //motor_control('F',speedd);
  //code
  // Serial.read();
  //while (!Serial.available()) { }
  //while (Serial.available()) Serial.read();   /////
  Serial.print(posX);
  Serial.print(" ");
  Serial.println(posY);
  if(color() > 0 && color() < 4) //  blue
  {
    Serial.println("blue");
    delay(5000);
    Serial.println("done bllue");
  }

  if (state[posX][posY] & 1) {
    Serial.println("old tile");
    Next();
  } else {
    Serial.println("new tile");

    all();
    //Serial.print("front(after all ) : ");
    //Serial.println(Front.readRangeContinuousMillimeters());
    Next();
    //align();

  }
  Serial.print("unvisited =");
  Serial.println(unvisited);
  Serial.println("Done Loop");
  Serial.print(posX);
  Serial.print(" ");
  Serial.println(posY);
  
  while (unvisited == 0 && posX == 25 && posY == 25) {}
}
