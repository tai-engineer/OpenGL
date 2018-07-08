#define GLEW_STATIC
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

const char* vertexSource =
"#version 400\n"
"layout(location = 0) in vec3 aPos;\n"
"layout(location = 1) in vec2 aTexCoord;\n"
"out vec2 texCoord;\n"
"void main(){\n"
"	gl_Position = vec4(aPos, 1.0);\n"
"	texCoord = aTexCoord;\n"
"}\n";

const char* fragmentSource =
"#version 400\n"
"in vec2 texCoord;\n"
"out vec4 color;\n"
"uniform sampler2D ourTexture;\n"
"void main(){\n"
//"	color = vec4(0.5, 0.0, 0.0, 1.0);\n"
"	color = texture(ourTexture, texCoord);\n"
"}\n";

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

GLuint create_shader(GLenum target, const char* source) {
	GLuint program = glCreateShader(target);
	glShaderSource(program, 1, &source, NULL);
	glCompileShader(program);

	GLint status = 0;
	char compileLog[512];
	glGetShaderiv(program, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE) {
		glGetShaderInfoLog(program, 512, NULL, compileLog);
		printf("[ERROR] Failed to compile shader:\n\r%s", compileLog);
		return GL_FALSE;
	}

	return program;
}

GLuint create_program(GLuint vertex, GLuint fragment) {
	GLuint program = glCreateProgram();
	glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	glLinkProgram(program);

	GLint success;
	GLchar infoLog[512];

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		printf("[ERROR] Failed to link program.\n");
		return GL_FALSE;
	}

	return program;
}

GLuint create_texture(){
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, channels;
	unsigned char *data = stbi_load("container.jpg", &width, &height, &channels, 0);
	if (data) 
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	else
	{
		printf("[ERROR] Failed to load texture.");
	}

	stbi_image_free(data);

	glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
}

int main() {
	GLuint windowHeight = 800;
	GLuint windowWidth = 600;

	// start GL context and O/S window using the GLFW helper library
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Hello Triangle", NULL, NULL);
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
	const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString(GL_VERSION); // version as a string
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);

	// tell GL to only draw onto a pixel if the shape is closer to the viewer
	glEnable(GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

	/* OTHER STUFF GOES HERE NEXT */
	GLfloat square_vertices[] = {
		 0.5f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
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

	GLuint vertexShader = create_shader(GL_VERTEX_SHADER, vertexSource);
	if (vertexShader == GL_FALSE)
	{
		return 0;
	}

	GLuint fragmentShader = create_shader(GL_FRAGMENT_SHADER, fragmentSource);
	if (fragmentShader == GL_FALSE)
	{
		return 0;
	}

	GLuint shaderProgram = create_program(vertexShader, fragmentShader);
	if (shaderProgram == GL_FALSE)
	{
		return 0;
	}

	/* DELETE SHADER AFTER LINKING */
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	/* VERTEX ARRAY OBJECT */
	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	/* VERTEX BUFFER OBJECT */
	GLuint square_vbo = 0;
	glGenBuffers(1, &square_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, square_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(square_vertices), square_vertices, GL_STATIC_DRAW);

	GLuint square_ebo = 0;
	glGenBuffers(1, &square_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, square_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(square_indices), square_indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
	/* TEXTURE */
	GLuint container_text = create_texture();

	while(!glfwWindowShouldClose(window)) {
		_update_fps_counter(window);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, windowWidth, windowHeight);

		glUseProgram(shaderProgram);

		glBindVertexArray(vao);
		glBindTexture(GL_TEXTURE_2D, container_text);
		
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwPollEvents();
		glfwSwapBuffers(window);

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
	}
	// close GL context and any other GLFW resources
	glDeleteBuffers(1, &square_vbo);
	glDeleteBuffers(1, &square_ebo);

	glDeleteTextures(1, &container_text);

	glDeleteVertexArrays(1, &vao);

	glDeleteProgram(shaderProgram);

	glfwTerminate();
	return 0;
}
