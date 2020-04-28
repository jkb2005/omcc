//system functions
byte rxbit1 = 0;
byte rxbit2 = 0;
byte rxbit3 = 0;
byte rxbit4 = 0;
byte rxbit5 = 0;
byte rxbit6 = 0;

boolean priority = 0;
int holdcounter = 0;
//****************************************************************************************************************************************************************************
void get4digits() {
  switch (Serial.read()) {
    case '0': rxbit1 = 0; break;
    case '1': rxbit1 = 1; break;
    case '2': rxbit1 = 2; break;
    case '3': rxbit1 = 3; break;
    case '4': rxbit1 = 4; break;
    case '5': rxbit1 = 5; break;
    case '6': rxbit1 = 6; break;
    case '7': rxbit1 = 7; break;
    case '8': rxbit1 = 8; break;
    case '9': rxbit1 = 9; break;
    default: rxbit1 = 0; break;
  }
  switch (Serial.read()) {
    case '0': rxbit2 = 0; break;
    case '1': rxbit2 = 1; break;
    case '2': rxbit2 = 2; break;
    case '3': rxbit2 = 3; break;
    case '4': rxbit2 = 4; break;
    case '5': rxbit2 = 5; break;
    case '6': rxbit2 = 6; break;
    case '7': rxbit2 = 7; break;
    case '8': rxbit2 = 8; break;
    case '9': rxbit2 = 9; break;
    default: rxbit2 = 0; break;
  }
  switch (Serial.read()) {
    case '0': rxbit3 = 0; break;
    case '1': rxbit3 = 1; break;
    case '2': rxbit3 = 2; break;
    case '3': rxbit3 = 3; break;
    case '4': rxbit3 = 4; break;
    case '5': rxbit3 = 5; break;
    case '6': rxbit3 = 6; break;
    case '7': rxbit3 = 7; break;
    case '8': rxbit3 = 8; break;
    case '9': rxbit3 = 9; break;
    default: rxbit3 = 0; break;
  }
  switch (Serial.read()) {
    case '0': rxbit4 = 0; break;
    case '1': rxbit4 = 1; break;
    case '2': rxbit4 = 2; break;
    case '3': rxbit4 = 3; break;
    case '4': rxbit4 = 4; break;
    case '5': rxbit4 = 5; break;
    case '6': rxbit4 = 6; break;
    case '7': rxbit4 = 7; break;
    case '8': rxbit4 = 8; break;
    case '9': rxbit4 = 9; break;
    default: rxbit4 = 0; break;
  }
}

void get3digits() {
  switch (Serial.read()) {
    case '0': rxbit1 = 0; break;
    case '1': rxbit1 = 1; break;
    case '2': rxbit1 = 2; break;
    case '3': rxbit1 = 3; break;
    case '4': rxbit1 = 4; break;
    case '5': rxbit1 = 5; break;
    case '6': rxbit1 = 6; break;
    case '7': rxbit1 = 7; break;
    case '8': rxbit1 = 8; break;
    case '9': rxbit1 = 9; break;
    default: rxbit1 = 0; break;
  }
  switch (Serial.read()) {
    case '0': rxbit2 = 0; break;
    case '1': rxbit2 = 1; break;
    case '2': rxbit2 = 2; break;
    case '3': rxbit2 = 3; break;
    case '4': rxbit2 = 4; break;
    case '5': rxbit2 = 5; break;
    case '6': rxbit2 = 6; break;
    case '7': rxbit2 = 7; break;
    case '8': rxbit2 = 8; break;
    case '9': rxbit2 = 9; break;
    default: rxbit2 = 0; break;
  }
  switch (Serial.read()) {
    case '0': rxbit3 = 0; break;
    case '1': rxbit3 = 1; break;
    case '2': rxbit3 = 2; break;
    case '3': rxbit3 = 3; break;
    case '4': rxbit3 = 4; break;
    case '5': rxbit3 = 5; break;
    case '6': rxbit3 = 6; break;
    case '7': rxbit3 = 7; break;
    case '8': rxbit3 = 8; break;
    case '9': rxbit3 = 9; break;
    default: rxbit3 = 0; break;
  }
}
//****************************************************************************************************************************************************************************
void resetholdtone(){
  holdcounter = 0;
}

void holdinterrupt(){
  if(priority == 1){
    if(channelbusy()){
      resetholdtone();
    }
  }
}

