#include "ofApp.h"


void ofApp::setup(){
	img.load("1.png");
	testSetup();
}

void ofApp::update(){
}

void ofApp::draw(){	
	img.draw(0, 0);
	testDraw();
}

void ofApp::keyPressed(int key){
}
