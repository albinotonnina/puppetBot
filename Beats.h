#ifndef Beats_H
#define Beats_H

#include <Arduino.h>

class Beats {
public:
    float bpm;
    float bps;
    float spb;

    float beatsTime;
    float lastTime;

    int beatsTriggered;
    int barsTriggered;

    int eighthsPassed;
    int beatsPassed;

    void start(float bpm = 60);

    void setBPM(float bpm);

    void update();

    bool triggerEighth();

    bool triggerBeat();
};

#endif