void holdtonecheck(){
  if(priority == 1){
    if(holdcounter > holdtoneinterval){
      keyup();
      audioroutelocal();
      tone(tonepin,800);
      delay(500);
      noTone(tonepin);
      audiorouteremote();
      dekey();
      holdcounter = 0;
    }
    delay(10);
    holdcounter++;
  }
  else{
    holdcounter = 0;
  }
}
//****************************************************************************************************************************************************************************
void encodetwotone(int tone1input, int duration1input, int tone2input, int duration2input) {
  keyup();
  audioroutelocal();
  tone(tonepin, tone1input);
  delay(duration1input);
  tone(tonepin, tone2input);
  delay(duration2input);
  noTone(tonepin);
  audiorouteremote();
  dekey();
}
//****************************************************************************************************************************************************************************
encodesingletone(int toneinputval, int tonedurationinputval) {
  keyup();
  audioroutelocal();
  tone(tonepin, toneinputval);
  delay(tonedurationinputval);
  noTone(tonepin);
  audiorouteremote();
  dekey();
}
//****************************************************************************************************************************************************************************
void tonepulse(byte inputpulse){
  byte repeats = 0;
  while(repeats < inputpulse){
    tone(tonepin,800);
    delay(125);
    noTone(tonepin);
    delay(60);
    repeats++;
  }
}
void encodealarmbox(byte digit1,byte digit2,byte digit3){
  keyup();
  audioroutelocal();
  tonepulse(digit1);
  delay(500);
  tonepulse(digit2);
  delay(500);
  tonepulse(digit3);
  audiorouteremote();
  dekey();
}
//****************************************************************************************************************************************************************************
void receivetwotone() {
  get4digits();
  int tone1 = rxbit1 * 1000;
  tone1 += rxbit2 * 100;
  tone1 += rxbit3 * 10;
  tone1 += rxbit4;
  get4digits();
  int duration1 = rxbit1 * 1000;
  duration1 += rxbit2 * 100;
  duration1 += rxbit3 * 10;
  duration1 += rxbit4;
  get4digits();
  int tone2 = rxbit1 * 1000;
  tone2 += rxbit2 * 100;
  tone2 += rxbit3 * 10;
  tone2 += rxbit4;
  get4digits();
  int duration2 = rxbit1 * 1000;
  duration2 += rxbit2 * 100;
  duration2 += rxbit3 * 10;
  duration2 += rxbit4;
  encodetwotone(tone1, duration1, tone2, duration2);
}
//****************************************************************************************************************************************************************************
void receivesingletone() {
  get4digits();
  int toneinput = rxbit1 * 1000;
  toneinput += rxbit2 * 100;
  toneinput += rxbit3 * 10;
  toneinput += rxbit4;
  get4digits();
  int tonedurationinput = rxbit1 * 1000;
  tonedurationinput += rxbit2 * 100;
  tonedurationinput += rxbit3 * 10;
  tonedurationinput += rxbit4;
  encodesingletone(toneinput, tonedurationinput);
}
//****************************************************************************************************************************************************************************
void mtpspulse(byte inputcode){
  switch(inputcode){
    case '0':tone(tonepin,1187); break;
    case '1':tone(tonepin,939); break;
    case '2':tone(tonepin,822); break;
    case '3':tone(tonepin,723); break;
    case '4':tone(tonepin,640); break;
    case '5':tone(tonepin,569); break;
    case '6':tone(tonepin,511); break;
    case '7':tone(tonepin,461); break;
    case '8':tone(tonepin,433); break;
    case '9':tone(tonepin,420); break;
    case 'A':tone(tonepin,1300); break;
    case 'B':tone(tonepin,1400); break;
    case 'C':tone(tonepin,1500); break;
    case 'D':tone(tonepin,1600); break;
    case 'E':tone(tonepin,1700); break;
    case 'F':tone(tonepin,1800); break;
  }
  delay(80);
  noTone(tonepin);
}

