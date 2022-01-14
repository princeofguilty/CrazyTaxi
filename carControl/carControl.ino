#define CAR_FORWARD   6
#define CAR_BACKWARD  5
#define CAR_LEFT      4
#define CAR_RIGHT     3

String g_incomingString = ""; // for incoming serial data

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
  if(g_incomingString == "s"){
    resetCarMovement();
    return;
  }
  if(g_incomingString == "f"){
    digitalWrite(CAR_BACKWARD, LOW);
    digitalWrite(CAR_FORWARD, HIGH);
  }
  else if(g_incomingString == "b"){
    digitalWrite(CAR_FORWARD, LOW);
    digitalWrite(CAR_BACKWARD, HIGH);
  }
  if(g_incomingString == "r"){
    digitalWrite(CAR_LEFT, LOW);
    digitalWrite(CAR_RIGHT,HIGH);
  }
  else if(g_incomingString == "l"){
    digitalWrite(CAR_RIGHT, LOW);
    digitalWrite(CAR_LEFT,HIGH);
  }
}

void loop() {
  g_incomingString="";
  if (Serial.available() > 0) {
    delay(60);
    int h= Serial.available();    
    h--; 
    for (int i=0;i<h;i++){
      g_incomingString += (char)Serial.read();
    }
    Serial.read();
  }
  if (g_incomingString != "") {
    Serial.println(g_incomingString);
    processData();
  }
  delay(50);
}
