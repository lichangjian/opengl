#include <GL/glew.h>
#include "render.h"

void Render()
{
    glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}