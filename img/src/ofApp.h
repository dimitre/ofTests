#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
	void setup() override;
	void update() override;
	void draw() override;
	void keyPressed(int key) override;

	ofImage i, i2, i3;
};
