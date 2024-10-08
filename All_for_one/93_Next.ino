
inline void Next()
{
  prevX = posX;
  prevY = posY;
  char nxt = NXT(); // nxt is the bfs function and it returns a character represtent the direction to be moved towards (F,B,R,L)
  delay(1000);
  //Serial.print("front(after nxt) : ");
  //Serial.println(Front.readRangeContinuousMillimeters());
  //cout<<nxt<<endl;
  Serial.print("go ");
  Serial.println(nxt);
  if (nxt == 'R') orientation++;
  if (nxt == 'L') orientation--;
  if (nxt == 'B') orientation += 2;
  if (orientation < 0)orientation += 4; // did this bec -1%4 is -1 idk why
  if (orientation > 3)orientation -= 4;
  
  if(nxt!='F')
  {
    turn(nxt);
  }
  delay(100);

  one_tile();
}
