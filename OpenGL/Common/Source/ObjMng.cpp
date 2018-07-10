#include "ObjMng.hpp"

void ObjMng::addDict(const char* type, GLuint ID)
{
	std::vector<GLuint> vID;
	if (mDict.find(type) == mDict.end()) // key is not present
	{
		vID.push_back(ID);
		mDict.insert(std::pair<const char*,std::vector<GLuint>>(type, vID));
	}
	else
	{
		mDict[type].push_back(ID);
	}
}

void ObjMng::print()
{
	std::map<const char*, std::vector<GLuint>>::iterator itmDict;
	std::vector<GLuint>::iterator itvID;
	for (itmDict = mDict.begin(); itmDict != mDict.end(); ++itmDict)
	{
		printf("key:%s\t\t value:", itmDict->first);
		for (itvID = itmDict->second.begin(); itvID != itmDict->second.end(); ++itvID)
		{
			printf("%d ", *itvID);
		}
		printf("\r\n");
	}
}

void ObjMng::deleteAll()
{
	std::map<const char*, std::vector<GLuint>>::iterator itmDict;
	std::vector<GLuint>::iterator itvID;
	itmDict = mDict.begin();
	while (++itmDict != mDict.end())
	{
		itvID = itmDict->second.begin();
		while (++itvID != itmDict->second.end())
		{
			if (itmDict->first == "Buffer")
				glDeleteBuffers(1, &(*itvID));
			else if (itmDict->first == "Vertexarray")
				glDeleteVertexArrays(1, &(*itvID));
			else if (itmDict->first == "Texture")
				glDeleteTextures(1, &(*itvID));
			else if (itmDict->first == "FrameBuffer")
				glDeleteFramebuffers(1, &(*itvID));
			else if (itmDict->first == "RenderBuffer")
				glDeleteRenderbuffers(1, &(*itvID));
		}
	}
}