#ifndef _OBJMNG_HPP_
#define _OBJMNG_HPP_

#include <map>
#include <vector>

#include "Buffer.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Framebuffer.hpp"
#include "Renderbuffer.hpp"

class ObjMng
{
private:
	std::map<const char*, std::vector<GLuint>> mDict;

	void addDict(const char* type, GLuint ID);

public:
	template <typename T>
	void create(T **object, const char* type);
	void print();
	void deleteAll();
};

template <typename T>
void ObjMng::create(T **object, const char* type)
{
	*object = new T();
	addDict(type, (*object)->getID());
}
#endif // !_OBJMNG_HPP_

