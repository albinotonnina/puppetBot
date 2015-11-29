#include "Wire.h"
#include "Adafruit_PWMServoDriver.h"
#include "Joint.h"

#include "Puppet.h"
#include "Metronome.h"

Adafruit_PWMServoDriver pwmDriver = Adafruit_PWMServoDriver();

float currentTime;

Joint F1;
Joint F2;
Joint R1;
Joint R2;

Metronome metronome;

Puppet puppet;

int countTemp = 0;

void setup() {
    Serial.begin(9600);

    pwmDriver.begin();
    pwmDriver.setPWMFreq(60);

    F1.init(pwmDriver, 0, 15, -1, 0);
    F2.init(pwmDriver, 1, 15, 1, 0);
    R1.init(pwmDriver, 2, 15, -1, 0);
    R2.init(pwmDriver, 3, 15, 1, 0);

    puppet.init(metronome, F1, F2, R1, R2);
    puppet.start();

    metronome.start(90);
}

void loop() {
    currentTime = (float) millis() / 1000.0;
    updateJoints();
}

void updateJoints() {

    puppet.update();

    F1.update(currentTime);
    F2.update(currentTime);
    R1.update(currentTime);
    R2.update(currentTime);
}
