#define LED_PIN 11

unsigned char int_to_char(int i)
{
  return (unsigned char) (i & 255);
}

void setup()
{
  Serial.begin(115200);         //begin serial with 115200 baud, even parity bit, and two end bits.
  //115200 - 115200*(3/11) = 83781 bps = 10472 Bps
  pinMode(LED_PIN, OUTPUT);
  for(int i = 0; i < 5000/3; i ++)           //synchronize arduinos
  {
    Serial.write((const uint8_t*)&i,2);
    delay(3);
  }
}

void loop()
{
  if(Serial.available())
  {
    Serial.write(int_to_char(Serial.read()));
  }
}

