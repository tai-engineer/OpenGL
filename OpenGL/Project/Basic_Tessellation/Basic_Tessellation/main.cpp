#include "main.h"

#define TEST

const int Faces[] = {
	2, 1, 0,
	3, 2, 0,
	4, 3, 0,
	5, 4, 0,
	1, 5, 0,

	11, 6,  7,
	11, 7,  8,
	11, 8,  9,
	11, 9,  10,
	11, 10, 6,

	1, 2, 6,
	2, 3, 7,
	3, 4, 8,
	4, 5, 9,
	5, 1, 10,

	2,  7, 6,
	3,  8, 7,
	4,  9, 8,
	5, 10, 9,
	1, 6, 10 };

const float Verts[] = {
	0.000f,  0.000f,  1.000f,
	0.894f,  0.000f,  0.447f,
	0.276f,  0.851f,  0.447f,
	-0.724f,  0.526f,  0.447f,
	-0.724f, -0.526f,  0.447f,
	0.276f, -0.851f,  0.447f,
	0.724f,  0.526f, -0.447f,
	-0.276f,  0.851f, -0.447f,
	-0.894f,  0.000f, -0.447f,
	-0.276f, -0.851f, -0.447f,
	0.724f, -0.526f, -0.447f,
	0.000f,  0.000f, -1.000f };

const float TriVertices[] =
{
	0.0f, 1.0f, 0.0f,
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
};

const float TriColor[]
{
	1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f
};

const unsigned int IndexCount = sizeof(Faces) / sizeof(Faces[0]);

