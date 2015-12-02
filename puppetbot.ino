#include "Wire.h"
#include "Adafruit_PWMServoDriver.h"
#include "Joint.h"
#include "Puppet.h"
#include "Beats.h"
#include "IRremote.h"

Adafruit_PWMServoDriver pwmDriver = Adafruit_PWMServoDriver();

float currentTime;

//init Joints
Joint F1;
Joint F2;
Joint R1;
Joint R2;
Joint HEAD;

//init beatCounters
Beats puppetBeats;
Beats botBeats;

//init puppet
Puppet puppet;

//init IR
IRrecv irrecv(11);
decode_results results;


void initPuppet() {
    pwmDriver.begin();
    pwmDriver.setPWMFreq(60);

    F1.init(pwmDriver, 0, 0, 1, 0);
    F2.init(pwmDriver, 1, 0, -1, 0);
    R1.init(pwmDriver, 2, 0, -1, 0);
    R2.init(pwmDriver, 3, 0, 1, 0);
    HEAD.init(pwmDriver, 5, 1, 1, 90);

    puppet.init(puppetBeats, F1, F2, R1, R2, HEAD);
    puppet.start();
}

void updateJoints() {
    puppet.update();

    F1.update(currentTime);
    F2.update(currentTime);
    R1.update(currentTime);
    R2.update(currentTime);
    HEAD.update(currentTime);
}

void updateBeats() {

    botBeats.update();

    if (botBeats.triggerEighth()) {
        decodeIrCommands();
    }
}

void decodeIrCommands(){
    if (irrecv.decode(&results)) {
//        Serial.println(results.value, HEX);

        switch (results.value) {
            case 0xFF6897: //1
                puppet.flyFor(5);
                break;
            case 0xFF9867: //2
                puppet.walkFor(5);
                break;
            case 0xFFB04F: //3
                puppet.waveFor(5);
                break;
        }

        irrecv.resume(); // receive the next value
    }
}

////////////////////////

void setup() {
    Serial.begin(9600);

    initPuppet();

    botBeats.start(); // Start timer
    irrecv.enableIRIn(); // Start the receiver
}


void loop() {
    currentTime = (float) millis() / 1000.0;
    updateBeats();
    updateJoints();
}