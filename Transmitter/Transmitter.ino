#define LED_PIN 13

unsigned char int_to_char(int i)
{
  return (unsigned char) (i & 255);
}

void setup()
{
  Serial.begin(115200,SERIAL_8O2);         //begin serial with 115200 baud, even parity bit, and two end bits.
  //115200 - 115200*(3/11) = 83781 bps = 10472 Bps
  pinMode(LED_PIN, OUTPUT);
  for(unsigned char i = 0; i < 255; i ++)           //synchronize arduinos
  {
    Serial.write((char)i);
    //Serial.write((const uint8_t*)&i,2);
    delay(1);
  }
}

void loop()
{
  delay(1000);
  char helloworld[15] = "Hello World!\n";
  Serial.print(helloworld);
  /*if(Serial.available())
  {
    Serial.write((char)Serial.read());
  }
  */
  
}

