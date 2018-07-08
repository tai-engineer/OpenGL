#include "transform_feedback.h"

const char* vertexSource =
"#version 400\n"
"layout(location = 0) in float inValue;\n"
"out float outValue;\n"
"void main(){\n"
"	outValue = inValue;\n"
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

	/* CREATE SHADER PROGRAM */
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);

	/* FEEDBACK */
	const char* feedbackVarying[] = { "outValue" };
	glTransformFeedbackVaryings(shaderProgram, 1, feedbackVarying, GL_INTERLEAVED_ATTRIBS);

	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	/* VERTEX ARRAY OBJECT */
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	/* DATA */
	GLfloat data[] = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f };

	/* VERTEX BUFFER OBJECT */
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, 0, 0);

	/* FEEDBACK BUFFER */
	GLuint TBO;
	glGenBuffers(1, &TBO);
	glBindBuffer(GL_ARRAY_BUFFER, TBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), NULL, GL_STATIC_READ);

	/* MAIN LOOP */
	while (!glfwWindowShouldClose(window)) {
		_update_fps_counter(window);

		glEnable(GL_RASTERIZER_DISCARD); // Disable rasterizer
		glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, TBO);

		glBeginTransformFeedback(GL_POINTS);
		glDrawArrays(GL_POINTS, 0, 5);
		glEndTransformFeedback();
		
		glFlush();

		/* GET DATA */
		GLfloat feedback[5];
		glGetBufferSubData(GL_TRANSFORM_FEEDBACK_BUFFER, 0, sizeof(feedback), feedback);
		printf("%f %f %f %f %f\n", feedback[0], feedback[1], feedback[2], feedback[3], feedback[4]);

		glfwPollEvents();

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
	}
	// close GL context and any other GLFW resources

	glfwTerminate();
	return 0;
}
