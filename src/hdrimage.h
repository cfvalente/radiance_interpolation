#ifndef PROJCG_HDRIMAGE_H_
#define PROJCG_HDRIMAGE_H_

#include <string>
#include <memory>
#include <iostream>

#include <FreeImage.h>


class HdrImage {
public:
	HdrImage(int width, int height) {
		imageBitmap_ = std::shared_ptr<FIBITMAP>(FreeImage_AllocateT(FIT_RGBAF, width, height, 128), &FreeImage_Unload);
	}

	HdrImage(std::string filename);

	HdrImage(const std::shared_ptr<FIBITMAP> &imageBitmap) :
		imageBitmap_(imageBitmap) {}

	int getWidth();
	int getHeight();
	void saveImageAsPng(std::string filename);
	void saveImageAsHdr(std::string filename);
	void saveImageAsTif(std::string filename);
	FIRGBAF getPixelAt(unsigned int x, unsigned int y);
	float calcDist(const HdrImage& param);
	HdrImage diffAbs(const HdrImage& param);
	float calcDist_L1(const HdrImage& param);
	float hdrabs();
	HdrImage operator-(const HdrImage& param);
	HdrImage operator+(const HdrImage& param);
	HdrImage operator*(const double& param);
	HdrImage operator/(const double& param);
	HdrImage clamp();
	void setPixelAt(unsigned int x, unsigned int y, FIRGBAF rgb);



private:
	std::shared_ptr<FIBITMAP> imageBitmap_;
};

#endif