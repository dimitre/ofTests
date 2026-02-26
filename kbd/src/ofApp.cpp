#include "ofApp.h"


void ofApp::setup() {
}

void ofApp::draw(){
	ofSetColor(255);
	ofDrawBitmapString(saida, 20, 30);
}

void ofApp::update(){}

void ofApp::keyPressed(int key){
	saida += char(key);
}
