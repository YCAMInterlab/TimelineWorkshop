/**
 * ofxTimeline - Duration - Particles workshop example
 *
 * Rhizomatiks Skills -- James George
 *
 * ofxTimeline supported by YCAM InterLab
 */

#pragma once

#include "ofMain.h"

class SimpleParticle {
  public:
    SimpleParticle(){
        energy = 0;
        position = ofVec3f(0,0,0);
        velocity = ofVec3f(0,0,0);
        force = ofVec3f(0,0,0);
    }
    
    void update(){
        velocity += force;
        position += velocity;
        force = ofVec3f(0,0,0);
        energy--;
        energyPercent = energy/initialEnergy;
    }
    
    ofVec3f connectorPoint;
    float connectorEnergy;
    float energy;
    float initialEnergy;
    float energyPercent;
	ofFloatColor color;
    ofVec3f origin;
    ofVec3f position;
    ofVec3f velocity;
    ofVec3f force;
    ofVec2f texcoord;
//    ofVec3f direction;
    
};

