//g++ BLA_hexagon.cpp -o hex -lGL -lGLU -lglut -lGLEW
//./hex
/*
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

float precision = 10;

vector<pair<float,float>> BLA_points;
vector<pair<float,float>> DDA_points;
vector<pair<float,float>> BRUTE_points;

int n1; int n2; int n3;

void pixel(float x, float y)
{
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
}

void mean_square_error()
{
	float MSE_BLA = 0;
	float MSE_DDA = 0;
	
	for(int i = 0; i < n1; i = i+1)
	{
		MSE_BLA = MSE_BLA + pow((BRUTE_points[i].first-BLA_points[i].first), 2) + pow((BRUTE_points[i].second-BLA_points[i].second), 2);
      	  	MSE_DDA = MSE_DDA + pow((BRUTE_points[i].first-DDA_points[i].first), 2) + pow((BRUTE_points[i].second-DDA_points[i].second), 2);
      	  	//sleep(2);
   	}
   	
   	MSE_BLA/=n1;
    	MSE_DDA/=n1;
    	
    	printf("MSE for BLA = %f and MSE for DDA = %f\n", MSE_BLA, MSE_DDA);
}     
                 
void DDA(float point_initial[2], float point_final[2])
{
	float x1 = point_initial[0]; float y1 = point_initial[1];
	float x2 = point_final[0]; float y2 = point_final[1];
	
	float distance_x = x2 - x1;
	float distance_y = y2 - y1;
	
	float length; float x_increment; float y_increment;
	if(abs(distance_x) > abs(distance_y))
	{
		length = abs(distance_x);
	}
	else
	{
		length = abs(distance_y);
	}
	
	x_increment = (distance_x/length);
	y_increment = (distance_y/length);
	
	float x; float y;
	x = x1;
	y = y1;
	for(int i = 0; i < length; i = i+1)
	{
		pixel(round(x), round(y));
		
		DDA_points.push_back(make_pair(x, y));
            	n1 = n1 + 1;
            	
		x = x + (x_increment);
		y = y + (y_increment);
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
            
            		BLA_points.push_back(make_pair(x1, y1));
            		n2 = n2 + 1;
            		
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
            
            		BLA_points.push_back(make_pair(x1, y1));
            		n2 = n2 + 1;
            		
            		y1 = y1 + distance_y/(abs(distance_y));
        	}
    	}	
}

void BRUTE(float point_initial[2], float point_final[2])
{
	float x1 = point_initial[0]; float y1 = point_initial[1];
	float x2 = point_final[0]; float y2 = point_final[1];
	
	float distance_x = x2 - x1;
	float distance_y = y2 - y1;
	
	float slope = (distance_y/distance_x);
	float c = y1 - (slope*x1);
    
    	if(abs(distance_y) <= abs(distance_x))
    	{
        	for(int i = 0; i < abs(distance_x); i = i+1)
        	{
        		pixel(round(x1), round(y1));
            
            		BRUTE_points.push_back(make_pair(x1,y1));
            		n3 = n3 + 1;
            		
            		y1 = slope*x1 + c;
            		x1 = x1 + distance_x/(abs(distance_x));
        	}
    	}
    	else
    	{
        	for(int i = 0; i < abs(distance_y); i = i+1)
       		{
       			pixel(round(x1), round(y1));
            
			BRUTE_points.push_back(make_pair(x1,y1));
            		n3 = n3 + 1;
            		
            		x1 = (y1-c)/slope;
            		y1 = y1 + distance_y/(abs(distance_y));
         		
        	}
    	}
}

void Display_hexagon(void)
{
    	n1 = n2 = n3 = 0;
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPointSize(4.0);
	glColor3f(0.0, 0.0, 0.0);
 	
 	float point1[2] = {300, 550};
 	float point2[2] = {600, 550};
	float point3[2] = {750, 325};
	float point4[2] = {600, 100};
	float point5[2] = {300, 100};
	float point6[2] = {150, 325};
    	
    	DDA(point1, point2);
	DDA(point2, point3);
	DDA(point3, point4);
	DDA(point4, point5);
	DDA(point5, point6);
	DDA(point6, point1);
	
	BLA(point1, point2);
	BLA(point2, point3);
	BLA(point3, point4);
	BLA(point4, point5);
	BLA(point5, point6);
	BLA(point6, point1);
	
	BRUTE(point1, point2);
	BRUTE(point2, point3);
	BRUTE(point3, point4);
	BRUTE(point4, point5);
	BRUTE(point5, point6);
	BRUTE(point6, point1);
    	
    	mean_square_error();
	
	glFlush();
   	glutSwapBuffers();
    	//glFinish();
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
}*/

#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <math.h>
#include <time.h>
using namespace std;

float alpha;
float beta;
float arcRadius;

float checkAngle;

struct circle
{
    float c[2];
    float r;
};

void changeViewPort(int w, int h) ;
void myinit(void);
void Pixel(float x, float y);
void PlotOctants(float c[2], float x, float y);
void PlotArc(float c[2], float x, float y);
void mcd(circle cir, int mode);
void BLD(float point1[2], float point2[2]);
void PlotArc(float c[2], float x, float y);
void draw_arcs();

void changeViewPort(int w, int h) 
{
	if(w>=h)
		glViewport(w/2-h/2, 0, h, h);
	else
		glViewport(0, h/2-w/2, w, w);
}

