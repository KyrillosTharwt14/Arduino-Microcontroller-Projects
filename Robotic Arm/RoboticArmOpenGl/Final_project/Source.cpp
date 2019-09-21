
#include <stdlib.h>
#include<glut.h>
#include <vector>
#include <string>
#include <algorithm>
#define _USE_MATH_DEFINES
#include <cmath> 
#include <math.h>


using namespace std;
static int shoulder = -65.0 , elbow = 90 , wrist = 0, finger1 = 0, finger11 = 0, finger12 = 0, finger2 = 0, finger21 = 0, finger22 = 0;
GLfloat cameraDistance = 12, cameraAngle = 0;

int arm_angles[5] = { 0, 0, 0, 0, 0 };
enum { SHOULDER_Y, SHOULDER_Z, ELBOW_Z, WRIST_X, WRIST_Z };


void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	GLfloat x = cameraDistance * sin(cameraAngle);
	GLfloat z = cameraDistance * cos(cameraAngle);
	gluLookAt(x, 0.0, z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glRotatef((GLfloat)arm_angles[SHOULDER_Y], 0., 1., 0.);
	glRotatef((GLfloat)arm_angles[SHOULDER_Z], 0., 0., 1.);


	

	/**************************************************************************/
	glPushMatrix();
	glTranslatef(-4, 4.0, 0.0);

	glColor3f(1, 0.85, 0);
	glutSolidSphere(.5, 20, 50);

	
	glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
	glColor3f(0.0, 0.74, 1.0);
	glTranslatef(2.5, 0.0, 0.0);

	glPushMatrix();
	glScalef(4.0, 1.0, 1.0);
	glutSolidCube(1.0);
	glPopMatrix();
	/**************************************************************************/
	glColor3f(1, 0.85, 0);
	glTranslatef(2.5, 0.0, 0.0);
	glutSolidSphere(.5, 20, 50);
	/****************************************************************************/
	glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
	glColor3f(0.11,0.56, 1.0);
	glTranslatef(2.5, 0.0, 0.0);
	glPushMatrix();
	glScalef(4.0, 1.0, 1.0);
	glutSolidCube(1.0);
	glPopMatrix();
	/**************************************************************************/
	glColor3f(1, 0.85, 0);
	glTranslatef(2.5, 0.0, 0.0);
	glutSolidSphere(.5, 20, 50);
	/**************************************************************************/
	glColor3f(0.87, 0.07, 0.23);
	glPushMatrix();
	glTranslatef(0.0, 0.25, -0.2);
	glRotatef((GLfloat)finger1, 0.0, 0.0, 1.0);
	glTranslatef(0.6, -0.2, 0.0);
	glPushMatrix();
	glScalef(0.8, 0.2, 0.2);
	glutSolidCube(1.0);
	glPopMatrix();
	glTranslatef(0.4, 0.0, 0.2);
	glRotatef((GLfloat)finger11, 0.0, 0.0, 1.0);
	glTranslatef(0.2, 0.0, -0.2);
	glPushMatrix();
	glScalef(0.4, 0.2, 0.2);
	glColor3f(0.25, 0.25, 0.25);
	glutSolidCube(1.0);
	glPopMatrix();
	glTranslatef(0.2, 0.0, 0.2);
	glRotatef((GLfloat)finger12, 0.0, 0.0, 1.0);
	glTranslatef(0.1, 0.0, -0.2);
	glScalef(0.2, 0.2, 0.2);
	glColor3f(0.87, 0.07, 0.23);
	glutSolidCube(1.0);
	glPopMatrix();
	/**************************************************************************/
	glPushMatrix();
	glTranslatef(0.0, 0.25, 0.2);
	glRotatef((GLfloat)finger2, 0.0, 0.0, 1.0);
	glTranslatef(0.6, -0.2, 0.0);
	glPushMatrix();
	glScalef(0.8, 0.2, 0.2);
	glutSolidCube(1.0);
	glPopMatrix();
	glColor3f(0.25, 0.25, 0.25);
	glTranslatef(0.4, 0.0, 0.2);
	glRotatef((GLfloat)finger21, 0.0, 0.0, 1.0);
	glTranslatef(0.2, 0.0, -0.2);
	glPushMatrix();
	glScalef(0.4, 0.2, 0.2);
	glutSolidCube(1.0);
	glPopMatrix();
	glColor3f(0.87, 0.07, 0.23);
	glTranslatef(0.2, 0.0, 0.2);
	glRotatef((GLfloat)finger22, 0.0, 0.0, 1.0);
	glTranslatef(0.1, 0.0, -0.2);
	glScalef(0.2, 0.2, 0.2);
	glutSolidCube(1.0);
	glPopMatrix();
	/**************************************************************************/
	glPopMatrix();
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -5.0);
}
void specialKeys(int key, int x, int y) {
	GLfloat distanceDelta = 1.0, angleDelta = 5 * M_PI / 180.0;
	if (key == GLUT_KEY_UP) {
		cameraDistance -= distanceDelta;
		cameraDistance = max((GLfloat)2.0, cameraDistance);
	}
	if (key == GLUT_KEY_DOWN) {
		cameraDistance += distanceDelta;
	}
	if (key == GLUT_KEY_LEFT) {
		cameraAngle -= angleDelta;
	}
	if (key == GLUT_KEY_RIGHT) {
		cameraAngle += angleDelta;
	}
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'q':
		if (shoulder <= 5) {
			shoulder = (shoulder + 5) % 360;
			glutPostRedisplay();
		}
		break;
	case 'w':
		if (shoulder >= -90) {
			shoulder = (shoulder - 5) % 360;
			glutPostRedisplay();
		}
		break;
	case 'e':
		if (elbow <= 100) {
			elbow = (elbow + 5) % 360;
			glutPostRedisplay();
		}
		break;
	case 'r':
		if (elbow >= 0) {
			elbow = (elbow - 5) % 360;
			glutPostRedisplay();
		}
		break;
	case 'a':
		if ((finger12 <= 0) ) {
			finger12 = (finger12 + 5) % 360;
			glutPostRedisplay();
		}
		else if ((finger11 <= 0)) {
			finger11 = (finger11 + 5) % 360;
			glutPostRedisplay();
		}
		else if ((finger1 <= 30)) {
			finger1 = (finger1 + 5) % 360;
			glutPostRedisplay();
		}
		break;
	case 'b':
		if ((finger1 >= 0) ) {
			finger1 = (finger1 - 5) % 360;
			glutPostRedisplay();
		}
		else if ((finger11 >= -90))
		{
			finger11 = (finger11 - 5) % 360;
			glutPostRedisplay();
		}
		else if ((finger12 >= -90)) {
			finger12 = (finger12 - 5) % 360;
			glutPostRedisplay();
		}
		break;
		case 'd':
		if ((finger22 <= 0)) {
			finger22 = (finger22 + 5) % 360;
			glutPostRedisplay();
		}
		else if ((finger21 <= 0)) {
			finger21 = (finger21 + 5) % 360;
			glutPostRedisplay();
		}
		else if ((finger2 <= 30)) {
			finger2 = (finger2 + 5) % 360;
			glutPostRedisplay();
		}
		break;
	case 'c':
		if ((finger2 >= 0)) {
			finger2 = (finger2 - 5) % 360;
			glutPostRedisplay();
		}
		else if ((finger21 >= -90))
		{
			finger21 = (finger21 - 5) % 360;
			glutPostRedisplay();
		}
		else if ((finger22 >= -90)) {
			finger22 = (finger22 - 5) % 360;
			glutPostRedisplay();
		}
		break;

	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeys);
	glutMainLoop();
	return 0;
}