std::string ReadFromFile(const char* path)
{
	std::string str_shaderCode;
	std::ifstream shaderFile;
	std::stringstream shaderStream;
	try
	{
		shaderFile.open(path);
		shaderStream << shaderFile.rdbuf();
		shaderFile.close();

		str_shaderCode = shaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		printf("[ERROR] Cannot read shader file.");
	}

	return str_shaderCode;
}
GLuint create_shader(GLenum target, const char* source)
{
	GLuint program = glCreateShader(target);
	std::string src_string = ReadFromFile(source);
	const char* src = src_string.c_str();
	glShaderSource(program, 1, &src, NULL);
	glCompileShader(program);

	GLint status;
	char log[512];
	glGetShaderiv(program, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE)
	{
		glGetShaderInfoLog(program, 512, NULL, log);
		printf("[ERROR] Failed to compile shader.\n");
		printf("%s", log);
		return GL_FALSE;
	}

	return program;
}
int main()
{
	if (!glfwInit())
	{
		printf("[ERROR] Count not start GLFW3.\n");
		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(width, height, "Basic Tessellation", NULL, NULL);
	if (!window)
	{
		printf("[ERROR] Count not create window.\n");
		glfwTerminate();
		return 1;
	}

	glfwMakeContextCurrent(window);

	glewInit();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

#if ndef TEST
	GLuint vs = create_shader(GL_VERTEX_SHADER, "vertex_shader.vsh");
#else
	GLuint vs = create_shader(GL_VERTEX_SHADER, "passthrough.vsh");
#endif

#if ndef TEST
	GLuint tcs = create_shader(GL_TESS_CONTROL_SHADER, "tessellation_control_shader.tcs");
	GLuint tes = create_shader(GL_TESS_EVALUATION_SHADER, "tessellation_eval_shader.tes");
#else
	GLuint tcs = create_shader(GL_TESS_CONTROL_SHADER, "passthrough.tcs");
	GLuint tes = create_shader(GL_TESS_EVALUATION_SHADER, "passthrough.tes");
#endif
	GLuint gs = create_shader(GL_GEOMETRY_SHADER, "geometry_shader.gs");
#if ndef TEST
	GLuint fs = create_shader(GL_FRAGMENT_SHADER, "fragment_shader.fsh");
#else
	GLuint fs = create_shader(GL_FRAGMENT_SHADER, "passthrough.fsh");
#endif
	GLuint program = glCreateProgram();
	glAttachShader(program, vs);
#if ndef TEST
	glAttachShader(program, tcs);
	glAttachShader(program, tes);
	glAttachShader(program, gs);
#else
	glAttachShader(program, tcs);
	glAttachShader(program, tes);
#endif
	glAttachShader(program, fs);
	glBindAttribLocation(program, 0, "Position");
	glLinkProgram(program);
	GLint status;
	GLchar log[512];
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status != GL_TRUE)
	{
		glGetProgramInfoLog(program, 512, NULL, log);
		printf("[ERROR] Failed to link program.\n");
		printf("%s", log);
		return 1;
	}

	glUseProgram(program);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint position;
	glGenBuffers(1, &position);
	glBindBuffer(GL_ARRAY_BUFFER, position);
#if ndef TEST
	glBufferData(GL_ARRAY_BUFFER, sizeof(Verts), Verts, GL_STATIC_DRAW);
#else
	glBufferData(GL_ARRAY_BUFFER, sizeof(TriVertices), TriVertices, GL_STATIC_DRAW);
#endif
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
#if defined TEST
	GLuint color;
	glGenBuffers(1, &color);
	glBindBuffer(GL_ARRAY_BUFFER, color);
	glBufferData(GL_ARRAY_BUFFER, sizeof(TriColor), TriColor, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
#endif

#if ndef TEST
	GLuint indices;
	glGenBuffers(1, &indices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Faces), Faces, GL_STATIC_DRAW);
#endif

	GLuint TessLevelInner = 3;
	GLuint TessLevelOuter = 2;

	GLuint locProjection = glGetUniformLocation(program, "Projection");
	GLuint locModelView = glGetUniformLocation(program, "ModelView");
	GLuint locNormalMatrix = glGetUniformLocation(program, "NormalMatrix");
	GLuint locLightPosition = glGetUniformLocation(program, "LightPosition");
	GLuint locAmbientMaterial = glGetUniformLocation(program, "AmbientMaterial");
	GLuint locDiffuseMaterial = glGetUniformLocation(program, "DiffuseMaterial");
	GLuint locTessLevelInner = glGetUniformLocation(program, "TessLevelInner");
	GLuint locTessLevelOuter = glGetUniformLocation(program, "TessLevelOuter");

	glUniform1f(locTessLevelInner, TessLevelInner);
	glUniform1f(locTessLevelOuter, TessLevelOuter);

	glm::vec4 LightPosition = glm::vec4(0.25f, 0.25f, 1.0f, 0.0f);
	glUniform3fv(locLightPosition, 1, glm::value_ptr(LightPosition));

	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
	glUniform4fv(locProjection, 1, glm::value_ptr(Projection));

	glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 View = glm::lookAt(
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 ModelView = View * Model;
	glUniform4fv(locModelView, 1, glm::value_ptr(ModelView));

	glm::mat3 NormalMatrix = glm::mat3(ModelView);
	NormalMatrix = glm::transpose(NormalMatrix);
	float packed[9] = {
		NormalMatrix[0].x, NormalMatrix[1].x, NormalMatrix[2].x,
		NormalMatrix[0].y, NormalMatrix[1].y, NormalMatrix[2].y,
		NormalMatrix[0].z, NormalMatrix[1].z, NormalMatrix[2].z,
	};
	glUniform3fv(locNormalMatrix, 1, &packed[0]);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPatchParameteri(GL_PATCH_VERTICES, 3);
		glUniform3f(locAmbientMaterial, 0.04f, 0.04f, 0.04f);
		glUniform3f(locDiffuseMaterial, 0.0f, 0.75f, 0.75f);
#if ndef TEST
		glDrawElements(GL_PATCHES, IndexCount, GL_UNSIGNED_INT, 0);
#else
		glDrawArrays(GL_PATCHES, 0, 3);
#endif
		glfwSwapBuffers(window);
		glfwPollEvents();

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
	}
}
