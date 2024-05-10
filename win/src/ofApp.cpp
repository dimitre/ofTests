#include "ofApp.h"


void ofApp::setup(){
//	float p = PI;
	float p = glm::pi<float>();
	cout << p << endl;
	
//	rel.setup();
//	cairo.setup();
	ofSetFrameRate(0);
	ofSetVerticalSync(false);
	grad.setup();
}

void ofApp::update(){
}

void ofApp::draw(){	
//	cairo.begin();
//	ofClear(0, 255);
//	rel.drawRelogio();
//	rel.draw2();
//	
//	cairo.end();
//	
//	ofTranslate(300, 300);
//	cairo.draw();
	
	grad.draw();
	ofDrawBitmapString(ofToString(ofGetFrameRate()), 30, 30);
}

void ofApp::keyPressed(int key){
	grad.reload();
}
