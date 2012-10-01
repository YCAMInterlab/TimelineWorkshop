/**
 * ofxTimeline - Duration - Particles workshop example
 *
 * Rhizomatiks Skills -- James George
 *
 * ofxTimeline supported by YCAM InterLab
 */

#pragma once

#include "SimpleForce.h"
class SimpelForceSwirl : public SimpleForce {
  public:
    
    float amplitude;
    ofVec3f center;
    
    SimpelForceSwirl() {
		amplitude = 0;
        center = ofVec3f(ofGetWidth()/2, ofGetHeight()/2);
    }
    
    void update(){}
	
    void applyForce(vector<SimpleParticle>& particles){
        for(int i = 0; i < particles.size(); i++){
			
            ofVec3f& pos = particles[i].position;
			particles[i].force += (pos-center).getNormalized().getRotated(90, ofVec3f(0,0,1))*amplitude;
        }
    }
};

