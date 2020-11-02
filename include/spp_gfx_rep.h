#ifndef SPP_GFX_REP_H
#define SPP_GFX_REP_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

/*
*	Sets up the OpenGL requierements
*	Returns true if succeeds, false otherwise
*/
bool initGFX();

/*
*	Callback function that is assigned to the resize event of the window
*	to manage the related changes
*/
void framebuffer_size_callback(GLFWwindow* window, int width, int height); 

/*
*	Checks wether any interaction has been made and applies changes if needed
*/
void processInput(GLFWwindow *window);

/*
*	When its called inside the rendering loop it draws a triangle
*/
void drawTriangle();

/*
*	Renders an empty window
*/
bool renderEmptyWindow();

#endif
