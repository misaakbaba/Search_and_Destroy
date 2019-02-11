const int ldr = 22;
int duration1;
int duration2;
void setup() {
  // put your setup code here, to run once:
  pinMode(ldr, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  int result = midValue(5);
//  Serial.println(result);
  delay(1000);

}
int calcLight() {
  if (digitalRead(ldr) == 0) { // 0 ken ışık var demek
    while (digitalRead(ldr) == 0) {
      Serial.println("IŞIK VAR");
    }
    duration1 = millis();
    while (digitalRead(ldr) == 1) {
      Serial.println("IŞIK YOK");
    }
    duration2 = millis();


  } else {
    while (digitalRead(ldr) == 1) {
      Serial.println("IŞIK YOK");
    }
    duration1 = millis();
    while (digitalRead(ldr) == 0) {
      Serial.println("IŞIK VAR");
    }
    duration2 = millis();


  }
  return (duration2 - duration1);
}

int midValue(int times) {
  int sum=0;
  for (int i = 0; i < times; i++) {
    sum += calcLight();
  }
  Serial.println(sum / 3);
  return (sum / 3);
}
