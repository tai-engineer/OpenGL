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
	std::map<const char*, std::vector<GLuint>>::iterator itmDict;
	std::vector<GLuint>::iterator itvID;

public:
	template <typename T>
	void create(T **object, const char* type);
	void print();
};

template <typename T>
void ObjMng::create(T **object, const char* type)
{
	std::vector<GLuint> vID;
	*object = new T();
	GLuint ID = (*object)->getID();

	itmDict = mDict.find(type);
	if (itmDict == mDict.end()) // key is not present
	{
		vID.push_back(ID);
		mDict.insert(std::pair<const char*,std::vector<GLuint>>(type, vID));
	}
	else
	{
		mDict[type].push_back(ID);
	}
}
#endif // !_OBJMNG_HPP_

