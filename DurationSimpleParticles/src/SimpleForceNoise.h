/**
 * ofxTimeline - Duration - Particles workshop example
 *
 * Rhizomatiks Skills -- James George
 *
 * ofxTimeline supported by YCAM InterLab
 */

#pragma once

#include "SimpleForce.h"
class SimpleForceNoise : public SimpleForce {
  public:
    
    float amplitude;
    float density;
    float speed;
    float currentOffset;
    
    SimpleForceNoise() {
        amplitude = .2;
        density = 10;
        speed = .001;
//        amplitude = 0;
//        density = 0;
//        speed = 0;
        currentOffset = 0;
    }
    
    void update(){
        currentOffset += speed;
    }
    
    void applyForce(vector<SimpleParticle>& particles){
        for(int i = 0; i < particles.size(); i++){
            ofVec3f& pos = particles[i].position;
            particles[i].force +=  ofVec3f(ofSignedNoise(pos.x/density, pos.y/density, pos.z/density, currentOffset)*amplitude,
                                           ofSignedNoise(pos.x/density, pos.y/density, pos.z/density, currentOffset+1000)*amplitude,
                                           ofSignedNoise(pos.x/density, pos.y/density, pos.z/density, currentOffset+2000)*amplitude );
        }
    }
};

