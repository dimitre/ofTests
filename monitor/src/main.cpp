//#include "ofMain.h"
//#include "ofApp.h"

#include "ofApp.h"             // for ofApp
#include "ofAppRunner.h"       // for ofRunApp, ofSetupOpenGL
#include "ofWindowSettings.h"  // for OF_WINDOW

int main( ){
	ofGLFWWindowSettings settings;
	// OK
//	settings.setSize(1512, 800);
	// NOT OK
	settings.setSize(1513, 800);
	settings.windowMode = OF_WINDOW;

//	settings.setGLVersion(3, 2);
//	settings.windowMode = OF_WINDOW;
	auto win { ofCreateWindow(settings) };
	auto app { make_shared<ofApp>() };
	
	// Second
	settings.windowMode = OF_FULLSCREEN;
	settings.shareContextWith = win;
	settings.monitor = 1;
	auto newWindow = ofCreateWindow(settings);
//	settings.windowName = "second";
//	ofAddListener(newWindow->events().draw, mainApp.get(), &ofApp::drawSecondWindow);
	
	
	ofRunApp(win, app);
	ofRunMainLoop();
}
