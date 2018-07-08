#include "main.h"

const char* vertexSource =
"#version 400\n"
"layout(location = 0) in vec3 aPos;\n"
"layout(location = 1) in vec2 aTexCoord;\n"
"layout(location = 2) in vec3 aTexColor;\n"
"uniform mat4 MVP;\n"
"out vec2 texCoord;\n"
"out vec3 texColor;\n"
"void main(){\n"
"	gl_Position = MVP * vec4(aPos, 1.0);\n"
"	texCoord = aTexCoord;\n"
"	texColor = aTexColor;\n"
"}\n";

const char* fragmentSource =
"#version 400\n"
"in vec2 texCoord;\n"
"in vec3 texColor;\n"
"out vec4 color;\n"
"uniform sampler2D ourTexture;\n"
"void main(){\n"
//"	color = vec4(0.5, 0.0, 0.0, 1.0);\n"
"	color = texture(ourTexture, texCoord) * vec4(texColor, 1.0);\n"
"}\n";

void init_window(const char* name, GLuint major, GLuint minnor, GLuint width, GLuint height) {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minnor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	window = glfwCreateWindow(windowWidth, windowHeight, name, NULL, NULL);
}

void get_version() {
	const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString(GL_VERSION); // version as a string
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);
}

void _update_fps_counter(GLFWwindow* window)
{
	static double previousSeconds = glfwGetTime();
	static int frameCount = 0;
	double currentSeconds = glfwGetTime();
	double elapsedSeconds = currentSeconds - previousSeconds;
	if (elapsedSeconds > 0.25) {
		previousSeconds = currentSeconds;
		double fps = (double)frameCount / elapsedSeconds;
		char tmp[128];
		sprintf(tmp, "opengl @ fps: %.2f", fps);
		glfwSetWindowTitle(window, tmp);
		frameCount = 0;
	}
	frameCount++;
}

int main() {
	// start GL context and O/S window using the GLFW helper library
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		return 1;
	}

	init_window("Projection Matrix", 3, 2, windowWidth, windowHeight);
	if (!window) {
		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	// get version info
	get_version();

	// tell GL to only draw onto a pixel if the shape is closer to the viewer
	glEnable(GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

	GLfloat square_vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  1.0f, 0.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.5f, 0.5f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.5f, 0.5f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.5f, 0.5f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.5f, 0.5f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.5f, 0.0f, 0.5f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,  0.5f, 0.0f, 0.5f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.5f, 0.0f, 0.5f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.5f, 0.0f, 0.5f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.5f, 0.0f, 0.5f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.5f, 0.0f, 0.5f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.5f, 0.5f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f, 0.5f, 0.5f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f, 0.5f, 0.5f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f, 0.5f, 0.5f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 0.5f, 0.5f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f, 0.5f, 0.5f
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

	camera = new Camera();
	camera->setProjection(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	camera->setModel(1.0f);
	camera->setView(
		glm::vec3(0.0f, 2.0f, 3.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(1.0f, 0.0f, 0.0f)
	);

	glm::mat4 MVP = camera->projection * camera->view * camera->model;

	vertexShader = new Shader();
	vertexShader->createShader(GL_VERTEX_SHADER, vertexSource);
	vertexShader->compile();
	if (!vertexShader->getID()) {
		return 0;
	}

	fragmentShader = new Shader();
	fragmentShader->createShader(GL_FRAGMENT_SHADER, fragmentSource);
	fragmentShader->compile();
	if (!fragmentShader->getID()) {
		return 0;
	}

	shaderProgram = new Shader();
	shaderProgram->createProgram(vertexShader->getID(), fragmentShader->getID());
	if (!shaderProgram->getID())
	{
		return 0;
	}

	/* DELETE SHADER AFTER LINKING */
	vertexShader->deleteShader();
	fragmentShader->deleteShader();

	/* UNIFORM LOCATION */
	glUseProgram(shaderProgram->getID());
	GLint mvpLocation = glGetUniformLocation(shaderProgram->getID(), "MVP");

	/* VERTEX ARRAY OBJECT */
	vao = new VertexArray;
	glBindVertexArray(vao->getID());

	/* VERTEX BUFFER OBJECT */
	bufSquare = new Buffer();
	glBindBuffer(GL_ARRAY_BUFFER, bufSquare->getID());
	glBufferData(GL_ARRAY_BUFFER, sizeof(square_vertices), square_vertices, GL_STATIC_DRAW);

	glBindVertexArray(0);
	/* TEXTURE */
	texContainer = new Texture();
	texContainer->load("container.jpg");

	angle = 1.0;
	while (!glfwWindowShouldClose(window)) {
		_update_fps_counter(window);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, windowWidth, windowHeight);

		glUseProgram(shaderProgram->getID());

		glBindVertexArray(vao->getID());
		glBindTexture(GL_TEXTURE_2D, texContainer->getID());

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));

		glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(MVP));

		glDrawArrays(GL_TRIANGLES, 0, 36);

		glfwSwapBuffers(window);
		glfwPollEvents();

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
	}
	// close GL context and any other GLFW resources
	bufSquare->deleteBuffer();
	texContainer->deleteTexture();
	vao->deleteVertexArray();
	shaderProgram->deleteProgram();

	glfwTerminate();
	return 0;
}
