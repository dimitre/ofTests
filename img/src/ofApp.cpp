#include "ofApp.h"

void ofApp::setup() {

	cout << "CWD  " << std::filesystem::current_path() << endl;

	cout << "ofToDataPath  " << ofToDataPath(".") << endl;

	i.load("1.png");
	
	i.draw(100, 100);
	i2.draw(300, 300);
}

void ofApp::update(){

}

void ofApp::draw(){
}

void ofApp::keyPressed(int key){

}
