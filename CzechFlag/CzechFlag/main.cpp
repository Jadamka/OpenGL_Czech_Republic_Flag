#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define WIDTH  800
#define HEIGHT 600

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const char* vertexShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
"}\0";

const char* fragmentShaderSourceTriangle =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
" FragColor = vec4(0.0f, 0.0f, 0.5f, 1.0f);\n"
"}\0";

const char* fragmentShaderSourceRect1 =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
" FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
"}\0";

const char* fragmentShaderSourceRect2 =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
" FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
"}\0";

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Czech flag", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	int success;
	char infoLog[512];

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "SHADER::VERTEX::COMPILE::ERROR:: " << infoLog << std::endl;
	}

	unsigned int fragmentShaderTriangle = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderTriangle, 1, &fragmentShaderSourceTriangle, NULL);
	glCompileShader(fragmentShaderTriangle);

	glGetShaderiv(fragmentShaderTriangle, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShaderTriangle, 512, NULL, infoLog);
		std::cout << "SHADER::FRAGMENT::COMPILE::ERROR:: " << infoLog << std::endl;
	}

	unsigned int fragmentShaderRect1 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderRect1, 1, &fragmentShaderSourceRect1, NULL);
	glCompileShader(fragmentShaderRect1);

	glGetShaderiv(fragmentShaderRect1, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShaderRect1, 512, NULL, infoLog);
		std::cout << "SHADER::FRAGMENT::COMPILE::ERROR:: " << infoLog << std::endl;
	}

	unsigned int fragmentShaderRect2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderRect2, 1, &fragmentShaderSourceRect2, NULL);
	glCompileShader(fragmentShaderRect2);

	glGetShaderiv(fragmentShaderRect2, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShaderRect2, 512, NULL, infoLog);
		std::cout << "SHADER::FRAGMENT::COMPILE::ERROR:: " << infoLog << std::endl;
	}

	unsigned int shaderProgramTriangle = glCreateProgram();
	glAttachShader(shaderProgramTriangle, vertexShader);
	glAttachShader(shaderProgramTriangle, fragmentShaderTriangle);
	glLinkProgram(shaderProgramTriangle);

	glGetProgramiv(shaderProgramTriangle, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(shaderProgramTriangle, 512, NULL, infoLog);
		std::cout << "SHADER::PROGRAM::TRIANGLE::LINK::ERROR:: " << infoLog << std::endl;
	}

	unsigned int shaderProgramRect1 = glCreateProgram();
	glAttachShader(shaderProgramRect1, vertexShader);
	glAttachShader(shaderProgramRect1, fragmentShaderRect1);
	glLinkProgram(shaderProgramRect1);

	glGetProgramiv(shaderProgramRect1, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(shaderProgramRect1, 512, NULL, infoLog);
		std::cout << "SHADER::PROGRAM::RECT1::LINK::ERROR:: " << infoLog << std::endl;
	}

	unsigned int shaderProgramRect2 = glCreateProgram();
	glAttachShader(shaderProgramRect2, vertexShader);
	glAttachShader(shaderProgramRect2, fragmentShaderRect2);
	glLinkProgram(shaderProgramRect2);

	glGetProgramiv(shaderProgramRect2, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(shaderProgramRect2, 512, NULL, infoLog);
		std::cout << "SHADER::PROGRAM::RECT2::LINK::ERROR:: " << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShaderTriangle);
	glDeleteShader(fragmentShaderRect1);
	glDeleteShader(fragmentShaderRect2);

	float verticesTriangle[] = {
		-0.7f, -0.5f, 0.0f,
		-0.1f,  0.0f, 0.0f,
		-0.7f,  0.5f, 0.0f,
	};

	float verticesRect1[] = {
		-0.1f,  0.0f, 0.0f,
		-0.7f,  0.5f, 0.0f,
		 0.7f,  0.5f, 0.0f,
		 0.7f,  0.0f, 0.0f
	};

	unsigned int indicesRect1[] = {
		0, 1, 2,
		0, 3, 2
	};

	float verticesRect2[] = {
		-0.1f,  0.0f, 0.0f,
		-0.7f, -0.5f, 0.0f,
		 0.7f,  0.0f, 0.0f,
		 0.7f, -0.5f, 0.0f
	};

	unsigned int indicesRect2[] = {
		0, 1, 3,
		0, 2, 3
	};

	unsigned int VBO[3], VAO[3], EBO[2];
	glGenVertexArrays(3, VAO);
	glGenBuffers(3, VBO);
	glGenBuffers(2, EBO);


	glBindVertexArray(VAO[0]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesTriangle), verticesTriangle, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	glBindVertexArray(VAO[1]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesRect1), verticesRect1, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesRect1), indicesRect1, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	glBindVertexArray(VAO[2]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesRect2), verticesRect2, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesRect2), indicesRect2, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgramRect1);
		glBindVertexArray(VAO[1]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glUseProgram(shaderProgramRect2);
		glBindVertexArray(VAO[2]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glUseProgram(shaderProgramTriangle);
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteBuffers(3, VBO);
	glDeleteBuffers(2, EBO);
	glDeleteVertexArrays(3, VAO);
	glDeleteProgram(shaderProgramTriangle);
	glDeleteProgram(shaderProgramRect1);
	glDeleteProgram(shaderProgramRect2);

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}