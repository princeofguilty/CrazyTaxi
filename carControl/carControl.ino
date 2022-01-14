#define CAR_FORWARD   6
#define CAR_BACKWARD  5
#define CAR_LEFT      4
#define CAR_RIGHT     3

String g_incomingstr = ""; // for incoming serial data

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
  if(g_incomingstr == "s"){
    resetCarMovement();
    return;
  }
  if(g_incomingstr == "f"){
    digitalWrite(CAR_BACKWARD, LOW);
    digitalWrite(CAR_FORWARD, HIGH);
  }
  else if(g_incomingstr == "b"){
    digitalWrite(CAR_FORWARD, LOW);
    digitalWrite(CAR_BACKWARD, HIGH);
  }
  if(g_incomingstr == "r"){
    digitalWrite(CAR_LEFT, LOW);
    digitalWrite(CAR_RIGHT,HIGH);
  }
  else if(g_incomingstr == "l"){
    digitalWrite(CAR_RIGHT, LOW);
    digitalWrite(CAR_LEFT,HIGH);
  }
}

void loop() {
  g_incomingstr= "";
  if (Serial.available() > 0) {
    delay(60);
    g_incomingstr = Serial.readStringUntil('\n');
    Serial.println("btts");  
  }
  if (g_incomingstr != "") {
    processData();
  }
  //delay(50);
}
