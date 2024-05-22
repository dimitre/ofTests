#include "ofMain.h"
//========================================================================
#include "imageIO.h"
namespace fs = of::filesystem;


template <typename PixelType>
void resizeTest(int width, int height, int thumbnailProxy, ofInterpolationMethod interp, ofColor_<PixelType> col) {
	ofPixels_<PixelType> pixels;
	pixels.allocate(width, height, OF_IMAGE_COLOR_ALPHA);
	pixels.setColor(col);
	{
		ofColor_<PixelType> color = pixels.getColor(pixels.getWidth() * .5, pixels.getHeight() * .5);
		ofLogNotice() << color;
	}
	auto proxy = pixels;
	proxy.resize(pixels.getWidth() / thumbnailProxy, pixels.getHeight() / thumbnailProxy, interp);
	{
		ofColor_<PixelType> color = pixels.getColor(pixels.getWidth() * .5, pixels.getHeight() * .5);
		ofLogNotice() << color;
	}
}

template <typename PixelType>
void resizeIOTest_ofImage(int thumbnailProxy, string prefix, string extension) {
	ofLogNotice() << "ofImage_<float> test (using freeimage resize)";
	ofImage_<PixelType> floatimage;
	auto filename = prefix + "." + extension;
	
	bool loaded = floatimage.load(filename);
	if (!loaded) {
		ofLogError() << "failed while loading ofImage (using freeimage) " << filename;
		return;
	}
	else {
		ofLogNotice() << "success while loading ofImage (using freeimage) " << filename;
	}
	filename = prefix + "_copy." + extension;
	if (!floatimage.save(ofToDataPath(filename)))
		ofLogWarning() << "failed while saving ofImage (using freeimage) " << filename;
	else
		ofLogNotice() << "success while saving ofImage (using freeimage) " << filename;
	floatimage.resize(floatimage.getWidth() / thumbnailProxy, floatimage.getHeight() / thumbnailProxy);
	filename = prefix + "_proxy." + extension;
	if (!floatimage.save(ofToDataPath(filename)))
		ofLogWarning() << "failed while saving ofImage (using freeimage) " << filename;
	else
		ofLogNotice() << "success while saving ofImage (using freeimage) " << filename;
}

template <typename PixelType>
void resizeIOTest_ofPixels(int thumbnailProxy, string prefix, string extension, ofInterpolationMethod interp) {
	ofLogNotice() << "ofPixels test using tinyexr & stb to load and save float images and proxies";
	int width, height, channels;
	auto filename = prefix + "." + extension;
	PixelType* data = ImageIO::loadImage(ofToDataPath(filename), width, height, channels);

	ofPixels_<PixelType> pixels;
	pixels.setFromPixels(data, width, height, OF_IMAGE_COLOR_ALPHA);
	filename = prefix + "_copy." + extension;
	ImageIO::saveImage(ofToDataPath(filename), width, height, channels, pixels.getData());
	
//	cout << "will resize to " << (pixels.getWidth() / thumbnailProxy) << endl;
//	cout << "will resize to " << (pixels.getHeight() / thumbnailProxy) << endl;
	pixels.resize(pixels.getWidth() / thumbnailProxy, pixels.getHeight() / thumbnailProxy, interp);
	width = pixels.getWidth() / thumbnailProxy;
	height = pixels.getHeight() / thumbnailProxy;
	filename = prefix + "_proxy." + extension;
	ImageIO::saveImage(ofToDataPath(filename), width, height, channels, pixels.getData());
}

int main() {
	int thumbnailProxy = 16;

	ofLogNotice();

//	ofLogNotice() << "--- HDR png resizeIOTest_ofImage";
//	resizeIOTest_ofImage<float>(thumbnailProxy, "Digital_LAD_HD720_hdr", "png");
	
//	ofLogNotice() << "--- 16 bits linear png resizeIOTest_ofImage";
//	resizeIOTest_ofImage<float>(thumbnailProxy, "Digital_LAD_HD720_16bit", "png");


	ofLogNotice() << "--- 32 bits linear tif resizeIOTest_ofImage";
	resizeIOTest_ofImage<float>(thumbnailProxy, "Digital_LAD_HD720", "tif");
	ofLogNotice();
	ofLogNotice() << "--- 32 bits linear exr resizeIOTest_ofPixels OF_INTERPOLATE_NEAREST_NEIGHBOR";
	resizeIOTest_ofPixels<float>(thumbnailProxy, "Digital_LAD_HD720", "exr", ofInterpolationMethod::OF_INTERPOLATE_NEAREST_NEIGHBOR);
	ofLogNotice();
	ofLogNotice() << "--- 32 bits linear exr resizeIOTest_ofPixels OF_INTERPOLATE_BICUBIC";
	resizeIOTest_ofPixels<float>(thumbnailProxy, "Digital_LAD_HD720", "exr", ofInterpolationMethod::OF_INTERPOLATE_BICUBIC);

}
