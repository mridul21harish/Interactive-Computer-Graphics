//g++ ellipse_arc.cpp -o arc -lGL -lGLU -lglut -lGLEW
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

struct ellipse
{
    	float centre[2];
    	float radius_x;
    	float radius_y;
};

void init(void);
void pixel(float x, float y);
int check_angle(float x, float y);
void MED(ellipse ell);
void BLA(float point1[2], float point2[2]);
void Draw_arc(float c[2], float x, float y);
void Display_arc(void);

float alpha;
float beta;
float VerticalAxis;
float HorizontalAxis;

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

float random_color() 
{
    	float color=(float)((rand() % 150))/99;
   	return color;    
}

float r; float g; float b;

void MED(ellipse ell)
{
	float dx; float dy; float d1; float d2; float x; float y;
    	x = 0;
    	y = ell.radius_y;
 
    	// Initial decision parameter of region 1
    	d1 = (ell.radius_y * ell.radius_y) - (ell.radius_x * ell.radius_x * ell.radius_y) + (0.25 * ell.radius_x * ell.radius_x);
    	dx = 2 * ell.radius_y * ell.radius_y * x;
    	dy = 2 * ell.radius_x * ell.radius_x * y;
 
    	// For region 1 (octant 2 esque)
    	while (dx < dy)
    	{
        	// Print points based on 4-way symmetry
        	Draw_arc(ell.centre, x, y);
        	// Checking and updating value of decision parameter based on algorithm
        	if (d1 < 0)
        	{
            		x = x+1;
            		dx = dx + (2 * ell.radius_y * ell.radius_y);
            		d1 = d1 + dx + (ell.radius_y * ell.radius_y);
        	}
        	else
        	{
            		x = x+1;
            		y = y-1;
            		dx = dx + (2 * ell.radius_y * ell.radius_y);
            		dy = dy - (2 * ell.radius_x * ell.radius_x);
            		d1 = d1 + dx - dy + (ell.radius_y * ell.radius_y);
        	}
    	}
 
    	// Decision parameter of region 2
    	d2 = ((ell.radius_y * ell.radius_y) * ((x + 0.5) * (x + 0.5))) + ((ell.radius_x * ell.radius_x) * ((y - 1) * (y - 1))) - (ell.radius_x * ell.radius_x * ell.radius_y * ell.radius_y);
 
    	// Plotting points of region 2
    	while (y >= 0)
    	{
        	// Print points based on 4-way symmetry
        	Draw_arc(ell.centre, x, y);
        	// Checking and updating parameter value based on algorithm
        	if (d2 > 0)
        	{
            		y = y-1;
            		dy = dy - (2 * ell.radius_x * ell.radius_x);
            		d2 = d2 + (ell.radius_x * ell.radius_x) - dy;
        	}
        	else
        	{
            		y = y-1;
            		x = x+1;
            		dx = dx + (2 * ell.radius_y * ell.radius_y);
            		dy = dy - (2 * ell.radius_x * ell.radius_x);
            		d2 = d2 + dx - dy + (ell.radius_x * ell.radius_x);
        	}
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

int check_angle(float x, float y)
{
	
    	float lower_angle;
    	float upper_angle;

    	float point_angle = (180 / M_PI) * atan2(x, y);
    	if(point_angle < 0)
    	{
    		point_angle = point_angle + 360;
    	}
    	
    	if(alpha >= 0 && beta >= 0)
    	{
    		lower_angle = alpha;
    		upper_angle = beta + alpha;
    	
    		if(upper_angle > 360)
    		{
    			upper_angle = upper_angle - 360; //rollover
    			if(point_angle >= lower_angle || point_angle <= upper_angle)
    			{
    				return 1;
    			}
    			else
    			{
    				return 0;
    			}
    		}
    		else
    		{
    			if(point_angle >= lower_angle && point_angle <= upper_angle)
    			{
    				return 1;
    			}
    			else
    			{
    				return 0;
    			}
    		}
    	}
    	else if(alpha < 0 && beta >= 0)
    	{
    		lower_angle = alpha + 360; //making it positive
    		upper_angle = lower_angle + beta;
    		
    		if(upper_angle > 360)
    		{
    			upper_angle = upper_angle - 360; //rollover
    			if(point_angle >= lower_angle || point_angle <= upper_angle)
    			{
    				return 1;
    			}
    			else
    			{
    				return 0;
    			}
    		}
    		else
    		{
    			if(point_angle >= lower_angle && point_angle <= upper_angle)
    			{
    				return 1;
    			}
    			else
    			{
    				return 0;
    			}
    		}
    	}
    	else if(alpha >= 0 && beta < 0)
    	{
    		upper_angle = alpha;
    		lower_angle = alpha + beta; //less than upper, maybe -ve
    		
    		if(lower_angle < 0)
    		{
    			lower_angle = lower_angle + 360;
    			if(point_angle >= lower_angle || point_angle <= upper_angle)
    			{
    				return 1;
    			}
    			else
    			{
    				return 0;
    			}
    		}
    		else
    		{
    			if(point_angle >= lower_angle && point_angle <= upper_angle)
    			{
    				return 1;
    			}
    			else
    			{
    				return 0;
    			}
    		}
    	}
    	else //both negative
    	{
    		upper_angle = alpha + 360; //>0
    		lower_angle = 360 + (alpha + beta); //<360
    		
    		if(lower_angle < 0)
    		{
    			lower_angle = lower_angle + 360;
    			if(point_angle >= lower_angle || point_angle <= upper_angle)
    			{
    				return 1;
    			}
    			else
    			{
    				return 0;
    			}
    		}
    		else
    		{
    			if(point_angle >= lower_angle && point_angle <= upper_angle)
    			{
    				return 1;
    			}
    			else
    			{
    				return 0;
    			}
    		}
    	}
    	return 0;
}

void Draw_arc(float c[2], float x, float y)
{
	if(check_angle(x, y) == 1)
	{
		pixel(c[0] + x, c[1] + y);
	}
	if(check_angle(-x, y) == 1)
	{
		pixel(c[0] - x, c[1] + y);
	}
	if(check_angle(-x, -y) == 1)
	{
		pixel(c[0] - x, c[1] - y);
	}
	if(check_angle(x, -y) == 1)
	{
		pixel(c[0] + x, c[1] - y);
	}
}

void Display_arc()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glLoadIdentity();
    			
    	ellipse ell = {{(400+rand()%200), (400+rand()%200)}, HorizontalAxis, VerticalAxis};
    	
    	glPointSize(1);
    	glColor3f(0.5, 0.5, 0.5);
    	
    	float xAxis[2][2] = {{ell.centre[0] - 1000, ell.centre[1]}, {ell.centre[0] + 1000, ell.centre[1]}};
    	float yAxis[2][2] = {{ell.centre[0], ell.centre[1] - 1000}, {ell.centre[0], ell.centre[1] + 1000}};
    	
    	BLA(xAxis[0], xAxis[1]);
    	BLA(yAxis[0], yAxis[1]);
    	
    	glColor3f(r, g, b);
    	glPointSize(3);
    	MED(ell);
    	
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
  	
  	alpha = -360 + rand() % 720;
  	beta = -360 + rand() % 720;
  	HorizontalAxis = rand() % 500;
  	VerticalAxis = rand() % 500;
   	
   	glutCreateWindow("Ellipse_arc_MED");
   	glutInitWindowPosition(0, 0); 
   	init();
    	glutDisplayFunc(Display_arc);
    	
    	glutMainLoop();
    	return 0;
}		
