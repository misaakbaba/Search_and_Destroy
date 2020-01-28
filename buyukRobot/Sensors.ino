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
int compareArrays(int * arr){ // qtr dan okunan değerleri prob arrayi ile karşılaştırıp pozisyonu buluyor
  int result;
    for(int i=0;i<8;i++){
      if(qtrVal[i]!=arr[i]){
        result=0;
        break;
      }else{
        result=arr[8];
      }
      
    }
    return result;
 }
/*
 void computePos(){ // qtr i okuyup compute pos a gönderiyor
  readQtr();
  for(int i=0;i<15;i++){   
    if(compareArrays(prob[i])!=0){
      pos=compareArrays(prob[i]);
    }
  }
}
*/

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

void initNrf(){
   radio.begin();
  radio.openWritingPipe(writingPipe); // 00002
  radio.openReadingPipe(1,readingPipe); // 00001
  radio.setPALevel(RF24_PA_MIN);
}
