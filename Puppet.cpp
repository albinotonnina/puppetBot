#include "Puppet.h"

void Puppet::init(Metronome &_metronome, Joint &_F1, Joint &_F2, Joint &_R1, Joint &_R2) {
    bits = &_metronome;
    F1 = &_F1;
    F2 = &_F2;
    R1 = &_R1;
    R2 = &_R2;
}

void Puppet::start() {
    orientation = (random(0, 2) == 0);
    direction = (random(0, 2) == 0 ? 1 : -1);
}

void Puppet::update() {

    bits->update();

    if (bits->triggerSection()) {
//        Serial.println("section");
    }

    if (bits->triggerBeat()) {
//        Serial.print("beat ");
        walk(bits->spb);
    }

    if (bits->triggerBar()) {

    }


}

void Puppet::walk(float duration) {

    bits->setBPM(90.0);

    float Joint1angle = 45 * direction;
    direction *= -1;
    float Joint1angle2 = 45 * direction;

//    F1->tween(Joint1angle, duration, Joint::EaseOut);
//    F2->tween(Joint1angle2, duration, Joint::EaseOut);
}

void Puppet::fly(float duration) {
    direction *= -1;
    float Joint1angle = 45 * direction;

//    R1->tween(Joint1angle, duration, Joint::EaseOut);
//    R2->tween(Joint1angle, duration, Joint::EaseOut);
}

