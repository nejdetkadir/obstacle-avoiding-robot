//variables
#define front_dist_echo 7
#define front_dist_trig 6
#define right_dist_echo 5
#define right_dist_trig 4
#define left_dist_echo 2
#define left_dist_trig 3
#define in1 9
#define in2 8
#define e1 12
#define in3 10
#define in4 11
#define e2 13
#define error_lamp 53

void setup() {
  //outputs
  pinMode(front_dist_trig, OUTPUT);
  pinMode(right_dist_trig, OUTPUT);
  pinMode(left_dist_trig, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(e1, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(e2, OUTPUT);
  pinMode(error_lamp, OUTPUT);  

  //inputs
  pinMode(front_dist_echo, INPUT);
  pinMode(right_dist_echo, INPUT);
  pinMode(left_dist_echo, INPUT);
}

void loop() {
  calculate_main();
}

void calculate_main() {
  show_error(false);
  int front = calculateDistance(front_dist_echo, front_dist_trig);
  int left = calculateDistance(left_dist_echo, left_dist_trig);
  int right = calculateDistance(right_dist_echo, right_dist_trig);
  if (front >= 25) {
    go();    
  } else if (front < 20 && right < 20 && left < 20) {
    show_error(true);
    stop_motor();    
  } else {
    stop_motor();
    go_back();
    right_or_left();
  }
}

int calculateDistance(int echo, int trigger) {
  int timee, distance;
  digitalWrite(trigger, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigger, LOW);
  timee = pulseIn(echo, HIGH);
  distance = (timee/2) / 29.1;  
  return distance;  
}

void turn_right() { 
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(e2, 0);      
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(e1, 150);  
  delay(150);
}

void turn_left() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(e1, 0);    
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(e2, 150);   
  delay(150);
}

void go() {
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(e1, 125); 
  analogWrite(e2, 125); 
  delay(150);
}

void go_back() {
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(e1, 130); 
  analogWrite(e2, 130); 
  delay(150);
}

void stop_motor() {
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(e1, 0); 
  analogWrite(e2, 0);
  delay(250);
}

void show_error(boolean error_status) {
  if (error_status) {
    digitalWrite(error_lamp, HIGH);
  } else {
    digitalWrite(error_lamp, LOW);
  }  
}

void right_or_left() {
  int left = calculateDistance(left_dist_echo, left_dist_trig);
  int right = calculateDistance(right_dist_echo, right_dist_trig);
  if (right > left) {
    turn_right();
    calculate_main();
  } else {
    turn_left();
    calculate_main();
  } 
}
