// no heated victims this year
//you can just skip this






Adafruit_MLX90614 temp1 = Adafruit_MLX90614(0x22);//right
Adafruit_MLX90614 temp2 = Adafruit_MLX90614(0x5A);//front  
Adafruit_MLX90614 temp3 = Adafruit_MLX90614(0x5E);//left

#define tr temp1.readObjectTempC()
#define tf temp2.readObjectTempC()
#define tl temp3.readObjectTempC()


void temp_setup()
{
  temp1.begin();
  temp2.begin();
  temp3.begin();
}

bool heat_victim()
{
  Serial.print(tl);
  Serial.print(" ");
  Serial.print(tr);
  Serial.print(" ");
  Serial.println(tf);
  delay(100);
  tl;
  tr;
  tf;
  if(tl>29)return 1;
  if(tr>29)return 1;
  if(tf>29)return 1;
  return 0;
}
