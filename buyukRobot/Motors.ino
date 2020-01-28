
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
  goRightStep(1.61);

  setMotors(-baseRight, 0);
  delay(50);
  setMotors(0, 0);
}

void turnRight() {
  goLeftStep(1.63);

  setMotors(0, -baseLeft);
  delay(50);
  setMotors(0, 0);
}

void turnBack() {
  goBackStep(1.63);

  setMotors(baseRight / 2, -baseLeft / 2);
  motorRight.run(FORWARD);
  delay(100);
  setMotors(0, 0);
}

void stopMotors() {
  setMotors(-baseRight, -baseLeft);
  delay(50);
  motorLeft.run(RELEASE);
  motorRight.run(RELEASE);
  setMotors(0, 0);
}

void stopMotorsV2(){
  setMotors(baseRight, baseLeft);
  delay(50);
  motorLeft.run(RELEASE);
  motorRight.run(RELEASE);
  setMotors(0, 0);
}


void goToLine() { // t görene kadar düz gitme
  resetEncoders();
  while (true) {
    goForward();
    if (computeQtr() < 5) break;
  }
  stopMotors();
}

void goOnLine() { // robotun t görene kadar follow line çalıştırma kodu. Parametre olarak kaçıncı T de duracagını alıyor.
  
  while (1) {
    //    Serial.println("çizgi izlicem");
    followLineV4();
    if (computeQtr() < 5) break; //t nin algılanma kodu
  }
  stopMotors();
}

void turnUntilLine(int choice) { //RIGHT ise sağa LEFT ise sola dönüş
  goStep(0.19);
  if (choice == 0) { // sağ dönüş için
    
    while (true) {
      setMotors(0, baseLeft);
      readQtr();
      setMotors(0, baseLeft);
      if (qtrVal[5] == 0) {
        setMotors(0, -baseLeft);
        delay(50);
        setMotors(0, 0);
        break;
      }
    }
  } else if (choice == 1) { // sol dönüş için
   
    while (true) {
       setMotors(baseRight, 0);
      readQtr();
      if (qtrVal[2] == 0) {
        setMotors(-baseRight, 0);
        delay(50);
        setMotors(0, 0);
        break;
      }
    }
  }
}
