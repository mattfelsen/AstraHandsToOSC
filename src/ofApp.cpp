#include "ofApp.h"

void ofApp::setup(){
	ofSetVerticalSync(true);
	ofBackground(ofColor::black);

	bool bError = false;

	if (!json.open("settings.json")) {
		ofLogError() << "No config file found!";
		bError = true;
	}

	if (!json["address"].isString()) {
		ofLogError() << "'address' should be a string!";
		bError = true;
	}

	if (!json["host"].isString()) {
		ofLogError() << "'host' should be a string!";
		bError = true;
	}

	if (!json["port"].isInt() || !json["port"].asInt()) {
		ofLogError() << "'int' should be a non-zero int!";
		bError = true;
	}

	if (bError) {
		ofExit();
		return;
	}

	address = json["address"].asString();
	host = json["host"].asString();
	port = json["port"].asInt();
	osc.setup(json["host"].asString(), json["port"].asInt());

	astra.setup();
	astra.initDepthStream();
	astra.initHandStream();
}

void ofApp::update(){
	astra.update();
	if (!astra.isFrameNew()) return;

	if (astra.getHandsWorld().size()) {
		for (auto& hand : astra.getHandsWorld()) {
			auto& id = hand.first;
			auto& pos = hand.second;

			ofxOscMessage m;
			m.setAddress(address);
			m.addInt32Arg(id);
			m.addFloatArg(pos.x);
			m.addFloatArg(pos.y);
			m.addFloatArg(pos.z);
			osc.sendMessage(m, false);
		}
	}
}

void ofApp::draw(){
	ofSetColor(ofColor::white);
	astra.drawDepth(0, 0);

	for (auto& hand : astra.getHandsWorld()) {
		auto& id = hand.first;
		auto& posWorld = hand.second;
		auto& posDepth = astra.getHandsDepth()[id];

		// Draw in 2D with depth coordinates so circle appears in the correct
		// place on the depth image
		// However, display the world coordinates in 3D which is actually what
		// gets broadcasted out to other clients
		ofSetColor(ofColor::white);
		ofDrawCircle(posDepth, 10);

		stringstream ss;
		ss << "id: " << id << endl;
		ss << "pos: " << posWorld;
		ofDrawBitmapStringHighlight(ss.str(), posDepth.x, posDepth.y - 30);
	}

	stringstream ss;
	ss << "fps: " << ofGetFrameRate() << endl;
	ss << "host: " << host << endl;
	ss << "port: " << ofToString(port) << endl;
	ss << "address: " << address << endl;
	ss << "press 'r' to reload settings file" << endl << endl;

	ss << "tracked hands: " << astra.getHandsDepth().size() << endl;
	ss << "try moving your hands in a circle until they are recognized";

	ofSetColor(ofColor::white);
	ofDrawBitmapStringHighlight(ss.str(), 20, 500);
}

void ofApp::keyPressed(int key){
	if (key == 'r') {
		setup();
	}
}
