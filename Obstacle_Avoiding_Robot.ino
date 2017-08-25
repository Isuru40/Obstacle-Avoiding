#define trigPin 13
#define echoPin 12
#define LEDpin 2
int L1 = 6, L2 = 7, L3 = 8, L4 = 9, tcrt = 0; // Pins connected to Motor driver L298N H-Bridge module
long duration, distance;

void setup() {
  pinMode(A4, INPUT);
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(L3, OUTPUT);
  pinMode(L4, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LEDpin, OUTPUT);
  digitalWrite(LEDpin, LOW);
  Serial.begin(9600);
}

void loop() {
  tcrt = analogRead(A4);
  Serial.println(tcrt);
  delay(1000);
  // Distance Mesuring
  analogWrite(A0, HIGH);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;

  if (distance < 20) {
    digitalWrite(LEDpin, HIGH);
    //Serial.print("Object Detected.  |  ");
    //Serial.print(distance);
    //Serial.println(" cm. We should Turn.");
    halt(100);
    reverse(200);
    leftSpin(500);
  } else {
    digitalWrite(LEDpin, LOW);
    forward(1000);
    //Serial.println("Yahooo! Going Forward.");
  }
  delay(0);
}

void robMove(int l1, int l2, int r1, int r2) {
  digitalWrite(L1, l1);
  digitalWrite(L2, l2);
  digitalWrite(L3, r1);
  digitalWrite(L4, r2);
}

void reverse(int wait) {
  robMove(LOW, HIGH, LOW, HIGH);
  delay(wait);
}
void forward(int wait) {
  robMove(HIGH, LOW, HIGH, LOW);
}
void leftSpin(int wait) {
  robMove(HIGH, LOW, LOW, HIGH);
  delay(wait);
}
void rightSpin(int wait) {
  robMove(LOW, HIGH, HIGH, LOW);
  delay(wait);
}
void halt(int wait) {
  robMove(LOW, LOW, LOW, LOW);
  delay(wait);
}
