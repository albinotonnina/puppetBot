#include "Joint.h"

const int SERVOMIN = 160;
const int SERVOMAX = 590;

void Joint::init(Adafruit_PWMServoDriver& _pwmDriver, int _pin, float _offset, float _direction, float _initialAngle) {
  pwmDriver = &_pwmDriver;

  pin = _pin;
  offset = _offset;
  direction = _direction;
  initialAngle = _initialAngle;
  currentTime = 0.1;

  currentAngle = initialAngle;
  move(currentAngle);
}

void Joint::rotate(float speed, bool direction) {

  int myabsAngle = map(speed, 0, 10, 0, 10);

  float absAngle = 90 - offset - myabsAngle;

  if(direction){
    absAngle = 90 + myabsAngle;
  }

  uint16_t pulseLen = map(absAngle, 0, 90, SERVOMIN, SERVOMAX);

  pwmDriver->setPWM(pin, 0, pulseLen);
}

void Joint::tween(float angle, float duration) {
  tween(angle, duration, EaseInOut);
}

void Joint::tween(float angle, float duration, Easing easing) {
  tweenStartTime  = currentTime;
  tweenEndTime    = currentTime + duration;
  tweenStartAngle = currentAngle;
  tweenEndAngle   = angle;
  tweenEasing     = easing;
}

float Joint::tweenCompletion() {
  float completion = (currentTime - tweenStartTime) / (tweenEndTime - tweenStartTime);
  if (completion < 0) { return 0; }
  if (completion > 1) { return 1; }

  switch(tweenEasing) {
    case EaseInOut:
      completion = 0.5 - cos(completion * PI) * 0.5;
      break;

    case EaseOut:
      completion = 1.0 - cos(completion * PI * 0.5);
      break;

    case EaseIn:
      completion = sin(completion * PI * 0.5);
      break;

    case EaseInOutLoop:
      completion = 0.5 - cos(completion * PI * 2) * 0.5;
      break;
  }

  return completion;
}

void Joint::update() {
  currentTime = (float) millis() / 1000;
  float diff = tweenEndAngle - tweenStartAngle;
  if (abs(diff) > 0.0) {
    move(tweenStartAngle + diff * tweenCompletion());
  }
}

void Joint::move(float angle) {
  currentAngle = angle;
  
  float absAngle = 90 + offset + currentAngle * direction;
  uint16_t pulseLen = map(absAngle, 0, 180, SERVOMIN, SERVOMAX);
  pwmDriver->setPWM(pin, 0, pulseLen);
}

void Joint::stop() {
  pwmDriver->setPWM(pin, 0, 4096);
}