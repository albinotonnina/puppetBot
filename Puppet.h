#ifndef Puppet_H
#define Puppet_H

#include <Arduino.h>
#include "Joint.h"

class Puppet {
  public:
	float direction;bool orientation;

    Joint *F1;
    Joint *F2;
    Joint *R1;
    Joint *R2;

    void init(
      Joint& _F1,
      Joint& _F2,
      Joint& _R1,
      Joint& _R2
    );

    void start();
    void update();
    void onBeatStart(float duration);
    void onBarStart(float duration);

    void walk(float duration);
    void fly(float duration);

};
#endif
