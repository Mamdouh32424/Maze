//MOTOR1
#define M1A 2
#define M1B 4
#define M1En 6
#define M1PWM 9

//MOTOR2
#define M2A 7
#define M2B 8
#define M2En 12
#define M2PWM 10

int speedd = 80;

// this function is self-explanitory
inline void motor_control(char move, int motorspeed) {
  digitalWrite(M1En, 1);
  digitalWrite(M2En, 1);
  if (move == 'F') {
    Serial.println("Front");
    analogWrite(M1PWM, motorspeed);
    analogWrite(M2PWM, motorspeed);

    digitalWrite(M1A, 0);
    digitalWrite(M1B, 1);


    digitalWrite(M2A, 0);
    digitalWrite(M2B, 1);
    return;

  } else if (move == 'B') {
    analogWrite(M1PWM, motorspeed);
    analogWrite(M2PWM, motorspeed);

    digitalWrite(M1A, 1);
    digitalWrite(M1B, 0);


    digitalWrite(M2A, 1);
    digitalWrite(M2B, 0);
  } else if (move == 'R') {
    analogWrite(M1PWM, motorspeed);
    analogWrite(M2PWM, motorspeed);

    digitalWrite(M1A, 1);
    digitalWrite(M1B, 0);


    digitalWrite(M2A, 0);
    digitalWrite(M2B, 1);

  } else if (move == 'L') {
    analogWrite(M1PWM, motorspeed);
    analogWrite(M2PWM, motorspeed);

    digitalWrite(M1A, 0);
    digitalWrite(M1B, 1);


    digitalWrite(M2A, 1);
    digitalWrite(M2B, 0u);
  } else if (move == 'S') {
    Serial.println("Stop");
    analogWrite(M1PWM, 255);
    analogWrite(M2PWM, 255);
    digitalWrite(M1A, 0);
    digitalWrite(M1B, 0);


    digitalWrite(M2A, 0);
    digitalWrite(M2B, 0);
  }
}

//____________________________________________________________________________________MOVING ONE TILE____________________________________________________________________________________
// read them in this order 
// one_tile
// front_one_tile and back_one_tile
// black_tile
// ramp


unsigned long tile_delay = 1000;

//this was used when we knew we're on a ramp using the imu
//it makes the robot move faster (last year's robot would slide down)
//and skips to the next tile in the map because we couldn't stop on the ramp (I'm pretty sure we could this year but oh well)

inline void ramp() {
  // motor_control('F', 165);
  // while (abs(mpu.getAngleY()) >= 5) {
  //   mpu.update();
  //   //Serial.println(-mpu.getAngleY());
  // }
  // motor_control('S', 0);
  // motor_control('F', speedd);
  // delay(tile_delay / 4);
  // motor_control('S', 0);
  // delay(1000);
  // byte x = 0;
  // x |= (1 << 3);
  // x |= (1 << 1);
  // x = ChangeOrientation(x);
  // state[posX][posY] = ((x << 4) | 1);

  // if (orientation == 0) posX--;
  // if (orientation == 1) posY++;
  // if (orientation == 2) posX++;
  // if (orientation == 3) posY++;
}



// when we're moving a tile we start a timer 
// so when the sensors sees black 
// we go back the amount of time we moved forward 
// last year this would make us go exactly to the starting position
// but I noticed this year it didn't bas it didn't make that much of a problem (because for some reason our backward speed was higher than forward)

inline void black_tile(int timee) {
  //Serial.println("black tile");
  delay(500);
  motor_control('B', speedd);
  delay(timee);
  motor_control('S', 0);
  state[posX][posY] |= (1 << 2);
  unvisited--;
  posX = prevX;
  posY = prevY;
}

// if there's anything you don't understand in this tell me
inline bool front_one_tile() 
{
  //Serial.flush();
  Serial.println("front one tile");
  delay(1000);
  int start = Front.readRangeContinuousMillimeters();
  Serial.println(start);
  Serial.println(start - 250);
  unsigned long tt = millis();

  Serial.println("START");
  int black = 0;
  delay(50);
  int hamada = Front.readRangeContinuousMillimeters();
  while (hamada > start - 270 &&( hamada > 60 || hamada != -1))  //////////////////RANGE CHANGE
  {
    while(hamada == -1) { delay(30); hamada = Front.readRangeContinuousMillimeters();    motor_control('S', 0);}

    motor_control('F', speedd);
    Serial.print("target : ");
    Serial.print(start - 250);
    Serial.print("  reading : ");
    Serial.println(hamada);
     if(color() == 0)black++;
     if(black == 5)
     {
       motor_control('S',0); 
       black_tile(millis() - tt);
       return 0;
     }
     delay(50);
    hamada = Front.readRangeContinuousMillimeters();
    
  }
  motor_control('S', 0);
  tile_delay = millis() - tt;
  Serial.println("STOP");
  return 1;
}




