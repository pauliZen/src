#include <iostream>
using namespace std;

#include <GL/glew.h>
#include <GL/gl.h>
//#inlcude "include/GL3/gl3.h"
//#include "include/GL3/gl3w.h"
#include <GL/freeglut.h>
//#include <GL/glut.h>
#include <GL/glu.h>

#include "include/LoadShaders.h"

#define BUFFER_OFFSET(offset) ((void*) (offset))

enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };
enum Attrib_IDs { vPosition = 0 };

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

const GLuint NumVertices = 6;

void
init(void)
{
  glGenVertexArrays(NumVAOs,VAOs);
  glBindVertexArray (VAOs[Triangles]);

  GLfloat vertices[NumVertices][2]={
    { -0.9, -0.9},
    { 0.85, -0.9},
    { -0.9, 0.85},
    { 0.9, -0.85},
    { 0.9, 0.9},
    { -0.85, 0.9}
  };

  glGenBuffers(NumVertices, Buffers);
  glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  ShaderInfo shaders[] = {
    { GL_VERTEX_SHADER, "triangles.vert" },
    { GL_FRAGMENT_SHADER, "triangles.frag" },
    { GL_NONE, NULL }
  };

  GLuint program = LoadShaders(shaders);
  glUseProgram(program);
  glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
  glEnableVertexAttribArray(vPosition);
}

void
display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glBindVertexArray(VAOs[Triangles]);
  glDrawArrays(GL_TRIANGLES,0,NumVertices);
  glFlush();
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA);
  glutInitWindowSize(512,512);
  glutInitContextVersion(4,3);
  glutInitContextProfile(GLUT_CORE_PROFILE);
  glutCreateWindow(argv[0]);

  if (glewInit()) {
    cerr <<"Unable to initialize GLEW ... exiting" <<endl;
    exit(EXIT_FAILURE);
  }

  init();

  glutDisplayFunc(display);

  glutMainLoop();
}


