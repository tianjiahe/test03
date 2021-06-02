#pragma once

#include <atlimage.h>// pngÍ¼±ê

class CTransparentPNG
{

public:
	CTransparentPNG() {}
	~CTransparentPNG() {}


	bool operator()(CImage* image) {
		if (!image)
			return false;
		if (image->GetBPP() != 32)
			return false;
		for (int i = 0; i < image->GetWidth(); ++i)
		{
			for (int j = 0; j < image->GetHeight(); ++j)
			{
				unsigned char* pucColor = reinterpret_cast<unsigned char*>(image->GetPixelAddress(i, j));
				pucColor[0] = pucColor[0] * pucColor[3] / 255;
				pucColor[1] = pucColor[1] * pucColor[3] / 255;
				pucColor[2] = pucColor[2] * pucColor[3] / 255;
			}
		}

		return true;
	}

	static bool TransPng(CImage* image)
	{
		if (!image)
			return false;
		if (image->GetBPP() != 32)
			return false;
		for (int i = 0; i < image->GetWidth(); ++i)
		{
			for (int j = 0; j < image->GetHeight(); ++j)
			{
				unsigned char* pucColor = reinterpret_cast<unsigned char*>(image->GetPixelAddress(i, j));
				pucColor[0] = pucColor[0] * pucColor[3] / 255;
				pucColor[1] = pucColor[1] * pucColor[3] / 255;
				pucColor[2] = pucColor[2] * pucColor[3] / 255;
			}
		}
		return true;
	}

};
