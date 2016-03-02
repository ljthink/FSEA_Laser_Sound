#define LED_PIN 11

unsigned char int_to_char(int i)
{
  return (unsigned char) (i & 255);
}

void setup()
{
  Serial.begin(115200,SERIAL_8E2);         //begin serial with 115200 baud, even parity bit, and two end bits.
                                           //115200 - 115200*(3/11) = 83781 bps = 10472 Bps
  pinMode(LED_PIN, OUTPUT);
  for(int i = 0; i < 5000; i ++)           //synchronize arduinos
    {
      Serial.write(&i,4);
      delay(1);
    }
}

void loop()
{
  if(Serial.available())
    {
      Serial.write(int_to_char(Serial.read()));
    }
}
