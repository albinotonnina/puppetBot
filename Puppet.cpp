#include "Puppet.h"

void Puppet::init(Metronome &_metronome, Joint &_F1, Joint &_F2, Joint &_R1, Joint &_R2) {
    beats = &_metronome;
    F1 = &_F1;
    F2 = &_F2;
    R1 = &_R1;
    R2 = &_R2;

    isFlying = false;
}

void Puppet::start() {
    orientation = false;
    direction = 1; // 1, -1

    beats->start(120);
}

void Puppet::update() {

    beats->update();

    if (beats->triggerBeat()) {

        animCycle--;

        if (animCycle >= 0) {

            if (isFlying) { fly(); }

        } else {
            animCycle = 0;
        }


    }

    if (beats->triggerBar()) { }
    if (beats->triggerSection()) { }

}

void Puppet::walk(float duration) {

    beats->setBPM(80.0);

    float angle = 45;

    orientation = !orientation;

    if (orientation) {
        F1->tween(angle, duration, Joint::EaseIn);
        F2->tween(angle * -1, duration, Joint::EaseOut);
    } else {
        F1->tween(angle * -1, duration, Joint::EaseOut);
        F2->tween(angle, duration, Joint::EaseIn);
    }
}

void Puppet::flyCycles(int cycles) {
    isFlying = true;

    if (animCycle == 0) {
        animCycle = cycles * 2;
    }

    F1->move(0);
    F2->move(0);
}

void Puppet::fly() {
    beats->setBPM(160.0);

    orientation = !orientation;

    if (orientation) {
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



