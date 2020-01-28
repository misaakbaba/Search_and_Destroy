

void goA() {
  delay(500);
  turnLeft();
  goToLine();
  turnUntilLine(LEFT);
  goOnLine();
  delay(500);
  goStep(0.3);
  lightFreqs[0] = calcLight();
  turnBack();

}

void goB() {
  goOnLine();
  delay(500);
  goStep(0.3);
  lightFreqs[1] = calcLight();
  turnBack();
  goStepOnLine(1.5);
  delay(500);
}

void goC() {
  turnLeft();
  goToLine();
  turnUntilLine(RIGHT);
  goOnLine();
  delay(500);
  goStep(0.3);
  lightFreqs[2] = calcLight();
  turnBack();
  goStepOnLine(1.5);
}

void goSafeZone() {
  delay(500);
  turnLeft();
  goStep(3.5);
  delay(500);
  turnRight();
  goToLine();
  findLine();
  delay(500);
  goStep(1.5);
  searchIsDone = true;
}


void travelRooms() {
  goOnLine();
  goStepNoStop(0.5);
  goOnLine();
  goStep(7.5);
  goA();
  goB();
  goC();
}


char whereAmI() {
  char room;
  int value = calcLight();

  if (value < lightFreqs[0] + 100 && value > lightFreqs[0] - 100) room = 'A';
  else if (value < lightFreqs[1] + 100 && value > lightFreqs[1] - 100) room = 'B';
  else if (value < lightFreqs[1] + 100 && value > lightFreqs[1] - 100) room = 'C';
  else room ='C';
  return room;
}

void listenDady() {
  radio.startListening();

  while (!radio.available()) {
    //    Serial.println("dinliyorum karşim");
  }
  roomName = whereAmI(); 
  //  Serial.println("Oda name belirlendi");
}

void helpDady() {

  while (1) {
    long duration = millis();
    while (millis() - duration < 2000) {
      radio.stopListening();
      radio.write(&roomName, sizeof(roomName));
    }

    radio.startListening();
    while (!radio.available()) {
      //      Serial.println("dinliyorum karşim");
    }
    radio.read(&Dady, sizeof(Dady));
    if (Dady == 'R') break;
  }

}




void escapefromAlcatraz() {
  exitRoom();
  goStepOnLine(2.5);

  if (roomName == 'A' || roomName == 'D') {
    turnRight();
  } else if (roomName == 'B' || roomName == 'C' ) {
    turnLeft();
  }
  goStep(4);

  if (roomName == 'A' || roomName == 'B') {
    turnLeft();
  } else if (roomName == 'C' || roomName == 'D' ) {
    turnRight();
  }

  goToLine();
  findLine();
  goStep(1);
}

void toparlaKendini() {
  setMotors(-baseRight, -baseLeft);
  delay(300);
  setMotors(0, 0);
}

void exitRoom() {
  if (digitalRead(mz80) == 1){
    turnBack();
  }
  while (1) {
    if (!digitalRead(sharp)) {
      turnLeft();
    }
    while (1) {
      if (digitalRead(mz80) == 1) {
        setMotors(0, 0);
        toparlaKendini();
        break;
      }
      setMotors(-baseRight / 2, baseLeft / 2);
    }

    resetEncoders();
    setMotors(baseRight, baseLeft);
    Input3 = 0;
    Output3 = 0;
    while (1) {
      if (digitalRead(mz80) == 0 || (computeQtr() > 5 && computeQtr() < 8)) break;
      goForward();

    }

    if (computeQtr() > 5 && computeQtr() < 8) break;
  }
}

void findLine() {
  unsigned int dis = SharpIR.distance();
  //  Serial.println(dis);
  if (dis > 20) { //28 30 olarak güncellencek
    setMotors(170, 90);
       Serial.println("sol");
  } else if (dis > 11) {
    setMotors(baseRight, baseLeft);
       Serial.println("duz");
  } else {
    setMotors(90, 140);
        Serial.println("sag");
  }
  delay(300);
  while (1) {
    readQtr();
    if (computeQtr() < 7) break;
  }
  goOnLine();
}
