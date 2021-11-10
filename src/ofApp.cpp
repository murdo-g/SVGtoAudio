#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	int bufferSize		= 512;
	sampleRate 			= 96000;

	ofSoundStreamSettings settings;

	auto devices = soundStream.getMatchingDevices("default");
	if(!devices.empty()){
		settings.setOutDevice(devices[0]);
	}

	lAudio.assign(bufferSize, 0.0);
	rAudio.assign(bufferSize, 0.0);

	settings.setOutListener(this);
	settings.sampleRate = sampleRate;
	settings.numOutputChannels = 2;
	settings.numInputChannels = 0;
	settings.bufferSize = bufferSize;
	soundStream.setup(settings);

	svg.load("flower.svg");
	std::cout << svg.getWidth() << "\n";
	std::cout << svg.getHeight() << "\n";
	std::cout << svg.getNumPath() << "\n";


	for(int i =0; i < svg.getNumPath(); i++) {
		ofMesh mesh = svg.getPathAt(i).getTessellation();
		std::cout << mesh.getNumVertices() << "\n";
		for(int j=0; j<mesh.getNumVertices(); j++) {
			auto vertex = mesh.getVertex(j);
			std::cout << "X: " << vertex.x << ", Y: " << vertex.y << "\n";
			xVerts.push_back(vertex.x/700.f);
			yVerts.push_back(vertex.y/700.f);
		}
	}

	std::cout << xVerts.size() << "\n";

	tableCounter = 0;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	for(int i =0; i < svg.getNumPath(); i++) {
		ofMesh mesh = svg.getPathAt(i).getTessellation();
		mesh.draw();
	}
}

void ofApp::audioOut(ofSoundBuffer & buffer){

	// ---------------------- noise --------------
	for (size_t i = 0; i < buffer.getNumFrames(); i++){
		if(xVerts.size() != 0) {
			lAudio[i] = buffer[i*buffer.getNumChannels()    ] = xVerts[tableCounter];
			rAudio[i] = buffer[i*buffer.getNumChannels() + 1] = yVerts[tableCounter];
		}
		else {
			lAudio[i] = buffer[i*buffer.getNumChannels()    ] = ofRandom(0, 1);
			rAudio[i] = buffer[i*buffer.getNumChannels() + 1] = ofRandom(0, 1);
		}
		tableCounter ++;
		if(tableCounter > xVerts.size()) tableCounter = 0;
	}


}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
