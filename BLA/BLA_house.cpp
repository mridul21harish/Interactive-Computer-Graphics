//g++ BLA_house.cpp -o house -lGL -lGLU -lglut -lGLEW
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
#include <unistd.h>
using namespace std;

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 100.0, 0.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

vector<pair<float,float>> BLA_points;
vector<pair<float,float>> DDA_points;
vector<pair<float,float>> BRUTE_points;

int n1; int n2; int n3;

float precision = 50;

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
      	  	printf("MSE for BLA = %f and MSE for DDA = %f\n", MSE_BLA, MSE_DDA);
      	  	sleep(2);
   	}
   	
   	MSE_BLA/=n1;
    	MSE_DDA/=n1;
    	
    	printf("MSE for BLA = %f and MSE for DDA = %f\n", MSE_BLA, MSE_DDA);
}     
                 
void DDA(float point_initial[2], float point_final[2], int check)
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
		
		if(check == 1)
		{
			DDA_points.push_back(make_pair(x, y));
            		n1 = n1 + 1;
            	}
		x = x + (x_increment);
		y = y + (y_increment);
	}
}

void Triangle_color_dda(float point1[2], float point2[2], float point3[2])
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
		DDA(point3, point, 0); 
		point[0] += x_increment/precision;
		point[1] += y_increment/precision;
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
	
void Display_house(void)
{
   	n1 = n2 = n3 = 0;
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPointSize(4.0);

	//lower part
	float point_a[2] = {20, 10};
	float point_b[2] = {60, 10};
	float point_c[2] = {60, 50};
	float point_d[2] = {20, 50};

	glColor3f(1.0, 0.0, 0.0);
	Triangle_color_dda(point_a, point_c, point_b);
	Triangle_color_dda(point_a, point_c, point_d);

	glColor3f(0,0,0); //black outline
	DDA(point_a, point_b, 1);
	DDA(point_b, point_c, 1);
	DDA(point_c, point_d, 1);
	DDA(point_d, point_a, 1);
	
	BRUTE(point_a, point_b);
	BRUTE(point_b, point_c);
	BRUTE(point_c, point_d);
	BRUTE(point_d, point_a);
	
	BLA(point_a, point_b);
	BLA(point_b, point_c);
	BLA(point_c, point_d);
	BLA(point_d, point_a);

	//upper part
	float point_e[2] = {40, 80};
	glColor3f(0.0, 0.0, 1.0);
	Triangle_color_dda(point_c, point_d, point_e);

	glColor3f(0,0,0); //black outline
	DDA(point_c, point_d, 1);
	DDA(point_d, point_e, 1);
	DDA(point_e, point_c, 1);
	
	BRUTE(point_c, point_d);
	BRUTE(point_d, point_e);
	BRUTE(point_e, point_c);
	
	BLA(point_c, point_d);
	BLA(point_d, point_e);
	BLA(point_e, point_c);

	//door	
	float point_f[2] = {35, 10};
	float point_g[2] = {45, 10};
	float point_h[2] = {45, 30};
	float point_i[2] = {35, 30};

	glColor3f(1.0, 1.0, 1.0);//white
	Triangle_color_dda(point_f, point_h, point_g);
	Triangle_color_dda(point_f, point_h, point_i);

	glColor3f(0,0,0); //black outline
	DDA(point_f, point_g, 1);
	DDA(point_g, point_h, 1);
	DDA(point_h, point_i, 1);
	DDA(point_i, point_f, 1);
	
	BRUTE(point_f, point_g);
	BRUTE(point_g, point_h);
	BRUTE(point_h, point_i);
	BRUTE(point_i, point_f);
	
	BLA(point_f, point_g);
	BLA(point_g, point_h);
	BLA(point_h, point_i);
	BLA(point_i, point_f);

	//left window
	float point_j[2] = {25, 25}; 
    	float point_k[2] = {30, 25};
    	float point_l[2] = {30, 30};
    	float point_m[2] = {25, 30};

	glColor3f(1.0, 1.0, 1.0);//white
	Triangle_color_dda(point_j, point_l, point_k);
	Triangle_color_dda(point_j, point_l, point_m);

	glColor3f(0,0,0); //black outline
	DDA(point_j, point_k, 1);
	DDA(point_k, point_l, 1);
	DDA(point_l, point_m, 1);
	DDA(point_m, point_j, 1);
	
	BRUTE(point_j, point_k);
	BRUTE(point_k, point_l);
	BRUTE(point_l, point_m);
	BRUTE(point_m, point_j);
	
	BLA(point_j, point_k);
	BLA(point_k, point_l);
	BLA(point_l, point_m);
	BLA(point_m, point_j);

	//right window
	float point_n[2] = {50, 25}; 
    	float point_o[2] = {55, 25};
    	float point_p[2] = {55, 30};
    	float point_q[2] = {50, 30};

	glColor3f(1.0, 1.0, 1.0);//white
	Triangle_color_dda(point_n, point_p, point_o);
	Triangle_color_dda(point_n, point_p, point_q);

	glColor3f(0,0,0); //black outline
	DDA(point_n, point_o, 1);
	DDA(point_o, point_p, 1);
	DDA(point_p, point_q, 1);
	DDA(point_q, point_n, 1);
	
	BRUTE(point_n, point_o);
	BRUTE(point_o, point_p);
	BRUTE(point_p, point_q);
	BRUTE(point_q, point_n);
	
	BLA(point_n, point_o);
	BLA(point_o, point_p);
	BLA(point_p, point_q);
	BLA(point_q, point_n);
	
	cout<<BLA_points[0].first<<DDA_points[0].first<<BRUTE_points[0].first<<endl;
	cout<<BLA_points[1].first<<DDA_points[1].first<<BRUTE_points[1].first<<endl;
	cout<<BLA_points[2].first<<DDA_points[2].first<<BRUTE_points[2].first<<endl;
	cout<<BLA_points[3].first<<DDA_points[3].first<<BRUTE_points[3].first<<endl;
	cout<<BLA_points[4].first<<DDA_points[4].first<<BRUTE_points[4].first<<endl;
	cout<<BLA_points[5].first<<DDA_points[5].first<<BRUTE_points[5].first<<endl;
	
	cout<<BLA_points[0].second<<DDA_points[0].second<<BRUTE_points[0].second<<endl;
	cout<<BLA_points[1].second<<DDA_points[1].second<<BRUTE_points[1].second<<endl;
	cout<<BLA_points[2].second<<DDA_points[2].second<<BRUTE_points[2].second<<endl;
	cout<<BLA_points[3].second<<DDA_points[3].second<<BRUTE_points[3].second<<endl;
	cout<<BLA_points[4].second<<DDA_points[4].second<<BRUTE_points[4].second<<endl;
	cout<<BLA_points[5].second<<DDA_points[5].second<<BRUTE_points[5].second<<endl;
	
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
  	glutInitWindowSize(400, 300);
   	glutInitWindowPosition(0, 0); 
   	glutCreateWindow("House");
   	init();
    	glutDisplayFunc(Display_house);
    	glutMainLoop();
    	return 0;
}
