#include <iostream>
#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>

namespace spooky {
	// width and height of window
	int WIDTH = 1024;
	int HEIGHT = 576;

	// function prototypes
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
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_DECORATED, GL_FALSE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Create a GLFW window
	GLFWwindow *window = glfwCreateWindow(spooky::WIDTH, spooky::HEIGHT, "Spooky", nullptr, nullptr);
	if (!window) {
		std::cout << "GLFW Window Creation Failed" << std::endl;
		return 0;
	}
	std::cout << "GLFW Window Creation Successful" << std::endl;
	std::cout << "GLFW version: " << glfwGetVersionString() << std::endl;
	// Make the window as current context
	glfwMakeContextCurrent(window);
	// Set swap interval to one refresh rate cycle of monitor
	glfwSwapInterval(1);

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

	// OpenGL context
	GLfloat vertices[] = {
		0.0f, 0.5f,
		0.5f, -0.5f,
		-0.5f, -0.5f
	};

	// Vertex Buffer & Array Buffer
	GLuint VBO, VAO;

	// Generate the vertex buffer
	glGenBuffers(1, &VBO);

	// Generate array buffer
	glGenVertexArrays(1, &VAO);

	// Change Vertex Attribs
	glBindVertexArray(VAO);

	// bind ARRAY_BUFFER to VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// copy vertices data to VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	// define formatting of vertex data in the given index
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GL_FLOAT), nullptr);

	// enable the given index
	glEnableVertexAttribArray(0);
	
	// unbind vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// unbind vertex array
	glBindVertexArray(0);

	// vertex shader source
	const GLchar *vertexShaderSource = ""
		"#version 330 core\n"
		"layout (location = 0) in vec2 position;\n"
		"void main() {"
		"    gl_Position = vec4(position.x, position.y, 0.0f, 1.0f);\n"
		"}\0";

	// declare vertex shader object
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// define vertex shader source
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);

	// compile vertex shader
	glCompileShader(vertexShader);
	{
		GLint success;
		// Get Compile Status of the vertex shader
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			GLchar infoLog[512];
			// Get info log of the compile status
			glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);

			std::cout << "VERTEX SHADER :: COMPILE ERRORS" << std::endl << infoLog << std::endl;
		}
		else {
			std::cout << "Compiled Vertex Shader Successfully." << std::endl;
		}
	}

	// fragment shader source
	const GLchar *fragmentShaderSource = ""
		"#version 330 core\n"
		"out vec4 color;\n"
		"void main() {\n"
		"    color = vec4(138/255.0f, 172/255.0f, 0.0f, 1.0f);"
		"}\0";

	// declare fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// define vertex shader source
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);

	// compile fragment shader
	glCompileShader(fragmentShader);
	{
		GLint success;
		// Get Compile Status of the fragment shader
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			GLchar infoLog[512];
			// Get info log of the compile status
			glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);

			std::cout << "FRAGMENT SHADER :: COMPILE ERRORS" << std::endl << infoLog << std::endl;
		}
		else {
			std::cout << "Compiled Fragment Shader Successfully." << std::endl;
		}
	}

	// loop until closed
	while (glfwWindowShouldClose(window) != GL_TRUE) {
		// poll various kinds of events
		glfwPollEvents();

		// render
		{
			// set background color
			int red = 0;
			int green = 61;
			int blue = 61;
			glClearColor(red / 255.0f, green / 255.0f, blue / 255.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		// swap front and back buffers
		glfwSwapBuffers(window);
	}

	//glfwTerminate();
	//system("pause");
	return 0;
}


// key callbacks
void spooky::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

// position callback to make window immovable
void spooky::positionCallback(GLFWwindow *window, int xPos, int yPos)
{
	const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	int x = (mode->width - WIDTH) / 2;
	int y = (mode->height - HEIGHT) / 2;
	glfwSetWindowPos(window, x, y);
}