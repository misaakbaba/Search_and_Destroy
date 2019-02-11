

void defineQtr() {
  for (int i = 0; i < qtr; i++) {
    pinMode(qtrPins[i], INPUT_PULLUP);
  }
}

void readQtr() {
  for (int i = 0; i < qtr; i++) {
    qtrVal[i] = digitalRead(qtrPins[i]);
  }
}

void printQtr() {
  for (int i = 0; i < qtr; i++) {
    Serial.print(qtrVal[i]);
    Serial.print("--");
  }
  Serial.println();
}

int computeQtr() { // siyah saysını döndürüyor. siyah=1
  int totalValue = 0;
  readQtr();
  for (int i = 0; i < qtr; i++) {
    totalValue += qtrVal[i];
  }
  return totalValue;
}

int positionSensor(int color) { //siyahta 1 döndürüyor
  readQtr();
  if (color == 0) { //beyaz çizgi
    if (!qtrVal[3] && !qtrVal[4] )
      return 0;
    if (!qtrVal[0] || !qtrVal[1])
      return 3;
    else if (!qtrVal[6] || !qtrVal[7])
      return -3;
    else if (!qtrVal[2] || !qtrVal[3])
      return 2;
    else if (!qtrVal[4] || !qtrVal[5])
      return -2;
    else
      return positionLast ;

  } else {//siyah çizgi
    if (qtrVal[3] && qtrVal[4] )
      return 0;
    if (qtrVal[0] || qtrVal[1])
      return 3;
    else if (qtrVal[6] || qtrVal[7])
      return -3;
    else if (qtrVal[2] || qtrVal[3])
      return 2;
    else if (qtrVal[4] || qtrVal[5])
      return -2;
    else
      return positionLast ;
  }
}

int measureLight() {
  if (digitalRead(ldr) == LOW) {
    while (digitalRead(ldr) == LOW) {

    }
    first = millis();
    while (digitalRead(ldr) == HIGH) {

    }
    second = millis();
    return second - first;
  }
  else if (digitalRead(ldr) == HIGH) {
    while (digitalRead(ldr) == HIGH) {

    }
    first = millis();
    while (digitalRead(ldr) == LOW) {

    }
    second = millis();
    return second - first;
  }
}

int measureDist() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
//  Serial.print("Distance: ");
//  Serial.println(distance);
return distance;
}
