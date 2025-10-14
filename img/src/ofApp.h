#pragma once

#include "ofMain.h"
//#define MANGO_IMPLEMENT_MAIN
// #include <mango/mango.hpp>
// #include <mango/opengl/opengl.hpp>

// using namespace mango;
// using namespace mango::math;
// using namespace mango::image;


class ofApp : public ofBaseApp {
public:
	void setup() override;
	void update() override;
	void draw() override;
	void keyPressed(int key) override;

	// ofImage img;
	ofImage i { ofToDataPath("1.tif") };

};
