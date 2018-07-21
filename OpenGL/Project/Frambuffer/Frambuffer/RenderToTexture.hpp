#ifndef _RENDERTOTEXTURE_HPP_
#define _RENDERTOTEXTURE_HPP_

#include "Buffer.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Camera.hpp"
#include "Framebuffer.hpp"
#include "Renderbuffer.hpp"

#include "ObjMng.hpp"

#define USE_MODEL

using namespace std;
class RenderToTexture
{

public:
	Shader*				fbProgram;
	Shader*				quadProgram;
	
	VertexArray*		cubeVAO;
	Buffer*				cubeVBO;

	VertexArray*		planeVAO;
	Buffer*				planeVBO;

	VertexArray*		quadVAO;
	Buffer*				quadVBO;

	Texture*			texMarble;
	Texture*			texMetal;

	FrameBuffer*		frameBuffer;
	Texture*			texColorBuffer;
	RenderBuffer*		renderBuffer;	

	Camera*				camera;

	ObjMng*				objMng;

#if defined USE_MODEL
	Buffer* vertexVBO = NULL;
	Buffer* uvVBO = NULL;
#endif

	bool initShader();
	void setupApplication();
	void render();
	Camera* getCameraObj();
	void deleteApplication();

private:
	unsigned int Width;
	unsigned int Height;

	void setCameraObj(glm::vec3 value);
	void setupVAO();
	void setupFBO();
	void loadTexture();
	void renderTexture();
	void renderScene();

#if defined USE_MODEL
	vector<glm::vec3> vertices;
	vector<glm::vec2> textures;
	vector<glm::vec3> normals;

	vector<string> split(const string str, const char &delimiter);
	void ParseToVector(const char* x, const char* y, const char* z, glm::vec3* vt);
	void ParseToVector(const char* x, const char* y, glm::vec2* vt);
	void ArrangeFromIndex(vector<glm::vec3>* vec3, unsigned int index, vector<glm::vec3>* vVec3);
	void ArrangeFromIndex(vector<glm::vec2>* vec2, unsigned int index, vector<glm::vec2>* vVec2);
	void LoadModel(const char* objFile, vector<glm::vec3>* vertices, vector<glm::vec2>* textures, vector<glm::vec3>* normals);
#endif

};
#endif // !_FRAMEBUFFER_HPP_

