namespace fs = of::filesystem;

fs::path fileSuffix(const fs::path & filename, const string & s) {
	return fs::path { fs::path("copy") / (filename.stem().string() + s + filename.extension().string()) };
}

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
void resizeIOTest_ofImage(int thumbnailProxy, const fs::path & filename) {
	ofLogNotice() << "ofImage_<PixelType> test (using freeimage resize)";
	ofImage_<PixelType> img;

	bool loaded = img.load(ofToDataPath(filename));
	if (!loaded) {
		ofLogError() << "failed while loading ofImage (using freeimage) " << filename;
		return;
	}
	else {
		ofLogNotice() << "success while loading ofImage (using freeimage) " << filename;
	}
	
	fs::path fileCopy = fileSuffix(filename, "_copy");
	if (!img.save(ofToDataPath(fileCopy)))
		ofLogWarning() << "failed while saving ofImage (using freeimage) " << filename;
	else
		ofLogNotice() << "success while saving ofImage (using freeimage) " << filename;
	img.resize(img.getWidth() / thumbnailProxy, img.getHeight() / thumbnailProxy);
	fs::path fileProxy = fileSuffix(filename, "_proxy");
	if (!img.save(ofToDataPath(fileProxy)))
		ofLogWarning() << "failed while saving ofImage (using freeimage) " << filename;
	else
		ofLogNotice() << "success while saving ofImage (using freeimage) " << filename;
}

template <typename PixelType>
void resizeIOTest_img(int thumbnailProxy, const fs::path & filename) {
	ofLogNotice() << "ofImage_<PixelType> test (using freeimage resize)";
	ofImage img;
	
	bool loaded = img.load(ofToDataPath(filename));
	if (!loaded) {
		ofLogError() << "failed while loading ofImage (using freeimage) " << filename;
		return;
	}
	else {
		ofLogNotice() << "success while loading ofImage (using freeimage) " << filename;
	}
	
	fs::path fileCopy = fileSuffix(filename, "_copy");
	if (!img.save(ofToDataPath(fileCopy)))
		ofLogWarning() << "failed while saving ofImage (using freeimage) " << filename;
	else
		ofLogNotice() << "success while saving ofImage (using freeimage) " << filename;
	img.resize(img.getWidth() / thumbnailProxy, img.getHeight() / thumbnailProxy);
	fs::path fileProxy = fileSuffix(filename, "_proxy");
	if (!img.save(ofToDataPath(fileProxy)))
		ofLogWarning() << "failed while saving ofImage (using freeimage) " << filename;
	else
		ofLogNotice() << "success while saving ofImage (using freeimage) " << filename;
}

template <typename PixelType>
void resizeIOTest_ofPixels(int thumbnailProxy, const fs::path & filename, ofInterpolationMethod interp = ofInterpolationMethod::OF_INTERPOLATE_NEAREST_NEIGHBOR) {
	ofLogNotice() << "ofPixels test using tinyexr & stb to load and save float images and proxies";
	int width, height, channels;
	PixelType* data = ImageIO::loadImage(ofToDataPath(filename), width, height, channels);

	ofPixels_<PixelType> pixels;
	pixels.setFromPixels(data, width, height, OF_IMAGE_COLOR_ALPHA);
	fs::path fileCopy = fileSuffix(filename, "_copy");
	ImageIO::saveImage(ofToDataPath(fileCopy), width, height, channels, pixels.getData());
	
	pixels.resize(pixels.getWidth() / thumbnailProxy, pixels.getHeight() / thumbnailProxy, interp);
	width = pixels.getWidth() / thumbnailProxy;
	height = pixels.getHeight() / thumbnailProxy;
	fs::path fileProxy = fileSuffix(filename, "_proxy");
	ImageIO::saveImage(ofToDataPath(fileProxy), width, height, channels, pixels.getData());
}
