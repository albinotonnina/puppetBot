#include "Puppet.h"

Beats *beats;
ServoEaser F1;
ServoEaser F2;
ServoEaser R1;
ServoEaser R2;
ServoEaser HEAD;

ServoMove _f1Moves[6];
ServoMove _f2Moves[6];
ServoMove _r1Moves[6];
ServoMove _r2Moves[6];
ServoMove _headMoves[6];

Adafruit_PWMServoDriver pwmDriver = Adafruit_PWMServoDriver();

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

void resetF1(int currPos, int movesIndex) {
    F1.easeTo(0, 400);
}

void resetF2(int currPos, int movesIndex) {
    F2.easeTo(0, 400);
}

void Puppet::walkFor(int cycles) {
    _f1Moves[0] = {45, 300};
    _f1Moves[1] = {0, 300};

    _f2Moves[0] = {0, 300};
    _f2Moves[1] = {45, 300};

    F1.play(_f1Moves, 2, cycles);
    F2.play(_f2Moves, 2, cycles);

    F1.setArrivedFunc(resetF2);
    F2.setArrivedFunc(resetF1);
}

void Puppet::flyFor(int cycles) {
    _f1Moves[0] = {60, 700};
    _f1Moves[1] = {60, 700};

    _f2Moves[0] = {60, 700};
    _f2Moves[1] = {60, 700};

    _r1Moves[0] = {60, 700};
    _r1Moves[1] = {0, 800};

    _r2Moves[0] = {60, 700};
    _r2Moves[1] = {0, 800};

    _headMoves[0] = {60, 700};
    _headMoves[1] = {0, 700};

    F1.play(_f1Moves, 2, cycles);
    F2.play(_f2Moves, 2, cycles);
    R1.play(_r1Moves, 2, cycles);
    R2.play(_r2Moves, 2, cycles);
    HEAD.play(_headMoves, 2, cycles);

    R1.setArrivedFunc(resetF1);
    R2.setArrivedFunc(resetF2);
}

void Puppet::waveFor(int cycles) {
    _r1Moves[0] = {0, 300};
    _r1Moves[1] = {45, 300};

    R1.play(_r1Moves, 2, cycles);
}

void Puppet::nodFor(int cycles) {
    _headMoves[0] = {70, 500};
    _headMoves[1] = {0, 500};

    HEAD.play(_headMoves, 2, cycles);
}

void Puppet::tapFor(int cycles) {
    _f1Moves[0] = {45, 800};
    _f1Moves[1] = {0, 800};

    F1.play(_f1Moves, 2, cycles);
}