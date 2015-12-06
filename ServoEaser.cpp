

#include "ServoEaser.h"

#include <math.h>

#define MIN_PULSE_WIDTH 160;
#define MAX_PULSE_WIDTH 590;
#define DEBUG 0

// FIXME: this debug setup sucks

#if (DEBUG > 0)
#define debug_update() { \
        Serial.print("update: currPos:"); Serial.print(currPos);        \
        Serial.print(" startPos:"); Serial.print(startPos);             \
        Serial.print(" changePos:"); Serial.print(changePos);           \
        Serial.print(" tick:"); Serial.print(tick);                     \
        Serial.print(" tickCount:"); Serial.print(tickCount);                     \
        Serial.print(" arrived:");Serial.println(((arrived)?"true":"false"));}
#define debug_getnextpos() { \
        Serial.print("getNextPos:"); Serial.print(movesIndex); \
        Serial.print(" changePos:"); Serial.print(changePos);     \
        Serial.print(" moves[i].pos:"); Serial.print(moves[movesIndex].pos); \
        Serial.print(" durMillis:"); Serial.print(durMillis); \
        Serial.print(" tickCount:"); Serial.println(tickCount); }
#define debug_reset() { \
        Serial.print("reset: currPos:"); Serial.print(currPos); \
        Serial.print(" changePos:"); Serial.print(changePos); \
        Serial.print(" durMillis:"); Serial.print(durMillis); \
        Serial.print(" movesIndex:"); Serial.print(movesIndex); \
        Serial.print(" tickCount:"); Serial.println(tickCount); }
#define debug_done_reps() { \
        Serial.print("DONE REPS:"); }
#else
#define debug_update() {}
#define debug_getnextpos() {}
#define debug_reset() {}
#define debug_done_reps() {}
#endif

// default easing function
// this is from Easing::easeInOutCubic()
// t: current time, b: beginning value, c: change in value, d: duration
// t and d can be in frames or seconds/milliseconds
inline float ServoEaser_easeInOutCubic(float t, float b, float c, float d) {
    if ((t /= d / 2) < 1) return c / 2 * t * t * t + b;
    return c / 2 * ((t -= 2) * t * t + 2) + b;
}

// set up an easer with a servo and a moves list
void ServoEaser::begin(Adafruit_PWMServoDriver s, int pin, int frameTime, ServoMove *mlist, int mcount) {
    begin(s, pin, frameTime);
    play(mlist, mcount);
}

// set up an easer with just a servo and a starting position
void ServoEaser::begin(Adafruit_PWMServoDriver s, int pin, int frameTime) {
    servo = s;
    frameMillis = frameTime;

    pinNumber = pin;

    flipped = false;
    arrived = true;

    easingFunc = ServoEaser_easeInOutCubic;
    arrivedFunc = NULL;

    movesIndex = 0;

    reset();
}

// reset easer to initial conditions, does not nuke easingFunc or arrivedFunc
void ServoEaser::reset() {
    currPos = getCurrPos();
    startPos = currPos;  // get everyone in sync
    changePos = 0;       // might be overwritten below

    if (movesCount > 0) {
        changePos = moves[movesIndex].pos - startPos;
        durMillis = moves[movesIndex].dur;
    }

    tickCount = durMillis / frameMillis;
    tick = 0;

    debug_reset();
}

//
void ServoEaser::play(ServoMove *mlist, int mcount) {
    play(mlist, mcount, 0, 0);
}

//
void ServoEaser::play(ServoMove *mlist, int mcount, int mreps) {
    play(mlist, mcount, mreps, 0);
}

void ServoEaser::play(ServoMove *mlist, int mcount, int mreps, int mindex) {
    moves = mlist;
    movesCount = (mcount > 0) ? mcount : 0;
    movesReps = (mreps > 0) ? mreps : 0;
    movesIndex = (mindex > 0) ? mindex : 0;
    //movesIndex = (mindex>0) ? ((mindex<mcount) ? mindex : mcount) : 0; 

    running = true;
    arrived = false;

    reset();
}

// manual, non-moves list, control of easer position
void ServoEaser::easeTo(int pos, int dur) {
    movesCount = 0;  // no longer doing moves list
    startPos = currPos;
    changePos = pos - startPos;
    durMillis = dur;
    tickCount = durMillis / frameMillis;
    tick = 0;
    arrived = false;
    running = true;
}

// used internally to select next servo position
void ServoEaser::getNextPos() {


    if (movesCount == 0) { // not in a moves list
        arrived = true;
        stop();
      //  if (arrivedFunc != NULL) { arrivedFunc(currPos, movesIndex); }
        return;
    }

    movesIndex++;
    if (movesIndex == movesCount) {
        movesIndex = 0;  // loop
        movesReps--;
        if (movesReps == 0) { // we are done
            arrived = true;

            if (arrivedFunc != NULL) { arrivedFunc(currPos, movesIndex); }
            debug_done_reps();

            stop();
        } else if (movesReps == -1) { // we are infinite
            movesReps = 0;
        }
    }
    startPos = currPos; // current position becomes new start position

    changePos = moves[movesIndex].pos - startPos;
    durMillis = moves[movesIndex].dur;

    tickCount = durMillis / frameMillis;
    tick = 0;
    arrived = false;

    debug_getnextpos();
}

// call this regularly in loop()
void ServoEaser::update() {
    if (((millis() - lastMillis) < frameMillis) || !running) {  // time yet?
        return;
    }
    lastMillis = millis();

    currPos = easingFunc(tick, startPos, changePos, tickCount);

    debug_update();

    if (!arrived) tick++;
    if (tick == tickCount) { // time for new position
        getNextPos();
    }
    float p = (flipped) ? 180.0 - currPos : currPos;

    uint16_t pulseLen = map(p, 0, 180, 160, 590);
    servo.setPWM(pinNumber, 0, pulseLen);

}

// from VarSpeedServo.cpp
#define SERVO_MIN() (MIN_PULSE_WIDTH - this->min * 4)  // min value in uS
#define SERVO_MAX() (MAX_PULSE_WIDTH - this->max * 4)  // max value in uS

#define in_min 0
#define in_max 180
#define out_min SERVO_MIN()
#define out_max SERVO_MAX()

void ServoEaser::setFlipped(boolean t) {
    flipped = t;
}

boolean ServoEaser::isFlipped() {
    return flipped;
}

//
void ServoEaser::start() {
    running = true;
}

//
void ServoEaser::stop() {
    running = false;
}

//
boolean ServoEaser::isRunning() {
    return running;
}

//
boolean ServoEaser::hasArrived() {
    return arrived;
}

float ServoEaser::getCurrPos() {
    return currPos;
}

// 
void ServoEaser::setEasingFunc(EasingFunc func) {
    easingFunc = func;
}

//
void ServoEaser::setArrivedFunc(ArrivedFunc func) {
    arrivedFunc = func;
}

//
/*
void ServoEaser::setMovesList( ServoMove* mlist, int mcount )
{
    moves = mlist;
    movesCount = mcount;

    reset();
}
*/

 

