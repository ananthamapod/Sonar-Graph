/************************* GLOBALS *************************/
const int pingPin = 7;
long distance = 0;
char val;
const int ledPin = 13;

/***********************************************************/


void setup()
{
  pinMode(ledPin, OUTPUT);
  // initialize serial communications at a 9600 baud rate
  Serial.begin(9600);
  establishContact();
}

void loop()
{
  if(Serial.available()) {
    val = Serial.read();
  }
  if(val == 1') {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
  
  int sensorValue = analogRead(A0);
  // print out the value you read:
  // Serial.println(sensorValue);
  Serial.println(distance);
  //wait 100 milliseconds so we don't drive themselves crazy
  distance = microsecondsToInches(ping());
  delay(300);
}

/************************ UTILITIES ************************/

void establishContact() {
  while (Serial.available() <= 0) {
  Serial.println("A");   // send a capital A
  delay(300);
  }
}

//These are modified from from built-in Ping example

long ping() {
  // Send out ping
  // Triggered by HIGH pulse of at least 2 microseconds
  // Bound with LOW pulses to ensure clean HIGH pulse
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
 
 // Read ping time
 pinMode(pingPin, INPUT);
 return pulseIn(pingPin, HIGH);
}

long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

/***********************************************************/
