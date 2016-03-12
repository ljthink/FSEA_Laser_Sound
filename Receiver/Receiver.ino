#define LED_PIN 13
#define SPEAKER_PIN 15

void setup()
{
  Serial.begin(115200);   //begin serial with 115200 baud, even parity bit, and two end bits.
  SYNC:
  pinMode(LED_PIN, OUTPUT);
  boolean hasGivenNo = false;
  bool HasSynced = false;
  for(int i = 0; i < 5000/3; i++)
  {
    if(Serial.available() >= 2)
    {
      int time = 0;
      Serial.readBytes((char*)&time,2);
      Serial.println((int)(time-i));
      i = time;
      if(i >= 5000)
        HasSynced = true;
      hasGivenNo = false;
    }
    else
    {
      if(!hasGivenNo) {
        Serial.print("no_recv:");
        Serial.println(i);
        hasGivenNo = true;
      }
    }
    delay(3);
  }
  if(HasSynced)
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
    PCM_to_delaytimes(Serial.read());
    mk_sound();
  }
}

