//#include "ofMain.h"
////========================================================================
//
//template <typename PixelType>
//void resizeTest(int width, int height, int thumbnailProxy, ofInterpolationMethod interp, ofColor col) {
//	ofPixels_<PixelType> pixels;
//	pixels.allocate(width, height, OF_IMAGE_COLOR_ALPHA);
//	pixels.setColor(col);
//	{
//		ofColor color = pixels.getColor(pixels.getWidth() * .5, pixels.getHeight() * .5);
//		ofLogWarning() << color;
//	}
////	ofLogWarning() << pixels.getColor(0);
////	ofLogWarning() << int(pixels.getColor(0).r) << "," << int(pixels.getColor(0).g) << "," << int(pixels.getColor(0).b) << "," << int(pixels.getColor(0).a);
//	auto proxy = pixels;
//	proxy.resize(pixels.getWidth() / thumbnailProxy, pixels.getHeight() / thumbnailProxy, interp);
//	{
//		ofColor color = pixels.getColor(pixels.getWidth() * .5, pixels.getHeight() * .5);
//		ofLogWarning() << color;
//	}
////	ofLogWarning() << color;
////	ofLogWarning() << int(proxy.getColor(0).r) << "," << int(proxy.getColor(0).g) << "," << int(proxy.getColor(0).b) << "," << int(proxy.getColor(0).a);
//}
//
//int main() {
//	int thumbnailProxy = 16;
//	cout << "--- one" << endl;
//	resizeTest<unsigned char>(1920, 1080, thumbnailProxy, ofInterpolationMethod::OF_INTERPOLATE_NEAREST_NEIGHBOR, ofColor(255, 255, 0, 255));
//	cout << "--- two" << endl;
//	resizeTest<unsigned char>(1920, 1080, thumbnailProxy, ofInterpolationMethod::OF_INTERPOLATE_BICUBIC, ofColor(255, 255, 0, 255));
//	cout << "--- three" << endl;
//	resizeTest<float>(1920, 1080, thumbnailProxy, ofInterpolationMethod::OF_INTERPOLATE_NEAREST_NEIGHBOR, ofFloatColor(1, 1, 0, 1));
//	cout << "--- four" << endl;
//	resizeTest<float>(1920, 1080, thumbnailProxy, ofInterpolationMethod::OF_INTERPOLATE_BICUBIC, ofFloatColor(1, 1, 0, 1));
//}
/*
outputs
[warning] 255, 255, 255, 255
[warning] ÿ,ÿ,ÿ,ÿ
[warning] 80, 1, 7, 76
[warning] P,�,�,L
[warning] 255, 255, 255, 255
[warning] ÿ,ÿ,ÿ,ÿ
[warning] 0, 255, 255, 255
[warning] [warning] 0.00392157, 0.00392157, 0.00392157, 0.00392157
[warning] 0.00392157,0.00392157,0.00392157,0.00392157
[warning] 3.53908e+07, 6.0396e-43, 3.55085e+07, 6.0396e-43
[warning] 3.53908e+07,6.0396e-43,3.55085e+07,6.0396e-43
[warning] 0.00392157, 0.00392157, 0.00392157, 0.00392157
[warning] 0.00392157,0.00392157,0.00392157,0.00392157
[warning] 0, 0, 0, 0
[warning] 0,0,0,0
*/

//#include "ofMain.h"
//template <typename PixelType>
//void resizeTest(int width, int height, int thumbnailProxy, ofInterpolationMethod interp) {
//	ofPixels_<PixelType> pixels;
//	pixels.allocate(width, height, OF_IMAGE_COLOR_ALPHA);
////	pixels.resize(pixels.getWidth() / thumbnailProxy, pixels.getHeight() / thumbnailProxy, interp);
////	ofLogWarning() << pixels.getColor(0);
//	auto proxy = pixels;
//	proxy.resize(pixels.getWidth() / thumbnailProxy, pixels.getHeight() / thumbnailProxy, interp);
//	ofLogWarning() << proxy.getColor(0);
//}
//
//int main( ){
//	int thumbnailProxy = 10;
//	cout << 1 << endl;
//	resizeTest<unsigned char>(1920, 1080, thumbnailProxy, ofInterpolationMethod::OF_INTERPOLATE_NEAREST_NEIGHBOR);
////	cout << 2 << endl;
////	resizeTest<unsigned char>(1920, 1080, thumbnailProxy, ofInterpolationMethod::OF_INTERPOLATE_BILINEAR);
//	cout << 3 << endl;
//	resizeTest<unsigned char>(1920, 1080, thumbnailProxy, ofInterpolationMethod::OF_INTERPOLATE_BICUBIC);
//	cout << 4 << endl;
//	resizeTest<float>(1920, 1080, thumbnailProxy, ofInterpolationMethod::OF_INTERPOLATE_NEAREST_NEIGHBOR);
////	cout << 5 << endl;
////	resizeTest<float>(1920, 1080, thumbnailProxy, ofInterpolationMethod::OF_INTERPOLATE_BILINEAR);
//	cout << 6 << endl;
//	resizeTest<float>(1920, 1080, thumbnailProxy, ofInterpolationMethod::OF_INTERPOLATE_BICUBIC);
//}


//#include "ofMain.h"
//#include "ofApp.h"

#include "ofApp.h"             // for ofApp
#include "ofAppRunner.h"       // for ofRunApp, ofSetupOpenGL
#include "ofWindowSettings.h"  // for OF_WINDOW

int main( ){
//	ofSetupOpenGL(1200,800,OF_WINDOW);			// <-------- setup the GL context
//	ofRunApp(new ofApp());
	
	ofGLFWWindowSettings settings;
	settings.setSize(600, 600);
//	settings.setGLVersion(3, 2);
	settings.windowMode = OF_WINDOW;
	auto win { ofCreateWindow(settings) };
	auto app { make_shared<ofApp>() };
	
	ofRunApp(win, app);
	ofRunMainLoop();
}
