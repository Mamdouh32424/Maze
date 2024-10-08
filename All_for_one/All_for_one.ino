

  /*   
   0    0     0    0    0     0     0     0
   l    f     r    b   uv   black   c     v
*/


#include<Wire.h> 
#include <I2Cdev.h>
#include <VL53L0X.h>
//#include <MeMegaPi.h>
#include <ArduinoQueue.h>
#include <Adafruit_MLX90614.h>

#define pushh enqueue
#define popp dequeue
#define front getHead
#define queue ArduinoQueue

#define INTERRUPT_PIN 2


int unvisited = 1;



struct bfsnode
{
  char dir;
  int x;
  int y;
};

byte state[12][12];
int orientation = 0;  //  0 -> Front ,  1 -> Right , 2 -> Back , 3 -> Left
int posX = 6 , posY = 6,prevX = 6 , prevY = 6;
int visited = 0;
int checkpointX = 50, checkpointY = 50;





inline byte ChangeOrientation(byte c) // changes the given input to how it would be in orientation 0
{
    //cout<<(c&(1))<<" "<<(c&(1<<1))<<" "<<(c&(1<<2))<<" "<<(c&(1<<3))<<endl;
  if (!orientation)return c;
  for (int i = 0 ; i <  orientation ; i++)
  {
    char x = c & 1;
    c >>= 1;
    c |= (x << 3);
  }
  //cout<<(c&(1))<<" "<<(c&(1<<1))<<" "<<(c&(1<<2))<<" "<<(c&(1<<3))<<endl;
  delay(10);
  return c;
}

inline byte fixdir (byte c) //changes the direction (given facing orientation 0) to the current orientation
{
    //cout<<"orientation "<<orientation<<endl;
  int x = 0;
  while (x != orientation)
  {
    if (c == 'R')c = 'F';
    else if (c == 'B')c = 'R';
    else if (c == 'L')c = 'B';
    else if (c == 'F')c = 'L';
    x++;
  }
  delay(10);
  return c;
}

inline bool fe_Wall(int x,int y)
{
  if(y<posY && state[posX][posY]&(1<<7))return 1;
  if(y>posY && state[posX][posY]&(1<<5))return 1;
  if(x>posX && state[posX][posY]&(1<<4))return 1;
  if(x<posX && state[posX][posY]&(1<<6))return 1;
  return 0; 
}


inline bfsnode get_bfsnode(char c)
{
  int x = orientation;
  while(x)
  {
    if(c == 'R') c = 'B';
    else if(c == 'B') c = 'L';
    else if(c == 'L') c = 'F';
    else if(c == 'F') c = 'R';
    x--;
  }
  int px = posX,py = posY;
  if(c=='R')py++;
  if(c=='L')py--;
  if(c=='F')px--;
  if(c=='B')px++;

  ////Serial.println(c);
  ////Serial.println(fe_Wall(px,py));
  if(fe_Wall(px,py))c = 'X';
  ////Serial.println(c);
  delay(10);
  return {c,px,py};
}


inline char NXT() // returns the direction you'll have to go in order to be on the shortest path to a non-visited tile or start tile(in case we visited all tiles)
{          // just bfs algorithm
  queue<bfsnode>q;
  byte start = state[posX][posY];
    q.pushh(get_bfsnode('R'));
    q.pushh(get_bfsnode('F'));
    q.pushh(get_bfsnode('L'));
    q.pushh(get_bfsnode('B'));
    
  //cout<<"pos "<<posX<< " "<<posY<<endl;

  while (!q.isEmpty())
  {
    delay(10);
    int x = q.front().x;
    int y = q.front().y;
    char ret = q.front().dir;
    q.popp();
    if(ret == 'X')continue;
    if (!(state[x][y] & 1))
    {
      char idk = fixdir(ret);
      if (ret == 'R')posY++;
      if (ret == 'L')posY--;
      if (ret == 'F')posX--;
      if (ret == 'B')posX++;
      if (orientation < 0)orientation += 4; // did this bec -1%4 is -1 idk y
      if (orientation > 3)orientation -= 4;
      Serial.print("idk ");
      Serial.println(idk);
      return idk;
    }

    if (unvisited == 0 && x == 25 && y == 25)
    {
      char idk = fixdir(ret);
      if (ret == 'R')posY++;
      if (ret == 'L')posY--;
      if (ret == 'F')posX--;
      if (ret == 'B')posX++;
      if (orientation < 0)orientation += 4; // did this bec -1%4 is -1 idk y
      if (orientation > 3)orientation -= 4;
      Serial.print("idk ");
      Serial.println(idk);
      return idk;
     // return fixdir(ret);
    } 

    byte cur = state[x][y];
    if (!(cur & (1 << 4))&&!(state[x+1][y]&(1<<2))) q.pushh({ret , x + 1 , y});
    if (!(cur & (1 << 5))&&!(state[x][y+1]&(1<<2))) q.pushh({ret , x , y + 1});
    if (!(cur & (1 << 6))&&!(state[x-1][y]&(1<<2))) q.pushh({ret , x - 1 , y});
    if (!(cur & (1 << 7))&&!(state[x][y-1]&(1<<2))) q.pushh({ret , x , y - 1});
  }

}
