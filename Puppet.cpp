#include "Puppet.h"

void Puppet::init(Beats &_beats, Joint &_F1, Joint &_F2, Joint &_R1, Joint &_R2, Joint &_HEAD) {
    beats = &_beats;
    F1 = &_F1;
    F2 = &_F2;
    R1 = &_R1;
    R2 = &_R2;
    HEAD = &_HEAD;

}

void Puppet::start() {
    toggleWalk = false;
    toggleFly = false;
    toggleWave = false;
    toggleNoddle = false;
    beats->start();
}

void Puppet::update() {

    beats->update();


    if (beats->triggerBeat()) {

        if (walkBeats > 0) {
            walk();
            walkBeats--;
        }

        if (flyBeats > 0) {
            fly();
            flyBeats--;
        }

        if (waveBeats > 0) {
            wave();
            waveBeats--;
        }

        if (nodBeats > 0) {
            nod();
            nodBeats--;
        } else {
            //stopNod();
        }

    }


}

void Puppet::walkFor(int cycles) {

    if (walkBeats == 0) {
        walkBeats = cycles * 2;
    }

}

void Puppet::flyFor(int cycles) {

    if (flyBeats == 0) {
        flyBeats = cycles * 2;
    }

}

void Puppet::waveFor(int cycles) {

    if (waveBeats == 0) {
        waveBeats = cycles * 2;
    }

}

void Puppet::nodFor(int cycles) {

    if (nodBeats == 0) {
        nodBeats = cycles * 2;
    }

}

void Puppet::walk() {

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

    toggleWave = !toggleWave;

    if (toggleWave) {
        riseLeftWing(30);
    } else {
        dropLeftWing();
    }
};

void Puppet::nod() {

    toggleNoddle = !toggleNoddle;

    if (toggleNoddle) {
        nodUp(6);
    } else {
        nodDown(6);
    }
};




void Puppet::riseLeftWing(int degrees) {
    R1->tween(degrees, 0.4, Joint::EaseIn);
}

void Puppet::riseRightWing(int degrees) {
    R2->tween(degrees, 0.4, Joint::EaseIn);
}

void Puppet::dropLeftWing(int degrees) {
    R1->tween(degrees, 0.4, Joint::EaseOut);
}

void Puppet::dropRightWing(int degrees) {
    R2->tween(degrees, 0.4, Joint::EaseOut);
}

void Puppet::riseLeftLeg(int degrees) {
    F1->tween(degrees, 0.4, Joint::EaseIn);
}

void Puppet::riseRightLeg(int degrees) {
    F2->tween(degrees, 0.4, Joint::EaseIn);
}

void Puppet::dropLeftLeg(int degrees) {
    F1->tween(degrees, 0.4, Joint::EaseOut);
}

void Puppet::dropRightLeg(int degrees) {
    F2->tween(degrees, 0.4, Joint::EaseOut);
}

void Puppet::nodUp(int speed) {
    Serial.print("nod up.. ");
    HEAD->rotate(80, 0.2);
}

void Puppet::nodDown(int speed) {
    Serial.print("nod down.. ");
    HEAD->rotate(90, 0.2);
}

void Puppet::stopNod() {
    Serial.println("stop nodding");
    HEAD->stop();
};


