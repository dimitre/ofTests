#include "ofApp.h"

void ofApp::setup() {

   	 img.load("1.jpg");
	 img2.load("1.png");
	 img3.load("1.tif");;

	string fileName = "1.png";
//
//	auto t1 { ofGetElapsedTimeMicros() };
////	cout << fs::exists(ofToDataPath("1.tif")) << endl;
////	Bitmap bitmap(ofToDataPath("1.png"));
////	Bitmap bitmap(ofToDataPath("1.png"));
//	Bitmap bitmap(ofToDataPath(fileName), Format(32, Format::UNORM, Format::RGBA, 8, 8, 8, 8));
//	img.allocate(bitmap.width, bitmap.height, OF_IMAGE_COLOR_ALPHA);
//	// Get pixels from ofImage
//	ofPixels& pixels = img.getPixels();
//
//	// Copy the data
//	memcpy(pixels.getData(), bitmap.image, bitmap.width * bitmap.height * 4);
//
//	// Update the texture
//	img.update();

//	cout << (ofGetElapsedTimeMicros() - t1) << endl;

	// auto t2 { ofGetElapsedTimeMicros() };
	// img2.load(fileName);
	// cout << (ofGetElapsedTimeMicros() - t2) << endl;

}

void ofApp::update(){

}

void ofApp::draw(){
	if (img.isAllocated()) {
		img.draw(0, 0);
	}
	if (img2.isAllocated()) {
		img2.draw(200, 200);
	}
	if (img3.isAllocated()) {
		img3.draw(400, 400);
	}
//	i.draw(300, 300);
}

void ofApp::keyPressed(int key){

}

// void ofApp::keyReleased(int key){}
// void ofApp::exit() {}

// void ofApp::mouseMoved(int x, int y ) {}
// void ofApp::mouseDragged(int x, int y, int button) {}
// void ofApp::mousePressed(int x, int y, int button) {}
// void ofApp::mouseReleased(int x, int y, int button) {}
// void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY) {}
// void ofApp::mouseEntered(int x, int y) {}
// void ofApp::mouseExited(int x, int y) {}
//
// void ofApp::windowResized(int w, int h) {}
// void ofApp::gotMessage(ofMessage msg) {}
// void ofApp::dragEvent(ofDragInfo dragInfo) {}
