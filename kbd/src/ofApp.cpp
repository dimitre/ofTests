#include "ofApp.h"


void ofApp::setup() {
}

void ofApp::draw(){
	ofSetColor(255);
	ofDrawBitmapString(saida, 20, 30);
	ofDrawLine(0, 0, mouseX, mouseY);
}

void ofApp::update(){}

void ofApp::keyPressed(int key){
	saida += char(key);
}
