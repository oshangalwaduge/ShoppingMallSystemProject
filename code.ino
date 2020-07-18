#define TRIG_PIN 8
#define ECHO_PIN 9
#define LED_PIN 5
#define LDR_PIN A1
#define DELAY 1000

//Varible declaration
int ldr_reading = 0;
//People count
int maxvisitors = 10;
long duration = 0;
int distance = 0;
String input = "";
int count = 0;

void setup() {  
  pinMode(LED_PIN, OUTPUT);              
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {
  int current_distance = Distance();

  //LDR value : F500
  ldr_reading = analogRead(LDR_PIN);

  Serial.print("D");
  Serial.println(current_distance);
  Serial.print("F");
  Serial.println(ldr_reading);
  delay(DELAY);
  
  while(Serial.available() > 0) {
    input += (char) Serial.read();
    delay(5);
  }

  if(input == "on") {
    digitalWrite(LED_PIN, HIGH);
    Serial.print("Input is ");
    Serial.println(input);
  } else if(input == "off") {
    digitalWrite(LED_PIN, LOW);
    Serial.print("Input is ");
    Serial.println(input);
  }
  
  while(Serial.available() > 0) {
    count += (int) Serial.read();
    delay(5);
  }

  //System return value is 1 system remove one user
  if(input == 1) {
    manageVisitors();
    Serial.print("Number of visitors in the mall:");
    Serial.println(maxvisitors);
  } else if(input == 0) {
    //Add a new visitor to the system as a visitor goes into the mall.
    manageVisitorsadd();
    Serial.print("New visitor entered.");
    Serial.println(maxvisitors);
  }
}

//Get distance value from the sensor HC-SR04
int Distance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration * 0.0330) / 2;

  return distance;
}

//Reduce the total number of visitors inside the mall when a visitor leaves the mall.
int manageVisitors(){
  maxvisitors--;
}

//Increase the total number of visitors inside the mall when a visitor comes to the mall.
int manageVisitorsadd(){
  maxvisitors++;
}
