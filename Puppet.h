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
    Joint *HEAD;


    void init(
            Metronome &_metronome,
            Joint &_F1,
            Joint &_F2,
            Joint &_R1,
            Joint &_R2,
            Joint &_HEAD
    );

    void start();

    void update();

    void flyFor(int cycles);

    void walkFor(int cycles);

    void waveFor(int cycles);

    void nodFor(int cycles);

    void stopNod();

private:

    bool toggleWalk;
    bool toggleFly;
    bool toggleWave;
    bool toggleNoddle;
    int walkBeats;
    int flyBeats;
    int waveBeats;
    int nodBeats;

    bool isFlying;
    bool isWalking;
    bool isWaving;

    void fly();

    void walk();

    void wave();

    void nod();


    void riseLeftWing(int degrees = 45);

    void riseRightWing(int degrees = 45);

    void dropLeftWing(int degrees = 0);

    void dropRightWing(int degrees = 0);

    void riseLeftLeg(int degrees = 45);

    void riseRightLeg(int degrees = 45);

    void dropLeftLeg(int degrees = 0);

    void dropRightLeg(int degrees = 0);

    void nodUp(int speed = 0);

    void nodDown(int speed = 0);
};

#endif
