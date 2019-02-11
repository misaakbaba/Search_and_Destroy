#include <AFMotor.h>
#include <Encoder.h>
#define qtr 8
#define lim 9
#define ldr 40
#define trigPin 36
#define echoPin 38
#include <PID_v1.h>
double Setpoint, Input, Output;
double Setpoint2, Input2, Output2; //encoder pid value
enum directions {
  RIGHT,
  LEFT
};

const byte qtrPins[] = {A15, A14, A13, A12, A11, A10, A9, A8};
int qtrVal[] = {0, 0, 0, 0, 0, 0, 0, 0};

Encoder rightEnc(18, 19);
Encoder leftEnc(20, 21);
AF_DCMotor motorRight(2);
AF_DCMotor motorLeft(1);
//#define kp 0.070f
//#define kd 0.013f
//#define ki 0
float kp = 22.5;
float ki = 1.5;
float kd = 0.5;

float kp2 = 5;
float ki2 = 0.25;
float kd2 = 0.25;

long oldRightPos  = -999; // encoder old pos
long oldLeftPos = -999;
const int baseRight = 109;
const int baseLeft = 100;
int positionLast;
int pos;
int error;
int lastError;

long duration;//ultrasonic sensor
int distance;

unsigned int first = 0; // ldr time count
unsigned int second = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  defineQtr();
  setMotors(baseRight, baseLeft);
  initPID();
  pinMode(ldr, INPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  initWallPID();
}

void loop() {
  // put your main code here, to run repeatedly:
  //  readQtr();
  //  printQtr();
  //    followLineV2(); //CURRENT LİNE FOLLOWER
  //  readQtr();
  //  printQtr();
  //  goStep(5);

  //  goOnLine();
  //  travelFirst();
  //  readEnc();
  //  delay(300);
  //  measureDist();
  followWall();
  delay(200);


}
