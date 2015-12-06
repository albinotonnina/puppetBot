
// Features:
// - Supports directly telling a servo to ease to a position over a duration
// - Supports playing of previously-defined "move lists"
// - User-specified easing functions (defaults to easeInOutCubic),see Easing lib
// - User-specified "servo arrived" function for async callback when move done
// - Supports both integer angle movement and a "microseconds" mode for 
//    fine-grained control with float-ing point angles
// - Works with both new Arduino 1.0 and Arduino 0022.


#ifndef ServoEaser_h
#define ServoEaser_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "Adafruit_PWMServoDriver.h"

// simple struct to encapsulate a servo move 
typedef struct _servoMove {
    int pos;   // position of servo in degrees
    int dur;   // duration in milliseconds to get to and stay at that position
} ServoMove;


// define "EasingFunc" callback function
// you can make your own of these to use
// t: current time, b: beginning value, c: change in value, d: duration
// t and d can be in frames or seconds/milliseconds
//
typedef float (*EasingFunc)(float t, float b, float c, float d); 

// define "ArrivedFunc" to be called when servo arrives at position
// arguments provided are: currPos of servo & movesIndex of move list (if appl)
typedef void (*ArrivedFunc)(int currPos, int movesIndex);


class ServoEaser 
{
private:
    Adafruit_PWMServoDriver servo;      // what servo we're operating on
    int pinNumber;

    int frameMillis;  // minimum update time between servo moves
    float startPos;   // where servo started its tween
    float currPos;    // current servo position, best of our knowledge

    float changePos;  // from servoMove list

    int durMillis;    // from servoMove list
    int tick;         // count of easing moves within move duration 
    int tickCount;    // number of frames between start & end pos
    unsigned long lastMillis; // time time we did something

    ServoMove* moves; // list of user-supplied servo moves
    int movesIndex;   // where in the moves list we are
    int movesCount;   // number of moves in the moves list
    int movesReps;    // number of repeats, 0==forever

    EasingFunc easingFunc; // func that describes tween motion
    ArrivedFunc arrivedFunc; // func to call when servo arrives at dest
    
    boolean running;  // is servo easer running?
    boolean arrived;  // has servo arrived at its destination
    boolean flipped;  // is servo mounted upside down so 0-180 -> 180->0?

    void getNextPos();

    // duplicate VarSpeedServo min/max micros functionality
    int8_t min;   // minimum is this value times 4 added to MIN_PULSE_WIDTH    
    int8_t max;   // maximum is this value times 4 added to MAX_PULSE_WIDTH   

public:
    
    // set up a servoeaser to use a particular servo
    //void begin(VarSpeedServo s, int frameTime, int startPos);
    void begin(Adafruit_PWMServoDriver s, int pin, int frameTime); //, int startPos);
    void begin(Adafruit_PWMServoDriver s, int pin, int frameTime, ServoMove* moves, int movesCount);

    void reset();
    
    // tell a servo to play a list of servo moves
    // movesCount is number of moves in the list
    // movesReps is number of times to repeat
    void play( ServoMove moves[], int movesCount);
    void play( ServoMove moves[], int movesCount, int movesReps);
    void play( ServoMove moves[], int movesCount, int movesReps, int movesIndex);

    // for manual movement of the servo (non moves list)
    void easeTo( int pos, int durMillis );

    // get current position in degrees
    float getCurrPos();
    
    // call this periodically in loop()
    void update();

    // you can set your own easing function
    void setEasingFunc( EasingFunc );
    // can optionally set a function to call when servo arrives at dest
    void setArrivedFunc( ArrivedFunc func );

    // has servo arrived at its commaned move point?
    boolean hasArrived();
    // is the servo running (start/stop flag)
    boolean isRunning();

    void start();
    void stop();

    void setFlipped( boolean t );
    boolean isFlipped();

};



#endif
