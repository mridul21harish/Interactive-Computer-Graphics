//g++ DDA_house.cpp -o house -lGL -lGLU -lglut -lGLEW
//./house

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
	gluOrtho2D(0.0, 100.0, 0.0, 100.0);
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
		x = x + (x_increment/precision);
		y = y + (y_increment/precision);
	}
}

void Triangle_color_dda(float point1[2],float point2[2],float point3[2])
{
	float x1 = point1[0] , y1 = point1[1];
	float x2 = point2[0] , y2 = point2[1];

	float dx = x2 - x1;
	float dy = y2 - y1;
	float m = dy / dx;
	float length, x_increment, y_increment;
	if (abs(dx) > abs(dy))
		length = abs(dx);
	else
		length = abs(dy);

	x_increment = dx / length;
	y_increment = dy / length;

	int i;
	float point[2] = {x1, y1};
	
	for (i = 0; i < length*precision; i++)
	{
		DDA(point3,point); 
		point[0] += x_increment/precision;
		point[1] += y_increment/precision;
	}
}
void Display_house(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glPointSize(4);

	//lower part
	float point_a[2] = {20, 10};
	float point_b[2] = {60, 10};
	float point_c[2] = {60, 50};
	float point_d[2] = {20, 50};

	glColor3f(1.0, 0.0, 0.0);
	Triangle_color_dda(point_a, point_c, point_b);
	Triangle_color_dda(point_a, point_c, point_d);

	glColor3f(0,0,0); //black outline
	DDA(point_a, point_b);
	DDA(point_b, point_c);
	DDA(point_c, point_d);
	DDA(point_d, point_a);

	//upper part
	float point_e[2] = {40, 80};
	glColor3f(0.0, 0.0, 1.0);
	Triangle_color_dda(point_c, point_d, point_e);

	glColor3f(0,0,0); //black outline
	DDA(point_c, point_d);
	DDA(point_d, point_e);
	DDA(point_e, point_c);

	//door	
	float point_f[2] = {35, 10};
	float point_g[2] = {45, 10};
	float point_h[2] = {45, 30};
	float point_i[2] = {35, 30};

	glColor3f(1.0, 1.0, 1.0);//white
	Triangle_color_dda(point_f, point_h, point_g);
	Triangle_color_dda(point_f, point_h, point_i);

	glColor3f(0,0,0); //black outline
	DDA(point_f, point_g);
	DDA(point_g, point_h);
	DDA(point_h, point_i);
	DDA(point_i, point_f);

	//left window
	float point_j[2] = {25, 25}; 
    	float point_k[2] = {30, 25};
    	float point_l[2] = {30, 30};
    	float point_m[2] = {25, 30};

	glColor3f(1.0, 1.0, 1.0);//white
	Triangle_color_dda(point_j, point_l, point_k);
	Triangle_color_dda(point_j, point_l, point_m);

	glColor3f(0,0,0); //black outline
	DDA(point_j, point_k);
	DDA(point_k, point_l);
	DDA(point_l, point_m);
	DDA(point_m, point_j);

	//right window
	float point_n[2] = {50, 25}; 
    	float point_o[2] = {55, 25};
    	float point_p[2] = {55, 30};
    	float point_q[2] = {50, 30};

	glColor3f(1.0, 1.0, 1.0);//white
	Triangle_color_dda(point_n, point_p, point_o);
	Triangle_color_dda(point_n, point_p, point_q);

	glColor3f(0,0,0); //black outline
	DDA(point_n, point_o);
	DDA(point_o, point_p);
	DDA(point_p, point_q);
	DDA(point_q, point_n);


    	glFlush();
    	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	srand(time(0));
    	glutInit(&argc, argv);
   	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  	glutInitWindowSize(400, 300);
   	glutInitWindowPosition(0, 0); 
   	glutCreateWindow("House");
   	init();
    	glutDisplayFunc(Display_house);
    	glutMainLoop();
    	return 0;
}
