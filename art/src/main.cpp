//#include "ofMain.h"
#include "ofApp.h"
#include "ofAppBaseWindow.h"
#include "ofAppRunner.h"

int main(){
//	ofGLFWWindowSettings settings;
	ofWindowSettings settings;
	settings.setSize(2000, 950);
	
	// FIXME: Temporario
//	settings.setSize(1990, 1400);
	settings.windowMode = OF_WINDOW;
	
	auto guiWindow = ofCreateWindow(settings);
	auto mainApp = make_shared<ofApp>();

	ofRunApp(guiWindow, mainApp);
	ofRunMainLoop();
}
