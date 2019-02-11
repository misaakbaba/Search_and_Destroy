void goStep(double target) {
  leftEnc.write(0);
  while (true) {
    setMotors(baseRight, baseLeft);
    long leftPos = leftEnc.read();
    double stepp = leftPos / (298.0 * 12);
    if (stepp >= target) break;
  }
  stopMotors();
  delay(500);
  //  long rightPos = rightEnc.read();

  //  double distance = 14.13 * stepp;
  //  Serial.println(wentDist);

}

int encError() {
  long leftPos = leftEnc.read();
  long rightPos=rightEnc.read();
  return leftPos-rightPos;
}

void resetEncoders(){
  leftEnc.write(0);
  rightEnc.write(0);
}
void readEnc(){
  int left=leftEnc.read();
  int right=rightEnc.read();
  Serial.print("left: ");
  Serial.print(left);
  Serial.print(" *** right: ");
  Serial.println(right);
  Serial.println("");
  Serial.print("error");
  Serial.println(left-right);
}
