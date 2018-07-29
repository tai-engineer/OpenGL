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

#if defined USE_MODEL
	LoadModel("stall.obj", &vertices, &textures, &normals);
#endif

	setupVAO();
	setupFBO();
	loadTexture();

	objMng->print();
}

void RenderToTexture::loadTexture()
{
	objMng->create<Texture>(&texMarble, "Texture");
	objMng->create<Texture>(&texMetal, "Texture");

#if defined USE_MODEL
	texMarble->load("stallTexture.png");
#else
	texMarble->load("Textures/marble.jpg");
#endif
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

#if defined USE_MODEL
	objMng->create<Buffer>(&vertexVBO, "Buffer");
	objMng->create<Buffer>(&uvVBO, "Buffer");
#endif

	glBindVertexArray(cubeVAO->getID());
#if defined USE_MODEL
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO->getID());
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvVBO->getID());
	glBufferData(GL_ARRAY_BUFFER, textures.size() * sizeof(glm::vec3), &textures[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
#else
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO->getID());
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
#endif

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
#if defined USE_MODEL
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
#else
	glDrawArrays(GL_TRIANGLES, 0, 36);
#endif

#if ndefined USE_MODEL
	Model = glm::mat4(1.0f);
	Model = glm::translate(Model, glm::vec3(2.0f, 0.0f, 0.0f));
	fbProgram->setMat4("Model", Model);
	glDrawArrays(GL_TRIANGLES, 0, 36);
#endif

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

#if defined USE_MODEL
vector<string> RenderToTexture::split(const string str, const char &delimiter)
{
	string::const_iterator iter;
	iter = str.begin();
	vector<string> token;

	while (iter != str.end())
	{
		string::const_iterator tmp_iter;
		tmp_iter = find(iter, str.end(), delimiter);
		token.push_back(string(iter, tmp_iter));
		iter = tmp_iter;
		if (iter != str.end())
			iter++;
	}
	return token;
}

void RenderToTexture::ParseToVector(const char* x, const char* y, const char* z, glm::vec3* vt)
{
	vt->x = stof(x);
	vt->y = stof(y);
	vt->z = stof(z);
}

void RenderToTexture::ParseToVector(const char* x, const char* y, glm::vec2* vt)
{
	vt->x = stof(x);
	vt->y = stof(y);
}

void RenderToTexture::ArrangeFromIndex(vector<glm::vec3>* vec3, unsigned int index, vector<glm::vec3>* vVec3)
{
	glm::vec3 tmp_vec3;
	tmp_vec3 = vec3->at(index - 1);
	vVec3->push_back(tmp_vec3);
}

void RenderToTexture::ArrangeFromIndex(vector<glm::vec2>* vec2, unsigned int index, vector<glm::vec2>* vVec2)
{
	glm::vec2 tmp_vec2;
	tmp_vec2 = vec2->at(index - 1);
	vVec2->push_back(tmp_vec2);
}

void RenderToTexture::LoadModel(const char* objFile, vector<glm::vec3>* vertices, vector<glm::vec2>* textures, vector<glm::vec3>* normals)
{
	string currentLine;
	vector<string> token;
	vector<glm::vec3> vVertice;
	vector<glm::vec2> vTexture;
	vector<glm::vec3> vNormal;

	glm::vec3 vertex;
	glm::vec2 texture;
	glm::vec3 normal;

	unsigned int vertexIndex;
	unsigned int textureIndex;
	unsigned int normalIndex;

	vector<string> faceSplit;

	ifstream fr(objFile);
	if (!fr.is_open())
	{
		printf("[ERROR] Cannot read file %s!\r\n", objFile);
		fr.close();
		return;
	}

	while (getline(fr, currentLine))
	{
		//printf("%s\r\n", currentLine.c_str());

		token = split((const string)currentLine, ' ');
		const char* first = token.at(0).c_str();
		if (strcmp(first, "v") == 0)
		{
			vertex.x = stof(token.at(1).c_str());
			vertex.y = stof(token.at(2).c_str());
			vertex.z = stof(token.at(3).c_str());
			//ParseToVector(token.at(1).c_str(), token.at(2).c_str(), token.at(3).c_str(), &vertex);
			vVertice.push_back(vertex);
		}
		else if (strcmp(first, "vt") == 0)
		{
			texture.x = stof(token.at(1).c_str());
			texture.y = stof(token.at(2).c_str());
			//ParseToVector(token.at(1).c_str(), token.at(2).c_str(), &texture);
			vTexture.push_back(texture);
		}
		else if (strcmp(first, "vn") == 0)
		{
			normal.x = stof(token.at(1).c_str());
			normal.y = stof(token.at(2).c_str());
			normal.z = stof(token.at(3).c_str());
			//ParseToVector(token.at(1).c_str(), token.at(2).c_str(), token.at(3).c_str(), &normal);
			vNormal.push_back(normal);
		}
		else if (strcmp(first, "f") == 0)
		{
			for (short numString = 1; numString <= 3; numString++)
			{
				faceSplit = split((const string)token.at(numString), '/');

				vertexIndex = stoi(faceSplit.at(0).c_str());
				glm::vec3 tmpVertex = vVertice.at(vertexIndex - 1);
				vertices->push_back(tmpVertex);
				//ArrangeFromIndex(&vVertice, vertexIndex, vertices);
				//printf("vertex: %f\t %f\t %f\r\n", vertices->at(vertices->size() - 1).x, vertices->at(vertices->size() - 1).y, vertices->at(vertices->size() - 1).z);

				textureIndex = stoi(faceSplit.at(1).c_str());
				glm::vec2 tmpTexture = vTexture.at(textureIndex - 1);
				textures->push_back(tmpTexture);
				//ArrangeFromIndex(&vTexture, textureIndex, textures);
				//printf("texture: %f\t %f\r\n", textures->at(textures->size() - 1).x, textures->at(textures->size() - 1).y);

				normalIndex = stoi(faceSplit.at(2).c_str());
				glm::vec3 tmpNormal = vNormal.at(normalIndex - 1);
				normals->push_back(tmpNormal);
				//ArrangeFromIndex(&vNormal, normalIndex, normals);
				//printf("normaln: %f\t %f\t %f\r\n", normals->at(normals->size() - 1).x, normals->at(normals->size() - 1).y, normals->at(normals->size() - 1).z);
			}
		}
	}
	fr.close();
}
#endif