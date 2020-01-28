void goStep(double target) {
  resetEncoders();
  while (true) {
    goForward();
    long leftPos = leftEnc.read();
    double stepp = leftPos / (297.92 * 12);
    if (stepp >= target) break;
  }
  stopMotors();


}

void goStepNoStop(double target) {
  resetEncoders();
  while (true) {
    goForward();
    long leftPos = leftEnc.read();
    double stepp = leftPos / (297.92 * 12);
    if (stepp >= target) break;
  }
}

void goStepOnLine(double target) {
  leftEnc.write(0);
  while (true) {
    followLineV4();
    long leftPos = leftEnc.read();
    double stepp = leftPos / (297.92 * 12);
    if (stepp >= target) break;
  }
  stopMotors();
}

void goRightStep(double target) {
  leftEnc.write(0);
  while (true) {
    setMotors(-baseRight, baseLeft);
    long leftPos = leftEnc.read();
    double stepp = leftPos / (298.0 * 12);
    if (stepp >= target) break;
  }
  resetEncoders();
}

void goLeftStep(double target) {
  rightEnc.write(0);
  while (true) {
    setMotors(baseRight, -baseLeft);
    long rightPos = rightEnc.read();
    double stepp = rightPos / (298.0 * 12);
    Serial.println(stepp);
    if (stepp >= target) break;
  }
  resetEncoders();
}

void goBackStep(double target) {
  leftEnc.write(0);
  while (true) {
    setMotors(-baseRight , baseLeft);
    long leftPos = leftEnc.read();
    double stepp = leftPos / (298.0 * 12);
    if (stepp >= target) break;
  }
  resetEncoders();
}

void resetEncoders() {
  leftEnc.write(0);
  rightEnc.write(0);
}

double encError() {
  long leftPos = leftEnc.read();
  long rightPos = rightEnc.read();
  double leftStep = leftPos / (297.92 * 12);
  double rightStep = rightPos / (297.92 * 12);
  //  Serial.print("left step: ");
  //  Serial.print(leftStep);
  //  Serial.print("***Right step: ");
  //  Serial.println(rightStep);
  return (rightStep - leftStep);
}


void readEnc() {
  int left = leftEnc.read();
  int right = rightEnc.read();
  Serial.print("left: ");
  Serial.print(left);
  Serial.print(" *** right: ");
  Serial.println(right);
  Serial.println("");
  Serial.print("error");
  Serial.println(left - right);
}
