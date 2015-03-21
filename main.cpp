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
		std::cout << "GLFW Initialization failed." << std::endl;
		return 0;
	}
	std::cout << "GLFW Successfully Initialized." << std::endl;

	GLFWwindow *window = glfwCreateWindow(spooky::WIDTH, spooky::HEIGHT, "Spooky", nullptr, nullptr);
	if (!window) {
		std::cout << "GLFW window couldn't be created." << std::endl;
		return 0;
	}
	std::cout << "GLFW window Successfully created." << std::endl;
	glfwMakeContextCurrent(window);

	while (glfwWindowShouldClose(window) != GL_TRUE) {
		glfwPollEvents();

		glfwSwapBuffers(window);
	}

	glfwTerminate();
	system("pause");
	return 0;
}