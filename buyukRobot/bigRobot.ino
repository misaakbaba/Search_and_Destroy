#include <SharpIR.h>
#include <nRF24L01.h>
#include <RF24_config.h>
#include <RF24.h>
#include <AFMotor.h>
#include <Encoder.h>
#include <PID_v1.h>

RF24 radio(47, 49); // CE, CSN
const uint64_t readingPipe = 0xE6E6E6E6E6E2;
const uint64_t writingPipe = 0xE6E6E6E6E6E6;
char roomName;
#define qtr 8
#define lim 9
#define ldr 42
#define trigPin 38
#define echoPin 40
#define IR A8
#define model 1080
char situation = 'Z';
char kid;
double Setpoint, Input, Output;
double Setpoint2, Input2, Output2; //wall follow pid value
double Setpoint3, Input3, Output3; //enc pıd value

enum directions {
  RIGHT,
  LEFT
};

const byte qtrPins[] = {22, 24, 26, 28, 30, 32, 34, 36};
int qtrVal[] = {0, 0, 0, 0, 0, 0, 0, 0};

Encoder rightEnc(18, 19);
Encoder leftEnc(21, 20);
AF_DCMotor motorRight(4);
AF_DCMotor motorLeft(3);
SharpIR SharpIR(IR, model);

float kp = 13;
float ki = 2;
float kd = 0.35;

float kp2 = 5;
float ki2 = 0.25;
float kd2 = 0.25;

float kp3 = 197;
float ki3 = 3.9;
float kd3 = 8.8;


long oldRightPos  = -999; // encoder old pos
long oldLeftPos = -999;
const int baseRight = 95;
const int baseLeft = 120;
int positionLast;
int pos;
int error;
int lastError;

long duration;//ultrasonic sensor
int distance;

unsigned int first = 0; // ldr time count
unsigned int second = 0;

boolean searchIsDone = false;
boolean imSafe = false;

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
  defineQtr();
 setMotors(baseRight, baseLeft);
  initNrf();
  initPID();
  initEncPID();
}

void loop() {
     findKid();
     saveKid();
     while(1);
}
