#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetWindowTitle("openFrameworks");
	ofSetFrameRate(25);

	ofBackground(39);
	ofSetColor(239);
	ofEnableDepthTest();

	this->noise_step = ofRandom(1000);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	if (ofGetFrameNum() % 50 < 40){

		this->noise_step += ofMap(ofGetFrameNum() % 50, 0, 40, 0.02, 0.0005);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	auto noise_seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));
	for (int size = 30; size <= 330; size += 30) {

		ofPushMatrix();

		auto x_value = ofNoise(noise_seed.x, size * 0.00025 + this->noise_step);
		auto y_value = ofNoise(noise_seed.y, size * 0.00025 + this->noise_step);
		auto z_value = ofNoise(noise_seed.z, size * 0.00025 + this->noise_step);

		auto x_deg = x_value < 0.35 ? ofMap(x_value, 0, 0.35, -360, 0) : x_value > 0.75 ? ofMap(x_value, 0.75, 1, 0, 360) : 0;
		auto y_deg = y_value < 0.35 ? ofMap(y_value, 0, 0.35, -360, 0) : y_value > 0.75 ? ofMap(y_value, 0.75, 1, 0, 360) : 0;
		auto z_deg = z_value < 0.35 ? ofMap(z_value, 0, 0.35, -360, 0) : z_value > 0.75 ? ofMap(z_value, 0.75, 1, 0, 360) : 0;

		ofRotateZ(z_deg);
		ofRotateY(y_deg);
		ofRotateX(x_deg);

		ofNoFill();
		ofDrawBox(size);

		ofPopMatrix();
	}

	/*
	int start = 150;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}