#include "ofMain.h"
//========================================================================
#include "imageIO.h"
#include "tests.h"

int main() {
	ofGLWindowSettings settings;
	settings.setSize(100, 100);
	auto window = ofCreateWindow(settings);

	
	int thumbnailProxy = 8;

	ofLogNotice();


	
	// working ok here, once we have a window
//	ofLogNotice() << "--- 8 bits linear png resizeIOTest_ofPixels";
//	resizeIOTest_ofImage<unsigned char>(thumbnailProxy, "Digital_LAD_HD720.png");

	ofLogNotice() << "--- 16 bits linear png resizeIOTest_ofImage";
	resizeIOTest_ofImage<float>(thumbnailProxy, "Digital_LAD_HD720_16bit.png");

//	ofLogNotice() << "--- 16 bits linear png resizeIOTest_ofImage";
//	resizeIOTest_img<float>(thumbnailProxy, "Digital_LAD_HD720_16bit.png");

//	ofLogNotice() << "--- 16 bits linear png resizeIOTest_ofPixels";
//	resizeIOTest_ofPixels<float>(thumbnailProxy, "Digital_LAD_HD720_16bit.png");

	//	ofLogNotice() << "--- HDR png resizeIOTest_ofPixels";
//	resizeIOTest_ofPixels<float>(thumbnailProxy, "Digital_LAD_HD720_hdr.png");

	

//	ofLogNotice() << "--- HDR png resizeIOTest_ofImage";
//	resizeIOTest_ofImage<float>(thumbnailProxy, "Digital_LAD_HD720_hdr", "png");
	


//	ofLogNotice() << "--- 16 bits linear tif resizeIOTest_ofImage";
//	resizeIOTest_ofImage<float>(thumbnailProxy, "Digital_LAD_HD720_16bit", "tif");
//	ofLogNotice();

//	ofLogNotice() << "--- 16 bits linear tif resizeIOTest_ofImage";
//	resizeIOTest_ofPixels<float>(thumbnailProxy, "Digital_LAD_HD720_16bit.tif", ofInterpolationMethod::OF_INTERPOLATE_NEAREST_NEIGHBOR);
//	ofLogNotice();
	
//	ofLogNotice() << "--- 32 bits linear tif resizeIOTest_ofImage";
//	resizeIOTest_ofImage<float>(thumbnailProxy, "Digital_LAD_HD720", "tif");
//	ofLogNotice();
//	ofLogNotice() << "--- 32 bits linear exr resizeIOTest_ofPixels OF_INTERPOLATE_NEAREST_NEIGHBOR";
//	resizeIOTest_ofPixels<float>(thumbnailProxy, "Digital_LAD_HD720", "exr", ofInterpolationMethod::OF_INTERPOLATE_NEAREST_NEIGHBOR);
//	ofLogNotice();
//	ofLogNotice() << "--- 32 bits linear exr resizeIOTest_ofPixels OF_INTERPOLATE_BICUBIC";
//	resizeIOTest_ofPixels<float>(thumbnailProxy, "Digital_LAD_HD720", "exr", ofInterpolationMethod::OF_INTERPOLATE_BICUBIC);

}
