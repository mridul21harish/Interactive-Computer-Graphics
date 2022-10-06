//g++ hyperbola.cpp -o hyp -lGL -lGLU -lglut -lGLEW
//./hyp

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

struct hyperbola
{
    float centre[2];
    float a;
    float b;
};

int mode;
float focusa;
float focusb;

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 1200.0, 0.0, 750.0);
	glMatrixMode(GL_MODELVIEW);
}

void plot(float x, float y)
{
    	glBegin(GL_POINTS);
    	glVertex2f(round(x), round(y));
    	glEnd();
}

float random_color() 
{
    	float color=(float)((rand() % 150))/99;
   	return color;    
}

float r; float g; float b;

void BLA(int point_initial[2], int point_final[2])
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
            		plot(round(x1), round(y1));
            
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
            		plot(round(x1), round(y1));
            		
            		y1 = y1 + distance_y/(abs(distance_y));
        	}
    	}	
}

void plot_quadrants(float centre[2], float x, float y, int quadrant[4])
{
    	if (quadrant[0] == 1)
        	plot(centre[0] + x, centre[1] + y); //Q1
    	if (quadrant[1] == 1)
        	plot(centre[0] - x, centre[1] + y); //Q2
    	if (quadrant[2] == 1)
        	plot(centre[0] - x, centre[1] - y); //Q3
    	if (quadrant[3] == 1)
        	plot(centre[0] + x, centre[1] - y); //Q4
}

void plot_hyperbola(hyperbola H, int x, int y)
{
    	int quadrants[4] = {1, 1, 1, 1};
    	if (mode == 1) //x2-y2
        	plot_quadrants(H.centre, x, y, quadrants);
    	else //y2-x2
        	plot_quadrants(H.centre, y, x, quadrants);
}

void Brute(hyperbola H)
{
    	float a = abs(H.a), b = abs(H.b);
    	float x = a;
    	float y = 0;
    	float a2 = a * a, b2 = b * b;

    	while (y < 2000)
    	{
        	plot_hyperbola(H, x, y);
        	x = x+1;
        	y = sqrt((x * x - a2) * b2 / a2);
    	}
}

void Parametric(hyperbola H)
{
    	float a = abs(H.a), b = abs(H.b);
    	float x;
    	float y;

    	for (float i = 0; i < 20; i = i + 0.001)
    	{
        	x = a / cos(i); //x=a secA
        	y = b * tan(i);
        	plot_hyperbola(H, x, y);
    	}
}

void MHD(hyperbola H)
{
    	float a = abs(H.a), b = abs(H.b);
    	float x = a;
    	float y = 0;
    	float a2 = a * a, b2 = b * b;

    	float ymid;
    	if (b < a)
        	ymid = b2 / sqrt(a2 - b2);
    	else
        	ymid = 2000;

    	float p = b2 * a - a2;

    	while (y < ymid)
    	{
        	plot_hyperbola(H, x, y);
        	if (p < 0)
        	{
            		x = x+1;
            		p = p + -a2 * (2 * y + 3) + 2 * b2 * (x + 1);
        	}
        	else
        	{
            		p = p + -a2 * (2 * y + 3);
        	}
        	y = y+1;
    	}
    	while (x < 2000)
    	{
        	plot_hyperbola(H, x, y);
        	if (p < 0)
        	{
            		p = p + b2 * (2 * x + 3);
        	}
        	else
        	{
            		y = y+1;
            		p = p + b2 * (2 * x + 3) - 2 * a2 * (y + 1);
        	}
        	x = x+1;
    	}
}

void Display_hyperbola_brute()
{
    	glClear(GL_COLOR_BUFFER_BIT);
    	glLoadIdentity();
    	glPointSize(3);
    	glColor3f(r, g, b);
    
    	int centre[2] = {(400+rand()%200), (400+rand()%200)};
    	hyperbola H = {centre[0], centre[1], focusa, focusb};
    	Brute(H);
    
    	glColor3f(0, 0, 0);
    	
    	int v_axis1[2] = {centre[0], 0};
    	int v_axis2[2] = {centre[0], 750};
    	//BLA(v_axis1, v_axis2);
    	
    	int h_axis1[2] = {0, centre[1]};
    	int h_axis2[2] = {1250, centre[1]};
    	//BLA(h_axis1, h_axis2);
    	
    	glutSwapBuffers();
}

void Display_hyperbola_parametric()
{
    	glClear(GL_COLOR_BUFFER_BIT);
    	glLoadIdentity();
    	glPointSize(3);
    	glColor3f(r, g, b);
    	
    	int centre[2] = {(400+rand()%200), (400+rand()%200)};
    	hyperbola H = {centre[0], centre[1], focusa, focusb};
    	Parametric(H);
    
    	glColor3f(0, 0, 0);
    	
    	int v_axis1[2] = {centre[0], 0};
    	int v_axis2[2] = {centre[0], 750};
    	//BLA(v_axis1, v_axis2);
    	
    	int h_axis1[2] = {0, centre[1]};
    	int h_axis2[2] = {1250, centre[1]};
    	//BLA(h_axis1, h_axis2);
    	
    	glutSwapBuffers();
}


void Display_hyperbola_mhd()
{
    	glClear(GL_COLOR_BUFFER_BIT);
    	glLoadIdentity();
   	glPointSize(3);
    	glColor3f(r, g, b);
    	
    	int centre[2] = {(400+rand()%200), (400+rand()%200)};
    	hyperbola H = {centre[0], centre[1], focusa, focusb};
    	MHD(H);
    
    	glColor3f(0, 0, 0);
    	
    	int v_axis1[2] = {centre[0], 0};
    	int v_axis2[2] = {centre[0], 750};
    	//BLA(v_axis1, v_axis2);
    	
    	int h_axis1[2] = {0, centre[1]};
    	int h_axis2[2] = {1250, centre[1]};
    	//BLA(h_axis1, h_axis2);
    	
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
  	glutInitWindowSize(750, 750);
  	
  	//focusa = -100 + rand()%300;
    	//focusb = -100 + rand()%300;
	focusa = 0;
	focusb = 0;
	
    	mode = rand() % 2;
 
   	glutCreateWindow("Hyperbola_MHD");
   	glutInitWindowPosition(0, 0); 
   	init();
    	glutDisplayFunc(Display_hyperbola_mhd);
    	
    	glutCreateWindow("Hyperbola_Parametric");
    	glutInitWindowPosition(2000, 1500); 
   	init();
    	glutDisplayFunc(Display_hyperbola_parametric);
    	
    	glutCreateWindow("Hyperbola_Brute");
    	glutInitWindowPosition(2800, 800);
   	init();
    	glutDisplayFunc(Display_hyperbola_brute);
    	
    	glutMainLoop();
    	return 0;
}

