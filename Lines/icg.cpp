//g++ icg.cpp -o icg -lGL -lGLU -lglut -lGLEW
//./icg

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
	
	//I
	glBegin(GL_QUADS);
    		glColor3f(r, g, b);        
        	
        	//lower
        	glVertex2f(100, 50);
        	glVertex2f(150, 50);
        	glVertex2f(150, 55);
        	glVertex2f(100,55);
  		
  		//upper
        	glVertex2f(100, 200);
        	glVertex2f(150, 200);
        	glVertex2f(150, 205);
        	glVertex2f(100, 205);
    		
    		//middle
        	glVertex2f(122.5, 50);
        	glVertex2f(127.5, 50);
        	glVertex2f(127.5, 205);
        	glVertex2f(122.5, 205);
    	glEnd();
    	
    	//C
    	circle inner_curve = {225, 125, 50, 75};
    	circle outer_curve = {225, 125, 55, 80};
    	
    	glBegin(GL_TRIANGLE_STRIP);
    		glColor3f(r, g, b);
    		float theta;
   		for(float i = 300; i >= 65; i = i - 0.001) // radians
		{
			theta = i*(3.14/180);
        		if(flag==0)
        		{
            			glVertex2f(outer_curve.x + outer_curve.rx*cos(theta), outer_curve.y + outer_curve.ry*sin(theta)); // x+r*cosA,y+r*sinA
            			flag = 1;
        		}
        		else
        		{
            			glVertex2f(inner_curve.x + inner_curve.rx*cos(theta), inner_curve.y + inner_curve.ry*sin(theta)); // x+r*cosA,y+r*sinA
				flag=0;
        		}
		}
	glEnd();
	
	//G
	circle inner_curve_G = {305, 125, 30, 75};
    	circle outer_curve_G = {305, 125, 35, 80};
    	
    	glBegin(GL_TRIANGLE_STRIP);
    		glColor3f(r, g, b);
    		float theta1;
   		for(float i = 360; i >= 75; i = i - 0.001) // radians
		{
			theta1 = i*(3.14/180);
        		if(flag==0)
        		{
            			glVertex2f(outer_curve_G.x + outer_curve_G.rx*cos(theta1), outer_curve_G.y + outer_curve_G.ry*sin(theta1)); // x+r*cosA,y+r*sinA
            			flag = 1;
        		}
        		else
        		{
            			glVertex2f(inner_curve_G.x + inner_curve_G.rx*cos(theta1), inner_curve_G.y + inner_curve_G.ry*sin(theta1)); // x+r*cosA,y+r*sinA
				flag=0;
        		}
		}
	glEnd();
	
	//middle line
	glBegin(GL_POLYGON);
		glColor3f(r, g, b);
		glVertex2f(335, 125);
		glVertex2f(305, 125);
		glVertex2f(305, 120);
		glVertex2f(335, 120);
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
   	glutCreateWindow("ICG");
   	init();
    	glutDisplayFunc(Display);
    	glutMainLoop();
    	return 0;
}
