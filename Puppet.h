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

    void waveFor(int cycles);

private:

    bool toggleWalk;
    bool toggleFly;
    bool toggleWave;
    int walkCycles;
    int flyCycles;
    int waveCycles;

    bool isFlying;
    bool isWalking;
    bool isWaving;

    void fly();

    void walk();

    void wave();

    void riseLeftWing(int degrees = 45);

    void riseRightWing(int degrees = 45);

    void dropLeftWing(int degrees = 0);

    void dropRightWing(int degrees = 0);

    void riseLeftLeg(int degrees = 45);

    void riseRightLeg(int degrees = 45);

    void dropLeftLeg(int degrees = 0);

    void dropRightLeg(int degrees = 0);
};

#endif
