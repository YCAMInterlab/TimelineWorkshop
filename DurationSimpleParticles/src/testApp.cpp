/**
 * ofxTimeline - Duration - Particles workshop example
 *
 * Rhizomatiks Skills -- James George
 *
 * ofxTimeline supported by YCAM InterLab
 */

#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetFrameRate(60);
	ofEnableSmoothing();
	ofBackground(ofColor(255*.05));
	ofEnableAlphaBlending();
	
	pointSize = .5;
	showDebug = true;
	
	//Smooth point sizes
	glEnable(GL_POINT_SMOOTH); // makes circular points
	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE_ARB);	// allows per-point size
	
	duration.setup(PORT);
	//ofxDuration is an OSC receiver, with special functions to listen for Duration specific messages
	//optionally set up a font for debugging
	duration.setupFont("GUI/NewMedia Fett.ttf", 12);
	ofAddListener(duration.events.trackUpdated, this, &testApp::trackUpdated);
	commandFont.loadFont("GUI/NewMedia Fett.ttf", 8);
	
	pointSize = 2;
	//setup one generator and a force
	setupSimpleParticleSystem();
	commands.push_back("/generator/clear");
	
	commands.push_back("/generator/birthrate");
	commands.push_back("/generator/lifespan");
	commands.push_back("/generator/lifespanVariance");
	commands.push_back("/generator/spread");
	commands.push_back("/generator/color");
	commands.push_back("/noise/amplitude");
	commands.push_back("/noise/birthrate");
	commands.push_back("/noise/density");
	commands.push_back("/noise/speed");
	commands.push_back("/gravity/amplitude");
	commands.push_back("/pointsize");
}

//--------------------------------------------------------------
void testApp::setupSimpleParticleSystem(){
	
	//create generators
	for(int i = 0; i < 200; i++){
		SimpleParticleGenerator generator;
		generator.addForce(&noiseForce);
		generator.addForce(&gravityForce);
		generator.addForce(&swirlForce);
		generator.position = ofVec3f(ofRandomWidth(), ofRandomHeight(), 0);
		generators.push_back(generator);
	}
	//add the noise force to the generator
	
	//init our mesh
	maxParticles = 10000;
    for(int i = 0; i < maxParticles; i++){
    	mesh.addVertex(ofVec3f(0,0,0));
        mesh.addColor(ofFloatColor(1.0,1.0,1.0,1.0));
//        mesh.addTexCoord(ofVec2f(0.0,0.0));
    }
}

//--------------------------------------------------------------
//Or wait to receive messages, sent only when the track changed
void testApp::trackUpdated(ofxDurationEventArgs& args){
	//ofLogVerbose("Duration Event") << "track type " << args.track->type << " updated with name " << args.track->name << " and value " << args.track->value << endl;
	string trackName = args.track->name;
	if(trackName == "/generator/clear"){
		for(int i = 0; i < generators.size(); i++){
			generators[i].particles.clear();
		}
	}
	if(trackName == "/generator/birthrate"){
		for(int i = 0; i < generators.size(); i++){
			generators[i].birthRate = args.track->value;
		}
	}
	//How long do the particles live on average
	else if(trackName == "/generator/lifespan"){
		for(int i = 0; i < generators.size(); i++){
			generators[i].birthRate = args.track->value;
		}
	}
	//Lifespan can vary this much from the average
	else if(trackName == "/generator/lifespanVariance"){
		for(int i = 0; i < generators.size(); i++){
			generators[i].birthRate = args.track->value;
		}
	}
	//how much to spread out from the source of the generator
	else if(trackName == "/generator/spread"){
		for(int i = 0; i < generators.size(); i++){
			generators[i].spread = args.track->value;
		}
	}
	else if(trackName == "/generator/color"){
		ofFloatColor floatColor = ofFloatColor(args.track->color);
		for(int i = 0; i < generators.size(); i++){
			generators[i].color = floatColor;
		}
	}
	//how much force from noise
	else if(trackName == "/noise/amplitude"){
		noiseForce.amplitude = args.track->value;
	}
	//density property of the noise field
	else if(trackName == "/noise/density"){
		noiseForce.density = args.track->value;
	}
	else if(trackName == "/noise/speed"){
		noiseForce.speed = args.track->value;
	}
	else if(trackName == "/pointsize"){
		pointSize = MAX(args.track->value, 1);
	}
	else if(trackName == "/gravity/amplitude"){
		gravityForce.amplitude = args.track->value;
	}
	else if(trackName == "/swirl/amplitude"){
		swirlForce.amplitude = args.track->value;
	}
	else if(trackName == "/swirl/x"){
		swirlForce.center.x = args.track->value;
	}
	else if(trackName == "/swirl/y"){
		swirlForce.center.y = args.track->value;
	}
	
}

//--------------------------------------------------------------
void testApp::update(){
	
	//the ofxDuration receiver is automatically updated.
	//You can iterate through the tracks every frame like this:
	vector<string>& allTracks = duration.getTracks();
	for(int i = 0; i < allTracks.size(); i++){
		ofxDurationTrack track = duration.getTrack(allTracks[i]);
		//do something with the track!
	}
	
	updateSimpleParticleSystem();
}

//--------------------------------------------------------------
void testApp::updateSimpleParticleSystem(){
	
	noiseForce.update();
	
	totalParticles = 0;
	for(int i = 0; i < generators.size(); i++){
		totalParticles += generators[i].particles.size();
	}
	
	int particlesPerGenerator = (maxParticles-totalParticles)/generators.size();
	for(int i = 0; i < generators.size(); i++){
		//make sure the generators know how many particles are left
		generators[i].remainingParticles = particlesPerGenerator; //maxParticles - totalParticles - 1;
		generators[i].update();
	}
	
	//Copy the particles into the mesh
	vector<ofVec3f>& meshVertices = mesh.getVertices();
    vector<ofFloatColor>& meshColors = mesh.getColors();
    int meshIndex = 0;
	for(int i = 0; i < generators.size(); i++){
		for(int v = 0; v < generators[i].particles.size(); v++){
			meshVertices[meshIndex] = generators[i].particles[v].position;
			float color = generators[i].particles[v].energy / generators[i].particles[v].initialEnergy;
			generators[i].particles[v].color.a = color;
			meshColors[meshIndex] = generators[i].particles[v].color;
			meshIndex++;
			if(meshIndex == meshVertices.size()){
				//our particle system shouldn't let this happen but just in case
				 ofLogError("exceeded max particles");
				return;
			}
		}
	}
	
	//black out all other particles
	memset(&(meshColors[meshIndex].r), 0, sizeof(ofFloatColor)*(meshColors.size()-meshIndex));
}

//--------------------------------------------------------------
void testApp::draw(){
	if(showDebug){
		duration.draw(0,0, 250, ofGetHeight());
		ofPushStyle();
		ofSetColor(128,128,128);
		for(int i = 0; i < commands.size(); i++){
			commandFont.drawString(commands[i], 260, (i+1)*(commandFont.getLineHeight()+4));
		}
		ofPopStyle();
		commandFont.drawString("particles: " + ofToString(totalParticles), 260, (commands.size()+1)*(commandFont.getLineHeight()+4));
	}
	
	glPointSize(pointSize);
	mesh.drawVertices();
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	showDebug = !showDebug;
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
