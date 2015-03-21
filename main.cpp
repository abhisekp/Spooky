#include <iostream>
#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>

namespace spooky {
	int WIDTH = 1024;
	int HEIGHT = 576;
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

	while (glfwWindowShouldClose(window) != GL_TRUE) {
		glfwPollEvents();

		glfwSwapBuffers(window);
	}

	glfwTerminate();
	system("pause");
	return 0;
}