#include "ofApp.h"

//string path = "-";
ofImage image;
//--------------------------------------------------------------
void ofApp::setup(){
	cout << "testing exe branch" << endl;
	cout << ofFilePath::getCurrentExePath() << endl;
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
		ofSystemAlertDialog("Translação, rotação");
	}
	else if (key == 's') {
		auto s = ofSystemTextBoxDialog("Anunciação what is your favorite color?" , "Anunciação blue");
	}
	else if (key == 'd') {
		ofFileDialogResult result = ofSystemLoadDialog("Anunciação Load file", true, "folderzão");
		if(result.bSuccess) {
			image.load(result.getPath());
			cout << result.getPath() << endl;
			wcout << result.getPath() << endl;
		}
	}
	else if (key == 'e') {
		ofFileDialogResult result = ofSystemLoadDialog("Anunciação Load file", false, "folderzão");
		if(result.bSuccess) {
			image.load(result.getPath());
			cout << result.getPath() << endl;
			wcout << result.getPath() << endl;
		}
	}
	else if (key == 'f') {
		ofFileDialogResult result = ofSystemLoadDialog("Anunciação Load file");
		if(result.bSuccess) {
			image.load(result.getPath());
			cout << result.getPath() << endl;
			wcout << result.getPath() << endl;
		}
	}

}
