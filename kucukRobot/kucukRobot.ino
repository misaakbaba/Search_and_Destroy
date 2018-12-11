#include <AFMotor.h>
#define qtr 8
#define lim 9


byte qtrPins[]={A8,A9,A10,A11,A12,A13,A14,A15};
int qtrVal[]={0,0,0,0,0,0,0,0};

AF_DCMotor motorRight(2);
AF_DCMotor motorLeft(1);
#define kp 0.070f
#define kd 0.013f


const int baseRight=90;
const int baseLeft=110;

int pos;
int error;
int lastError;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  defineQtr();
  motorRight.run(RELEASE);
  motorLeft.run(RELEASE);

}

void loop() {
  // put your main code here, to run repeatedly:
  
 turnRight();
 delay(1000);  
}