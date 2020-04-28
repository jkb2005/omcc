//pinout for microcontroller
/* pinout
D02 - tone output
D03 - audio switch
D04 - ptt request
D05 - COR input
D06 - TX/BUSY input
D07 - emergency alarm input
D08 - emergency ack output
D09 - aux alarm input
D10 - aux ack output 
D11 - n/a
D12 - n/a
D13 - heartbeat led
A00 - n/a
A01 - n/a
A02 - n/a
A03 - n/a
A04 - n/a
A05 - n/a
A06 - n/a
A07 - n/a
*/

byte tonepin = 2;
byte routepin = 3;
byte pttpin = 4;
byte corpin = 5;
byte busyinput = 6;
byte emergencyinput = 7;
byte emergencyackoutput = 8;
byte auxalarminput = 9;
byte auxackoutput = 10;
byte heartbeat = 13;

byte routeon = LOW;
byte routeoff = HIGH;
byte pttenableval = LOW;
byte pttdisableval = HIGH;
byte carrieractiveval = LOW;
byte channelbusyval = LOW;
byte emergencyactiveval = LOW;
byte auxactiveval = LOW;
byte ackon = HIGH;
byte ackoff = LOW;

void initializepins(){
  pinMode(tonepin,OUTPUT);
  pinMode(routepin,OUTPUT);
  digitalWrite(routepin,routeoff);
  pinMode(pttpin,OUTPUT);
  digitalWrite(pttpin,pttdisableval);
  pinMode(corpin,INPUT_PULLUP);
  pinMode(busyinput,INPUT_PULLUP);
  pinMode(emergencyinput,INPUT_PULLUP);
  pinMode(emergencyackoutput,OUTPUT);
  digitalWrite(emergencyackoutput,ackoff);
  pinMode(auxalarminput,INPUT_PULLUP);
  pinMode(auxackoutput,ackoff);
  pinMode(heartbeat,OUTPUT);
}

boolean channelbusy(){
  if(digitalRead(corpin) == carrieractiveval || digitalRead(busyinput) == channelbusyval){
    return true;
  }
  else{
    return false;
  }
}
void keyup(){
  digitalWrite(pttpin,pttenableval);
  delay(pttdelay * 10);
}
void dekey(){
  delay(pttdelay * 10);
  digitalWrite(pttpin,pttdisableval);
  delay(pttdelay * 10);
}
void heartbeatcycle(){
  byte state = digitalRead(heartbeat);
  digitalWrite(heartbeat,!state);
}
boolean emergencyactive(){
  if(digitalRead(emergencyinput) == emergencyactiveval){
    digitalWrite(emergencyackoutput,ackon);
    delay(acktime);
    digitalWrite(emergencyackoutput,ackoff);
    return true;
  }
  else{
    return false;
  }
}
boolean auxactive(){
  if(digitalRead(auxalarminput) == auxactiveval){
    digitalWrite(auxackoutput,ackon);
    delay(acktime);
    digitalWrite(auxackoutput,ackoff);
    return true;
  }
  else{
    return false;
  }
}
void audioroutelocal(){
  digitalWrite(routepin,routeon);
}
void audiorouteremote(){
  digitalWrite(routepin,routeoff);
}
