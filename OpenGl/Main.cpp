#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

//IDK HOW THAT WORKS - COPIED & PASTED
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//IDK HOW THAT WORKS - COPIED & PASTED
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

int main() {
	//Initializing GLFW
	glfwInit();

	//VERSION OF GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Defining that core profile is used
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	//3 coordinates of vertices
	GLfloat vertices[] = {
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,
	};
	
	//800x800 Window 
	GLFWwindow* window = glfwCreateWindow(800, 800, "YEAH OPENGL BITCHES", NULL, NULL);
	//Checking for errors
	if (window == NULL) {
		std::cout << "Failure in creating a glfw window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//Window into current context
	glfwMakeContextCurrent(window);
	//GLAD loading so it will configure OPENGL
	gladLoadGL();

	//Viewport of OPENGL, creating a color
	// and clearing back buffer and swapping it with font
	glViewport(0, 0, 800, 800);

	//Gluint Is like unsigned int
	// Create vertex shader obj and ge treference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//attach its source to the vs obj
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//compile
	glCompileShader(vertexShader);

	// Create vertex shader obj and ge treference
	GLuint fragmentShader = glCreateShader(GL_VERTEX_SHADER);
	//attach its source to the vs obj
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//compile
	glCompileShader(fragmentShader);	

	GLuint shaderProgram = glCreateProgram();
	//Create shader program and get its reference
	glAttachShader(shaderProgram, vertexShader);
	//Attach both shaders to the shade program
	glAttachShader(shaderProgram, fragmentShader);
	//;ink together shaders into program
	glLinkProgram(shaderProgram);

	//delete shaders(only program is used now)
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	//vertex buffer object / vertex array obj
	//creating reference containers for them
	GLuint  VAO, VBO;
	//generate VAO VBO with 1 obj each
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//make the vao the current vertex array obj
	glBindVertexArray(VAO);
	//Bind the VBO 
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//introduce vertices into VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//Configure vertex attribute 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//Enable vertex attribute
	glEnableVertexAttribArray(0);

	//Bind both to 0 so its unmodifiable
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);



	glfwSwapBuffers(window);

	//Main loop
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.07, 0.13f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//tell openGl what program needs to be used
		glUseProgram(shaderProgram);
		//bind the vao
		glBindVertexArray(VAO);
		//draw triangle!

	
		glfwPollEvents();
		int state = glfwGetKey(window, GLFW_KEY_E);
		int state2 = glfwGetKey(window, GLFW_KEY_A);
		int state3 = glfwGetKey(window, GLFW_KEY_D);
		
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glDeleteVertexArrays(1, &VAO);
			glDeleteBuffers(1, &VBO);
			if (state2 == GLFW_PRESS)
			{
				for (int i = 0; i < 9; i++) {
					vertices[i] += 0.0001f;
				}
			}if (state3 == GLFW_PRESS) {
				for (int i = 0; i < 9; i++) {
					vertices[i] -= 0.0001f;
				}
			}
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			//make the vao the current vertex array obj
			glBindVertexArray(VAO);
			//Bind the VBO 
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			//introduce vertices into VBO
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			//Configure vertex attribute 
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			//Enable vertex attribute
			glEnableVertexAttribArray(0);
			//Bind both to 0 so its unmodifiable
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		
		glfwSwapBuffers(window);
	}
	//Delete all of this shit
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	//Deleting window
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}