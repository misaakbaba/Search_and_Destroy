void saveA() {
  goOnLine();
  goStepNoStop(0.5);
  goOnLine();
  goStep(7.35);
  delay(500);
  turnLeft();
  goToLine();
  turnUntilLine(LEFT);
  malazgirt();
  goBackwardStep(-2.5);
  delay(500);
  turnLeft();
  goStep(2.7);
  gacKurtul();
  turnLeft();
  goToLine();
  findLine();
  goOnLine();
  //çizgi bulma sharp ı eklenecek
}

void saveB() {
  goOnLine();
  goStepNoStop(0.5);
  goOnLine();
  goStep(6.5);
  delay(500);
  turnLeft();
  goToLine();
  turnUntilLine(RIGHT);
  malazgirt();
  goBackwardStep(-2.5);
  delay(500);
  turnRight();
  goStep(2.7);
  gacKurtul();
  turnLeft();
  goToLine();
  findLine();
  goOnLine();
  //çizgi bulma sharp ı eklenecek
}

void saveC() {
  goOnLine();
  goStepNoStop(0.5);
  goOnLine();
  goStep(7.65);
  delay(500);
  turnRight();
  goToLine();
  turnUntilLine(RIGHT);
  malazgirt();
  goBackwardStep(-2.5);
  delay(500);
  turnRight();
  goStep(2.7);
  gacKurtul();
  turnRight();
  goToLine();
  findLine();
  goOnLine();
  //çizgi bulma sharp ı eklenecek
}

void saveD() {
  goOnLine();
  goStep(7.4);
  delay(500);
  turnRight();
  goToLine();
  turnUntilLine(LEFT);
  malazgirt();
  goBackwardStep(-2.5);
  delay(500);
  turnLeft();
  goStep(3.2);
  gacKurtul();
  turnRight();
  goToLine();
  findLine();
  goOnLine();
  //çizgi bulma      sharp ı eklenecek
}

void findKid() {
  while (1) {
    radio.stopListening();
    radio.write(&situation, sizeof(situation));

    radio.startListening();
    while (!radio.available());

    radio.read(&roomName, sizeof(roomName));
    Serial.print("Oda Numarası :");
    Serial.println(roomName);
    if (roomName == 'A' || roomName == 'B' || roomName == 'C' || roomName == 'D') break;
  }
}

void saveKid() {
  if (roomName == 'A') {
    saveA();
  } else if (roomName == 'B') {
    saveB();
  } else if (roomName == 'C') {
    saveC();
  } else if (roomName == 'D') {
    saveD();
  }

  goStep(2.7);
}


void gacKurtul() {
  situation = 'R';
  long duration = millis();
  while (millis() - duration < 3000) {
    radio.stopListening();
    radio.write(&situation, sizeof(situation));
  }

}
void findLine() {
  unsigned int dis = SharpIR.distance();
  Serial.println(dis);
  if (dis > 15) { //28 30 olarak güncellencek
    setMotors(200, 90);
    Serial.println("sag");
  } else if (dis > 10) {
    setMotors(baseRight, baseLeft);
    Serial.println("duz");
  } else {
    setMotors(70, 170);
    Serial.println("sol");
  }
  delay(300);
  while (1) {
    readQtr();
    if  (computeQtr() < 7)  break;
  }
  goOnLine();
}

void malazgirt() {
  while (1) {
    //    Serial.println("çizgi izlicem");
    followLineV4();
    if (computeQtr() < 5) break; //t nin algılanma kodu
  }
  goStep(0.5);
}
