
//This is should work bas I think there was a problem with it
//
void cam()
{
    int rescue = 0;
    if(digitalRead(43)==1||digitalRead(41))rescue++;  // 2 pins, one for each cam
    if(digitalRead(45)==1||digitalRead(43))rescue+=2;
    if(digitalRead(47)==1||digitalRead(45))rescue+=3;
    //if(rescue != 2&&rescue!=1)return;
    Serial.println(rescue);
    rescue_kit(rescue);
}
