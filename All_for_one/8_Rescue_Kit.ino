int rescue1 = 32;
int rescuepwm2 = 7;
int rescue3 = 33; 
int rescueen = 51;
void rescue_setup()
{
  pinMode(rescue1,OUTPUT);
  pinMode(rescuepwm2,OUTPUT);
  pinMode(rescue3,OUTPUT);
  pinMode(rescueen,OUTPUT);
  digitalWrite(rescueen,HIGH);
}

const int led_pin = A3;

void rescue_kit(int count)
{
  if(count == 0)return;
  //analogWrite(led_pin,1023);
  //delay(5000);

  //analogWrite(led_pin,0);
  while(count--)
  {
    Serial.println("shoot");
    analogWrite(rescuepwm2,50);
    digitalWrite(rescue1,0);
    digitalWrite(rescue3,1);
    
    
    delay(300);
    
    
    analogWrite(rescuepwm2,40);
    digitalWrite(rescue1,1);
    digitalWrite(rescue3,0);
    
    
    delay(200);
    
    
    digitalWrite(rescue1,1);
    digitalWrite(rescue3,1);
    delay(100);
    
  }
}
