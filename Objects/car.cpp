//g++ car.cpp -o car -lGL -lGLU -lglut -lGLEW
//./car

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>
#include <math.h>

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
	glColor3f(0.0f, 0.5f, 1.0f);//baby Blue
	glBegin(GL_POLYGON);
		glVertex2i(140, 95);
    		glVertex2i(140, 150);
    		glVertex2i(300, 150);
    		glVertex2i(300, 95);
 	glEnd();
 	
 	//upper part
 	glColor3f(0.0f, 0.5f, 1.0f);//baby Blue
 	glBegin(GL_POLYGON);
		glVertex2i(180, 150);
    		glVertex2i(200, 200);
    		glVertex2i(280, 200);
    		glVertex2i(300, 150);
 	glEnd();
 	
 	//left window
 	glColor3f(0.0f, 0.0f, 0.0f);//Black
 	glBegin(GL_POLYGON);
		glVertex2i(182, 152);
    		glVertex2i(200, 198);
    		glVertex2i(235, 198);
    		glVertex2i(235, 152);
 	glEnd();
 	
 	//right window
 	glColor3f(0.0f, 0.0f, 0.0f);//Black
 	glBegin(GL_POLYGON);
		glVertex2i(237, 152);
    		glVertex2i(237, 198);
    		glVertex2i(278, 198);
    		glVertex2i(298, 152);
 	glEnd();
 	
 	//left wheel
 	glColor3f(0.0f, 0.0f, 0.0f);//Black
 	float theta;
 	glBegin(GL_POLYGON);
 		for(int i = 0; i < 360; i = i+1)
 		{
 			theta = i*(3.14/180);
 			glVertex2f(180 + 17.5*cos(theta), 95 + 30*sin(theta));
 		}
 	glEnd();
 	
 	//right wheel
 	glColor3f(0.0f, 0.0f, 0.0f);//Black
 	float theta1;
 	glBegin(GL_POLYGON);
 		for(int i = 0; i < 360; i = i+1)
 		{
 			theta1 = i*(3.14/180);
 			glVertex2f(260 + 17.5*cos(theta1), 95 + 30*sin(theta1));
 		}
 	glEnd();
 	
 	glutSwapBuffers();
}
int main(int argc, char** argv)
{
    	glutInit(&argc, argv);
   	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  	glutInitWindowSize(1200, 750);
   	glutInitWindowPosition(0, 0); 
   	glutCreateWindow("CAR");
    	glutDisplayFunc(Display);
    	init();
    	glutMainLoop();
    	return 0;
}

