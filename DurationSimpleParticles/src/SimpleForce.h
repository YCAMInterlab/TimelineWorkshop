/**
 * ofxTimeline - Duration - Particles workshop example
 *
 * Rhizomatiks Skills -- James George
 *
 * ofxTimeline supported by YCAM InterLab
 */

#pragma once

#include "ofMain.h"
#include "SimpleParticle.h"

class SimpleForce {
  public:    
    virtual void update() = 0;
    virtual void applyForce(vector<SimpleParticle>& particles) = 0;    
};

