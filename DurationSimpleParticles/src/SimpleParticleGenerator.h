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
#include "SimpleForce.h"

class SimpleParticleGenerator {
  public:
	
    SimpleParticleGenerator(){
        birthRate = .1;
        lifespan = 200;
		spread = 30;
        numToBear = ofRandom(0,1);
		lifespanVariance = 40;
        //setup forces
        freeze = false;
		color = ofFloatColor(1.0,1.0,1.0,1.0);
    }
    
    void update(){
		
        if(!freeze){
            numToBear += birthRate;
            while(numToBear > 1.0 && remainingParticles > 0){
				particles.push_back(SimpleParticle());
                SimpleParticle& p = particles[particles.size()-1];

                p.energy = p.initialEnergy = lifespan + ofRandom(-lifespanVariance/2, lifespanVariance/2);
                p.origin = p.position = position + ofVec3f(0,1,0).getRotated(ofRandom(0,360),ofVec3f(0,0,1)) * ofRandom(0,spread);
                p.velocity = direction;
				p.color = color;
				
                numToBear--;
                remainingParticles--;
            }
            
            //sacrifice the rest
            numToBear -= int(numToBear);
        
            for(int i = 0; i < forces.size(); i++){
                forces[i]->applyForce(particles);
            }
        
            for(int i = particles.size()-1; i >= 0; i--){
                particles[i].update();
                if(particles[i].energy < 0){
                    particles.erase(particles.begin() + i); 
                }
            }
        }
    }
    
    void drawTextDebug(float x, float y){
        ofDrawBitmapString("Num Particles " + ofToString(particles.size()), x, y);
    }
    
    void drawDebug(){
        ofPushStyle();
        ofNoFill();
        ofSetColor(255,0,0);
        ofSphere(position, 20);
        ofLine(position, position+direction*100);
        ofPopStyle();
    }
    
    vector<SimpleParticle> particles;
    vector<SimpleForce*> forces;
    
    void addForce(SimpleForce* force){
        forces.push_back(force);
    }
    
    int remainingParticles;
    float birthRate;
    float lifespan;
    float lifespanVariance;
	float spread;
    ofVec3f position;
    ofVec3f direction;
    ofVec2f texcoord;
    ofFloatColor color;
    bool freeze;
    
  protected:
    float numToBear;
};

