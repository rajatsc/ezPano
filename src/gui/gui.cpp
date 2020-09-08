#include "gui.h"

#include <iostream>
#include <stdexcept>

namespace ezPano{


void framebuffer_size_callback(GLFWwindow* window, int width, int height){
	glViewport(0, 0, width, height);
	std::cout << "frame size changed" << width << " " << height << "\n";
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
		glfwSetWindowShouldClose(window, true);	
	}
}



gui::gui(system* s)
	:m_system(s)
	{
	
	try{
	/*Initialize the library*/
	if (!glfwInit())
		throw std::runtime_error("cannot initialize glfw"); 

	/*create a windowed mode window and its OpenGL context*/
	m_window = glfwCreateWindow(640, 480, "my window", NULL, NULL);

	if (!m_window)
	{
		glfwTerminate();
		throw std::runtime_error("cannot create window");
	}

	/*Make the window's context current*/
	glfwMakeContextCurrent(m_window);

	//register callbacks
	glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
	glfwSetKeyCallback(m_window, key_callback);

	//glew: load all OpenGL function pointers
	if (glewInit() != GLEW_OK){
		std::cout << "Error!" << std::endl;
		throw std::runtime_error("glew error");
	}
	}
	catch(std::exception& ex){
		std::cout << "exception occured" << std::endl;
	}

}


gui::~gui(){
	glfwSetWindowShouldClose(m_window, true);
}


void gui::run(){
	while(!glfwWindowShouldClose(m_window)){

		/**Render here */
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		/* swap front and back buffers */
		glfwSwapBuffers(m_window);
		
		//poll for and process events
		glfwPollEvents();

		//std::cout << "gui" << std::endl;
	}
}




} //namespace ezPano
