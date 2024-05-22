#ifndef _IMAGELOADER_H_
#define _IMAGELOADER_H_

#include <string>
#include <iostream>
namespace ImageIO {
	float* loadImage(const std::string filepath, int& width, int& height, int& channels);
	bool saveImage(const std::string filepath, int& width, int& height, int& channels, const float* data);
}
#endif
