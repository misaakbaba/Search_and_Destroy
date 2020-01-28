
// qtr dan gelen verilere göre hangi pozisyonda olduğunu gösteren dataset


PID myPID(&Input, &Output, &Setpoint, kp, ki, kd, DIRECT);
PID wallPID(&Input2, &Output2, &Setpoint2, kp2, ki2, kd2, DIRECT);
PID encPID(&Input3, &Output3, &Setpoint3, kp3, ki3, kd3, DIRECT);

void initPID() {
  Setpoint = 0;
  Input = 0;
  myPID.SetOutputLimits(-255, 255);
  myPID.SetMode(AUTOMATIC);
}

void initEncPID() {
  Setpoint3 = 0;
  Input3 = 0;
  encPID.SetOutputLimits(-255, 255);
  encPID.SetMode(AUTOMATIC);
}



void followLineV4() {
  pos = getPosition();
  positionLast = pos;
  Input = pos;
  myPID.Compute();
//  Serial.print("error is: ");
//  Serial.print(Input);
//  Serial.print("*** Output is: ");
//  Serial.println(Output);
  setMotors(baseRight + Output, baseLeft - Output);
//  Serial.println(Output);
}

void goForward() {
  Input3 = encError();
  Serial.println(Input3);
  encPID.Compute();
 Serial.print("Output: ");
 Serial.println(Output3);
  setMotors(baseRight + Output3, baseLeft - Output3);
}
