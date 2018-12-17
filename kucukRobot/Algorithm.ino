
void travelRooms() {
  goForward(6000);
  delay(3000);
  turnLeft();
  goToLine();
  turnUntilLine(LEFT);
  goOnLine();
  delay(3000);
  turnBack();
  goOnLine();
  delay(3000);
  turnBack();
  goForward(1500);
  delay(1000);
  turnLeft();
  goToLine();
  turnUntilLine(RIGHT);
  goOnLine();
}


void followLine() {
  computePos();
  error = pos - 3500;
  int addSpeed = kp * error + kd * (error - lastError);
  lastError = error;
  setMotors(baseRight + addSpeed, baseLeft - addSpeed);
}
