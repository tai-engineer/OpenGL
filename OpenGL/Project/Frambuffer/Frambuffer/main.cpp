#include "main.h"

#define D_WIDTH		840
#define D_HEIGHT	480

static double lastX = (float)D_WIDTH / 2.0;
static double lastY = (float)D_HEIGHT / 2.0;
static bool firstMouse = true;

static float deltaTime = 0.0f;
static float lastFrame = 0.0f;

GLFWwindow* window;

RenderToTexture* renderToTexture = NULL;

int main() {
	GLuint windowWidth = D_WIDTH;
	GLuint windowHeight = D_HEIGHT;

	renderToTexture = new RenderToTexture();

	// start GL context and O/S window using the GLFW helper library
	if (!glfwInit()) {
		printf("[ERROR] Could not start GLFW3.\r\n");
		return false;
	}

	/* SETUP CONTEXT, WINDOW */
	createWindow(window, "RenderToTexture", 3, 2, windowWidth, windowHeight);
	if (!window)
		return false;

	// tell GL to only draw onto a pixel if the shape is closer to the viewer
	glEnable(GL_DEPTH_TEST); // enable depth-testing

	/* INIT SHADER */
	if (!renderToTexture->initShader())
		return false;

	/* SETUP APPLICATION */
	renderToTexture->setupApplication();

	while (!glfwWindowShouldClose(window)) 
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		/* CAPTURE INPUT */
		processInput(window, renderToTexture->getCameraObj(), deltaTime);
		
		/* RENDER */
		renderToTexture->render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// close GL context and any other GLFW resources
	renderToTexture->deleteApplication();

	glfwTerminate();
	return false;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mouseMoverment(double xoffset, double yoffset)
{
	renderToTexture->getCameraObj()->ProcessMouseMovement(xoffset, yoffset);
}
// glfw: whenever the mouse moves, this callback is called
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	double xoffset = xpos - lastX;
	double yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	mouseMoverment(xoffset, yoffset);
}

void mouseScroll(double yoffset)
{
	renderToTexture->getCameraObj()->ProcessMouseScroll(yoffset);
}
// glfw: whenever the mouse scroll wheel scrolls, this callback is called
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	mouseScroll(yoffset);
}

void createWindow(GLFWwindow*& ptrWindow, const char* name, 
	unsigned int major, unsigned int minnor, 
	unsigned int width, unsigned int height)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minnor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	ptrWindow = glfwCreateWindow(width, height, name, NULL, NULL);
	if (!ptrWindow) {
		printf("[ERROR] Could not open window with GLFW3.\r\n");
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(ptrWindow);
	glfwSetFramebufferSizeCallback(ptrWindow, framebuffer_size_callback);
	glfwSetCursorPosCallback(ptrWindow, mouse_callback);
	glfwSetScrollCallback(ptrWindow, scroll_callback);
	// tell GLFW to capture our mouse
	glfwSetInputMode(ptrWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();
}
void processInput(GLFWwindow *window, Camera* camera, float deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->ProcessKeyboard(RIGHT, deltaTime);
}