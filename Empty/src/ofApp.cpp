#include "ofApp.h"


void ofApp::setup(){
	img.load("1.png");
	testSetup();
}

void ofApp::update(){
}

void ofApp::draw(){	
	img.draw();
	testDraw();
}

void ofApp::keyPressed(int key){
}
