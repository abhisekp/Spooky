#include <iostream>
#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>

int main(int argc, char *argv[])
{
	if (glfwInit() != GL_TRUE) {
		std::cout << "GLFW Initialization failed." << std::endl;
	}
	std::cout << "GLFW Successfully Initialized." << std::endl;

	glfwTerminate();
	system("pause");
	return 0;
}