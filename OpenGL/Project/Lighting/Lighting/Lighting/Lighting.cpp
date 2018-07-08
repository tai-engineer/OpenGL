#include "Lighting.h"

#define PI 3.14

glm::vec3 objCameraPos = glm::vec3(0.0f, 1.0f, 3.0f);
glm::vec3 lightPos(0.0f, 0.0f, 1.4f);

GLfloat square_vertices[] = {
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

GLfloat texCoord[] = {
	1.0f, 1.0f,
	1.0f, 0.0f,
	0.0f, 0.0f,
	0.0f, 1.0f
};

GLuint square_indices[] = {
	0, 1, 3,
	1, 2, 3
};

int main() {
	GLFWwindow* window				= NULL;
	GLuint windowWidth				= D_WIDTH;
	GLuint windowHeight				= D_HEIGHT;

	Shader* lightingShaderProgram	= NULL;
	Shader* lampShaderProgram		= NULL;

	Buffer* bufSquare				= NULL;
	VertexArray* vao				= NULL;

	Camera* objCamera				= NULL;
	Camera* lampCamera				= NULL;
	

	GLfloat angle = 0.0f;

	// start GL context and O/S window using the GLFW helper library
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		return 1;
	}

	window = init_window("Lighting", 3, 2, windowWidth, windowHeight);
	if (!window) {
		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	// tell GL to only draw onto a pixel if the shape is closer to the viewer
	glEnable(GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

	// init camera properties
	objCamera = new Camera();
	lampCamera = new Camera();
	init_camera(objCamera, lampCamera);

	/* LIGHTING MODEL*/
	lightingShaderProgram = new Shader("Lighting.vsh", "Lighting.fsh");
	if (!lightingShaderProgram)
	{
		return 0;
	}

	/* LAMP SHADER */
	lampShaderProgram = new Shader("Lamp.vsh", "Lamp.fsh");
	if (!lampShaderProgram)
	{
		return 0;
	}

	/* VERTEX ARRAY OBJECT */
	vao = new VertexArray;
	glBindVertexArray(vao->getID());

	/* VERTEX BUFFER OBJECT */
	bufSquare = new Buffer();
	glBindBuffer(GL_ARRAY_BUFFER, bufSquare->getID());
	glBufferData(GL_ARRAY_BUFFER, sizeof(square_vertices), square_vertices, GL_STATIC_DRAW);

	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window)) 
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, windowWidth, windowHeight);

		/* LIGHTING PROGRAM */
		lightingShaderProgram->use();
		glBindVertexArray(vao->getID());

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

		lightingShaderProgram->setMat4("Projection", objCamera->getProjection());
		lightingShaderProgram->setMat4("View", objCamera->getView());
		lightingShaderProgram->setMat4("Model", objCamera->getModel());

		lightingShaderProgram->setVec3("viewPos", objCameraPos);

		lightingShaderProgram->setVec3("objectColor", 1.0f, 0.5f, 0.31f);
		lightingShaderProgram->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
		lightingShaderProgram->setVec3("lightPos", lightPos);

		lightingShaderProgram->setVec3("light.position", lightPos);
		lightingShaderProgram->setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
		lightingShaderProgram->setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
		lightingShaderProgram->setVec3("light.specular", 1.0f, 1.0f, 1.0f);

		lightingShaderProgram->setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
		lightingShaderProgram->setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
		lightingShaderProgram->setVec3("material.specular", 0.5f, 0.5f, 0.5f);
		lightingShaderProgram->setFloat("material.shininess", 32.0f);

		glDrawArrays(GL_TRIANGLES, 0, 36);

		/* ROTATE LIGHT SOURCE */
		GLfloat radius = 10.0;
		GLfloat camY = cos(angle * 3.14f / 180.0f) * radius; //printf("camY: %f\t", camY);
		GLfloat camZ = sin(angle * 3.14f / 180.0f) * radius + 13.0f; //printf("camZ: %f\n\r", camZ);
		lampCamera->setView(
			glm::vec3(0.0f, camY, camZ),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f)
		);

		lightPos.y = cos(angle * PI / 180.0f) * -1.0f;
		lightPos.z = sin(angle * PI / 180.0f) * -1.0f;

		angle += 0.2f;
		if (angle >= 360.0) {
			angle = 0.0;
		}

		lampShaderProgram->use();
		glBindVertexArray(vao->getID());

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

		lampShaderProgram->setMat4("Projection", lampCamera->getProjection());
		lampShaderProgram->setMat4("View", lampCamera->getView());
		lampShaderProgram->setMat4("Model", lampCamera->getModel());

		glDrawArrays(GL_TRIANGLES, 0, 36);

		glfwSwapBuffers(window);
		glfwPollEvents();

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
	}
	// close GL context and any other GLFW resources
	bufSquare->deleteBuffer();
	vao->deleteVertexArray();

	lightingShaderProgram->deleteProgram();
	lampShaderProgram->deleteProgram();

	glfwTerminate();
	return 0;
}

GLFWwindow* init_window(const char* name, GLuint major, GLuint minnor, GLuint width, GLuint height) {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minnor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow *window = glfwCreateWindow(width, height, name, NULL, NULL);
	return window;
}

void init_camera(Camera* objCamera, Camera* lampCamera)
{
	/* LIGHTING OBJECT */
	objCamera->setProjection(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	objCamera->setModel(1.0f);
	objCamera->setView(
		glm::vec3(0.0f, 2.0f, 4.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
	);

	/* LIGHT SOURCE */
	lampCamera->setProjection(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	lampCamera->setModel(glm::translate(objCamera->getModel(), lightPos));
	lampCamera->setModel(glm::scale(lampCamera->getModel(), glm::vec3(0.3f)));
	objCamera->setView(
		glm::vec3(0.0f, 2.0f, 4.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
	);
}