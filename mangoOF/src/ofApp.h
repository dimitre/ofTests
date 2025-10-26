#pragma once

#include "ofMain.h"
//#define MANGO_IMPLEMENT_MAIN
#include <mango/mango.hpp>
//#include <mango/opengl/opengl.hpp>

using namespace mango;
using namespace mango::math;
using namespace mango::image;


class ofApp : public ofBaseApp {
public:
	void setup() override;
	void update() override;
	void draw() override;
	void keyPressed(int key) override;

	ofImage img;
	ofImage img2;
	ofImage img3;
//	ofImage i { "1.tif" };

	// void keyReleased(int key) override;
	// void exit() override;

	// void mouseMoved(int x, int y ) override;
	// void mouseDragged(int x, int y, int button) override;
	// void mousePressed(int x, int y, int button) override;
	// void mouseReleased(int x, int y, int button) override;
	// void mouseScrolled(int x, int y, float scrollX, float scrollY) override;
	// void mouseEntered(int x, int y) override;
	// void mouseExited(int x, int y) override;

	// void windowResized(int w, int h) override;
	// void dragEvent(ofDragInfo dragInfo) override;
	// void gotMessage(ofMessage msg) override;
};
