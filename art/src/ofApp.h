#pragma once

#include "ofMain.h"
#include "ofxMicroUI.h"
#include "art2023.h"

class ofApp : public ofBaseApp{
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	
	ofxMicroUI u;
	
//#include "art2023.h"
	artnetDmtr art { "2.0.0.31" };

	artnetDmtr art2 { "127.0.0.1" };

};

