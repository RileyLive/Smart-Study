String command;
String commands;

//pomodoro led lights for the cycle
#define green_first 12
#define yellow_secound 13
#define red_third 11

//The Number of Pomodoro's
#define pom4LED A5
#define pom3LED A4
#define pom2LED A3
#define pom1LED A2

//pomodoro modes and states
#define studying 0
#define shorter_Break 1
#define long_Break 2
int current_state = studying;
int current_count = 0;

//photoresistor led and light level pins
#define sensorPin A0
#define orangeLed 8
#define yellowLed 9
#define blueLed 4
#define greenLed 6
#define redLed 5
#define BUTTON_PIN 10

//distance sensor pins
#define echoPin 2
#define trigPin 3
long duration;
int distance;
int buzzer = 7;

//setup of the pins
void setup() {

  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(blueLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(orangeLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(green_first, OUTPUT);
  pinMode(yellow_secound, OUTPUT);
  pinMode(red_third, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(pom4LED, OUTPUT);
  pinMode(pom3LED, OUTPUT);
  pinMode(pom2LED, OUTPUT);
  pinMode(pom2LED, OUTPUT);

  while (digitalRead(BUTTON_PIN) == HIGH);

}

//loop current state of the pomodoro
void loop()
{

  if (current_state == studying) {
    study_Mode();

  }
  if (current_state == shorter_Break) {
    short_Mode();
  }
  if (current_state == long_Break) {
    long_Mode();
  }

}

//the work_mode of the Pomodoro
void study_Mode(void) {
  pomodoro_Count();

  //first LED Green- 0-20 minutes
  digitalWrite(green_first, HIGH);

  //loops through to print out the data from the photoresistor and distance sensor.
  sensorloop();

  ;
  //yellow LED-5 Minutes
  digitalWrite(yellow_secound, HIGH);
   digitalWrite(green_first, LOW);
  //loops through to print out the data from the photoresistor and distance sensor.
  sensorloop2();

  
  //Red LED-25 minutes is up
  digitalWrite(red_third, LOW);


  //checks the current_count, increments each cycle
  current_count++;

  //if the count is less than 3 go to a short break
  if (current_count <= 3) {
    current_state = shorter_Break;
  }

  // if the current count is 4 then go to long_break
  if (current_count == 4) {
    current_state = long_Break;
  }
}

void short_Mode(void) {
  pomodoro_Count();

  // Red Led is turned on, the rest of the LED lights are turned off
  digitalWrite(green_first, LOW);
  digitalWrite(yellow_secound, LOW);
  digitalWrite(red_third, HIGH);
  delay(1000);

  //Buzzer sounds when 5 minutes of study is up
  tone(buzzer, 300, 400);
    delay(500);
  digitalWrite(buzzer, LOW);
  delay(300000);

  //buzzer sounds when 5 minutes is up and red_led is turned off
   tone(buzzer, 300, 400);
    delay(500);
  digitalWrite(buzzer, LOW);
  digitalWrite(red_third, LOW);

  //if current count is less than 3 then the current state goes to study mode
  if (current_count <= 3) {
    current_state = studying;
  }

  if (current_count == 4) {
    current_state = long_Break;

  }
}

//longer break
void long_Mode(void) {
  pomodoro_Count();

  digitalWrite(green_first, LOW);
  digitalWrite(yellow_secound, LOW);
  digitalWrite(red_third, HIGH);
  // digitalWrite(longBreakLED, HIGH);
  tone(buzzer, 300, 400);
    delay(500);
  digitalWrite(buzzer, LOW);
 delay(1800000);    
   tone(buzzer, 300, 400);
    delay(500);
    digitalWrite(red_third, LOW);
  digitalWrite(buzzer, LOW);

  //reset count to 0 and go to working mode after longer break
  digitalWrite(BUTTON_PIN, HIGH);
  current_count = 0;
  current_state = studying;

}

//function represents number of pomodoros
void pomodoro_Count(void) {
  if (current_count == 0) {


    digitalWrite(pom1LED, LOW);
    digitalWrite(pom2LED, LOW);
    digitalWrite(pom3LED, LOW);
    digitalWrite(pom4LED, LOW);

  }
  if (current_count == 1) {
    digitalWrite(pom1LED, HIGH);
    digitalWrite(pom2LED, LOW);
    digitalWrite(pom3LED, LOW);
    digitalWrite(pom4LED, LOW);

  }
  if (current_count == 2) {
    digitalWrite(pom1LED, HIGH);
    digitalWrite(pom2LED, HIGH);
    digitalWrite(pom3LED, LOW);
    digitalWrite(pom4LED, LOW);
  }
  if (current_count == 3) {
    digitalWrite(pom1LED, HIGH);
    digitalWrite(pom2LED, HIGH);
    digitalWrite(pom3LED, HIGH);
    digitalWrite(pom4LED, LOW);
  }
  if (current_count == 4) {
    digitalWrite(pom1LED, HIGH);
    digitalWrite(pom2LED, HIGH);
    digitalWrite(pom3LED, HIGH);
    digitalWrite(pom4LED, HIGH);
  }

}

//distance sensor function
void motion()
{ digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; 
  float voltage = distance;
  Serial.println(distance);
  if (Serial.available()) {
    commands = Serial.readStringUntil('\n');
    commands.trim();
  }

  if (commands.equals("black")) {

    Serial.print(distance);

  }
  else if (commands.equals("white")) {


    Serial.print(distance);

  }
  else if (commands.equals("silver")) {


    Serial.print(distance);

  }

}

//photoresistor led function
void light() {
  int reading = analogRead(sensorPin);


  Serial.println(reading);

  if (Serial.available()) {
    command = Serial.readStringUntil('\n');
    command.trim();

  }

  if (command.equals("blue")) {
    digitalWrite(blueLed, HIGH);
    digitalWrite(yellowLed, LOW);
    digitalWrite(redLed, LOW);
    digitalWrite(orangeLed, LOW);
    digitalWrite(greenLed, LOW);

  }


  else if (command.equals("red")) {
    digitalWrite(blueLed, LOW);
    digitalWrite(yellowLed, LOW);
    digitalWrite(redLed, HIGH);
    digitalWrite(orangeLed, LOW);
    digitalWrite(greenLed, LOW);

  }

  else if (command.equals("yellow")) {
    digitalWrite(blueLed, LOW);
    digitalWrite(yellowLed, HIGH);
    digitalWrite(redLed, LOW);
    digitalWrite(orangeLed, LOW);
    digitalWrite(greenLed, LOW);

  }

  else if (command.equals("orange")) {
    digitalWrite(blueLed, LOW);
    digitalWrite(yellowLed, LOW);
    digitalWrite(redLed, LOW);
    digitalWrite(orangeLed, HIGH);
    digitalWrite(greenLed, LOW);

  }

  else if (command.equals("green")) {
    digitalWrite(blueLed, LOW);
    digitalWrite(yellowLed, LOW);
    digitalWrite(redLed, LOW);
    digitalWrite(orangeLed, LOW);
    digitalWrite(greenLed, HIGH);

  }

}

//function to output the data of the distance sensor and the photoresistor for the green led light
void sensorloop()

{
  int i = 1;
  while (i <= 120) // the number of 10 sec in 20 minutes is 120. This will be called with the green led of pomodro
  {
    light();
    motion();
    delay(10000); //10000
    i = i + 1;
  }

}

//function to output the data of the distance sensor and the photoresistor for the yellow led light
void sensorloop2()

{
  int j = 1;
  while (j <= 30) //// the number of 10 sec in 5 minutes is 30. This will be called with the yellow led of pomodro
  {
    light();
    motion();
    delay(10000); //10000
    j = j + 1;
  }

}
