#include "Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture() 
{
	glGenTextures(1, &ID);
}

GLuint Texture::getID() 
{
	return ID;
}

GLint Texture::getWidth() 
{
	return width;
}

GLint Texture::getHeight() 
{
	return height;
}

GLint Texture::getChannels() 
{
	return channels;
}

GLuint Texture::load(const char* image) 
{
	glBindTexture(GL_TEXTURE_2D, ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char *data = stbi_load(image, &width, &height, &channels, 0);
	if (data)
	{
		GLenum format;
		if (channels == 1)
		{
			format = GL_RED;
		}
		else if (channels == 3)
		{
			format = GL_RGB;
		}
		else if (channels == 4)
		{
			format = GL_RGBA;
		}
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	}
	else
	{
		printf("[ERROR] Failed to load texture.");
		ID = 0;
	}
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);
	return ID;
}

GLuint Texture::loadCubeMap(std::vector<std::string> faces)
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, ID);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &channels, 0);
		if (data)
		{
			GLenum format;
			if (channels == 1)
			{
				format = GL_RED;
			}
			else if (channels == 3)
			{
				format = GL_RGB;
			}
			else if (channels == 4)
			{
				format = GL_RGBA;
			}
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			printf("Cubemap texture failed to load at path: %s", faces[i].c_str());
			stbi_image_free(data);
		}
	}
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	return ID;
}

void Texture::deleteTexture() 
{
	glDeleteTextures(1, &ID);
}