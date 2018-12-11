const int ldr = 7;
int duration1;
int duration2;
void setup() {
  // put your setup code here, to run once:
  pinMode(ldr, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:



  if (digitalRead(ldr) == 0) {
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
  Serial.println(duration2 - duration1);
  delay(1000);
}