void myinit(void)
{
	glClearColor(0.8,0.8,0.8,0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D (0.0,1000.0,0.0,1000.0);
	glMatrixMode(GL_MODELVIEW);
}

void Pixel(float x, float y)
{
	glBegin(GL_POINTS);
	glVertex2f(x,y);
	glEnd();
}

void PlotOctants(float c[2], float x, float y)
{
    Pixel(c[0] + y, c[1] + x); //O1
    Pixel(c[0] + x, c[1] + y); //O2
    Pixel(c[0] - x, c[1] + y); //O3
    Pixel(c[0] - y, c[1] + x); //O4

    Pixel(c[0] - y, c[1] - x); //O5
    Pixel(c[0] - x, c[1] - y); //O6
    Pixel(c[0] + x, c[1] - y); //O7
    Pixel(c[0] + y, c[1] - x); //O8
}

void mcd(circle cir, int mode)
{
    float x = 0;
    float y = cir.r;

    float p = 1 - cir.r;

    int x_limit = cir.r / sqrt(2);

    for (int i = 0; i < x_limit; i++)
    {

        if (mode == 0)
            PlotOctants(cir.c, x, y);
        else
            PlotArc(cir.c, x, y);
        if (p < 0) //y does not change
            p += 2 * x + 3;
        else //y decrement
        {
            p += 2 * x - 2 * y + 5;
            y--;
        }
        x++;
    }
}

void BLD(float point1[2], float point2[2])
{
	int x1 = point1[0], y1 = point1[1];
	int x2 = point2[0], y2 = point2[1];

	int dx = (int)(x2 - x1);
	int dy = (int)(y2 - y1);
	int p;

	if (abs(dy) <= abs(dx))
	{
		p = 2 * abs(dy) - abs(dx);
		for (int i = 0; i < abs(dx); i++)
		{
			
			if (p >= 0)
			{
				p += (2 * abs(dy) - 2 * abs(dx));
				y1 += dy / abs(dy);
			}
			else
			{
				p += (2 * abs(dy));
			}
			x1 += dx / (abs(dx));

			
			Pixel(round(x1), round(y1));
			

			
		}
	}
	else
	{
		p = 2 * abs(dx) - abs(dy);
		for (int i = 0; i < abs(dy); i++)
		{
            

			if (p >= 0)
			{
				p += (2 * abs(dx) - 2 * abs(dy));
				x1 += dx / abs(dx);
			}
			else
			{
				p += (2 * abs(dx));
			}
			y1 += dy / (abs(dy));

			Pixel(round(x1), round(y1));

		}
	}
}

void PlotArc(float c[2], float x, float y)
{
    float lowerAngle = 0;
    float upperAngle = beta;

    checkAngle = (180 / M_PI) * atan2(x, y) + 0; //O1 y,x
    if (checkAngle >= lowerAngle && checkAngle <= upperAngle)
        Pixel(c[0] + y, c[1] + x); //O1

    checkAngle = (180 / M_PI) * atan2(y, x) + 0; //O2 x,y
    if (checkAngle >= lowerAngle && checkAngle <= upperAngle)
        Pixel(c[0] + x, c[1] + y); //O2

    checkAngle = (180 / M_PI) * atan2(y, -x) + 0; //O3 -x,y
    if (checkAngle >= lowerAngle && checkAngle <= upperAngle)
        Pixel(c[0] - x, c[1] + y); //O3

    checkAngle = (180 / M_PI) * atan2(x, -y) + 0; //O4 -y,x
    if (checkAngle >= lowerAngle && checkAngle <= upperAngle)
        Pixel(c[0] - y, c[1] + x); //O4

    checkAngle = (180 / M_PI) * atan2(-x, -y) + 360; //O5 -y,-x
    if (checkAngle >= lowerAngle && checkAngle <= upperAngle)
        Pixel(c[0] - y, c[1] - x); //O5

    checkAngle = (180 / M_PI) * atan2(-y, -x) + 360; //O6 -x,-y
    if (checkAngle >= lowerAngle && checkAngle <= upperAngle)
        Pixel(c[0] - x, c[1] - y); //O6

    checkAngle = (180 / M_PI) * atan2(-y, x) + 360; //O7 x,-y
    if (checkAngle >= lowerAngle && checkAngle <= upperAngle)
        Pixel(c[0] + x, c[1] - y); //O7

    checkAngle = (180 / M_PI) * atan2(-x, y) + 360; //O8 y,-x
    if (checkAngle >= lowerAngle && checkAngle <= upperAngle)
        Pixel(c[0] + y, c[1] - x); //O8
}

void draw_arcs()
{

    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    circle arc = {{500, 500}, arcRadius};
   

    float arcBeginning[2] = {arc.c[0] + arcRadius * (float)cos(0 * M_PI / 180), arc.c[1] + arcRadius * (float)sin(0 * M_PI / 180)};
    float arcEnding[2] = {arc.c[0] + arcRadius * (float)cos((beta) * M_PI / 180), arc.c[1] + arcRadius * (float)sin((beta) * M_PI / 180)};
    glPointSize(1);
    glColor3f(0.5, 0.5, 0.5);
    
    //rotate
    glTranslatef(arc.c[0], arc.c[1], 0);
    glRotatef(alpha, 0, 0, 1);
    glTranslatef(-arc.c[0], -arc.c[1], 0);

    BLD(arc.c, arcBeginning);
    BLD(arc.c, arcEnding);
    glPointSize(5);
    glColor3f(0, 0, 0);
    mcd(arc, 1);

    glutSwapBuffers();
}


int main(int argc, char **argv)
{
    srand(time(0));
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(500, 500);

    cout<<"enter alpha"<<endl;
    cin>>alpha;
    cout<<"enter Beta"<<endl;
    cin>>beta;
    cout<<"Enter Radius"<<endl;
    cin>>arcRadius;

    glutCreateWindow("CED18I039_ARC_MCD");
    myinit();
    glutDisplayFunc(draw_arcs);
    glutReshapeFunc(changeViewPort);
    glutMainLoop();
}
