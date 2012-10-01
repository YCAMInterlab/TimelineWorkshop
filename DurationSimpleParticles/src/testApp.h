/**
 * ofxTimeline - Duration - Particles workshop example
 *
 * Rhizomatiks Skills -- James George
 *
 * ofxTimeline supported by YCAM InterLab
 */

#pragma once

#include "ofMain.h"
#include "ofxDuration.h"

#define PORT 12345
#include "SimpleParticleGenerator.h"
#include "SimpleForceNoise.h"
#include "SimpleForceGravity.h"
#include "SimpleForceSwirl.h"

class testApp : public ofBaseApp {
	public:

	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	ofxDuration duration;

	void trackUpdated(ofxDurationEventArgs& args);
	void setupSimpleParticleSystem();
	void updateSimpleParticleSystem();
	
	int maxParticles;
	vector<SimpleParticleGenerator> generators;
	SimpleForceNoise noiseForce;
	SimpleForceGravity gravityForce;
	SimpelForceSwirl swirlForce;
	ofVboMesh mesh;
	float pointSize;
	int port;
	int totalParticles;
	ofTrueTypeFont commandFont;
	//to show all commands on screen
	vector<string> commands;
	
	bool showDebug;
};
