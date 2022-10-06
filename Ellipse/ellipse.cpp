//g++ ellipse.cpp -o ell -lGL -lGLU -lglut -lGLEW
//./ell

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
void region1_symmetry(float c[2], float x, float y);
void region2_symmetry(float c[2], float x, float y);
void MED(ellipse ell);
void BLA(float point1[2], float point2[2]);
void PlotArc(float c[2], float x, float y);
void Display_arc(void);

float VerticalAxis;
float HorizontalAxis;

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

float random_color() 
{
    	float color=(float)((rand() % 150))/99;
   	return color;    
}

float r; float g; float b;

void region1_symmetry(float c[2], float x, float y)
{
    	pixel(x + c[0] , y + c[1]); //O1
    	pixel(-x + c[0] , y + c[1]); //O2
    	pixel(x + c[0] , -y + c[1]); //O3
    	pixel(-x + c[0] , -y + c[1]); //O4
}

void region2_symmetry(float c[2], float x, float y)
{
    	pixel(x + c[0] , y + c[1]); //O1
    	pixel(-x + c[0] , y + c[1]); //O2
    	pixel(x + c[0] , -y + c[1]); //O3
    	pixel(-x + c[0] , -y + c[1]); //O4
}

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
        	region1_symmetry(ell.centre, x, y);
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
        	region2_symmetry(ell.centre, x, y);
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

void parametric(ellipse ell)
{
    	float centre_x = ell.centre[0];
    	float centre_y = ell.centre[1];
    	float horizontal_radius_x = ell.radius_x;
    	float vertical_radius_y = ell.radius_y;
    
    	for(float i = 3.14*0; i <= 3.14*2; i = i + 0.001) // radians
    	{
        	pixel(centre_x + (horizontal_radius_x)*cos(i) , centre_y + (vertical_radius_y)*sin(i) ); // x+r*cosA,y+r*sinA
    	} 
}

void brute(ellipse ell)
{
    	float centre_x = ell.centre[0];
    	float centre_y = ell.centre[1];
    	float horizontal_radius_x = ell.radius_x;
    	float vertical_radius_y = ell.radius_y;
    	float a2 = horizontal_radius_x*horizontal_radius_x;
    	float b2 = vertical_radius_y*vertical_radius_y;
    	float y = b2; float x = 0;
    	
    	while (y >= 0)
    	{
        	region1_symmetry(ell.centre, x, y);
        	x = x+1;
        	y = sqrt((a2 - (x*x)) * (b2/a2));
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

void Display_ellipse_med()
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

void Display_ellipse_parametric()
{
    	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    	glLoadIdentity();
    
    	ellipse ell_1 = {{(400+rand()%200), (400+rand()%200)}, HorizontalAxis, VerticalAxis};
    	
    	glPointSize(1);
    	glColor3f(0.5, 0.5, 0.5);
    
    	float xAxis[2][2] = {{ell_1.centre[0] - 1000, ell_1.centre[1]}, {ell_1.centre[0] + 1000, ell_1.centre[1]}};
	float yAxis[2][2] = {{ell_1.centre[0], ell_1.centre[1] - 1000}, {ell_1.centre[0], ell_1.centre[1] + 1000}};
    
    	BLA(xAxis[0], xAxis[1]);
    	BLA(yAxis[0], yAxis[1]);
    
    	glColor3f(r, g, b);
    	glPointSize(3);
    	parametric(ell_1);
    
    	glFlush();
    	glutSwapBuffers();
}

void Display_ellipse_brute()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    	glLoadIdentity();
    
    	ellipse ell_1 = {{(400+rand()%200), (400+rand()%200)}, HorizontalAxis, VerticalAxis};
    	
    	glPointSize(1);
    	glColor3f(0.5, 0.5, 0.5);
    
    	float xAxis[2][2] = {{ell_1.centre[0] - 1000, ell_1.centre[1]}, {ell_1.centre[0] + 1000, ell_1.centre[1]}};
	float yAxis[2][2] = {{ell_1.centre[0], ell_1.centre[1] - 1000}, {ell_1.centre[0], ell_1.centre[1] + 1000}};
    
    	BLA(xAxis[0], xAxis[1]);
    	BLA(yAxis[0], yAxis[1]);
    
    	glColor3f(r, g, b);
    	glPointSize(3);
    	brute(ell_1);
    
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
  	glutInitWindowSize(500, 500);
  	
  	//HorizontalAxis = rand() % 500;
  	//VerticalAxis = rand() % 500;
  	
  	HorizontalAxis = 100;
  	VerticalAxis = 100;
   	
   	glutCreateWindow("Ellipse_MED");
   	glutInitWindowPosition(0, 0); 
   	init();
    	glutDisplayFunc(Display_ellipse_med);
    	
    	glutCreateWindow("Ellipse_Parametric");
    	glutInitWindowPosition(2000, 1500); 
   	init();
    	glutDisplayFunc(Display_ellipse_parametric);
    	
    	glutCreateWindow("Ellipse_Brute");
    	glutInitWindowPosition(2800, 800);
   	init();
    	glutDisplayFunc(Display_ellipse_brute);
    	
    	glutMainLoop();
    	return 0;
}

