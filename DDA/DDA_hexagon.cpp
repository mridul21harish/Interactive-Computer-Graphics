//g++ DDA_hexagon.cpp -o hex -lGL -lGLU -lglut -lGLEW
//./hex

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
using namespace std;

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 1200.0, 0.0, 750.0);
	glMatrixMode(GL_MODELVIEW);
}

float precision = 100;

void pixel(float x, float y)
{
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
}

void DDA(float point_initial[2], float point_final[2])
{
	float x1 = point_initial[0]; float y1 = point_initial[1];
	float x2 = point_final[0]; float y2 = point_final[1];
	
	float distance_x = x2 - x1;
	float distance_y = y2 - y1;
	
	float slope = (distance_y/distance_x);
	
	float length; float x_increment; float y_increment;
	if(abs(distance_x) > abs(distance_y))
	{
		length = abs(distance_x);
	}
	else if(abs(distance_y) > abs(distance_x))
	{
		length = abs(distance_y);
	}
	
	x_increment = (distance_x/length);
	y_increment = (distance_y/length);
	
	float x; float y;
	x = x1;
	y = y1;
	for(int i = 0; i < length*precision; i = i+1)
	{
		pixel(round(x), round(y));
		printf("%f, %f\n", x, y);
		x = x + (x_increment/precision);
		y = y + (y_increment/precision);
	}
}

void Display_hexagon(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPointSize(4.0);
	
	float centre[2] = {600, 375};
	float radius = 250;
	
	float point1[2] = {centre[0] + radius*(float)cos(360*(3.14/180)), centre[1] + radius*(float)sin(360*(3.14/180))};
	float point2[2] = {centre[0] + radius*(float)cos(300*(3.14/180)), centre[1] + radius*(float)sin(300*(3.14/180))};
	float point3[2] = {centre[0] + radius*(float)cos(240*(3.14/180)), centre[1] + radius*(float)sin(240*(3.14/180))};
	float point4[2] = {centre[0] + radius*(float)cos(180*(3.14/180)), centre[1] + radius*(float)sin(180*(3.14/180))};
	float point5[2] = {centre[0] + radius*(float)cos(120*(3.14/180)), centre[1] + radius*(float)sin(120*(3.14/180))};
	float point6[2] = {centre[0] + radius*(float)cos(60*(3.14/180)), centre[1] + radius*(float)sin(60*(3.14/180))};
	
	glColor3f(0.0, 0.0, 0.0);
	DDA(point1, point2);
	DDA(point2, point3);
	DDA(point3, point4);
	DDA(point4, point5);
	DDA(point5, point6);
	DDA(point6, point1);
	
	glFlush();
   	glutSwapBuffers();
}
	

int main(int argc, char** argv)
{
	srand(time(0));
    	glutInit(&argc, argv);
   	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  	glutInitWindowSize(1200, 750);
   	glutInitWindowPosition(0, 0); 
   	glutCreateWindow("Hexagon");
   	init();
    	glutDisplayFunc(Display_hexagon);
    	glutMainLoop();
    	return 0;
}



