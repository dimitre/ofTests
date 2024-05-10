#include "ofApp.h"

void ofApp::setup(){
	auto exe = ofFilePath::getCurrentExePathFS();
	cout << exe << endl;
	ofSystemAlertDialog ( ofPathToString(exe) );
	auto answer = ofSystemTextBoxDialog( ofPathToString(exe) , ofPathToString(exe) );
}

void ofApp::update(){
}

void ofApp::draw(){	

}

void ofApp::keyPressed(int key){
}
