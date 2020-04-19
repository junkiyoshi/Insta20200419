#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(0);
	ofSetColor(255);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.5);

	int radius = 200;

	auto seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));
	vector<glm::vec3> vertices;
	for (int i = 0; i < 100; i++) {

		auto location = glm::vec3(
			ofMap(ofNoise(seed.x, (ofGetFrameNum() + i) * 0.008), 0, 1, -1, 1),
			ofMap(ofNoise(seed.y, (ofGetFrameNum() + i) * 0.008), 0, 1, -1, 1),
			ofMap(ofNoise(seed.z, (ofGetFrameNum() + i) * 0.008), 0, 1, -1, 1)
		);
		location = glm::normalize(location) * radius;
		vertices.push_back(location);
	}

	this->drawVertices(vertices);

	for (int i = 0; i < 18; i++) {

		ofRotateX(60);
		ofRotateY(60);
		ofRotateZ(60);
		this->drawVertices(vertices);
	}
		
	this->cam.end();
}

//--------------------------------------------------------------
void ofApp::drawVertices(vector<glm::vec3> vertices) {

	ofNoFill();
	ofBeginShape();
	ofVertices(vertices);
	ofEndShape();

	ofFill();
	ofDrawSphere(vertices.front(), 3);
	ofDrawSphere(vertices.back(), 3);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}