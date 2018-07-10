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

	ObjMng*	objMng;
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
};
#endif // !_FRAMEBUFFER_HPP_

