#include "Ultil.hpp"

using namespace std;
void CheckError()
{
	GLenum error = glGetError();

	string errString;
	switch (error)
	{
		case GL_NO_ERROR: errString = "NO_ERROR"; break;
		case GL_INVALID_OPERATION: errString = "INVALID_OPERATION"; break;
		case GL_INVALID_ENUM: errString = "INVALID_ENUM"; break;
		case GL_INVALID_VALUE: errString = "INVALID_VALUE"; break;
		case GL_OUT_OF_MEMORY: errString = "OUT_OF_MEMORY"; break;
		case GL_INVALID_FRAMEBUFFER_OPERATION: errString = "INVALID_FRAMEBUFFER_OPERATION"; break;
		case GL_STACK_OVERFLOW: errString = "STACK_OVERFLOW"; break;
		case GL_STACK_UNDERFLOW: errString = "STACK_UNDERFLOW"; break;
		default: errString = "UNKNOWN_ERROR";
	}
	printf("[LOG] glGetError: %s\r\n", errString.c_str());
}
void CaptureScreen(const char* name, unsigned int width,
	unsigned int height, unsigned int format, unsigned int type, unsigned short channel)
{
	BITMAPFILEHEADER bf;
	BITMAPINFOHEADER bi;
	unsigned int imgSize = width * height * 4;

	unsigned char* image = (unsigned char*)malloc(imgSize * sizeof(unsigned char));
	if (!image)
	{
		printf("[ERROR] Not enough memory.\r\n");
		return;
	}

	glReadPixels(0, 0, width, height, format, type, image);
	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
	{
		printf("[ERROR] Cannot read pixels from frame buffer.\r\n");
		printf("[ERROR] Error on glReadPixels: %d\r\n", err);
		return;
	}

	FILE* file = fopen(name, "wb");
	if (!file)
	{
		printf("[ERROR] Cannot create file: %s\r\n", name);
		return;
	}

	memset(&bf, 0, sizeof(bf));
	memset(&bi, 0, sizeof(bi));

	bf.bfType = 'MB';
	bf.bfSize =  sizeof(bf) + sizeof(bi) + imgSize;
	bf.bfOffBits =  sizeof(bf) + sizeof(bi);

	bi.biSize = sizeof(bi);
	bi.biWidth = width;
	bi.biHeight = height;
	bi.biPlanes = 1;
	bi.biBitCount = 24;
	bi.biSizeImage = imgSize;

	fwrite(&bf, sizeof(bf), 1, file);
	fwrite(&bi, sizeof(bi), 1, file);
	fwrite(image, imgSize, 1, file);
	fclose(file);
	free(image);
}