
// qtr dan gelen verilere göre hangi pozisyonda olduğunu gösteren dataset


PID myPID(&Input, &Output, &Setpoint, kp, ki, kd, DIRECT);
PID wallPID(&Input2, &Output2, &Setpoint2, kp2, ki2, kd2, DIRECT);

void initPID() {
  Setpoint = 0;
  Input = 0;
  myPID.SetOutputLimits(-255, 255);
  myPID.SetMode(AUTOMATIC);
}
void initWallPID() {
  Setpoint2 = 9;
  Input2 = 9;
  wallPID.SetOutputLimits(-255, 255);
  wallPID.SetMode(AUTOMATIC);
}

void followWall() {
  Input2 = measureDist();
  Serial.print("distance");
  Serial.println(Input2);
  Serial.println("");
  wallPID.Compute();
  Serial.print("output is");
  Serial.println(Output2);
  setMotors(baseRight - Output2, baseLeft + Output2);
  delay(300);
//  resetEncoders();
}

void followLineV2() {
  //  computePos();
  pos = positionSensor(0);
  positionLast = pos;
  Input = pos;
  myPID.Compute();
  setMotors(baseRight + Output, baseLeft - Output);
  Serial.println(Output);
}

//int prob[][lim] = {{0, 1, 1, 1, 1, 1, 1, 1, 2000}, {1, 1, 1, 1, 1, 1, 1, 0, 5000}
//  , {0, 0, 1, 1, 1, 1, 1, 1, 2500}, {1, 0, 0, 1, 1, 1, 1, 1, 2833}
//  , {1, 1, 0, 0, 1, 1, 1, 1, 3166}, {1, 1, 1, 0, 0, 1, 1, 1, 3500}
//  , {1, 1, 1, 1, 0, 0, 1, 1, 3833}
//  , {1, 1, 1, 1, 1, 0, 0, 1, 4166}, {1, 1, 1, 1, 1, 1, 0, 0, 4500}
//};


//
//int compareArrays(int * arr) { // qtr dan okunan değerleri prob arrayi ile karşılaştırıp pozisyonu buluyor
//  int result;
//  for (int i = 0; i < 8; i++) {
//    if (qtrVal[i] != arr[i]) {
//      result = 0;
//      break;
//    } else {
//      result = arr[8];
//    }
//
//  }
//  return result;
//}
//
//void computePos() { // qtr i okuyup compute pos a gönderiyor
//  readQtr();
//  for (int i = 0; i < 9; i++) {
//    if (compareArrays(prob[i]) != 0) {
//      pos = compareArrays(prob[i]);
//    }
//  }
//}
