void setup() {
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);

  Serial.begin(9600);

  int x = 0;
  int y = x - 2; unsigned int z = y; Serial.println(z);
}

void loop() {
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
}
