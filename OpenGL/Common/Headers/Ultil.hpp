#ifndef _ULTIL_HPP_
#define _ULTIL_HPP_

#include <stdio.h>
#include <stdlib.h>
#include <string>

#define GLEW_STATIC
#include <GL/glew.h> // include GLEW and new version of GL on Windows

/* Use this pragma to avoid compiler padding 2 bytes to this struct */
#pragma pack(push)
#pragma pack(1)
struct BITMAPFILEHEADER 
{
	unsigned short bfType;	// must always be set to 'BM' to declare that this is a .bmp-file
	unsigned int bfSize;			// specifies the size of the file in bytes
	unsigned short bfReserved1;	// must always be set to zero
	unsigned short bfReserved2; // must always be set to zero
	unsigned int bfOffBits;	// specifies the offset from the beginning of the file to the bitmap data
};
#pragma pack(pop)

struct BITMAPINFOHEADER
{
	unsigned int biSize; // specifies the size of the BITMAPINFOHEADER structure, in bytes
	unsigned int biWidth; // specifies the width of the image, in pixels.
	unsigned int biHeight; // specifies the height of the image, in pixels.
	unsigned short biPlanes; // specifies the number of planes of the target device, must be set to 1.
	unsigned short biBitCount; // specifies the number of bits per pixel.
	unsigned int biCompression; // Specifies the type of compression, usually set to zero (no compression).
	unsigned int biSizeImage; // specifies the size of the image data, in bytes. If there is no compression, it is valid to set this member to zero.
	unsigned int biXPelsPerMeter; // specifies the the horizontal pixels per meter on the designated targer device, usually set to zero.
	unsigned int biYPelsPerMeter; // specifies the the vertical pixels per meter on the designated targer device, usually set to zero.
	unsigned int biClrUsed; // specifies the number of colors used in the bitmap, if set to zero the number of colors is calculated using the biBitCount member.
	unsigned int biClrImportant; // specifies the number of color that are 'important' for the bitmap, if set to zero, all colors are important.
};

void CheckError();
void CaptureScreen(const char* name, unsigned int width,
	unsigned int height, unsigned int format, unsigned int type, unsigned short channel = 3);

#endif // !_UTIL_HPP_

