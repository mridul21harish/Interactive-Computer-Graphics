//g++ rollnumber.cpp -o rno -lGL -lGLU -lglut -lGLEW
//./rno

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>
#include <math.h>
#include <unistd.h>
#include <time.h>

using namespace std;

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 400.0, 0.0, 400.0);
}

float random_color() 
{
    	float color=(float)((rand() % 150))/99;
   	return color;    
}

float r; float g; float b;

struct circle // centre (a,b) ; Radius (ra,rb)
{
	float x;
	float y;
	float rx;
	float ry;
};
	
int flag = 0;

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPointSize(4.0);
	
	//3
	//upper
	circle inner_U_curve = {100, 250, 70, 70};
    	circle outer_U_curve = {100, 250, 75, 75};
    	
    	glBegin(GL_TRIANGLE_STRIP);
    		glColor3f(r, g, b);
    		float theta;
   		for(float i = 120; i >= -90; i = i - 0.001) // radians
		{
			theta = i*(3.14/180);
        		if(flag == 0)
        		{
            			glVertex2f(outer_U_curve.x + outer_U_curve.rx*cos(theta), outer_U_curve.y + outer_U_curve.ry*sin(theta)); // x+r*cosA,y+r*sinA
            			flag = 1;
        		}
        		else
        		{
            			glVertex2f(inner_U_curve.x + inner_U_curve.rx*cos(theta), inner_U_curve.y + inner_U_curve.ry*sin(theta)); // x+r*cosA,y+r*sinA
				flag = 0;
        		}
		}
	glEnd();
	
	//lower
	circle inner_L_curve = {100, 105, 70, 70};
    	circle outer_L_curve = {100, 105, 75, 75};
    	
    	glBegin(GL_TRIANGLE_STRIP);
    		glColor3f(r, g, b);
    		float theta1;
   		for(float i = 90; i >= -120; i = i - 0.001) // radians
		{
			theta1 = i*(3.14/180);
        		if(flag == 0)
        		{
            			glVertex2f(outer_L_curve.x + outer_L_curve.rx*cos(theta1), outer_L_curve.y + outer_L_curve.ry*sin(theta1)); // x+r*cosA,y+r*sinA
            			flag = 1;
        		}
        		else
        		{
            			glVertex2f(inner_L_curve.x + inner_L_curve.rx*cos(theta1), inner_L_curve.y + inner_L_curve.ry*sin(theta1)); // x+r*cosA,y+r*sinA
				flag = 0;
        		}
		}
	glEnd();
	
	//4
	glBegin(GL_QUADS);
    		glColor3f(r, g, b);        
        	
        	//left line
        	glVertex2f(200, 320);
        	glVertex2f(200, 180);
        	glVertex2f(205, 180);
        	glVertex2f(205, 320);
  		
  		//middle line
        	glVertex2f(205, 180);
        	glVertex2f(290, 180);
        	glVertex2f(290, 185);
        	glVertex2f(205, 185);
    		
    		//right line
        	glVertex2f(290, 35);
        	glVertex2f(295, 35);
        	glVertex2f(295, 320);
        	glVertex2f(290, 320);
        	
        	glVertex2f(200, 320);
        	glVertex2f(200, 325);
        	glVertex2f(295, 325);
        	glVertex2f(295, 320);
    	glEnd();
	
	glFlush();
   	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	srand(time(0));
	r = random_color();
	g = random_color();
	b = random_color();
    	glutInit(&argc, argv);
   	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  	glutInitWindowSize(1200, 750);
   	glutInitWindowPosition(0, 0); 
   	glutCreateWindow("Roll Number");
   	init();
    	glutDisplayFunc(Display);
    	glutMainLoop();
    	return 0;
}
