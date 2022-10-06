//g++ triangle.cpp -o triangle -lGL -lGLU -lglut -lGLEW
//./triangle

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>

using namespace std;

void changeViewPort(int w, int h)
{
	glViewport(0, 0, w, h);
}

void Display()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);
    	
    	glBegin(GL_POLYGON);
        	glVertex2f(0.0, 0.5);
        	glVertex2f(-0.5, 0.0);
        	glVertex2f( 0.5, 0.0);
    	glEnd();
    	glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(780, 540);
    glutInitWindowPosition(300, 300); 
    glutCreateWindow("Triangle");
    glutReshapeFunc(changeViewPort);
    glutDisplayFunc(Display);
    glutMainLoop();
    return 0;
}





