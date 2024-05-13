#include "ofApp.h"

//string path = "-";
ofImage image;
//--------------------------------------------------------------
void ofApp::setup(){
	cout << "testing exe branch" << endl;
	cout << ofFilePath::getCurrentExePathFS() << endl;
	cout << "will test loading file now" << endl;
	image.load("consolação.jpg");
	cout << "file loaded" << endl;
}

void ofApp::update(){
}

void ofApp::draw(){
//	ofDrawBitmapString(path, 10, 30);
	ofDrawBitmapString("Consolação", 10, 46);
	if (image.isAllocated()) {
		image.draw(10,50);
	}
}

void ofApp::keyPressed(int key){
	if (key == 'a') {
		auto s = ofSystemTextBoxDialog("Anunciação what is your favorite color?" , "Anunciação blue");
	}
	else if (key == 'l') {
		ofFileDialogResult result = ofSystemLoadDialog("Anunciação Load file");
		if(result.bSuccess) {
			image.load(result.getPath());
//			path = result.getPath().u8string();
//			image.load(result.getPath());
			cout << result.getPath() << endl;
		  // load your file at `path`
		}
	}
}
