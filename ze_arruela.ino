const int LIMIAR_OPPONENT_DISTANCE = 35;

class DCMotor {
  int spd = 255, pin1, pin2;

 public:
  DCMotor() {}

  DCMotor(int in1, int in2) : pin1(in1), pin2(in2) {
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
  }

  void setSpeed(int in1) {
    spd = in1;
    // Serial.print("Motor speed set to: ");
    // Serial.println(spd);
  }

  void forward() {
    analogWrite(pin1, spd);
    digitalWrite(pin2, LOW);
    // Serial.println("Motor moving forward");
  }

  void backward() {
    digitalWrite(pin1, LOW);
    analogWrite(pin2, spd);
    // Serial.println("Motor moving backward");
  }

  void stop() {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
    // Serial.println("Motor stopped");
  }
};

class UltrassonicSensor {
 private:
  int triggerPin;
  int echoPin;

 public:
  UltrassonicSensor() {}

  UltrassonicSensor(int triggerPin, int echoPin) : triggerPin(triggerPin), echoPin(echoPin) {
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

class LineFollowerSensor {
 private:
  int pin;

 public:
  LineFollowerSensor() {}

  LineFollowerSensor(int pin) : pin(pin) {
    pinMode(pin, INPUT);
  }

  int identified() {
    return !digitalRead(pin);;
  }
};


enum State { WAITING, FORWARDING, BACKWARDING, SPINNING, STOPPED };

class Robot {
 private:
  DCMotor motor1;
  DCMotor motor2;
  UltrassonicSensor ultrassonic;
  LineFollowerSensor irFrontRight;
  LineFollowerSensor irFrontLeft;
  LineFollowerSensor irBack;
  int speed;
  State state;

 public:
  Robot() {}

  Robot(DCMotor motor1, DCMotor motor2, UltrassonicSensor ultrassonic, LineFollowerSensor irFrontRight, LineFollowerSensor irFrontLeft, LineFollowerSensor irBack) : motor1(motor1), motor2(motor2), ultrassonic(ultrassonic), irFrontRight(irFrontRight), irFrontLeft(irFrontLeft), irBack(irBack) {
    state = WAITING;
    motor1.setSpeed(speed);
    motor2.setSpeed(speed);
  }

  void spin() {
    stop();
    state = SPINNING;
    motor1.forward();
    motor2.backward();
    // Serial.println("Robot spinning");
  }

  void spinReverse() {
    stop();
    state = SPINNING;
    motor1.backward();
    motor2.forward();
    // Serial.println("Robot spinning reverse");
  }

  void spinWait() {
    delay(6000);
    // Serial.println("Robot waiting");
    spin();
  }

  void toggleDirection() {
    if (getState() == FORWARDING) {
      stop();
      delay(500);
      backward();
    } else if (getState() == BACKWARDING) {
      stop();
      delay(500);
      forward();
    }
  }

  void forward() {
    state = FORWARDING;
    // setSpeed(speed);
    motor1.forward();
    motor2.forward();
    // Serial.println("Robot moving forward");
  }

  void backward() {
    state = BACKWARDING;
    motor1.backward();
    motor2.backward();
    // Serial.println("Robot moving backward");
  }

  void stop() {
    state = STOPPED;
    motor1.stop();
    motor2.stop();
    // Serial.println("Robot stopped");
  }

  void setSpeed(int speedValue) {
    speed = speedValue;
    motor1.setSpeed(speed);
    motor2.setSpeed(speed);
  }

  long opponentDistance() {
    long d = ultrassonic.distance();
    Serial.println(d);
    return d;
  }

  int frontBorderIdentified() {
      return irFrontRight.identified() || irFrontLeft.identified();
  }

  int backBorderIdentified() {
      return irBack.identified();
  }

  void toggleDirectionAndSpin() {
    toggleDirection();
    stop();
    delay(500);
    spin();
  }
   
  int borderDetected() {
    return frontBorderIdentified() || backBorderIdentified();
  }

  void nextState() {
    if (getState() == SPINNING) {
      long distance = opponentDistance();
      if (distance != 0 && distance <= LIMIAR_OPPONENT_DISTANCE) {
        stop();
        delay(200);
        forward();
      } else if (borderDetected()) {
        stop();
        delay(200);
        spinReverse();
        delay(200);
      }
    } else if(getState() == FORWARDING && frontBorderIdentified()) {
        stop();
        delay(200);
        backward();
        delay(300);
        stop();
        delay(100);
        spin();
    } else if(getState() == BACKWARDING && backBorderIdentified()) {
        stop();
        delay(200);
        forward();
        delay(300);
        stop();
        delay(100);
        spin();
    } else {
      spin();
    }
  }
  
  State getState() {
    return state;
  }
};

Robot robot;

void setup() {
  Serial.begin(9600);
  DCMotor motor1(6, 5);
  DCMotor motor2(10, 9);
  UltrassonicSensor ultrassonic(12, 13);
  LineFollowerSensor irFrontRight(11);
  LineFollowerSensor irFrontLeft(4);
  LineFollowerSensor irBack(8);
  robot = Robot(motor1, motor2, ultrassonic, irFrontRight, irFrontLeft, irBack);
  robot.setSpeed(200);
  robot.spinWait();
}

void loop() { 
  robot.nextState();
 }
