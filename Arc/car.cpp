//g++ car.cpp -o car -lGL -lGLU -lglut -lGLEW
//./car

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

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 1200.0, 0.0, 750.0);
	glMatrixMode(GL_MODELVIEW);
}

void pixel(float x, float y)
{
	glBegin(GL_POINTS);
	glVertex2f(x,y);
	glEnd();
}

struct circle
{
    	float centre[2];
    	float radius;
};

void octants(float c[2], float x, float y)
{
    	pixel(c[0] + y, c[1] + x); //O1
    	pixel(c[0] + x, c[1] + y); //O2
    	pixel(c[0] - x, c[1] + y); //O3
    	pixel(c[0] - y, c[1] + x); //O4
    	pixel(c[0] - y, c[1] - x); //O5
    	pixel(c[0] - x, c[1] - y); //O6
    	pixel(c[0] + x, c[1] - y); //O7
    	pixel(c[0] + y, c[1] - x); //O8
}

void MCD(circle cir)
{
    	float x = 0;
    	float y = cir.radius;

    	float p = 1 - cir.radius;

    	int x_limit = cir.radius / sqrt(2);

    	for (int i = 0; i < x_limit; i++)
    	{
		octants(cir.centre, x, y);
        
        	if (p < 0) //y does not change
            	{
            		p = p + 2*(x + 3);
            	}
        	else //y decrement
        	{
            		p = p + 2*x - 2*y + 5;
            		y = y-1;
        	}
        	x = x+1;
	}
}

void BLA(float point_initial[2], float point_final[2])
{

	float x1 = point_initial[0]; float y1 = point_initial[1];
	float x2 = point_final[0]; float y2 = point_final[1];
	
	int distance_x = (int)(x2 - x1);
	int distance_y = (int)(y2 - y1);
    	int parameter;

    	if(abs(distance_y) <= abs(distance_x))
    	{
        	parameter = 2*abs(distance_y) - abs(distance_x);
        	for(int i = 0; i < abs(distance_x); i = i+1)
        	{
            		if(parameter >= 0)
            		{
                		parameter = parameter + (2*abs(distance_y) - 2*abs(distance_x));
                		y1 = y1 + distance_y/abs(distance_y);
                	}
            		else
            		{
                		parameter = parameter + (2*abs(distance_y));
            		}
            		pixel(round(x1), round(y1));
            
            		x1 = x1 + distance_x/(abs(distance_x));
        	}
    	}
    	else
    	{
        	parameter = 2*abs(distance_x) - abs(distance_y);
        	for(int i = 0; i < abs(distance_y); i = i+1)
        	{
            		if(parameter >= 0)
            		{
            			parameter = parameter + (2*abs(distance_x) - 2*abs(distance_y));
               			x1 = x1 + distance_x/abs(distance_x);
			}
            		else
            		{
            			parameter = parameter + (2*abs(distance_x));
            		}
            		pixel(round(x1), round(y1));
            		
            		y1 = y1 + distance_y/(abs(distance_y));
        	}
    	}	
}

void Display_car(void)
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPointSize(4.0);
	
	glLoadIdentity();
   	 //car body
    	float a[2] = {125, 250};
    	float b[2] = {950, 250};
    	float c[2] = {950, 400};
    	float d[2] = {125, 400};
    	// Front Window
    	float e[2] = {270, 410};
    	float f[2] = {390, 600};
    	float g[2] = {580, 600};
    	float h[2] = {580, 410};
    	//Rear Window
    	float i[2] = {590, 410};
    	float j[2] = {590, 600};
    	float k[2] = {810, 600};
    	float l[2] = {930, 410};
    	//car roof
    	// point c
    	float m[2] = {820, 610};
    	float n[2] = {380, 610};
    	float o[2] = {250, 400};

    	//Drawing Line segments  with BLD
    	//car body
    	glColor3f(0, 0, 0);
    	BLA(a, b);
    	BLA(b, c);
    	BLA(c, d);
    	BLA(d, a);
    	//front window
    	BLA(e, f);
    	BLA(f, g);
    	BLA(g, h);
    	BLA(h, e);
    	//rear Window
    	BLA(i, j);
    	BLA(j, k);
    	BLA(k, l);
    	BLA(l, i);
    	//car roof
    	BLA(c, m);
    	BLA(m, n);
    	BLA(n, o);

    	//WHEELS
    	circle frontW = {{350, 250}, 100};
    	circle backW = {{750, 250}, 100};
    	MCD(frontW);
    	MCD(backW);
    	//Colouring the wheel
    	glColor3f(0.5, 0.5, 0.5);
    	float temp = frontW.radius;
    	while (temp = temp - 1)
    	{
        	circle f = {{frontW.centre[0], frontW.centre[1]}, temp};
        	circle b = {{backW.centre[0], backW.centre[1]}, temp};
        	glColor3f(0.5, 0.5, 0.5);
        	MCD(f);
        	MCD(b);
    	}
	
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
   	glutCreateWindow("Car");
   	init();
    	glutDisplayFunc(Display_car);
    	glutMainLoop();
    	return 0;
}
