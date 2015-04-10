/*
*    People Counter using
*    ultrasonic sensor (4-pin)
*    and a 7 segment display
*/

byte seven_seg_digits[10][7] = { { 1,1,1,1,1,1,0 },  // = 0
                                 { 0,1,1,0,0,0,0 },  // = 1
                                 { 1,1,0,1,1,0,1 },  // = 2
                                 { 1,1,1,1,0,0,1 },  // = 3
                                 { 0,1,1,0,0,1,1 },  // = 4
                                 { 1,0,1,1,0,1,1 },  // = 5
                                 { 1,0,1,1,1,1,1 },  // = 6
                                 { 1,1,1,0,0,0,0 },  // = 7
                                 { 1,1,1,1,1,1,1 },  // = 8
                                 { 1,1,1,1,0,1,1 }   // = 9
                                 };


int pingPin = 3;      //attach pin 3 to Trig
int echoPin = 4;      //attach pin 4 to Echo
int vccPin = 2;       //attach pin 2 to VCC
int gndPin = 5;       //attach pin 5 to GND

int count = 0;

long baseline = 0;     //baseline distance
long tempBaseline = 0; //temp baseline
int setupSamples = 30; //baseline setup samples
long threshold = 5;    //threshold from baseline to count
int initialSetup = 0;  //has been stabilized at least once

int incrSamples = 3;

void setup() {
  // setup sensor
  pinMode(vccPin, OUTPUT);
  pinMode(gndPin, OUTPUT);
  
  // setup display
  pinMode(6, OUTPUT);   
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  writeDot(0);  // start with the "dot" off
  sevenSegWrite(count);
}

void flashDot() {
  writeDot(1);
  delay(100);
  writeDot(0);
  delay(100);
  writeDot(1);
  delay(100);
  writeDot(0);
  delay(100);
  writeDot(1);
  delay(100);
  writeDot(0);
}

void writeDot(byte dot) {
  digitalWrite(13, dot);
}

void sevenSegWrite(byte digit) {
  byte pin = 6;
  for (byte segCount = 0; segCount < 7; ++segCount) {
    digitalWrite(pin, seven_seg_digits[digit][segCount]);
    ++pin;
  }
}

void loop() {
  long duration, inches, cm;

  digitalWrite(vccPin, HIGH);
 
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);
  
  if (!initialSetup) {
    writeDot(0);
    if (setupSamples > 0) {
      setupSamples--;
    }
    else {
      baseline = cm;
      setupSamples = 30;
      initialSetup = 1;
      flashDot();
    }
  }
  
  if (abs(baseline - cm) >= threshold && initialSetup) {
    writeDot(1);
    if (incrSamples > 0) {
      incrSamples--;
    }
    else {
      count++;
      if (count > 9) {
        count = 0;
      }
      sevenSegWrite(count);
      incrSamples = 3;
    }
    if (abs(tempBaseline - cm) < threshold) {
      if (setupSamples > 0) {
        tempBaseline = cm;
        setupSamples--;
      }
      else {
        baseline = cm;
        setupSamples = 30;
        flashDot();
      }
    }
  }
  else {
    writeDot(0);
  }
    
  delay(100);
}

long microsecondsToInches(long microseconds) {
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
