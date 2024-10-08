/*
   0    0     0    0    0     0     0     0
   l    f     r    b    un   black   c     v
*/
inline void Mapp(void)
{   
  delay(50);
  int ff = Front.readRangeContinuousMillimeters();
  int r1 = Right1.readRangeContinuousMillimeters();
  int r2 = Right2.readRangeContinuousMillimeters();
  int rr = max(r1,r2);
  int l1 = Left1.readRangeContinuousMillimeters();
  int l2 = Left2.readRangeContinuousMillimeters();
  int ll = max(l1,l2);
  //int bb = Back.readRangeContinuousMillimeters();       
  delay(1000); 
    ff = Front.readRangeContinuousMillimeters();
    r1 = Right1.readRangeContinuousMillimeters();
    r2 = Right2.readRangeContinuousMillimeters();
    rr = max(r1,r2);
    l1 = Left1.readRangeContinuousMillimeters();
    l2 = Left2.readRangeContinuousMillimeters();
    ll = max(l1,l2);
    //bb = Back.readRangeContinuousMillimeters();
    bool odam = (ff<=200);
    bool right= (rr<=200);
    bool left = (ll<=200);
   // bool back = (bb<=200);
    bool back = 0;
    if(posX==25&&posY==25)back = 1;
  
    //bool checkpoint = check_checkpoint();
    bool checkpoint = 0;
    Serial.print("front ");
    //Serial.print(odam);
    //Serial.print(" ");
    Serial.print(ff);
    Serial.print(" right ");
    //Serial.print(right);
    //Serial.print(" ");
    Serial.print(rr);
    Serial.print("  left ");
    //Serial.print(left);
    //Serial.print(" ");
    Serial.print(ll);
    Serial.print(" back\n ");
    //Serial.println(back);
    //Serial.print(" ");
    //Serial.println(bb);

    //if (!(state[posX][posY] & 1))visited++;
    byte x = 0;
    x |= left << 3;
    x |= odam << 2;
    x |= right << 1;
    x |= back;
    x = ChangeOrientation(x);
    
    if(!(x&(1)) && !(state[posX+1][posY]&1)&&!(state[posX+1][posY]&(1<<3)))
    {
      Serial.println("back unvisited");
      unvisited ++;
      state[posX+1][posY]|= (1<<3);
    }
    if(!(x&(1<<1)) && !(state[posX][posY+1]&1)&&!(state[posX][posY+1]&(1<<3)))
    {
      Serial.println("right unvisited");
      unvisited ++;
      state[posX][posY+1]|= (1<<3);
    }
    if(!(x&(1<<2)) && !(state[posX-1][posY]&1)&&!(state[posX-1][posY]&(1<<3)))
    {
      Serial.println("front unvisited");
      unvisited ++;
      state[posX-1][posY]|= (1<<3);
    }
    if(!(x&(1<<3)) && !(state[posX][posY-1]&1)&&!(state[posX][posY-1]&(1<<3)))
    {
      Serial.println("left unvisited");
      unvisited ++;
      state[posX][posY-1]|= (1<<3);
    }
    state[posX][posY] |= ((x << 4) | 1);
    state[posX][posY] |= checkpoint << 1;

    byte xx = state[posX][posY];
 
    if (checkpoint) checkpointX = posX, checkpointY = posY;

    


    
}
