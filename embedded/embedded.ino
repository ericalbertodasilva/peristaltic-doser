

/*
 * PINS IN USE:
 *  0: RX
 *  1: TX
 *  2: Zero Cross
 *  3: Peristaltic Pump 1
 *  5: Peristaltic Pump 2
 *  6: Peristaltic Pump 3
 *  9: Peristaltic Pump 4
 *  10: Shaker
 *  11: Resistance
 *  A0: Temperature sensor
 */

struct peristalticPump {
  int pin;
  int pinRevert;
  int number;
  int ratio;
  int tempOn;
  int turn;
  int turningDirection;
};

peristalticPump pump1;
peristalticPump pump2;
peristalticPump pump3;
peristalticPump pump4;
peristalticPump getPumpSerial;

/*Serial communication*/
const byte NUMCHARS = 64;
char _receivedChars[NUMCHARS];
boolean _newMsgReceived = false;

/*Temp*/
unsigned long _previousMillis = 0;
unsigned long modDivMinTime;

void setConfigInitPumps(){
  pump1.pin = 3;
  pump1.pinRevert = 5;
  pump1.number = 1;
  pump1.ratio = 0;
  pump1.tempOn = 0;
  pump1.turn = 0;
  pump1.turningDirection = 0;

  pump2.pin = 6;
  pump2.pinRevert = 9;
  pump2.number = 2;
  pump2.ratio = 0;
  pump2.tempOn = 0;
  pump2.turn = 0;
  pump2.turningDirection = 0;

  pump3.pin = 10;
  pump3.pinRevert = 11;
  pump3.number = 3;
  pump3.ratio = 0;
  pump3.tempOn = 0;
  pump3.turn = 0;
  pump3.turningDirection = 0;

  getPumpSerial.pin = 0;
  getPumpSerial.pinRevert = 11;
  getPumpSerial.number = 0;
  getPumpSerial.ratio = 0;
  getPumpSerial.tempOn = 0;
  getPumpSerial.turn = 0;
  getPumpSerial.turningDirection = 0;

}

void setPins(){
  pinMode(pump1.pin, OUTPUT);
  pinMode(pump1.pinRevert, OUTPUT); 
  pinMode(pump2.pin, OUTPUT);
  pinMode(pump2.pinRevert, OUTPUT);  
  pinMode(pump3.pin, OUTPUT);
  pinMode(pump3.pinRevert, OUTPUT);
  pinMode(pump4.pin, OUTPUT);
  pinMode(pump4.pinRevert, OUTPUT); 
}

void setConfigPump()
{
  
  char * strtokIndx;
  char tempChars[NUMCHARS];
  strcpy(tempChars, _receivedChars);
  strtokIndx = strtok(tempChars,";");

  strtokIndx = strtok(NULL, ";");
  getPumpSerial.number = atoi(strtokIndx);

  strtokIndx = strtok(NULL, ";");
  getPumpSerial.ratio = atoi(strtokIndx);

  strtokIndx = strtok(NULL, ";");
  getPumpSerial.tempOn = atoi(strtokIndx);

  strtokIndx = strtok(NULL, ";");
  getPumpSerial.turn = atoi(strtokIndx);

  strtokIndx = strtok(NULL, ";");
  getPumpSerial.turningDirection = atoi(strtokIndx);

  getPumpSerial.ratio = map(getPumpSerial.ratio, 0, 100, 0, 255);
  getPumpSerial.tempOn = map(getPumpSerial.tempOn, 0, 100, 0, 120);

  setSerialConfigPeristalticPump();

  String s = "<c;" + String(getPumpSerial.number) + ";" + String(getPumpSerial.ratio) + ";" + String(getPumpSerial.tempOn) + ";" + String(getPumpSerial.turn)+";"+String(getPumpSerial.turningDirection) + ">";
  
  Serial.println(s);
}

