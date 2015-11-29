#include "Puppet.h"

void Puppet::init(Metronome &_metronome, Joint &_F1, Joint &_F2, Joint &_R1, Joint &_R2) {
    beats = &_metronome;
    F1 = &_F1;
    F2 = &_F2;
    R1 = &_R1;
    R2 = &_R2;

    isFlying = false;
    isWalking = false;
}

void Puppet::start() {
    toggleWalk = false;
    toggleFly = false;
    beats->start(120);
}

void Puppet::update() {

    beats->update();

    if (beats->triggerBeat()) {

        if (walkCycles > 0) {
            walk();
            walkCycles--;
        }

        if (flyCycle > 0) {
            fly();
            flyCycle--;
        }

    }

    if (beats->triggerBar()) { }
    if (beats->triggerSection()) { }

}

void Puppet::walkFor(int cycles) {

    if (walkCycles == 0) {
        walkCycles = cycles * 2;
    }

}

void Puppet::walk() {
    beats->setBPM(180.0);

    toggleWalk = !toggleWalk;

    if (toggleWalk) {
        riseRightLeg();
        dropLeftLeg();
    } else {
        riseLeftLeg();
        dropRightLeg();
    }
}

void Puppet::flyFor(int cycles) {

    if (flyCycle == 0) {
        flyCycle = cycles * 2;
    }

}

void Puppet::fly() {
    beats->setBPM(160.0);

    toggleFly = !toggleFly;

    if (toggleFly) {
        riseLeftWing();
        riseRightWing();
    } else {
        dropLeftWing();
        dropRightWing();
    }
};


void Puppet::riseLeftWing() {
    R1->tween(45, 0.2, Joint::EaseIn);
}

void Puppet::riseRightWing() {
    R2->tween(45, 0.2, Joint::EaseIn);
}

void Puppet::dropLeftWing() {
    R1->tween(0, 0.2, Joint::EaseOut);
}

void Puppet::dropRightWing() {
    R2->tween(0, 0.2, Joint::EaseOut);
}

void Puppet::riseLeftLeg() {
    F1->tween(45, 0.2, Joint::EaseIn);
}

void Puppet::riseRightLeg() {
    F2->tween(45, 0.2, Joint::EaseIn);
}

void Puppet::dropLeftLeg() {
    F1->tween(0, 0.2, Joint::EaseOut);
}

void Puppet::dropRightLeg() {
    F2->tween(0, 0.2, Joint::EaseOut);
}



