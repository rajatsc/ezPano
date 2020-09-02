#ifndef GUI_H
#define GUI_H

//opengl stuff
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//standard
#include <mutex>

#include "system.h"

namespace ezPano{


void framebuffer_size_callback(GLFWwindow* window, int width, int height);


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);




class system;

class gui{
public:
	//constructor
	gui(system* s);
	gui() = delete;
	~gui();
	void run();
	
private:
	


	//set the system pointer
	GLFWwindow* m_window;
	system* m_system;
};



} //namespace ezPano

#endif
