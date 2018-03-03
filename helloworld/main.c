#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "render.h"

int main(void)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    GLFWwindow *window = glfwCreateWindow(800, 600, "Helloworld", NULL, NULL);
    if(window == NULL)
    {
        printf("Failed to create GLFW window");
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    glViewport(0, 0, 800, 600);
    while(!glfwWindowShouldClose(window))
    {
        Render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}