#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <math.h>
#include <stdio.h>

GLUquadric *sun, *earth, *moon;
GLint fps;
GLdouble radiusSun, radiusEarth, angleEarth, radiusMoon, angleMoon;
GLdouble orbitEarth, orbitMoon;
GLdouble xSun, ySun, xEarth, yEarth;

void myReshape(int w, int h) {
    glViewport (0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluOrtho2D(-2.0, 2.0, -2.0, 2.0);
    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();
}

void drawSun(void) {
	glColor3f(1.0f, 1.0f, 0.0f); // amarelo
	glPushMatrix();
	glTranslated(xSun, ySun, 1.0);
	gluDisk(sun, 0, radiusSun, 24, 1);
	glPopMatrix();
}

void drawEarth(void){
    glColor3f(0.0f, 0.0f, 1.0f); // Azul
	glPushMatrix();
    
    xEarth = xSun + orbitEarth * cos(angleEarth);
    yEarth = ySun + orbitEarth * sin(angleEarth);

	glTranslated(xEarth, yEarth, 0.5);
	gluDisk(earth, 0, radiusEarth, 24, 1);
	glPopMatrix();
}

void drawnMoon(void){
    glColor3f(0.5f, 0.5f, 0.5f); // Cinza
	glPushMatrix();
    
    double x = xEarth + orbitMoon * cos(angleMoon);
    double y = yEarth + orbitMoon * sin(angleMoon);

	glTranslated(x, y, 0.5);
	gluDisk(moon, 0, radiusMoon, 24, 1);
	glPopMatrix();
}
void myDisplay(void) {                 
    glClearColor(0.0, 0.0, 0.0, 1.0);  
    glClear(GL_COLOR_BUFFER_BIT);      
    drawSun();
    drawEarth();
    drawnMoon();
    glutSwapBuffers();                 
}

void spinEarth(int value) {
	angleEarth = angleEarth + 0.002;

	glutPostRedisplay();
	glutTimerFunc(1000/fps, spinEarth, 1);
}

void spinMoon(int value) {
	angleMoon = angleMoon + 0.02;

	glutPostRedisplay();
	glutTimerFunc(1000/fps, spinMoon, 1);
}

void init(void) {
	sun = gluNewQuadric();
    earth = gluNewQuadric();
    moon = gluNewQuadric();
    radiusSun = 0.4;
    radiusEarth = 0.08;
    radiusMoon = 0.03;

    angleEarth = 0.0;
    angleMoon = 0.0;

    orbitEarth = 1.2; // Orbita do planeta
    orbitMoon = 0.2;

    xSun = 0.0, ySun = 0.0;

	fps = 25;
	glutTimerFunc(1000/fps, spinEarth, 1); // Aqui fica a animação
    glutTimerFunc(1000/fps, spinMoon, 1);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(50, 100);
    glutCreateWindow("Sol");

    init();
    glutDisplayFunc(myDisplay);
    glutReshapeFunc(myReshape);

    glutMainLoop();
    return 0;
}