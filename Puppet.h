#ifndef Puppet_H
#define Puppet_H

#include <Arduino.h>
#include "Joint.h"
#include "Metronome.h"

class Puppet {
public:


    Metronome *beats;
    Joint *F1;
    Joint *F2;
    Joint *R1;
    Joint *R2;

    void init(
            Metronome &_metronome,
            Joint &_F1,
            Joint &_F2,
            Joint &_R1,
            Joint &_R2
    );

    void start();

    void update();

    void flyFor(int cycles);

    void walkFor(int cycles);

private:

    bool toggleWalk;
    bool toggleFly;
    int walkCycles;
    int flyCycle;

    bool isFlying;
    bool isWalking;

    void fly();

    void walk();

    void riseLeftWing();

    void riseRightWing();

    void dropLeftWing();

    void dropRightWing();

    void riseLeftLeg();

    void riseRightLeg();

    void dropLeftLeg();

    void dropRightLeg();
};

#endif
