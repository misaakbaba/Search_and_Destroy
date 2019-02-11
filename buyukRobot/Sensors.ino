
void defineQtr(){
  for(int i=0;i<qtr;i++){
    pinMode(qtrPins[i],INPUT_PULLUP);
  }
}

 void readQtr(){
   for(int i=0;i<qtr;i++){
     qtrVal[i]=digitalRead(qtrPins[i]);
   }
 }

 void printQtr(){
  for(int i=0;i<qtr;i++){
    Serial.print(qtrVal[i]);
     Serial.print("--");
  }
  Serial.println();
 }

 void defineLdr(){
  pinMode(ldr,INPUT);
 }

 
