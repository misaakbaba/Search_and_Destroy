const int qtrMults[] = {7, 5, 3, 1, -1, -3, -5, -7};

int getPosition() {
  readQtr();
  printQtr();
  int sum = 0;
  int valueCounter = 0;
  for (byte i = 0; i < 8; i++) {
    if (qtrVal[i] == 0) {
      valueCounter++;
    }
    sum += qtrVal[i] * qtrMults[i];
  }
  if (valueCounter == 0) {
    return positionLast;
  }
  sum /= valueCounter;
  return sum;
}

void defineSensors() {
  pinMode(ldr, INPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(mz80, INPUT);
}

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
int prob[][lim] = {
  {0, 1, 1, 1, 1, 1, 1, 1, -7},
  {0, 0, 1, 1, 1, 1, 1, 1, -6},
  {1, 0, 1, 1, 1, 1, 1, 1, -5},
  {1, 0, 0, 1, 1, 1, 1, 1, -4},
  {1, 1, 0, 1, 1, 1, 1, 1, -3},
  {1, 1, 0, 0, 1, 1, 1, 1, -2},
  {1, 1, 1, 0, 1, 1, 1, 1, -1},
  {1, 1, 1, 0, 0, 1, 1, 1, 0},
  {1, 1, 1, 1, 0, 1, 1, 1, 1},
  {1, 1, 1, 1, 0, 0, 1, 1, 2},
  {1, 1, 1, 1, 1, 0, 1, 1, 3},
  {1, 1, 1, 1, 1, 0, 0, 1, 4},
  {1, 1, 1, 1, 1, 1, 0, 1, 5},
  {1, 1, 1, 1, 1, 1, 0, 0, 6},
  {1, 1, 1, 1, 1, 1, 1, 0, 7}
};

int compareArrays(int * arr) { // qtr dan okunan değerleri prob arrayi ile karşılaştırıp pozisyonu buluyor
  int result;
  for (int i = 0; i < 8; i++) {
    if (qtrVal[i] != arr[i]) {
      result = 0;
      break;
    } else {
      result = arr[8];
    }

  }
  return result;
}

void computePos() { // qtr i okuyup compute pos a gönderiyor
  readQtr();
  for (int i = 0; i < 15; i++) {
    if (compareArrays(prob[i]) != 0) {
      pos = compareArrays(prob[i]);
    }
  }
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
    if (!qtrVal[3] || !qtrVal[4] )
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





int calcLight() {
  int duration1;
  int duration2;
  while (1){
  if (digitalRead(ldr) == 0) { // 0 ken ışık var demek
    while (digitalRead(ldr) == 0) {
    }
    duration1 = millis();
    while (digitalRead(ldr) == 1) {
    }
    duration2 = millis();


  } else {
    while (digitalRead(ldr) == 1) {
    }
    duration1 = millis();
    while (digitalRead(ldr) == 0) {
    }
    duration2 = millis();


  }
  if(duration2 - duration1>20) break;
 }
 return (duration2 - duration1);
}



void initNrf() {
  radio.begin();
  radio.openWritingPipe(writingPipe); // 00002
  radio.openReadingPipe(1, readingPipe); // 00001
  radio.setPALevel(RF24_PA_MIN);
}

void defineMotors() {
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}
