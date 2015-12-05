#include "Wire.h"
#include "Puppet.h"
#include "Beats.h"
#include "IRremote.h"


//init beatCounters
Beats puppetBeats;
Beats botBeats;

//init puppet
Puppet puppet;

//init IR
IRrecv irrecv(11);
decode_results results;


void initPuppet() {

    puppet.init(puppetBeats);
    puppet.start();
}

void updatePuppet() {
    puppet.update();
}

void initBeats(){
    botBeats.start(); // Start timer
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
            case 0xFF30CF: //4
                puppet.nodFor(5);
                break;
            case 0xFF18E7: //5
                puppet.tapFor(5);
                break;
        }

        irrecv.resume(); // receive the next value
    }
}

////////////////////////

void setup() {
    Serial.begin(115200);

    initPuppet();
    initBeats();
    irrecv.enableIRIn(); // Start the receiver

    puppet.resetPosition();
}


void loop() {
    updateBeats();
    updatePuppet();
}