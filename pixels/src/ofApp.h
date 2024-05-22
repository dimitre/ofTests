#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);

	ofImage img { "Digital_LAD_HD720.exr" };
};
