//g++ insideout.cpp -o io -lGL -lGLU -lglut -lGLEW
//./io

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

void init() 
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(5.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 499.0, 0.0, 499.0);
}

void display() 
{
	int n; 
	printf("Enter the number of points you want to check : ");
	cin >> n;
	int x; int y;
	
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 1.0);
	
	glBegin(GL_LINE_LOOP);
		glVertex2f(150, 150);
		glVertex2f(150, 350);
		glVertex2f(350, 350);
		glVertex2f(350, 150);
	glEnd();

	for (int i = 0; i < n; i = i+1) 
	{
		printf("Enter the coordinates of the point : ");
		cin >> x; cin >> y;

		glBegin(GL_POINTS);
		if (x >= 150 && x <= 350 && y >= 150 && y <= 350)
		{

			glColor3f(1.0, 0.0, 0.0);
			glVertex2f(x, y);
			printf("THE POINT IS INSIDE : %d %d \n", x, y);
		}
		else 
		{
			glColor3f(0.0, 1.0, 0.0);
			glVertex2f(x, y);
			printf("THE POINT IS OUTSIDE : %d %d \n", x, y);
		}

		glEnd();
	}
	glFlush();


}

int main(int argc, char** argv) 
{
	srand(0);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Inside Out");
	glutDisplayFunc(display);

	init();
	glutMainLoop();
}
