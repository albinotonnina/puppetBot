#ifndef Puppet_H
#define Puppet_H

#include <Arduino.h>
#include "ServoEaser.h"
#include "Adafruit_PWMServoDriver.h"
#include "Beats.h"

class Puppet {
public:

    void init(
            Beats &_beats
    );

    void start();

    void update();

    void flyFor(int cycles);

    void walkFor(int cycles);

    void waveFor(int cycles);

    void nodFor(int cycles);

    void tapFor(int cycles);

    void resetPosition();

private:


};

#endif
