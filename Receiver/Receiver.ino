#define LED_PIN 13
#define SPEAKER_PIN 15

void setup()
{
  Serial.begin(115200,SERIAL_8O2);   //begin serial with 115200 baud, even parity bit, and two end bits.
  SYNC: 
  pinMode(LED_PIN, OUTPUT);
  boolean hasGivenNo = false;
  bool hasSynced = false;
  for(unsigned char i = 0; i < 255; i++)
  {
    if(Serial.available())
    {
      unsigned char time = 0;
      unsigned char p1 = (unsigned char)Serial.read();
      int k = (int)p1;
      Serial.print("current time: ");
      Serial.println((int)i);
      Serial.print("difference received: ");
      Serial.println((int)(time-i));
      i = time;
      hasSynced = true;
    }
    else
    {
      if(!hasGivenNo) {
        Serial.print("no_recv:");
        Serial.println(i);
        hasGivenNo = true;
      }
    }
    delay(1);
  }
  if(hasSynced)
    Serial.println("synced!");
  else {
    Serial.print("not synced! ");
    Serial.println("Attempting to sync again.");
    goto SYNC;
  }
}

unsigned int delaytimes[2];

void PCM_to_delaytimes(unsigned char c)
{
  delaytimes[0] = ((255 - c)/510.0)*95;
  delaytimes[1] = (c/255.0)*95;
}

void mk_sound()
{
  delayMicroseconds(delaytimes[0]);
  digitalWrite(SPEAKER_PIN,HIGH);
  delayMicroseconds(delaytimes[1]);
  digitalWrite(SPEAKER_PIN,LOW);
}

void loop()
{
  if(Serial.available())
  {
    //Serial.print("Recieved Char: ");
    Serial.print((char)Serial.read());
    //PCM_to_delaytimes(Serial.read());
    //mk_sound();
  }
}

