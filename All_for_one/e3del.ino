//e3delr/e3dell are used to make the robot parallel to the wall
// the others were used to make the robot in the center of the tile ( we didn't use them this year )



void e3delr()
{
  Serial.println("e3delr");
  //Serial.print(Right1.readRangeContinuousMillimeters());
  //Serial.print(" ");
  //Serial.println(Right2.readRangeContinuousMillimeters());
  int r1 = Right1.readRangeContinuousMillimeters()-30;
  int r2 = Right2.readRangeContinuousMillimeters();
  Serial.print(r1);
  Serial.print(" ");
  Serial.println(r2);
  if(max(r1,r2)>240)return;
  while(abs(r1-r2)>5)
  {
    delay(20);
    r1 = Right1.readRangeContinuousMillimeters()-30;
    r2 = Right2.readRangeContinuousMillimeters();
    Serial.print(r1);
    Serial.print(" ");
    Serial.println(r2);
    if(r1<0||r2<0)break;
    if(r1>r2)
    {
      motor_control('R',speedd);
    }
    else if (r2>r1)
    {
      motor_control('L',speedd);
    }
  }
  motor_control('S',0);
}


void e3dell()
{
  Serial.println("e3dell");
  int l1 = Left1.readRangeContinuousMillimeters();
  int l2 = Left2.readRangeContinuousMillimeters();
  Serial.print(l1);
  Serial.print(" ");
  Serial.println(l2);
  if(max(l1,l2)>240)return;
  while(abs(l1-l2)>2)
  {
    delay(20);
    l1 = Left1.readRangeContinuousMillimeters();
    l2 = Left2.readRangeContinuousMillimeters();
    Serial.print(l1);
    Serial.print(" ");
    Serial.println(l2);
    if(l1 == -1 || l2 == -1)break;
    if(l1>l2)
    {
      motor_control('L',speedd);
    }
    else if (l2>l1)
    {
      motor_control('R',speedd);
    }
  }
  motor_control('S',0);
}

void e3del()
{
  int l1 = Left1.readRangeContinuousMillimeters();
  int l2 = Left2.readRangeContinuousMillimeters();
  int r1 = Right1.readRangeContinuousMillimeters()-30;
  int r2 = Right2.readRangeContinuousMillimeters();
  delay(20);
  if(max(r1,r2)<1000)
  {
    for(int i=0;i<5;i++)e3delr();
  }
  else if (max(l1,l2)<1000)
  {
    for(int i=0;i<5;i++)e3dell();
  }

}


void eb3edf()
{
  // int f = Front.readRangeSingleMillimeters();
  // //Serial.println("eb3edf");
  // //Serial.println(f);
  // while((f<75||f>90)&&f<240)
  // {
  //   f = Front.readRangeSingleMillimeters(); 
  //   if(f<75)motor_control('B',speedd/2);
  //   else if(f >90)motor_control('F',speedd/2);
  // }
  // motor_control('S',0);    
}

void eb3edb()
{
  // int b = Back.readRangeSingleMillimeters();
  // //Serial.println("eb3edb");
  // //Serial.println(b);
  // while((b<85||b>100)&&b<240)
  // {
  //   b = Back.readRangeSingleMillimeters(); 
  //   if(b<85)motor_control('F',speedd/2);
  //   else if(b >100)motor_control('B',speedd/2);
  // }
  // motor_control('S',0);    
}


void eb3edr()
{
  // int r = Right1.readRangeSingleMillimeters();
  // //Serial.println("eb3edr");
  // //Serial.println(r);
  // while((r<90||r>107)&&r<240)
  // {
  //   r = Right1.readRangeSingleMillimeters(); 
  //   if(r<90)motor_control('A',speedd/2);
  //   else if(r>107)motor_control('D',speedd/2);
  // }
  // motor_control('S',0); 
}


void eb3edl()
{
//   int l = Left1.readRangeSingleMillimeters();
//   //Serial.println("eb3edl");
//   //Serial.println(l);
//   while((l<90||l>107)&&l<240)
//   {
//     l = Left1.readRangeSingleMillimeters(); 
//     if(l<90)motor_control('D',speedd/2);
//     else if(l>107)motor_control('A',speedd/2);
//   }
//   motor_control('S',0); 
// }

// void align()
// {
//    e3delr();
//    delay(100);
//    e3dell();
//    delay(100);
   
//    //eb3edr();
//    //delay(100);
//    //eb3edl();
//    //delay(100);

//    e3delr();
//    delay(100);
//    e3dell();
//    delay(100);

//    eb3edf();
//    delay(100);
//    eb3edb();
//    delay(100);
}
