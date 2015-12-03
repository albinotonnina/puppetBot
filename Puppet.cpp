#include "Puppet.h"

Beats *beats;
ServoEaser F1;
ServoEaser F2;
ServoEaser R1;
ServoEaser R2;
ServoEaser HEAD;

Adafruit_PWMServoDriver pwmDriver = Adafruit_PWMServoDriver();

// configurable list of servo moves
int walkMovesCount = 2;
ServoMove _walkMovesLeft[] = {{45, 100}, {0,  500}};
ServoMove _walkMovesRight[] = {{0, 100}, {45,  500}};

int headMoveCount = 2;
ServoMove _headMove[] = {{90, 800}, {0,  800}};

ServoMove *headMove = _headMove;
ServoMove *walkMovesLeft = _walkMovesLeft;
ServoMove *walkMovesRight = _walkMovesRight;

int servoFrameMillis = 20;  // minimum time between servo updates

void Puppet::init(Beats &_beats) {
    pwmDriver.begin();
    pwmDriver.setPWMFreq(60);

    F1.begin(pwmDriver, 0, servoFrameMillis);
    F2.begin(pwmDriver, 1, servoFrameMillis);
    F2.setFlipped(true);
    R1.begin(pwmDriver, 2, servoFrameMillis);
    R1.setFlipped(true);
    R2.begin(pwmDriver, 3, servoFrameMillis);

    HEAD.begin(pwmDriver, 4, servoFrameMillis);

    beats = &_beats;
}

void Puppet::start() {
    beats->start();
}

void Puppet::update() {

    F1.update();
    F2.update();
    R1.update();
    R2.update();
    HEAD.update();

}


void Puppet::resetPosition() {
    F1.stop();
    F2.stop();
    R1.stop();
    R2.stop();
}

void resetF2(int currPos, int movesIndex){
    F2.easeTo(0,400);
}

void Puppet::walkFor(int cycles) {
    F1.play(walkMovesLeft, walkMovesCount, cycles);
    F2.play(walkMovesRight, walkMovesCount, cycles);

    F1.setArrivedFunc(resetF2);
}

void Puppet::flyFor(int cycles) {
    R1.play(walkMovesLeft, walkMovesCount, cycles);
    R2.play(walkMovesLeft, walkMovesCount, cycles);
}

void Puppet::waveFor(int cycles) {
    R2.play(walkMovesLeft, walkMovesCount, cycles);
}

void Puppet::nodFor(int cycles) {
    HEAD.play(headMove, headMoveCount, cycles);
}


