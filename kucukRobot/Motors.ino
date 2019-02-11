
void setMotors(int rightSpeed, int leftSpeed) {

  if (leftSpeed < 0 || rightSpeed < 0) {
    if (leftSpeed < 0) {
      motorLeft.run(BACKWARD);
    }
    if (rightSpeed < 0) {
      motorRight.run(BACKWARD);
    }
  } else {
    motorRight.run(FORWARD);
    motorLeft.run(FORWARD);
  }

  motorLeft.setSpeed(abs(leftSpeed));
  motorRight.setSpeed(abs(rightSpeed));
}

void turnLeft() {
  setMotors(baseRight, -baseLeft);
  delay(600);
  setMotors(-baseRight, baseLeft);
  delay(20);
  setMotors(0, 0);
}

void turnRight() {
  setMotors(-baseRight, baseLeft);
  delay(700);
  setMotors(baseRight, -baseLeft);
  delay(20);
  setMotors(0, 0);
}

void turnBack() {
  setMotors(baseRight, -baseLeft);
  delay(1400);
  stopMotors();
}

void stopMotors() {
  setMotors(-baseRight, -baseLeft);
  delay(50);
  motorLeft.run(RELEASE);
  motorRight.run(RELEASE);
  setMotors(0, 0);
}

void goForward(int distance) { //verilen delay e göre düz gitme kodu
  setMotors(baseRight, baseLeft);
  delay(distance);
  stopMotors();
}

void goToLine() { // t görene kadar düz gitme
  while (true) {
    setMotors(baseRight, baseLeft);
    if (computeQtr() < 2) break;
  }
  stopMotors();
  delay(2000);
}

void goOnLine() { // robotun t görene kadar follow line çalıştırma kodu
  while (true) {
    //    Serial.println("çizgi izlicem");
    followLineV2();
    if (computeQtr() < 2) break; //t nin algılanma kodu
  }
  stopMotors();
  delay(2000);
}

void turnUntilLine(int choice) { //r ise sağa l ise sola dönüş
  setMotors(baseRight, baseLeft);
  delay(300);

  if (choice == 0) { // sağ dönüş için
    while (true) {
      readQtr();
      setMotors(-baseRight, baseLeft);
      if (qtrVal[3] == 0) {
        stopMotors();
        break;
      }
    }
  } else if (choice == 1) { // sol dönüş için
    while (true) {
      readQtr();
      setMotors(baseRight, -baseLeft);
      if (qtrVal[2] == 0) {
        stopMotors();
        break;
      }
    }
  }
}