void setSerialConfigPeristalticPump(){
  switch (getPumpSerial.number)
  {
  case 1:
    pump1.ratio = getPumpSerial.ratio;
    pump1.tempOn = getPumpSerial.tempOn;
    pump1.turn = getPumpSerial.turn;
    pump1.turningDirection = getPumpSerial.turningDirection;
    break;

  case 2:
    pump2.ratio = getPumpSerial.ratio;
    pump2.tempOn = getPumpSerial.tempOn;
    pump2.turn = getPumpSerial.turn;
    pump2.turningDirection = getPumpSerial.turningDirection;
    break;

  case 3:
    pump3.ratio = getPumpSerial.ratio;
    pump3.tempOn = getPumpSerial.tempOn;
    pump3.turn = getPumpSerial.turn;
    pump3.turningDirection = getPumpSerial.turningDirection;
    break;

  case 4:
    pump4.ratio = getPumpSerial.ratio;
    pump4.tempOn = getPumpSerial.tempOn;
    pump4.turn = getPumpSerial.turn;
    pump4.turningDirection = getPumpSerial.turningDirection;
    break;
  
  default:
    Serial.println("Pump does not exist, try again!");
    break;
  }
}

/*
 * Atencao: Duas variaveis static... algumas vezes nem toda a mensagem chega 
 * de uma vez. É possível compor a mensagem em mais do que um ciclo do loop
*/
void getSerialMessage() {
  static boolean recvInProgress = false;
  static byte j = 0;
  char startMarker = '<';
  char endMarker = '>';
  char c;

  while (Serial.available() > 0 && _newMsgReceived == false) {
    c = Serial.read();

    if (recvInProgress == true) {
      if (c != endMarker) {
        _receivedChars[j] = c;
        j++;
        if (j >= NUMCHARS) {
            j = NUMCHARS - 1;
        }
      } else {
        _receivedChars[j] = '\0'; // terminate the string
        recvInProgress = false;
        j = 0;
        _newMsgReceived = true;
      }
    }

    else if (c == startMarker) {
      recvInProgress = true;
    }
  }
}

void decodeRequest()
{    
  String s;

  char cmd = _receivedChars[0];

  switch(cmd)
  {
    case '?':
      Serial.println("<?>");
      break;

    case 'r':
      // to do
      // sendAllData();
      break;

    case 'c':
      setConfigPump();
      break;

    default:
      Serial.println("<?>");
      break;
  }    
}

void setPortOutAnalogicToWithRevert(int pin, int pinRevert, int value, int revert){

  if (revert){
    analogWrite(pin, value);
    analogWrite(pinRevert, 0);
  }else{
    analogWrite(pin, 0);
    analogWrite(pinRevert, value);
  }
  
}


void setPeristalticPumps(){
  modDivMinTime = millis() / 1000 % 120;
  

  if((pump1.turn == 1) && (modDivMinTime < pump1.tempOn)){
    setPortOutAnalogicToWithRevert(pump1.pin, pump1.pinRevert, pump1.ratio, pump1.turningDirection);
  } else {
    setPortOutAnalogicToWithRevert(pump1.pin, pump1.pinRevert, 0, pump1.turningDirection);
  }

  if((pump2.turn == 1) && (modDivMinTime < pump2.tempOn)){
    setPortOutAnalogicToWithRevert(pump2.pin, pump2.pinRevert, pump2.ratio, pump2.turningDirection);
  } else {
    setPortOutAnalogicToWithRevert(pump2.pin, pump2.pinRevert, 0, pump2.turningDirection);
  }

  if((pump3.turn == 1) && (modDivMinTime < pump3.tempOn)){
    setPortOutAnalogicToWithRevert(pump3.pin, pump3.pinRevert, pump3.ratio, pump3.turningDirection);
  } else {
    setPortOutAnalogicToWithRevert(pump3.pin, pump3.pinRevert, 0, pump3.turningDirection);
  }
}

void setup(){

  Serial.begin(57600);

  //setPins();
  setConfigInitPumps();
}

void loop() {
  getSerialMessage();
  if (_newMsgReceived == true) {      
      decodeRequest();    
      _newMsgReceived = false;
  }

  setPeristalticPumps();
}
