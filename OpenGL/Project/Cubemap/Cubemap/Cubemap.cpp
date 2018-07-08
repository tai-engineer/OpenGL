#include "Cubemap.hpp"

static GLfloat cubeVertices[] = {
	/* VERTICES(3)			NORMAL(3)		 */
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

static GLfloat skyBoxVertices[] = {
	// positions          
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	1.0f,  1.0f, -1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	1.0f, -1.0f,  1.0f
};

static std::vector<std::string> faces
{
	"skybox/right.jpg",
	"skybox/left.jpg",
	"skybox/top.jpg",
	"skybox/bottom.jpg",
	"skybox/front.jpg",
	"skybox/back.jpg",
};

void Cubemap::setCameraObj(glm::vec3 value)
{
	objCamera = new Camera(value);
}

Camera* Cubemap::getCameraObj()
{
	return objCamera;
}
bool Cubemap::initShader()
{
	/* WOODEN BOX PROGRAM */
	woodenBoxProgram = NULL;
	woodenBoxProgram = new Shader("Woodenbox.vsh", "Woodenbox.fsh");
	if (!woodenBoxProgram)
	{
		printf("Failed to create woodenBoxProgram.\r\n");
		return false;
	}

	/* SKY BOX PROGRAM */
	skyBoxProgram = NULL;
	skyBoxProgram = new Shader("Skybox.vsh", "Skybox.fsh");
	if (!skyBoxProgram)
	{
		printf("Failed to create skyBoxProgram.\r\n");
		return false;
	}

	return true;
}
void Cubemap::setup_application()
{
	setCameraObj(glm::vec3(0.0f, 0.0f, 3.0f));
	/* WOODEN BOX SETUP */
	woodenBoxVBO = NULL;
	woodenBoxVAO = NULL;
	woodenBox = new Texture();
	woodenBoxVAO = new VertexArray;
	woodenBoxVBO = new Buffer();
	glBindVertexArray(woodenBoxVAO->getID());
	glBindBuffer(GL_ARRAY_BUFFER, woodenBoxVBO->getID());
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	/* SKY BOX SETUP */
	skyBoxVBO = NULL;
	skyBoxVAO = NULL;
	skyBox = new Texture();
	skyBoxVAO = new VertexArray;
	skyBoxVBO = new Buffer();
	glBindVertexArray(skyBoxVAO->getID());
	glBindBuffer(GL_ARRAY_BUFFER, skyBoxVBO->getID());
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyBoxVertices), &skyBoxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	/* COLLECT DATA */
	addShader(woodenBoxProgram);
	addShader(skyBoxProgram);
	addTexture(woodenBox);
	addTexture(skyBox);
	addVertexArray(woodenBoxVAO);
	addVertexArray(skyBoxVAO);
	addBuffer(woodenBoxVBO);
	addBuffer(skyBoxVBO);
}
void Cubemap::render()
{
	/* CLEAN WINDOW */
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, windowWidth, windowHeight);

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = objCamera->GetViewMatrix();
	glm::mat4 projection = glm::perspective(glm::radians(objCamera->Zoom), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);

	/* WOODEN BOX PROGRAM */
	woodenBoxProgram->use();
	woodenBoxProgram->setInt("skyBox", 0);
	woodenBoxProgram->setMat4("Projection", projection);
	woodenBoxProgram->setMat4("View", view);
	woodenBoxProgram->setMat4("Model", model);
	woodenBoxProgram->setVec3("cameraPos", objCamera->Position); printf("Position: x=%f, y=%f, z=%f\r\n", objCamera->Position.x, objCamera->Position.y, objCamera->Position.z);
	glBindVertexArray(woodenBoxVAO->getID());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyBox->getID());
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	/* SKY BOX PROGRAM */
	glDepthFunc(GL_LEQUAL);
	skyBoxProgram->use();
	skyBoxProgram->setInt("skybox", 0);
	skyBoxProgram->setMat4("Projection", projection);
	view = glm::mat4(glm::mat3(objCamera->GetViewMatrix()));
	skyBoxProgram->setMat4("View", view);
	glBindVertexArray(skyBoxVAO->getID());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyBox->getID());
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS);
}
void Cubemap::deleteAll()
{
	for (std::list<Shader*>::iterator it = shaderList.begin(); it != shaderList.end(); it++)
	{
		(*it)->deleteProgram();
		delete (*it);
	}
	for (std::list<Texture*>::iterator it = texList.begin(); it != texList.end(); it++)
	{
		(*it)->deleteTexture();
		delete (*it);
	}
	for (std::list<VertexArray*>::iterator it = vArrayList.begin(); it != vArrayList.end(); it++)
	{
		(*it)->deleteVertexArray();
		delete (*it);
	}
	for (std::list<Buffer*>::iterator it = bufList.begin(); it != bufList.end(); it++)
	{
		(*it)->deleteBuffer();
		delete (*it);
	}
}

void Cubemap::loadTexture()
{
	/* WOODEN BOX */
	woodenBox->load("wooden_box.png");

	/* CUBEMAP */
	skyBox->loadCubeMap(faces);
}
void Cubemap::addShader(Shader* shader)
{
	shaderList.push_back(shader);
	shaderCount++;
}
void Cubemap::addTexture(Texture* texture)
{
	texList.push_back(texture);
	texCount++;
}
void Cubemap::addVertexArray(VertexArray* vArray)
{
	vArrayList.push_back(vArray);
	vArrayCount++;
}
void Cubemap::addBuffer(Buffer* buffer)
{
	bufList.push_back(buffer);
	bufCount++;
}
