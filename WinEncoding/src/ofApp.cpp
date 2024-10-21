#include "ofApp.h"

//string path = "-";
ofImage image;
//--------------------------------------------------------------
void ofApp::setup(){
	std::setlocale(LC_ALL, "");
	cout << ofFilePath::getCurrentExePath() << endl;
	cout << "consolação" << endl;
	std::wcout << "consolação" << endl;

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
		auto saida = ofSystemTextBoxDialog("Anunciação what is your favorite color?" , "Anunciação blue");
		cout << saida << endl;
	}
	else if (key == 'd') {
		ofFileDialogResult result = ofSystemLoadDialog("Anunciação Load file", true, "folderzão");
		if(result.bSuccess) {
//			image.load(result.getPath());
			cout << result.getPath() << endl;
			std::wcout << result.getPath() << endl;
		}
	}
	else if (key == 'f') {
		ofFileDialogResult result = ofSystemLoadDialog("Anunciação Load file", false, "folderzão");
		if(result.bSuccess) {
			image.load(result.getPath());
			cout << result.getPath() << endl;
			std::wcout << result.getPath() << endl;
		}
	}
	else if (key == 'g') {
		ofFileDialogResult result = ofSystemLoadDialog("Anunciação Load file");
		if(result.bSuccess) {
			image.load(result.getPath());
			cout << result.getPath() << endl;
			std::wcout << result.getPath() << endl;
		}
	}

}
