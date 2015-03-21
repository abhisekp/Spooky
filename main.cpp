#include <iostream>
#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>

namespace spooky {
	int WIDTH = 1024;
	int HEIGHT = 576;

	void keyCallback(GLFWwindow*, int, int, int, int);
	void positionCallback(GLFWwindow*, int, int);
}

int main(int argc, char *argv[])
{
	// Check GLFW initialization
	if (glfwInit() != GL_TRUE) {
		std::cout << "GLFW Initialization Failed." << std::endl;
		return 0;
	}
	std::cout << "GLFW Initialized Successfully." << std::endl;

	// Set window configurations
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_DECORATED, GL_FALSE);

	// Create a GLFW window
	GLFWwindow *window = glfwCreateWindow(spooky::WIDTH, spooky::HEIGHT, "Spooky", nullptr, nullptr);
	if (!window) {
		std::cout << "GLFW Window Creation Failed" << std::endl;
		return 0;
	}
	std::cout << "GLFW Window Creation Successful" << std::endl;
	// Make the window as current context
	glfwMakeContextCurrent(window);

	// Check GLEW initialization
	if (glewInit() != GLEW_OK) {
		std::cout << "GLEW Initialized Failed." << std::endl;
	}
	std::cout << "GLEW Initialized Successfully" << std::endl;

	// Set key callbacks
	glfwSetKeyCallback(window, spooky::keyCallback);
	// Set the postion callback to make the window immovable
	glfwSetWindowPosCallback(window, spooky::positionCallback);
	// Set the position to center
	spooky::positionCallback(window, 0, 0);

	// loop until closed
	while (glfwWindowShouldClose(window) != GL_TRUE) {
		// poll various kinds of events
		glfwPollEvents();

		// swap front and back buffers
		glfwSwapBuffers(window);
	}

	//glfwTerminate();
	//system("pause");
	return 0;
}

void spooky::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

void spooky::positionCallback(GLFWwindow *window, int xPos, int yPos)
{
	const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	int x = (mode->width - WIDTH) / 2;
	int y = (mode->height - HEIGHT) / 2;
	glfwSetWindowPos(window, x, y);
}