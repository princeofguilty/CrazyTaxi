#define CAR_FORWARD   6
#define CAR_BACKWARD  5
#define CAR_LEFT      4
#define CAR_RIGHT     3

char g_incomingChar = ""; // for incoming serial data

void setup() {
  pinMode(CAR_FORWARD, OUTPUT);
  pinMode(CAR_BACKWARD, OUTPUT);
  pinMode(CAR_LEFT, OUTPUT);
  pinMode(CAR_RIGHT, OUTPUT);

  digitalWrite(CAR_FORWARD, LOW);
  digitalWrite(CAR_BACKWARD, LOW);
  digitalWrite(CAR_LEFT, LOW);
  digitalWrite(CAR_RIGHT, LOW);
  Serial.begin(9600);
}


void resetCarMovement(){
  digitalWrite(CAR_FORWARD, LOW);
  digitalWrite(CAR_BACKWARD, LOW);
  digitalWrite(CAR_LEFT, LOW);
  digitalWrite(CAR_RIGHT, LOW);
}

void processData(){
  if(g_incomingChar == 6){ // stop
    resetCarMovement();
    return;
  }
  if(g_incomingChar == 0){ // forward
    digitalWrite(CAR_BACKWARD, LOW);
    digitalWrite(CAR_FORWARD, HIGH);
  }
  else if(g_incomingChar == 1){ // backward
    digitalWrite(CAR_FORWARD, LOW);
    digitalWrite(CAR_BACKWARD, HIGH);
  }
  else if(g_incomingChar == 2){ // right forward
    digitalWrite(CAR_LEFT, LOW);
    digitalWrite(CAR_RIGHT,HIGH);
    digitalWrite(CAR_BACKWARD, LOW);
    digitalWrite(CAR_FORWARD, HIGH);
  }
  else if(g_incomingChar == 3){ // left forward
    digitalWrite(CAR_RIGHT, LOW);
    digitalWrite(CAR_LEFT,HIGH);
    digitalWrite(CAR_BACKWARD, LOW);
    digitalWrite(CAR_FORWARD, HIGH);
  }
  else if(g_incomingChar == 4){ // right backward
    digitalWrite(CAR_LEFT, LOW);
    digitalWrite(CAR_RIGHT,HIGH);
    digitalWrite(CAR_FORWARD, LOW);
    digitalWrite(CAR_BACKWARD, HIGH);
  }
  else if(g_incomingChar == 5){ // left backward
    digitalWrite(CAR_RIGHT, LOW);
    digitalWrite(CAR_LEFT,HIGH);
    digitalWrite(CAR_FORWARD, LOW);
    digitalWrite(CAR_BACKWARD, HIGH);
  }
}

void loop() {
  g_incomingChar= ' ';
  if (Serial.available() > 0) {
    delay(60);
    g_incomingChar = Serial.read();
    g_incomingChar -= '0';
  }
  if (g_incomingChar != ' ') {
    processData();
  }
  delay(50);
}