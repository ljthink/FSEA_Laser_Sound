#define PHOTO_PIN 11
#define LED_PIN 13


void setup()
{
  Serial.begin(9600);
  pinMode(PHOTO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop()
{
  Serial.println(digitalRead(PHOTO_PIN));
  int photo = digitalRead(PHOTO_PIN);
  digitalWrite(LED_PIN, photo);
}
