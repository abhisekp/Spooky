#include <iostream>
#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>

namespace spooky {
	int WIDTH = 1024;
	int HEIGHT = 576;

	void keyCallback(GLFWwindow*, int, int, int, int);
}

int main(int argc, char *argv[])
{
	if (glfwInit() != GL_TRUE) {
		std::cout << "GLFW Initialization Failed." << std::endl;
		return 0;
	}
	std::cout << "GLFW Initialized Successfully." << std::endl;

	GLFWwindow *window = glfwCreateWindow(spooky::WIDTH, spooky::HEIGHT, "Spooky", nullptr, nullptr);
	if (!window) {
		std::cout << "GLFW Window Creation Failed" << std::endl;
		return 0;
	}
	std::cout << "GLFW Window Creation Successful" << std::endl;
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		std::cout << "GLEW Initialized Failed." << std::endl;
	}
	std::cout << "GLEW Initialized Successfully" << std::endl;

	glfwSetKeyCallback(window, spooky::keyCallback);

	while (glfwWindowShouldClose(window) != GL_TRUE) {
		glfwPollEvents();

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