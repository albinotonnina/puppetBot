#include "Puppet.h"

void Puppet::init(Metronome &_metronome, Joint &_F1, Joint &_F2, Joint &_R1, Joint &_R2) {
    beats = &_metronome;
    F1 = &_F1;
    F2 = &_F2;
    R1 = &_R1;
    R2 = &_R2;

    isFlying = false;
    isWalking = false;
    isWaving = false;
}

void Puppet::start() {
    toggleWalk = false;
    toggleFly = false;
    toggleWave = false;
    beats->start(120);
}

void Puppet::update() {

    beats->update();

    if (beats->triggerBeat()) {

        if (walkCycles > 0) {
            walk();
            walkCycles--;
        }

        if (flyCycles > 0) {
            fly();
            flyCycles--;
        }

        if (waveCycles > 0) {
            wave();
            waveCycles--;
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

void Puppet::flyFor(int cycles) {

    if (flyCycles == 0) {
        flyCycles = cycles * 2;
    }

}

void Puppet::waveFor(int cycles) {

    if (waveCycles == 0) {
        waveCycles = cycles * 2;
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


void Puppet::wave() {
    beats->setBPM(200.0);

    toggleWave = !toggleWave;

    if (toggleWave) {
        riseLeftWing(30);
    } else {
        dropLeftWing();
    }
};


void Puppet::riseLeftWing(int degrees) {
    R1->tween(degrees, 0.2, Joint::EaseIn);
}

void Puppet::riseRightWing(int degrees) {
    R2->tween(degrees, 0.2, Joint::EaseIn);
}

void Puppet::dropLeftWing(int degrees) {
    R1->tween(degrees, 0.2, Joint::EaseOut);
}

void Puppet::dropRightWing(int degrees) {
    R2->tween(degrees, 0.2, Joint::EaseOut);
}

void Puppet::riseLeftLeg(int degrees) {
    F1->tween(degrees, 0.2, Joint::EaseIn);
}

void Puppet::riseRightLeg(int degrees) {
    F2->tween(degrees, 0.2, Joint::EaseIn);
}

void Puppet::dropLeftLeg(int degrees) {
    F1->tween(degrees, 0.2, Joint::EaseOut);
}

void Puppet::dropRightLeg(int degrees) {
    F2->tween(degrees, 0.2, Joint::EaseOut);
}



