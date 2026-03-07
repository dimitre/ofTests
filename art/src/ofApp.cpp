#include "ofApp.h"

int uni = 0;
void ofApp::setup(){
	ofSetFrameRate(30);
	string s = ofBufferFromFile("uni.txt").getData();
	uni = ofToInt(s);
	cout << uni << endl;

	art.addUniverse(uni);
	art2.addUniverse(uni);
	vector <string> lines;
	for (int a=0; a<8; a++) {
		int i = a * 40;
		int f = (a+1)*40;
		lines.emplace_back("");
		lines.emplace_back("ints	c["+ofToString(i)+"-"+ofToString(f)+"]	0 255 0");
		lines.emplace_back("newCol");
	}

//	string l { "ints	c[0-30]	0 255 0" };
	u.createFromLines(lines);
}

void ofApp::update() {
}

void ofApp::draw(){
	for (int a=0; a<320; a++) {
		art.getUniverse(uni)->data[a] = u.pInt["c_" + ofToString(a)];
		art2.getUniverse(uni)->data[a] = u.pInt["c_" + ofToString(a)];
	}
	art.send();
	art2.send();
}

void ofApp::keyPressed(int key) {
}
