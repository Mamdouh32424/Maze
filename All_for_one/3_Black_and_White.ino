//We communicate with the lego color sensor using i2c
//we send it a byte then request a byte
//the sensor sends a number representing the color it sees

byte color()
{
  Wire.beginTransmission(0x01);
  Wire.write(0x42);
  Wire.endTransmission();
  Wire.requestFrom( 0x01, 1);
  byte ret = Wire.read();
  return ret;
}
