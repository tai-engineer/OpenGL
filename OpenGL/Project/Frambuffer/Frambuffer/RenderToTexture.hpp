#ifndef _RENDERTOTEXTURE_HPP_
#define _RENDERTOTEXTURE_HPP_

#include "Buffer.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "VertexArray.hpp"
#include "Camera.hpp"
#include "Framebuffer.hpp"
#include "Renderbuffer.hpp"

class RenderToTexture
{

public:
	Shader*			fbProgram;
	Shader*			quadProgram;
	
	VertexArray*	cubeVAO;
	Buffer*			cubeVBO;

	VertexArray*	planeVAO;
	Buffer*			planeVBO;

	VertexArray*	quadVAO;
	Buffer*			quadVBO;

	Texture*		texMarble;
	Texture*		texMetal;

	Framebuffer*	frameBuffer;
	Texture*		texColorBuffer;
	Renderbuffer*	renderBuffer;	

	Camera*			camera;

	bool initShader();
	void setup_application();
	void render();
	Camera* getCameraObj();
	void deleteAll();

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
