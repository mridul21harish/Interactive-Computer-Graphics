//g++ lineclipping.cpp -o lc -lGL -lGLU -lglut -lGLEW
//./lc

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

#define LENGTH 600
#define HEIGHT 600

void window_color()
{
	glClearColor(1.0,1.0,1.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

int signvalue(int p)
{
	int k;
	if(p > 0)
	{
		k = 1;
	}
	else
	{
		k = 0;
	}
    	return k;
}

void CSA(int xmin, int ymin, int xmax, int ymax, int x1, int y1, int x2, int y2)
{
	printf("CSA Algorithm;\n");
	printf("Before Clipping : P1 = (%d, %d), P2 = (%d, %d)\n", x1, y1, x2, y2);
    	int k = 0;
    	string seq1 = ""; 
    	string seq2 = "";
    	do
    	{
        	//Region codes for x1,y1
        	seq1 = seq1 + (char)(signvalue(y1-ymax) + 48);
        	seq1 = seq1 + (char)(signvalue(ymin-y1) + 48);
        	seq1 = seq1 + (char)(signvalue(x1-xmax) + 48);
        	seq1 = seq1 + (char)(signvalue(xmin-x1) + 48);

        	//Region codes for x2,y2
        	seq2 = seq2 + (char)(signvalue(y2-ymax) + 48);
        	seq2 = seq2 + (char)(signvalue(ymin-y2) + 48);
        	seq2 = seq2 + (char)(signvalue(x2-xmax) + 48);
        	seq2 = seq2 + (char)(signvalue(xmin-x2) + 48);

        	bitset<4> b1(seq1), b2(seq2);
        	bitset<4>c = b1&b2;

        	if(b1 == 0000 && b2 == 0000)
        	{
            		//Trivially accept
            		printf("After Clipping : P1 = (%d, %d), P2 = (%d, %d)\n", x1, y1, x2, y2);
            		
            		glPointSize(3.5);
            		glColor3f(1, 0, 0);
            		glBegin(GL_LINES);
                		glVertex2f(x1,y1);
                		glVertex2f(x2,y2);
            		glEnd();
            		break;
        	}
        	else if((c[0] | c[1] | c[2] | c[3]) == 1)
        	{
            		//Trivially reject
            		printf("The line is not inside the window\n");
            		break;
        	}
        	else
        	{
            		float slope = (float)(y2-y1)/(float)(x2-x1);
            		float x;
            		float y;
            		if(b1 != 0000)
            		{
                		if(b1[0] == 1) // x<xmin
                		{
                			x = xmin;
                			y = y1 + slope*(xmin - x1);   
                		}
                		else if(b1[1] == 1) // x>xmax
                		{
                			x = xmax;
                			y = y1 + slope*(xmax - x1);   
                		}
                		else if(b1[2] == 1) // y<ymin
                		{
               				y = ymin;
                			x = x1 + (1/slope)*(ymin - y1);
                		}
                		else if(b1[3] == 1) // y>ymax
                		{
                			y = ymax;
                			x = x1 + (1/slope)*(ymax - y1);
                		}
                		else;
                			x1 = x;
                			y1 = y;
            		}
            		else
            		{
                		if(b2[0] == 1) // x<xmin
                		{
                			x = xmin;
                			y = y1 + slope*(xmin - x1);   
                		}
                		else if(b2[1] == 1) // x>xmax
                		{
                			x = xmax;
                			y = y1 + slope*(xmax - x1);   
                		}
                		else if(b2[2] == 1) // y<ymin
                		{
                			y = ymin;
                			x = x1 + (1/slope)*(ymin - y1);
                		}
                		else if(b2[3] == 1) // y>ymax
                		{
                			y = ymax;
                			x = x1 + (1/slope)*(ymax - y1);
                		}
                		else;
                		x2 = x;
                		y2 = y;
            		}     
        	}
        	seq1 = "";
        	seq2 = "";  
    	}while(1);
}

void LBA(int xmin, int ymin, int xmax, int ymax, int x1, int y1, int x2, int y2)
{
    	printf("LBA Algorithm;\n");
	printf("Before Clipping : P1 = (%d, %d), P2 = (%d, %d)\n", x1, y1, x2, y2);
    	int xa; int xb; int ya; int yb;
    	int delx = x2-x1;
    	int dely = y2-y1;
    	int p[4] = {-delx, delx, -dely, dely};
    	int q[4] = {x1-xmin, xmax-x1, y1-ymin, ymax-y1};
    	float u; float u1; float u2;
    	vector<float> m1; vector<float> m2;
    	int k = 0;
    	for(int i = 0; i < 4; i = i+1)
    	{
        	if(p[i] == 0 && q[i] < 0)
        	{
            		printf("The line is not inside the window\n");
            		k = 1;
            		break;
        	}
    	}
    	if(k != 1)
    	{
        	m1.push_back(0);
        	m2.push_back(1);
       		for(int i = 0; i < 4; i = i+1)
       		{
           		u = (float)q[i]/(float)p[i];
           		if(p[i] < 0)
            			m1.push_back(u);
           		else if(p[i] > 0)
            			m2.push_back(u);
           		else;
       		}
        	u1 = *max_element(m1.begin(),m1.end());
        	u2 = *min_element(m2.begin(),m2.end());
       		
       		xa = x1 + u1*delx;
       		ya = y1 + u1*dely;
       		printf("After Clipping : P1 = (%d, %d), ", xa, ya);
       		xb = x1 + u2*delx;
       		yb = y1 + u2*dely;
		printf("P2 = (%d, %d)\n", xb, yb);
		
		if(xa >= xmin && xa <= xmax && ya >= ymin && ya <= ymax && xb >= xmin && xb <= xmax && yb >= ymin && yb <= ymax)
		{
			glPointSize(3.5);
            		glColor3f(1, 0, 0);
            		glBegin(GL_LINES);
                		glVertex2f(xa,ya);
                		glVertex2f(xb,yb);
            		glEnd();
            	}
    	}
}

void Display_CSA()
{
    
	window_color();
    	srand(time(0));
    	
    	int xmin = rand()%300+100;
    	int ymin = rand()%300+100;
    	int xmax = rand()%300+300;
    	int ymax = rand()%300+300;
    	
    	glColor3f(0,0,0);
    	glBegin(GL_LINE_LOOP);
        	glVertex2f(xmin,ymin);
        	glVertex2f(xmin,ymax);
        	glVertex2f(xmax,ymax);
        	glVertex2f(xmax,ymin);
    	glEnd();
    	
   	int n = 15;
    	int x1; int y1; int x2; int y2;
    	for(int i = 0; i < n; i = i+1)
    	{
        	x1 = rand()%600;
        	y1 = rand()%600;
        	x2 = rand()%600;
        	y2 = rand()%600;
        	CSA(xmin, ymin, xmax, ymax, x1, y1, x2, y2);
    	}
	glFlush();
}

void Display_LBA()
{
    
	window_color();
    	srand(time(0));
    	
    	int xmin = rand()%300+100;
    	int ymin = rand()%300+100;
    	int xmax = rand()%300+300;
    	int ymax = rand()%300+300;
    	
    	glColor3f(0,0,0);
    	glBegin(GL_LINE_LOOP);
        	glVertex2f(xmin,ymin);
        	glVertex2f(xmin,ymax);
        	glVertex2f(xmax,ymax);
        	glVertex2f(xmax,ymin);
    	glEnd();
    	
   	int n = 15;
    	int x1; int y1; int x2; int y2;
    	for(int i = 0; i < n; i = i+1)
    	{
        	x1 = rand()%600;
        	y1 = rand()%600;
        	x2 = rand()%600;
        	y2 = rand()%600;
        	LBA(xmin, ymin, xmax, ymax, x1, y1, x2, y2);
    	}
	glFlush();
}

int main(int argc,char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(LENGTH, HEIGHT);
	
	glutCreateWindow("Line Clipping CSA");
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, LENGTH, 0.0, HEIGHT);
	glutDisplayFunc(Display_CSA);
	
	glutCreateWindow("Line Clipping LBA");
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, LENGTH, 0.0, HEIGHT);
	glutDisplayFunc(Display_LBA);
	glutMainLoop();
}
