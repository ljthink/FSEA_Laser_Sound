#define PHOTO_PIN 11
#define LED_PIN 13
#define PIN_SPEAKER = 10;

void setup()
{
  
}

void do_sound(byte in)
{
  for(int i = 0; i < 8; i++)
  {
    if((0x80 >> i) | in)
    {
      digitalWrite(SPEAKER_PIN,HIGH);
    }
  else  
  {
    digitalWrite(SPEAKER_PIN, LOW);
  }  
}

void loop()
{
  byte dat;
  if(Serial.available())
    dat = Serial.read();
   op_sound(dat);
   
}
