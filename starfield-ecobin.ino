#include <Servo.h> // Library to control servo motor

Servo myservo;

#define trigIn 10 // Trigger pin for ultrasonic sensor inside the dustbin 
#define echoIn 9 // Echo pin for ultrasonic sensor inside the dustbin
#define trigOut 8 // Trigger pin for ultrasonic sensor outside the dustbin
#define echoOut 7 // Echo pin for ultrasonic sensor outside the dustbin
#define binLevel 10 // max bin level declared as 10cm

#define powerLed 5 // led to indicate power
#define avlLed 4 // led to indicate bin is not full
#define fullLed 3 // led to indicate bin is full
#define buzzer 11  // buzzer pin

int pos = 180; // initial position of servo motor (Close or remain closed)
long duration; // store time duration of sound travel
int distance; // store actual distance to object
bool flag = 0; // to exit a loop
float disIn; // to store level of bin inside
float disOut; // to store distance to an obstruction outside

unsigned long alarmThreshholdTime = 10000; // threshhold for non-stop alarm
unsigned long alarmStartTime, currentTime, elapsedTime = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Open serial communications and wait for port to open:

  // setting pinMode
  pinMode(buzzer, OUTPUT);
  pinMode(powerLed, OUTPUT);
  pinMode(avlLed, OUTPUT);
  pinMode(fullLed, OUTPUT);
  pinMode(trigIn, OUTPUT);
  pinMode(echoIn, INPUT);
  pinMode(trigOut, OUTPUT);
  pinMode(echoOut, INPUT);

  myservo.attach(6);
  myservo.write(pos);

  digitalWrite(powerLed, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  currentTime = millis();
  elapsedTime = currentTime - alarmStartTime;

  disOut = checkDistance(trigOut, echoOut);
  disIn = checkDistance(trigIn, echoIn);
  Serial.println("\nInside = " + String(disIn));
    Serial.println("\nOutside = " + String(disOut));

  // Condition to check if object in front of dustbin (Open)
  if ((disOut < 30) && (flag == 0)) {
    myservo.write(pos - 150);
    delay(1000);

    // loop to keep the bin open until obstruction cleares
    while (disOut < 30) {
      disOut = checkDistance(trigOut, echoOut);
      delay(1000);
    }
  }
  else {  // Condition to check if no object in front of dustbin (Close or stay closed)
    myservo.write(pos);
  }
  delay(100);

  // Condition to check if bin is full
  if ((disIn < binLevel) && (flag == 0)) {
    delay(500);
    disIn = checkDistance(trigIn, echoIn);
    if ((disIn < binLevel) && (flag == 0)) {
      myservo.write(pos);
      flag = 1;
      alarmStartTime = millis();

      Serial.println("\nBIN FULL..............");
      digitalWrite(avlLed, LOW);
      digitalWrite(fullLed, HIGH);
      digitalWrite(buzzer, HIGH);
      delay(300);
      digitalWrite(fullLed, LOW);
      delay(300);
      digitalWrite(fullLed, HIGH);
      delay(300);
      digitalWrite(fullLed, LOW);
      delay(300);
      digitalWrite(fullLed, HIGH);
      delay(300);
      digitalWrite(fullLed, LOW);
      delay(300);
      digitalWrite(fullLed, HIGH);
    }
  }

  Serial.println("Time is " + String(elapsedTime));
  if (elapsedTime >= alarmThreshholdTime) {
    alarmStartTime = 0;
    digitalWrite(buzzer, LOW);
    Serial.println("Time up for alarms ");
  }

  // Condition to check if bin is not full
  if (disIn > binLevel) {
    flag = 0;
    Serial.println("\nBin emptied...");
    digitalWrite(buzzer, LOW);
    digitalWrite(fullLed, LOW);
    digitalWrite(avlLed, HIGH);
  }
  delay(100);
}

int checkDistance(int var1, int var2) {
  digitalWrite(var1, LOW);
  delayMicroseconds(2);
  digitalWrite(var1, HIGH); // triger signal
  delayMicroseconds(10);
  digitalWrite(var1, LOW);
  duration = pulseIn(var2, HIGH);
  distance = 0.034 * (duration / 2); // formula to get distance using speed of sound and time
  return distance;
}
