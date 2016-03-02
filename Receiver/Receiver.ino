#define PHOTO_PIN 11
#define LED_PIN 13
#define SPEAKER_PIN 15

void setup()
{
  Serial.begin(115200,SERIAL_8E2);                //begin serial with 115200 baud, even parity bit, and two end bits.
  pinMode(PHOTO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  for(int i = 0; i < 5000; i++)
    {
      if(Serial.available() >= 2)
        {
          int time = 0;
          Serial.readBytes(&time,4);
          Serial.println(time-i);
          i = time;
        }
      delay(1);
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
