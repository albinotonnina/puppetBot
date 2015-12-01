#include "Beats.h"

void Beats::start(float _bpm) {
    setBPM(_bpm);
    lastTime = (float) millis() / 1000;
    beatsTime = 0;
    triggerBar();
}

void Beats::setBPM(float _bpm) {
    bpm = _bpm;
    bps = bpm / 60.0;
    spb = 1.0 / bps;
}

void Beats::update() {
    float time = (float) millis() / 1000;
    float diff = (time - lastTime) * bps;
    lastTime = time;

    beatsTime += diff;

    beatsPassed = floor(beatsTime);
    barsPassed = floor(beatsTime / 4.0);
    sectionsPassed = floor(beatsTime / 16.0);
}

bool Beats::triggerBeat() {
    if (beatsPassed > beatsTriggered) {
        beatsTriggered = beatsPassed;
        return true;
    }
    return false;
}

bool Beats::triggerBar() {
    if (barsPassed > barsTriggered or beatsTime == 0) {
        barsTriggered = barsPassed;
        return true;
    }
    return false;
}

bool Beats::triggerSection() {
    if (sectionsPassed > sectionsTriggered) {
        sectionsTriggered = sectionsPassed;
        return true;
    }
    return false;
}