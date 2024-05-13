#include "ofApp.h"

namespace fs = of::filesystem;
void ofApp::setup(){
	ofInit();

	cout << "current " << fs::current_path() << endl;
	cout << fs::absolute(fs::current_path()) << endl;
	cout << ofFile("test.txt").getAbsolutePath() << endl;
	cout << "create " << ofFile("arwil.txt").create() << endl;
	cout << "exists " <<ofFile("arwil.txt").exists() << endl;
	cout << ofFile("test.txt").getAbsolutePath() << endl;
	cout << ofToDataPath("",true) << endl;
	std::exit(0);
}

void ofApp::update(){
}

void ofApp::draw(){	

}

void ofApp::keyPressed(int key){
}
