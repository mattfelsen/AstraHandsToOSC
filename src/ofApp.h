#pragma once

#include "ofMain.h"
#include "ofxJSON.h"
#include "ofxOrbbecAstra.h"
#include "ofxOsc.h"

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);

private:
	ofxOrbbecAstra astra;
	ofxOscSender osc;
	ofxJSON json;

	std::string address;
	std::string host;
	int port;
};
