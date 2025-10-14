#include "ofApp.h"

void ofApp::setup() {
	cout << std::filesystem::current_path() << endl;
}

void ofApp::update(){

}

void ofApp::draw(){
	i.draw(300, 300);
}

void ofApp::keyPressed(int key){

}
