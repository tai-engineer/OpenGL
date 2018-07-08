#ifndef _CUBEMAP_H_
#define _CUBEMAP_H_

#include <vector>
#include <string>
#include <list>

#define GLEW_STATIC
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

/* User define class*/
#include "Shader.hpp"
#include "Buffer.hpp"
#include "VertexArray.hpp"
#include "Texture.hpp"
#include "Camera.hpp"

using namespace std;

#define D_WIDTH		1024
#define D_HEIGHT	1280

class Cubemap
{
	public:
		Camera* objCamera = NULL;

		GLuint windowWidth = D_WIDTH;
		GLuint windowHeight = D_HEIGHT;

		list<Shader*> shaderList;
		list<Texture*> texList;
		list<VertexArray*> vArrayList;
		list<Buffer*> bufList;

		unsigned int shaderCount = 0;
		unsigned int texCount = 0;
		unsigned int vArrayCount = 0;
		unsigned int bufCount = 0;

		Texture* woodenBox;
		Texture* skyBox;

		Shader* woodenBoxProgram;
		Buffer* woodenBoxVBO;
		VertexArray* woodenBoxVAO;

		Shader* skyBoxProgram;
		Buffer* skyBoxVBO;
		VertexArray* skyBoxVAO;

		void setCameraObj(glm::vec3 value);
		Camera* getCameraObj();

		bool initShader();
		void setup_application();
		void render();
		void deleteAll();

		void loadTexture();
		void addShader(Shader* shader);
		void addTexture(Texture* texture);
		void addVertexArray(VertexArray* vArray);
		void addBuffer(Buffer* buffer);
		//void processInput(GLFWwindow *window, Camera* camera, float deltaTime);
	private:
		
		/*void loadTexture();
		void addShader(Shader* shader);
		void addTexture(Texture* texture);
		void addVertexArray(VertexArray* vArray);
		void addBuffer(Buffer* buffer);
		void processInput(GLFWwindow *window, Camera* camera, float deltaTime);*/
};
#endif
