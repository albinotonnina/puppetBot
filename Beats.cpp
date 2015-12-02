#include "Beats.h"

void Beats::start(float _bpm) {
    setBPM(_bpm);
    lastTime = (float) millis() / 1000;
    beatsTime = 0;
    triggerBeat();
}

void Beats::setBPM(float _bpm) {
    bpm = _bpm;
    bps = (bpm / 60.0) * 4;
    spb = 1.0 / bps;
}

void Beats::update() {
    float time = (float) millis() / 1000;
    float diff = (time - lastTime) * bps;
    lastTime = time;

    beatsTime += diff;

    eighthsPassed = floor(beatsTime);
    beatsPassed = floor(beatsTime / 4.0);
}

bool Beats::triggerEighth() {
    if (eighthsPassed > beatsTriggered) {
        beatsTriggered = eighthsPassed;
        return true;
    }
    return false;
}

bool Beats::triggerBeat() {
    if (beatsPassed > barsTriggered or beatsTime == 0) {
        barsTriggered = beatsPassed;
        return true;
    }
    return false;
}
