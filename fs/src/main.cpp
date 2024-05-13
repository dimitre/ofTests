//#include "ofFileUtils.h"
//#include "ofUtils.h"
//#include "ofxUnitTests.h"
//
//of::filesystem::path initial_cwd;
//
//class ofApp: public ofxUnitTestsApp{
//	void run(){
//		
//		ofLogNotice() << "testing ofFile";
//		{
//			ofFile("arwil.txt").create();
//		}
//		
//		ofxTest(ofFile("arwil.txt").exists(),"ofFile::create && ofFile::exists");
//		
//		std::exit(0);
//	}
//};
//
//#include "ofAppNoWindow.h"
//#include "ofAppRunner.h"
////========================================================================
//int main( ){
//	ofInit();
//	initial_cwd = of::filesystem::current_path();
//	auto window = std::make_shared<ofAppNoWindow>();
//	auto app = std::make_shared<ofApp>();
//	ofRunApp(window, app);
//	return ofRunMainLoop();
//}



#include "ofApp.h"             // for ofApp
#include "ofAppRunner.h"       // for ofRunApp, ofSetupOpenGL
#include "ofWindowSettings.h"  // for OF_WINDOW
#include "ofAppNoWindow.h"

int main( ){
	ofGLFWWindowSettings settings;
	settings.setSize(600, 600);
	settings.windowMode = OF_WINDOW;
//	auto win { ofCreateWindow(settings) };
	auto win = std::make_shared<ofAppNoWindow>();
	auto app { make_shared<ofApp>() };
	ofRunApp(win, app);
	ofRunMainLoop();
}
