#include "Puppet.h"

void Puppet::init(Metronome &_metronome, Joint &_F1, Joint &_F2, Joint &_R1, Joint &_R2) {
    beats = &_metronome;
    F1 = &_F1;
    F2 = &_F2;
    R1 = &_R1;
    R2 = &_R2;
}

void Puppet::start() {
    orientation = true;
    direction = 1; // 1, -1
}

void Puppet::update() {

    beats->update();

    if (beats->triggerSection()) {

    }

    if (beats->triggerBeat()) {
        walk(beats->spb);
    }

    if (beats->triggerBar()) {
        fly(beats->spb);
    }


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

void Puppet::fly(float duration) {
    beats->setBPM(80.0);

    direction *= -1;
    float Joint1angle = 45 * direction;

    R1->tween(Joint1angle, duration, Joint::EaseOut);
    R2->tween(Joint1angle, duration, Joint::EaseOut);
}

