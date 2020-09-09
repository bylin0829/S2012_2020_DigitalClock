
void setup() {
  Serial.begin(9600);
  pinMode(3, OUTPUT);
}

void loop() {
  String myLog = "";
  for (int i = 0; i < 255; i += 1) {
    analogWrite(3, i);
    Serial.println(i);
    delay(50);    
  }

}
