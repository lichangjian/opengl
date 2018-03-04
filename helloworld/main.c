#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

const char *vshader = "#version 410\n"
		"layout (location = 0) in vec3 vp;"
        "layout (location = 1) in vec3 color;"
        "out vec4 vertexColor;"
		"void main () {"
		"  gl_Position = vec4 (vp, 1.0);"
        "  vertexColor = vec4 (color, 1.0);"
		"}";
const char *fshader = "#version 410\n"
		"out vec4 frag_colour;\n"
        "in vec4 vertexColor;\n"
		"void main () {\n"
		"  frag_colour = vertexColor;\n"
		"}";
GLfloat points[] = {-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 
                    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 
                    0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f};
GLuint indexs[] = {0, 2, 1};

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

	glewInit();
    glViewport(0, 0, 800, 600);

    GLuint vbo;
    glGenBuffers(1, &vbo); 
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GL_FLOAT), points, GL_STATIC_DRAW);

    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(GLuint), indexs, GL_STATIC_DRAW);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), NULL);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (void*)(3 * sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBindVertexArray(0);

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vshader, NULL);
    glCompileShader(vs);
    GLint succ;
    GLchar infoLog[512];
    glGetShaderiv(vs, GL_COMPILE_STATUS, &succ);
    if(!succ)
    {
        glGetShaderInfoLog(vs, 512, NULL, infoLog);
        printf("vs error, %s", infoLog);
    }

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fshader, NULL);
    glCompileShader(fs);
    glGetShaderiv(fs, GL_COMPILE_STATUS, &succ);
    if(!succ)
    {
        glGetShaderInfoLog(fs, 512, NULL, infoLog);
        printf("fs error, %s", infoLog);
    }

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vs);
    glAttachShader(shaderProgram, fs);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &succ);
    if(!succ)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("%s", infoLog);
    }
    glDeleteShader(vs);
    glDeleteShader(fs);

    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}