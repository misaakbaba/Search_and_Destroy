#include <SharpIR.h>
#include <PID_v1.h>
#include <AFMotor.h>
#include <Encoder.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(47, 49); // CE, CSN
const uint64_t writingPipe = 0xE6E6E6E6E6E2;
const uint64_t readingPipe = 0xE6E6E6E6E6E6;
char roomName;
char Dady = 'Z';
char situation;
#define qtr 8
#define lim 9
#define ldr 42
#define trigPin 38
#define echoPin 40
#define  mz80 45
#define sharp A8
#define IR A9
#define model 1080
double Setpoint, Input, Output;
double Setpoint2, Input2, Output2; //wall follow pid value
double Setpoint3, Input3, Output3; //enc pıd value

enum directions {
  RIGHT,
  LEFT
};

const byte qtrPins[] = {36, 34, 32, 30, 28, 26, 24, 22};
int qtrVal[] = {0, 0, 0, 0, 0, 0, 0, 0};

Encoder leftEnc(19, 18);
Encoder rightEnc(21, 20);
AF_DCMotor motorRight(2);
AF_DCMotor motorLeft(1);
SharpIR SharpIR(IR, model);

float kp = 6.4;
float ki = 0.3;
float kd = 1.5;

float kp2 = 5;
float ki2 = 1;
float kd2 = 2;

float kp3 = 160;
float ki3 = 3.25;
float kd3 = 4;


long oldRightPos  = -999; // encoder old pos
long oldLeftPos = -999;
const int baseRight = 102;
const int baseLeft = 102;

int positionLast;
int pos;
int error;
int lastError;
int wallLast = 0;


unsigned int first = 0; // ldr time count
unsigned int second = 0;

boolean searchIsDone = false;
boolean imSafe = false;

int enA = 2;
int in1 = 43;
int in2 = 41;
// motor two
int enB = 3;
int in3 = 39;
int in4 = 37;


int lightFreqs[] = {0, 0, 0};

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
  defineQtr();
  setMotors(baseRight, baseLeft);
  initPID();
  defineSensors();
  initEncPID();
  initNrf();
  defineMotors();

}

void loop() {
  
    if (!imSafe) {
      if (!searchIsDone) {
        travelRooms();
        goSafeZone();
      } else {
        listenDady();
        helpDady();
        escapefromAlcatraz();
      }
    }
   
  
}
