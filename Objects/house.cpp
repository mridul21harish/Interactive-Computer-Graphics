//g++ house.cpp -o house -lGL -lGLU -lglut -lGLEW
//./house

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>

using namespace std;

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 400.0, 0.0, 400.0);
}

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(4.0);
	
	//lower part
	glColor3f(0.0f, 0.0f, 1.0f);//blue
	glBegin(GL_POLYGON);
		glVertex2i(140, 40);
    		glVertex2i(140, 200);
    		glVertex2i(260, 200);
    		glVertex2i(260, 40);
 	glEnd();
 	
 	//upper part
 	glColor4f(1.0f, 0.0f, 0.0f, 0.0f);//red
 	glBegin(GL_POLYGON);
 		glVertex2i(140, 201);
 		glVertex2i(200, 350);
 		glVertex2i(260, 201);
 	glEnd();
 	
 	//door
 	glColor4f(1.0f, 1.0f, 1.0f, 0.0f);//white
 	glBegin(GL_POLYGON);
 		glVertex2i(190, 41);
 		glVertex2i(190, 120);
 		glVertex2i(210, 120);
 		glVertex2i(210, 41);
 	glEnd();
 	
 	//left window
 	glColor4f(1.0f, 1.0f, 1.0f, 0.0f);//white
 	glBegin(GL_POLYGON);
 		glVertex2i(160, 100);
 		glVertex2i(160, 120);
 		glVertex2i(170, 120);
 		glVertex2i(170, 100);
 	glEnd(); 
 	
 	//right window
 	glColor4f(1.0f, 1.0f, 1.0f, 0.0f);//white
 	glBegin(GL_POLYGON);
 		glVertex2i(230, 100);
 		glVertex2i(230, 120);
 		glVertex2i(240, 120);
 		glVertex2i(240, 100);
 	glEnd(); 
 	
 	
 	glutSwapBuffers();
}	
	

int main(int argc, char** argv)
{
    	glutInit(&argc, argv);
   	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  	glutInitWindowSize(1200, 750);
   	glutInitWindowPosition(0, 0); 
   	glutCreateWindow("HOUSE");
    	glutDisplayFunc(Display);
    	init();
    	glutMainLoop();
    	return 0;
}


