/**
 * ofxTimeline - Duration - Particles workshop example
 *
 * Rhizomatiks Skills -- James George
 *
 * ofxTimeline supported by YCAM InterLab
 */


#pragma once

#include "SimpleForce.h"

class SimpleForceGravity : public SimpleForce {
  public:
    
    float amplitude;
    
    SimpleForceGravity() {
        amplitude = 0;
    }
    
    void update(){}
    
    void applyForce(vector<SimpleParticle>& particles){
        for(int i = 0; i < particles.size(); i++){
			particles[i].force += ofVec3f(0, amplitude, 0);
        }
    }
};