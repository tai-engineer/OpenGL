#include "RenderToTexture.hpp"


static float cubeVertices[] = {
	// positions          // texture Coords
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
static float planeVertices[] = {
	// positions          // texture Coords 
	5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
	-5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
	-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

	5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
	-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
	5.0f, -0.5f, -5.0f,  2.0f, 2.0f
};
static float quadVertices[] =
{ 
	// positions   // texCoords
	-1.0f,  1.0f,  0.0f, 1.0f,
	-1.0f, -1.0f,  0.0f, 0.0f,
	1.0f, -1.0f,  1.0f, 0.0f,

	-1.0f,  1.0f,  0.0f, 1.0f,
	1.0f, -1.0f,  1.0f, 0.0f,
	1.0f,  1.0f,  1.0f, 1.0f
};

bool RenderToTexture::initShader()
{
	fbProgram = NULL;
	quadProgram = NULL;

	fbProgram = new Shader("framebuffer.vsh", "framebuffer.fsh");
	if (!fbProgram)
	{
		printf("Failed to create framebuffer program.\r\n");
		return false;
	}

	quadProgram = new Shader("quad.vsh", "quad.fsh");
	if (!quadProgram)
	{
		printf("Failed to create quad program.\r\n");
		return false;
	}
	return true;
}

void RenderToTexture::setupApplication()
{
	Width = 840;
	Height = 480;

	setCameraObj(glm::vec3(0.0f, 0.0f, 3.0f));
	setupVAO();
	setupFBO();
	loadTexture();

	objMng->print();
}

void RenderToTexture::loadTexture()
{
	objMng->create<Texture>(&texMarble, "Texture");
	objMng->create<Texture>(&texMetal, "Texture");

	texMarble->load("Textures/marble.jpg");
	texMetal->load("Textures/metal.png");
}

void RenderToTexture::render()
{
	renderTexture();
	renderScene();
}

void RenderToTexture::setupVAO()
{
	objMng		= NULL;
	cubeVAO		= NULL;
	cubeVBO		= NULL;
	planeVAO	= NULL;
	planeVBO	= NULL;
	quadVAO		= NULL;
	quadVBO		= NULL;

	objMng = new ObjMng();

	objMng->create<VertexArray>(&cubeVAO, "VertexArray");
	objMng->create<Buffer>(&cubeVBO, "Buffer");

	objMng->create<VertexArray>(&planeVAO, "VertexArray");
	objMng->create<Buffer>(&planeVBO, "Buffer");

	objMng->create<VertexArray>(&quadVAO, "VertexArray");
	objMng->create<Buffer>(&quadVBO, "Buffer");

	glBindVertexArray(cubeVAO->getID());
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO->getID());
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glBindVertexArray(planeVAO->getID());
	glBindBuffer(GL_ARRAY_BUFFER, planeVBO->getID());
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glBindVertexArray(quadVAO->getID());
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO->getID());
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
		printf("Failed to setup VAO");
}

void RenderToTexture::setupFBO()
{
	frameBuffer		= NULL;
	texColorBuffer	= NULL;
	renderBuffer	= NULL;

	objMng->create<FrameBuffer>(&frameBuffer, "FrameBuffer");
	objMng->create<Texture>(&texColorBuffer, "Texture");
	objMng->create<RenderBuffer>(&renderBuffer, "RenderBuffer");
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer->getID());

	glBindTexture(GL_TEXTURE_2D, texColorBuffer->getID());
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer->getID(), 0);

	glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer->getID());
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Width, Height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer->getID());

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		printf("Framebuffer is not complete!\r\n");

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RenderToTexture::renderTexture()
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer->getID());
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, Width, Height);

	fbProgram->use();
	glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 View = camera->GetViewMatrix();
	glm::mat4 Projection = glm::perspective(glm::radians(camera->Zoom), (float)Width / (float)Height, 0.1f, 100.0f);
	fbProgram->setMat4("View", View);
	fbProgram->setMat4("Projection", Projection);

	glBindVertexArray(cubeVAO->getID());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texMarble->getID());

	Model = glm::translate(Model, glm::vec3(-1.0f, 0.0f, -1.0f));
	fbProgram->setMat4("Model", Model);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	Model = glm::mat4(1.0f);
	Model = glm::translate(Model, glm::vec3(2.0f, 0.0f, 0.0f));
	fbProgram->setMat4("Model", Model);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindVertexArray(planeVAO->getID());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texMetal->getID());
	Model = glm::mat4(1.0f);
	fbProgram->setMat4("Model", Model);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST);
}

void RenderToTexture::renderScene()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, Width, Height);
	quadProgram->use();
	glBindVertexArray(quadVAO->getID());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texColorBuffer->getID());
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void RenderToTexture::setCameraObj(glm::vec3 value)
{
	camera = new Camera(value);
}

Camera* RenderToTexture::getCameraObj()
{
	return camera;
}

void RenderToTexture::deleteApplication()
{
	fbProgram->deleteProgram();
	quadProgram->deleteProgram();

	objMng->deleteAll();

	delete objMng;
	delete camera;
}