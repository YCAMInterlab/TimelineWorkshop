/**
 * Rhizomatiks * ofxTimeline * workshop
 *
 * Simple Video Flagger
 */

#include "testApp.h"
#define BUTTON_HEIGHT 30

//--------------------------------------------------------------
void testApp::setup(){
	
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
    ofEnableSmoothing();
	ofEnableAlphaBlending();
	
	ofxTimeline::removeCocoaMenusFromGlut("VideoTimer");

	timeline.setup();    
	timeline.setLoopType(OF_LOOP_NORMAL);
	
	video = timeline.addVideoTrack("Video", "fingers.mov");
	flags = timeline.addFlags("flags");
	
	ofAddListener(timeline.events().bangFired, this, &testApp::flagFired);
}

//--------------------------------------------------------------
void testApp::flagFired(ofxTLBangEventArgs& flag){
	
}

//--------------------------------------------------------------
void testApp::update(){
	videoRectangle = ofRectangle(timeline.getBottomLeft(), video->getPlayer()->getWidth(),video->getPlayer()->getHeight());
}

//--------------------------------------------------------------
void testApp::draw(){
	
	ofBackground(.15*255); 

	timeline.draw();
	video->getPlayer()->draw(timeline.getBottomLeft());
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key == ' '){
        timeline.togglePlay();
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
	if(videoRectangle.inside(x,y)){
		flags->addFlag("flag");
	}
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
	
