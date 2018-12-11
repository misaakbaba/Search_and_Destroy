


void setMotors(int rightSpeed,int leftSpeed){

 if(leftSpeed<0 || rightSpeed<0){
    if(leftSpeed<0){
      motorLeft.run(BACKWARD);
    }
    if(rightSpeed<0){
      motorRight.run(BACKWARD);
    }
 }else{
    motorRight.run(FORWARD);
    motorLeft.run(FORWARD);
 }
    
    motorLeft.setSpeed(abs(leftSpeed));
    motorRight.setSpeed(abs(rightSpeed));
}

void turnLeft(){
  setMotors(baseRight,-baseLeft);
  delay(1000);
  stopMotors();
}

void turnRight(){
  setMotors(-baseRight,baseLeft);
  delay(1000);
  stopMotors();
}

void turnBack(){
  setMotors(baseRight,-baseLeft);
  delay(2000);
  stopMotors();
}

void stopMotors() {
  setMotors(-baseRight,-baseLeft);
  delay(100);
  motorLeft.run(RELEASE);
  motorRight.run(RELEASE);
  setMotors(0, 0);
}


  
