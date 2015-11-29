#include "Puppet.h"

void Puppet::init(Joint &_F1, Joint &_F2, Joint &_R1, Joint &_R2) {
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
//Serial.print(".");
}

void Puppet::onBeatStart(float duration) {

    direction *= -1;
    float Joint1angle = 45 * direction;
    float Joint2angle = 90 * direction;

    if (orientation) {
        Serial.println("orientation 1");
        F1->tween(Joint1angle, duration, Joint::EaseOut);
        F2->tween(Joint2angle, duration, Joint::EaseIn);
//		Joint3->tween(Joint1angle, duration, Joint::EaseIn);
//		Joint4->tween(Joint2angle, duration, Joint::EaseOut);
    } else {
        Serial.println("orientation 2");
        F1->tween(Joint1angle, duration, Joint::EaseIn);
        F2->tween(Joint2angle, duration, Joint::EaseOut);
//		Joint3->tween(Joint1angle, duration, Joint::EaseOut);
//		Joint4->tween(Joint2angle, duration, Joint::EaseIn);
    }

}

void Puppet::onBarStart(float duration) {
//	orientation = !orientation;
}

void Puppet::walk(float duration) {
    float Joint1angle = 45 * direction;
    direction *= -1;
    float Joint1angle2 = 45 * direction;

    F1->tween(Joint1angle, duration, Joint::EaseOut);
    F2->tween(Joint1angle2, duration, Joint::EaseOut);
}

void Puppet::fly(float duration) {
    direction *= -1;
    float Joint1angle = 45 * direction;

//    R1->tween(Joint1angle, duration, Joint::EaseOut);
//    R2->tween(Joint1angle, duration, Joint::EaseOut);
}

