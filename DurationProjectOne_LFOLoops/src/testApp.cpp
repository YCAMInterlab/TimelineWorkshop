#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	
	duration.setup(12345);
	
	
}

//--------------------------------------------------------------
void testApp::update(){
	
	vector<string> allTracks = duration.getTracks();
	for(int i = 0; i < allTracks.size(); i++){
		ofxDurationTrack track = duration.getTrack(allTracks[i]);
		if(track.name == "/ball1/x"){
			ball1.x = track.value;
		}
		else if(track.name == "/ball1/y"){
			ball1.y = track.value;
		}
		else if(track.name == "/ball2/x"){
			ball2.x = track.value;
		}
		else if(track.name == "/ball2/y"){
			ball2.y = track.value;
		}
		cout << track.name << endl;
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	ofBackground(255);
	ofSetColor(255, 0, 0);
	ofCircle(ball1.x, ball1.y, 10);
	ofSetColor(0, 255, 0);
	ofCircle(ball2.x, ball2.y, 10);
	
	ofSetColor(0, 0, 255);
	ofLine(ball1, ball2);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

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