inline bool back_one_tile() {
  Serial.println("back one tile");
  delay(30);
  int start = Back.readRangeContinuousMillimeters();
  unsigned long tt = millis();

  int black = 0;
  Serial.print("target  : ");
  Serial.println(start + 200);
  Serial.print("front ");
  delay(30);
  Serial.println(Front.readRangeContinuousMillimeters());
  delay(50);
  int hamada = Back.readRangeContinuousMillimeters();
  int hamadaF=  Front.readRangeContinuousMillimeters();
  while (hamada < start + 230 && hamadaF > 100)  //////////////////RANGE CHANGE
  {
    //Serial.flush();
    motor_control('F', speedd);
    //mpu.update();
    Serial.print("back ");
    Serial.println(hamada);
    //Serial.print("front ");
    //Serial.println(Front.readRangeContinuousMillimeters());

    /*if(abs(mpu.getAngleY())>10)
      {
        Serial.println("RAMP");
        ramp();
        return;
      }*/
    //Serial.println(check_black());
    if(color() == 0)black++;
    if(black == 5)
      {
        Serial.println("black");
        motor_control('S',0);
        black_tile(millis() - tt);
        return 0;
      }
      delay(50);
      hamada = Back.readRangeContinuousMillimeters();
      hamadaF=  Front.readRangeContinuousMillimeters();
      
  }
  motor_control('S', 0);
  tile_delay = millis() - tt;
  return 1;
}



//if this is used as the first movement the delay is 1000
//otherwise in front_one_tile or back_one_tile the variable is updated 
//probably a bad idea to have it update everytime (maybe just once is fine)
inline void delay_one_tile() {
  Serial.println("delay one tile");
  unsigned long tt = millis();
  Serial.println(tile_delay);
  int black = 0;
  delay(50);
  int hamada = Front.readRangeContinuousMillimeters();
  while ((unsigned long)(millis() - tt) < tile_delay && ( hamada > 60 || hamada != -1)) {
    motor_control('F', speedd);
    //mpu.update();
    // if (abs(mpu.getAngleY()) > 10) {
    //   ramp();
    //   return;
    // }
     if (color() == 0) black++;
     if (black == 5) {
       motor_control('S', 0);
       black_tile(millis() - tt);
       return;
    }
    delay(10);
     hamada = Front.readRangeContinuousMillimeters();
  }

  motor_control('S', 0);
}



//this fucntions checks the readings of the front/back tofs
//and accordingly chooses front_one_tile or back_one_tile
//depending on which one is closer
//because when you're closer you're more accurate
inline bool one_tile() {
  delay(50);
  int sf = Front.readRangeContinuousMillimeters();
  int sb = Back.readRangeContinuousMillimeters();

  if (sf > 1700) sf = -1;
  if (sb > 1700) sb = -1;
  Serial.print("sf = ");
  Serial.print(sf);
  Serial.print(" sb = ");
  Serial.println(sb);

  delay(1000);
  if(sf >600) sf = -1;
  if (sf == -1 && sb == -1) delay_one_tile();
  else if (sb == -1) return front_one_tile();
  else if (sf == -1) return back_one_tile();
  else if (sf <= sb) return front_one_tile();
  else if (sb < sf) return back_one_tile();
}

//__________________________________________________________________________________________TURNING__________________________________________________________________________________________

/*inline void turn(char dir) {
  mpu.update();
  if (dir == 'L') {
    int start = mpu.getAngleZ();
    motor_control('L', speedd);
    while (mpu.getAngleZ() < start + 90) {
      mpu.update();
      Serial.print(start + 90);
      Serial.print("  ");
      Serial.println(mpu.getAngleZ());
    }
    motor_control('S', 0);
    //return;
  }
  //______________L
  if (dir == 'R') {
    
    Serial.println("Right");
    int start = mpu.getAngleZ();
    Serial.println(start);
    int omg = millis();
    motor_control('R', speedd);
    while (mpu.getAngleZ() > start - 90) {
      mpu.update();
      Serial.print(start - 90);
      Serial.print("  ");
      Serial.println(mpu.getAngleZ());
    }
    //turn_delay = millis() - omg;
    motor_control('S', 0);
    //return;
  }
  //____________B
  if (dir == 'B') {
    int start = mpu.getAngleZ();
    motor_control('L', speedd);
    while (mpu.getAngleZ() < start + 175) {
      mpu.update();
      Serial.println(mpu.getAngleZ());
    }
    motor_control('S', 0);
    //return;
  }
}*/



int turn_delay = 900;  

inline void delay_turn(char dir) {
  Serial.print("delay turn ");
  if (dir == 'L') {
    Serial.println("left");
    motor_control('L', speedd);
    delay(turn_delay);
    motor_control('S', 0);
    return;
  }
  //______________L
  if (dir == 'R') {
    Serial.println("right");
    motor_control('R', speedd);
    delay(turn_delay);
    motor_control('S', 0);
    return;
  }
  //____________B
  if (dir == 'B') {
    motor_control('L', speedd);
    delay(turn_delay*2);
    motor_control('S', 0);
    return;
  }
}



//this sends 1 to the uno 
// and the uno sends 1 back when  |initial angle - current angle| > 90(or whatever the number is in the code)
void turn (char c)
{
  int reps =  1;
  if(c == 'B')
  {
    reps ++;
    c = 'L';
  }
  for(int i=0;i<reps ; i++)
  {
    digitalWrite(52 , 0);
    delay(1000);
    digitalWrite(52 , 1);
    while(digitalRead(53))
    {
      motor_control(c,speedd+20);
      delay(50);
    }
    motor_control('S',0);
  }

}




