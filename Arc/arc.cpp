//g++ arc.cpp -o arc -lGL -lGLU -lglut -lGLEW
//./arc

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

struct circle
{
    	float centre[2];
    	float radius;
};

void init(void);
void pixel(float x, float y);
void octants(float c[2], float x, float y);
void PlotArc(float c[2], float x, float y);
void MCD(circle cir, int mode);
void BLA(float point1[2], float point2[2]);
void PlotArc(float c[2], float x, float y);
void Display_arc(void);

float alpha;
float beta;
float arc_radius;

float check_angle;

void pixel(float x, float y)
{
	glBegin(GL_POINTS);
	glVertex2f(x,y);
	glEnd();
}

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 1200.0, 0.0, 750.0);
	glMatrixMode(GL_MODELVIEW);
}

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

void MCD(circle cir, int mode)
{
    	float x = 0;
    	float y = cir.radius;

    	float p = 1 - cir.radius;

    	int x_limit = cir.radius / sqrt(2);

    	for (int i = 0; i < x_limit; i++)
    	{
		if (mode == 0)
            		octants(cir.centre, x, y);
        	else
            		PlotArc(cir.centre, x, y);
        
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

void PlotArc(float c[2], float x, float y)
{
    	float lower_angle = 0;
    	float upper_angle = beta;

    	check_angle = (180 / M_PI) * atan2(x, y) + 0; //O1 y,x
    	if (check_angle >= lower_angle && check_angle <= upper_angle)
        	pixel(c[0] + y, c[1] + x); //O1

    	check_angle = (180 / M_PI) * atan2(y, x) + 0; //O2 x,y
    	if (check_angle >= lower_angle && check_angle <= upper_angle)
        	pixel(c[0] + x, c[1] + y); //O2

    	check_angle = (180 / M_PI) * atan2(y, -x) + 0; //O3 -x,y
    	if (check_angle >= lower_angle && check_angle <= upper_angle)
        	pixel(c[0] - x, c[1] + y); //O3

    	check_angle = (180 / M_PI) * atan2(x, -y) + 0; //O4 -y,x
    	if (check_angle >= lower_angle && check_angle <= upper_angle)
        	pixel(c[0] - y, c[1] + x); //O4

    	check_angle = (180 / M_PI) * atan2(-x, -y) + 360; //O5 -y,-x
    	if (check_angle >= lower_angle && check_angle <= upper_angle)
        	pixel(c[0] - y, c[1] - x); //O5

    	check_angle = (180 / M_PI) * atan2(-y, -x) + 360; //O6 -x,-y
    	if (check_angle >= lower_angle && check_angle <= upper_angle)
        	pixel(c[0] - x, c[1] - y); //O6

    	check_angle = (180 / M_PI) * atan2(-y, x) + 360; //O7 x,-y
    	if (check_angle >= lower_angle && check_angle <= upper_angle)
        	pixel(c[0] + x, c[1] - y); //O7

    	check_angle = (180 / M_PI) * atan2(-x, y) + 360; //O8 y,-x
    	if (check_angle >= lower_angle && check_angle <= upper_angle)
        	pixel(c[0] + y, c[1] - x); //O8
}

void Display_arc(void)
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	
	circle arc = {{600, 375}, arc_radius};
    
    	float arc_beginning[2] = {arc.centre[0] + arc_radius * (float)cos(0 * M_PI / 180), arc.centre[1] + arc_radius * (float)sin(0 * M_PI / 180)};
    	float arc_ending[2] = {arc.centre[0] + arc_radius * (float)cos((beta) * M_PI / 180), arc.centre[1] + arc_radius * (float)sin((beta) * M_PI / 180)};
    	glPointSize(2);
    	glColor3f(0.5, 0.5, 0.5);
    
    	//rotate
    	glTranslatef(arc.centre[0], arc.centre[1], 0);
    	glRotatef(alpha, 0, 0, 1);
    	glTranslatef(-arc.centre[0], -arc.centre[1], 0);

    	BLA(arc.centre, arc_beginning);
    	BLA(arc.centre, arc_ending);
    	glPointSize(5.0);
    	glColor3f(0, 0, 0);
    	MCD(arc, 1);
	
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
   	
   	cout<<"Enter the value of alpha"<<endl;
    	cin>>alpha;
    	cout<<"Enter the value of Beta"<<endl;
    	cin>>beta;
    	cout<<"Enter the valRadius"<<endl;
    	cin>>arc_radius;

   	glutCreateWindow("Arc");
   	init();
    	glutDisplayFunc(Display_arc);
    	glutMainLoop();
    	return 0;
}
