#include <ArduinoUnit.h>

test(setSpeedTest) {
  Robot robot;
  robot.setSpeed(100);
  assertEqual(100, robot.getSpeed());
}

test(forwardTest) {
  Robot robot;
  robot.forward();
  assertEqual(FORWARDING, robot.getState());
  // Add assertions for motor behavior
}

test(backwardTest) {
  Robot robot;
  robot.backward();
  assertEqual(BACKWARDING, robot.getState());
  // Add assertions for motor behavior
}

test(stopTest) {
  Robot robot;
  robot.stop();
  assertEqual(WAITING, robot.getState());
  // Add assertions for motor behavior
}

test(spinTest) {
  Robot robot;
  robot.spin();
  assertEqual(SPINNING, robot.getState());
  // Add assertions for motor behavior
}

test(toggleDirectionTest) {
  Robot robot;
  robot.toggleDirection();
  assertEqual(BACKWARDING, robot.getState());
  // Add assertions for motor behavior

  robot.toggleDirection();
  assertEqual(FORWARDING, robot.getState());
  // Add assertions for motor behavior
}

test(nextStateTest) {
  Robot robot;
  robot.nextState();
  assertEqual(SPINNING, robot.getState());
  // Add assertions for motor behavior

  robot.opponentDistance = []() { return 40; };
  robot.nextState();
  assertEqual(FORWARDING, robot.getState());
  // Add assertions for motor behavior

  robot.opponentDistance = []() { return 60; };
  robot.nextState();
  assertEqual(SPINNING, robot.getState());
  // Add assertions for motor behavior
}

unittest_main()