void encodemtps(byte char1, byte char2, byte char3, byte char4, byte char5, byte char6) {
  keyup();
  audioroutelocal();
  mtpspulse(char1);
  mtpspulse(char2);
  mtpspulse(char3);
  mtpspulse(char4);
  mtpspulse(char5);
  mtpspulse(char6);
  audiorouteremote();
  dekey();
}
//****************************************************************************************************************************************************************************
void receivealarmbox() {
  get3digits();
  encodealarmbox(rxbit1,rxbit2,rxbit3);
}
//****************************************************************************************************************************************************************************
void advisorytone() {
  keyup();
  audioroutelocal();
  tone(tonepin, 800);
  delay(250);
  tone(tonepin, 1500);
  delay(250);
  tone(tonepin, 800);
  delay(250);
  tone(tonepin, 1500);
  delay(250);
  tone(tonepin, 800);
  delay(250);
  tone(tonepin, 1500);
  delay(250);
  tone(tonepin, 800);
  delay(250);
  tone(tonepin, 1500);
  delay(250);
  tone(tonepin, 800);
  delay(250);
  tone(tonepin, 1500);
  delay(250);
  noTone(tonepin);
  audiorouteremote();
  dekey();
}
void alarmtone(byte alarmtype) {
  keyup();
  audioroutelocal();
  if (alarmtype == 1) {
    tone(tonepin, 1000);
    delay(250);
    noTone(tonepin);
    delay(250);
    tone(tonepin, 1000);
    delay(250);
    noTone(tonepin);
    delay(250);
    tone(tonepin, 1000);
    delay(250);
    noTone(tonepin);
    delay(250);
    tone(tonepin, 1000);
    delay(250);
    noTone(tonepin);
    delay(250);
    tone(tonepin, 1000);
    delay(250);
    noTone(tonepin);
  }
  else if (alarmtype == 2) {
    tone(tonepin, 500);
    delay(125);
    tone(tonepin, 1000);
    delay(125);
    tone(tonepin, 500);
    delay(125);
    tone(tonepin, 1000);
    delay(125);
    tone(tonepin, 500);
    delay(125);
    tone(tonepin, 1000);
    delay(125);
    tone(tonepin, 500);
    delay(125);
    tone(tonepin, 1000);
    delay(125);
    tone(tonepin, 500);
    delay(125);
    tone(tonepin, 1000);
    delay(125);
    tone(tonepin, 500);
    delay(125);
    tone(tonepin, 1000);
    delay(125);
    tone(tonepin, 500);
    delay(125);
    tone(tonepin, 1000);
    delay(125);
    tone(tonepin, 500);
    delay(125);
    tone(tonepin, 1000);
    delay(125);
    tone(tonepin, 500);
    delay(125);
    tone(tonepin, 1000);
    delay(125);
    tone(tonepin, 500);
    delay(125);
    tone(tonepin, 1000);
    delay(125);
    noTone(tonepin);
  }
  else if (alarmtype == 3) {
    tone(tonepin, 1000);
    delay(2500);
    noTone(tonepin);
  }
  audiorouteremote();
  dekey();
}
//****************************************************************************************************************************************************************************
void checkforevents() {
  if (Serial.available()) {
    delay(100);
    byte prefix = Serial.read();
    if (prefix == 'A') {
      resetholdtone();
      receivetwotone();
    }
    else if (prefix == 'B') {
      resetholdtone();
      receivesingletone();
    }
    else if (prefix == 'C') {
      resetholdtone();
      encodemtps(Serial.read(), Serial.read(), Serial.read(), Serial.read(), Serial.read(), Serial.read());
    }
    else if (prefix == 'D') {
      resetholdtone();
      receivealarmbox();
    }
    else if (prefix == '0') {
      resetholdtone();
      advisorytone();
    }
    else if (prefix == '1') {
      resetholdtone();
      alarmtone(1);
    }
    else if (prefix == '2') {
      resetholdtone();
      alarmtone(2);
    }
    else if (prefix == '3') {
      resetholdtone();
      alarmtone(3);
    }
    else if (prefix == '4') {
      priority = 1;
      keyup();
      audioroutelocal();
      tone(tonepin,800);
      delay(125);
      tone(tonepin,1500);
      delay(125);
      noTone(tonepin);
      audiorouteremote();
      dekey();
    }
    else if (prefix == '5') {
      priority = 0;
      keyup();
      audioroutelocal();
      tone(tonepin,1500);
      delay(125);
      tone(tonepin,800);
      delay(125);
      noTone(tonepin);
      audiorouteremote();
      dekey();
    }
  }
}
//****************************************************************************************************************************************************************************
