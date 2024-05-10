#include "ofApp.h"             // for ofApp
#include "ofAppRunner.h"       // for ofRunApp, ofSetupOpenGL
#include "ofWindowSettings.h"  // for OF_WINDOW

int main( ){
	ofGLFWWindowSettings settings;
	settings.setSize(600, 600);
	settings.windowMode = OF_WINDOW;
	auto win { ofCreateWindow(settings) };
	auto app { make_shared<ofApp>() };
	ofRunApp(win, app);
	ofRunMainLoop();
}
