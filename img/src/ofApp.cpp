#include "ofApp.h"

void ofApp::setup() {
	// cout << "png_OK " << FreeImage_FIFSupportsReading (FIF_PNG) << endl;
	// cout << "jpegOK " << FreeImage_FIFSupportsReading (FIF_JPEG) << endl;
	// cout << "tiffOK " << FreeImage_FIFSupportsReading (FIF_TIFF) << endl;

	// i.load("1.tif");
	cout << ofToDataPath("1.jpg") << fs::exists(ofToDataPath("1.jpg")) << endl;
	cout << ofToDataPath("1.png") << fs::exists(ofToDataPath("1.png")) << endl;
	cout << ofToDataPath("1.tif") << fs::exists(ofToDataPath("1.tif")) << endl;

	i.load("1.tif");
	i2.load("1.png");
	i3.load("1.jpg");
}

void ofApp::draw(){
	if (i.isAllocated()) {
		i.draw(100, 100);
		ofDrawBitmapString("i tif" , 100, 100);
	}
	if (i2.isAllocated()) {
		i2.draw(300, 300);
		ofDrawBitmapString("i2 png" , 300, 300);
	}
	if (i3.isAllocated()) {
		i3.draw(500, 500);
		ofDrawBitmapString("i3 jpg" , 500, 500);
	}
}

void ofApp::update(){}

void ofApp::keyPressed(int key){

}
