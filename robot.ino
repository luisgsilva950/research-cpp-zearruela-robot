class DCMotor {
  int spd = 255, pin1, pin2;

 public:
  DCMotor() {}

  DCMotor(int in1, int in2) : pin1(in1), pin2(in2) {
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
  }

  void setSpeed(int in1) { spd = in1; }

  void forward() {
    analogWrite(pin1, spd);
    digitalWrite(pin2, LOW);
  }

  void backward() {
    digitalWrite(pin1, LOW);
    analogWrite(pin2, spd);
  }

  void stop() {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
  }
};

class UltrassonicSensor {
 private:
  int triggerPin;
  int echoPin;

 public:
  UltrassonicSensor() {}

  UltrassonicSensor(int triggerPin, int echoPin)
      : triggerPin(triggerPin), echoPin(echoPin) {
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
  }

  long distance() {
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    long duration = pulseIn(echoPin, HIGH);
    long distance = duration * 0.0343 / 2;
    return distance;
  }
};

enum State { WAITING, FORWARDING, BACKWARDING, SPINNING };

class Robot {
 private:
  DCMotor motor1;
  DCMotor motor2;
  UltrassonicSensor ultrassonic;
  int speed;
  State state;

 public:
  Robot() {}

  Robot(DCMotor motor1, DCMotor motor2, UltrassonicSensor ultrassonic)
      : motor1(motor1), motor2(motor2), ultrassonic(ultrassonic) {
    speed = 255;
    state = WAITING;
    motor1.setSpeed(speed);
    motor2.setSpeed(speed);
  }

  void spin() {
    state = SPINNING;
    motor1.forward();
    motor2.backward();
  }

  void spinWait() {
    delay(10000);
    spin();
  }

  void toggleDirection() {
    if (state == FORWARDING)
      backward();
    else if (state == BACKWARDING)
      forward();
  }

  void forward() {
    state = FORWARDING;
    motor1.forward();
    motor2.forward();
  }

  void backward() {
    state = BACKWARDING;
    motor1.backward();
    motor2.backward();
  }

  void stop() {
    state = WAITING;
    motor1.stop();
    motor2.stop();
  }

  void setSpeed(int speedValue) {
    speed = speedValue;
    motor1.setSpeed(speed);
    motor2.setSpeed(speed);
  }

  long opponentDistance() { return ultrassonic.distance(); }

  void nextState() {
    if (state == WAITING) spinWait();
    if (state == SPINNING && opponentDistance() <= 50) forward();
    if (state == FORWARDING && opponentDistance() > 50) spin();
  }
};

Robot robot;

void setup() {
  DCMotor motor1(5, 6);
  DCMotor motor2(9, 10);
  UltrassonicSensor ultrassonic(2, 4);
  robot = Robot(motor1, motor2, ultrassonic);
}

void loop() { robot.nextState(); }