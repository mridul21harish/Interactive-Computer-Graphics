//g++ pointclipping.cpp -o pc -lGL -lGLU -lglut -lGLEW
//./pc

#include <GL/glew.h>
#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include <cmath>
#include <unistd.h>
using namespace std;

#define LENGTH 600
#define HEIGHT 600

void window_color()
{
	glClearColor(1.0,1.0,1.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

void PC(int xmin, int ymin, int xmax, int ymax, int x, int y)
{
	printf("Point Clipping Algorithm\n");
	printf("The point coordinates are : (%d, %d)\n", x, y);
  
  	if(x>=xmin && x<=xmax && y>=ymin && y<=ymax)
  	{ 
    		glPointSize(3.5);
    		glColor3f(1, 0, 0);
    		glBegin(GL_POINTS);
        	glVertex2f(x,y);
    		glEnd();
    		printf("The point is inside the window\n");
  	}
  	else
  	{
  		printf("The point is not inside the window\n");
  	}
}

void Display_window()
{
	window_color();
    	srand(time(0));
    	
    	int xmin = rand()%300+100;
    	int ymin = rand()%300+100;
    	int xmax = rand()%300+300;
    	int ymax = rand()%300+300;
    	
    	glColor3f(0,0,0);
    	glBegin(GL_LINE_LOOP);
        	glVertex2f(xmin,ymin);
        	glVertex2f(xmin,ymax);
        	glVertex2f(xmax,ymax);
        	glVertex2f(xmax,ymin);
    	glEnd();
    	
    	int n = 100;
    	int xpoint; int ypoint;
    	for(int i = 0; i < n; i = i+1)
    	{
        	xpoint = rand()%600;
        	ypoint = rand()%600;
        	PC(xmin, ymin, xmax, ymax, xpoint, ypoint);
    	}
	glFlush();
}

int main(int argc,char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(LENGTH, HEIGHT);
	glutCreateWindow("Point Clipping");
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, LENGTH, 0.0, HEIGHT);
	glutDisplayFunc(Display_window);
	glutMainLoop();
}
