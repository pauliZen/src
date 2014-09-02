#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <iomanip>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

using namespace std;


static int shoulder = 0, elbow = 0, head = 0, leg = 0, foot = 0;

void init(void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_FLAT);
}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT);

   glPushMatrix();

     glPushMatrix(); //It's body
       glScalef (1.6, 2.0, 1.0);
       glutWireCube (1.0);
     glPopMatrix();

     glPushMatrix();
       glTranslatef (0.0, 1.4, 0.0);   //It's head
       glRotatef ((GLfloat) head, 0.0, 1.0, 0.0);
       glScalef (0.5,0.6,0.5);
       glutWireCube (1.0);
     glPopMatrix();
     
     glPushMatrix();
       glTranslatef (0.8, 0.9, 0.0);  //It's the right shoulder
       glRotatef ((GLfloat) shoulder, 0.0, 0.0, 1.0);
       glTranslatef (0.6, 0.0, 0.0);

       glPushMatrix();
       glScalef (1.2, 0.4, 0.5);
       glutWireCube (1.0);
       glPopMatrix();

       glTranslatef (0.6, 0.0, 0.0);  //It's the right elbow
       glRotatef ((GLfloat) elbow, 0.0, 0.0, 1.0);
       glTranslatef (0.7, 0.0, 0.0);

       glPushMatrix();
       glScalef (1.4, 0.4, 0.5);
       glutWireCube (1.0);
       glPopMatrix();
	 glPopMatrix();

     glPushMatrix();
       glTranslatef (-0.8, 0.9, 0.0);  //It's the left shoulder
       glRotatef ((GLfloat) shoulder, 0.0, 0.0, 1.0);
       glTranslatef (-0.6, 0.0, 0.0);

       glPushMatrix();
       glScalef (1.2, 0.4, 0.5);
       glutWireCube (1.0);
       glPopMatrix();

       glTranslatef (-0.6, 0.0, 0.0);  //It's the left elbow
       glRotatef ((GLfloat) elbow, 0.0, 0.0, 1.0);
       glTranslatef (-0.7, 0.0, 0.0);

       glPushMatrix();
       glScalef (1.4, 0.4, 0.5);
       glutWireCube (1.0);
       glPopMatrix();
	 glPopMatrix();

	 glPushMatrix();
       glTranslatef (0.5, -1.0, 0.0); //It's the right leg
       glRotatef ((GLfloat) leg, 0.0, 1.0, 0.0);
	   glTranslatef (0.0, -0.6, 0.0);
       
	   glPushMatrix();
	   glScalef (0.5, 1.2, 0.5);
	   glutWireCube (1.0);
	   glPopMatrix();

	   glTranslatef (0.0, -0.6, 0.0);//It's the right foot
	   glRotatef ((GLfloat) foot, 0.0, 1.0, 0.0);
	   glTranslatef (0.0, -0.7, 0.0);
	   
	   glPushMatrix();
	   glScalef (0.5, 1.4, 0.5);
	   glutWireCube (1.0);
       glPopMatrix();
     glPopMatrix();

	 glPushMatrix();
       glTranslatef (-0.5, -1.0, 0.0);//It's the left leg
       glRotatef ((GLfloat) leg, 0.0, 1.0, 0.0);
	   glTranslatef (0.0, -0.6, 0.0);
       
	   glPushMatrix();
	   glScalef (0.5, 1.2, 0.5);
	   glutWireCube (1.0);
	   glPopMatrix();

	   glTranslatef (0.0, -0.6, 0.0);//It's the left foot
	   glRotatef ((GLfloat) foot, 0.0, 1.0, 0.0);
	   glTranslatef (0.0, -0.7, 0.0);
	   
	   glPushMatrix();
	   glScalef (0.5, 1.4, 0.5);
	   glutWireCube (1.0);
       glPopMatrix();
     glPopMatrix();
   
   glPopMatrix();

   glutSwapBuffers();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef (0.0, 1.0, -5.0);
}

void keyboard (unsigned char key, int x, int y)
{
   switch (key) {
      case 's':
         shoulder = (shoulder + 5) % 360;
         glutPostRedisplay();
         break;
      case 'S':
         shoulder = (shoulder - 5) % 360;
         glutPostRedisplay();
         break;

      case 'e':
         elbow = (elbow + 5) % 360;
         glutPostRedisplay();
         break;
      case 'E':
         elbow = (elbow - 5) % 360;
         glutPostRedisplay();
         break;

	  case 'h':
         head = (head + 5) % 360;
         glutPostRedisplay();
         break;
      case 'H':
         head = (head - 5) % 360;
         glutPostRedisplay();
         break;
		 	  
	  case 'l':
         leg = (leg + 5) % 360;
         glutPostRedisplay();
         break;
      case 'L':
         leg = (leg - 5) % 360;
         glutPostRedisplay();
         break;

	  case 'f':
         foot = (foot + 5) % 360;
         glutPostRedisplay();
         break;
      case 'F':
         foot = (foot - 5) % 360;
         glutPostRedisplay();
         break;

      case 27:
         exit(0);
         break;
      default:
         break;
   }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
