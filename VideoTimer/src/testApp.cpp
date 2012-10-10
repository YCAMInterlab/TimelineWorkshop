/**
 * Rhizomatiks * ofxTimeline * workshop
 *
 * Simple Video Flagger
 */

#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
	
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
    ofEnableSmoothing();
	ofEnableAlphaBlending();
	
	ofxTimeline::removeCocoaMenusFromGlut("VideoTimer");
	
	timeline.setup();
	timeline.setLoopType(OF_LOOP_NORMAL);
	timeline.addVideoTrack("fingers", "fingers.mov");
	steps = timeline.addBangs("steps");
	mousex = timeline.addCurves("mousex", ofRange(0,timeline.getVideoPlayer("fingers")->getWidth()));
	mousey = timeline.addCurves("mousey", ofRange(0,timeline.getVideoPlayer("fingers")->getHeight()));
	
	timeline.addColors("ball");
	timeline.addLFO("slaveControl", ofRange(0,1.0));
	
	
	ofAddListener(timeline.events().bangFired, this, &testApp::bangFired);
	lastFrameReceived = 0;
	
	slaveTimeline.setup();
	slaveTimeline.setDurationInSeconds(2);
	slaveTimeline.addCurves("curves");
}

//--------------------------------------------------------------
void testApp::bangFired(ofxTLBangEventArgs& bang){
	cout << " bang fired at frame " << bang.currentFrame << endl;
	lastFrameReceived = bang.currentFrame;
}

//--------------------------------------------------------------
void testApp::update(){
	slaveTimeline.setOffset(ofVec2f(ofGetWidth()/2, timeline.getBottomLeft().y));
	slaveTimeline.setWidth(ofGetWidth()/2);
	
	float currentLFOValue = timeline.getValue("slaveControl");
	slaveTimeline.setPercentComplete(currentLFOValue);
	
	if(ofGetKeyPressed('r') && timeline.getIsPlaying()){
		float x = ofGetMouseX() - timeline.getBottomLeft().x;
		float y = ofGetMouseY() - timeline.getBottomLeft().y;
		mousex->addKeyframe(x);
		mousey->addKeyframe(y);
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	int backgroundColor = ofMap(timeline.getCurrentFrame()-lastFrameReceived, 0, 20, 255, 40, true);
	ofBackground(backgroundColor);
	
	timeline.draw();
	slaveTimeline.draw();
	timeline.getVideoPlayer("fingers")->draw(timeline.getBottomLeft());
	
	float slaveTimelinePosition = slaveTimeline.getValue("curves");
	ofLine(slaveTimelinePosition*ofGetWidth(), 0,
		   slaveTimelinePosition*ofGetWidth(), ofGetHeight());
	
	ofPushStyle();
	float x = timeline.getValue("mousex");
	float y = timeline.getValue("mousey");
	ofSetColor(timeline.getColor("ball"));
	ofCircle(x, y+timeline.getBottomLeft().y, 10);
	
	ofPopStyle();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key == ' '){
		timeline.togglePlay();
	}
	
	if(key == 's'){
		steps->addKeyframe(0);
	}
	
	if(key == '1'){
		timeline.stop();
		timeline.setInPointAtFrame(30);
		timeline.setOutPointAtFrame(100);
		timeline.setLoopType(OF_LOOP_NORMAL);
		timeline.setCurrentTimeToInPoint();
		timeline.play();
	}
	
	if(key == 'h'){
		timeline.toggleShow();
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
	
