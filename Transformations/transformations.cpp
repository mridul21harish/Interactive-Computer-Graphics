//g++ transformations.cpp -o tf -lGL -lGLU -lglut -lGLEW
//./tf

#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <GL/glut.h>
using namespace std;

int pntX1; int pntY1; int choice = 0; int edges;
vector<int> pntX;
vector<int> pntY;
int transX; int transY;
double scaleX; double scaleY;
double angle; double angleRad;
char reflectionAxis; 
char shearingAxis;
int shearingX; char shearingY;

double round(double d)
{
	return floor(d + 0.5);
}

void drawPolygon()
{
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	for (int i = 0; i < edges; i = i+1)
	{
		glVertex2i(pntX[i], pntY[i]);
	}
	glEnd();
}


void drawPolygonTrans(int x, int y)
{
	glBegin(GL_POLYGON);
	glColor3f(0.0, 1.0, 0.0);
	for (int i = 0; i < edges; i = i+1)
	{
		glVertex2i(pntX[i] + x, pntY[i] + y);
	}
	glEnd();
}

void drawPolygonScale(double x, double y)
{
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 1.0);
	for (int i = 0; i < edges; i = i+1)
	{
		glVertex2i(round(pntX[i] * x), round(pntY[i] * y));
	}
	glEnd();
}

void drawPolygonRotation(double angleRad)
{
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 1.0);
	for (int i = 0; i < edges; i = i+1)
	{
		glVertex2i(round((pntX[i] * cos(angleRad)) - (pntY[i] * sin(angleRad))), round((pntX[i] * sin(angleRad)) + (pntY[i] * cos(angleRad))));
	}
	glEnd();
}

void drawPolygonMirrorReflection(char reflectionAxis)
{
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 1.0);

	if (reflectionAxis == 'x' || reflectionAxis == 'X')
	{
		for (int i = 0; i < edges; i = i+1)
		{
			glVertex2i(round(pntX[i]), round(pntY[i] * -1));

		}
	}
	else if (reflectionAxis == 'y' || reflectionAxis == 'Y')
	{
		for (int i = 0; i < edges; i = i+1)
		{
			glVertex2i(round(pntX[i] * -1), round(pntY[i]));
		}
	}
	else if (reflectionAxis == 'z' || reflectionAxis == 'z')
	{
		for (int i = 0; i < edges; i = i+1)
		{
			glVertex2i(round(pntY[i]), round(pntX[i]));
		}
	}
	else if (reflectionAxis == 'w' || reflectionAxis == 'w')
	{
		for (int i = 0; i < edges; i = i+1)
		{
			glVertex2i(round(pntY[i] * -1), round(pntX[i] * -1));
		}
	}
	glEnd();
}

void drawPolygonShearing()
{
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 1.0);

	if (shearingAxis == 'x' || shearingAxis == 'X')
	{
		glVertex2i(pntX[0], pntY[0]);

		glVertex2i(pntX[1] + shearingX, pntY[1]);

		glVertex2i(pntX[2] + shearingX, pntY[2]);

		glVertex2i(pntX[3] + shearingX, pntY[3]);

		glVertex2i(pntX[4], pntY[4]);
	}
	else if (shearingAxis == 'y' || shearingAxis == 'Y')
	{
		glVertex2i(pntX[0], pntY[0]);
		glVertex2i(pntX[1], pntY[1]);

		glVertex2i(pntX[2], pntY[2] + shearingY);

		glVertex2i(pntX[3], pntY[3] + shearingY);

		glVertex2i(pntX[4], pntY[4] + shearingY);
	}
	else if (shearingAxis == 'z' || shearingAxis == 'Z')
	{
		glVertex2i(pntX[0], pntY[0]);

		glVertex2i(pntX[1] + shearingX, pntY[1] + shearingY);
		glVertex2i(pntX[2] + shearingX * 2, pntY[2] + shearingY * 2);
		glVertex2i(pntX[3] + shearingX * 2, pntY[3] + shearingY * 2);
		glVertex2i(pntX[4] + shearingX, pntY[4] + shearingY);
	}
	glEnd();
}

void myInit(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(4.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-640.0, 640.0, -480.0, 480.0);
}


void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);

	if (choice == 1)
	{
		drawPolygon();
		drawPolygonTrans(transX, transY);
	}
	else if (choice == 2)
	{
		drawPolygon();
		drawPolygonScale(scaleX, scaleY);
	}
	else if (choice == 3)
	{
		drawPolygon();
		drawPolygonRotation(angleRad);
	}
	else if (choice == 4)
	{
		drawPolygon();
		drawPolygonMirrorReflection(reflectionAxis);
	}
	else if (choice == 5)
	{
		drawPolygon();
		drawPolygonShearing();
	}

	glFlush();
}

int main(int argc, char** argv)
{
	cout << "Enter your choice:\n\n" << endl;

	cout << "1. Translation" << endl;
	cout << "2. Scaling" << endl;
	cout << "3. Rotation" << endl;
	cout << "4. Mirror Reflection" << endl;
	cout << "5. Shearing" << endl;
	cout << "6. Exit" << endl;

	cin >> choice;

	if (choice == 6) {
		return 0;
	}

	cout << "\n\nFor Polygon:\n" << endl;

	cout << "Enter no of edges: "; cin >> edges;

	for (int i = 0; i < edges; i++)
	{
		cout << "Enter co-ordinates for vertex  " << i + 1 << " : "; cin >> pntX1 >> pntY1;
		pntX.push_back(pntX1);
		pntY.push_back(pntY1);
	}

	if (choice == 1)
	{
		cout << "Enter the translation factor for X and Y: "; cin >> transX >> transY;
	}
	else if (choice == 2)
	{
		cout << "Enter the scaling factor for X and Y: "; cin >> scaleX >> scaleY;
	}
	else if (choice == 3)
	{
		cout << "Enter the angle for rotation: "; cin >> angle;
		angleRad = angle * 3.1416 / 180;
	}
	else if (choice == 4)
	{
		cout << "Enter reflection axis ( x or y  or z for xy or w for -xy ): "; cin >> reflectionAxis;
	}
	else if (choice == 5)
	{
		cout << "Enter shearing axis ( x or y or z for xy ): "; cin >> shearingAxis;
		if (shearingAxis == 'x' || shearingAxis == 'X')
		{
			cout << "Enter the shearing factor for X: "; cin >> shearingX;
		}
		else if (shearingAxis == 'y' || shearingAxis == 'Y')
		{
			cout << "Enter the shearing factor for Y: "; cin >> shearingY;
		}
		else if (shearingAxis == 'z' || shearingAxis == 'Z')
		{
			cout << "Enter the X shearing factor for XY: "; cin >> shearingX;
			cout << "Enter the Y shearing factor for XY: "; cin >> shearingY;
		}
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(200, 150);
	glutCreateWindow("POLYGON_TRANSFORMATION");
	glutDisplayFunc(myDisplay);
	myInit();
	glutMainLoop();
}
