#include "ffImage.h"

#define STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"

ffImage* ffImage::readFromFile(const char* _fileName)
{
	int			_picType = 0;
	int			_width = 0;
	int			_height = 0;

	//stbimage读入的图片是反过来的
	stbi_set_flip_vertically_on_load(true);

	unsigned char* bits = stbi_load(_fileName, &_width, &_height, &_picType, STBI_rgb_alpha);
	ffImage* _image = new ffImage(_width, _height, _picType, (ffRGBA*)bits);

	stbi_image_free(bits);
	return _image;
}