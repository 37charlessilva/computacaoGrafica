#include <GL/glut.h>
#include <math.h>

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Projecao Ortogonal
    if (w <= h) {
        glOrtho(-3.0, 3.0, -3.0 * (GLfloat)h / (GLfloat)w, 3.0 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
    } else {
        glOrtho(-3.0 * (GLfloat)w / (GLfloat)h, 3.0 * (GLfloat)w / (GLfloat)h, -3.0, 3.0, -10.0, 10.0);
    }
    glMatrixMode(GL_MODELVIEW);
}


void drawCube(void) {
    glBegin(GL_QUADS);

    // Face Branca (Frente) - z=1.0, oposta ao Amarelo
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f( 1.0f, -1.0f, 1.0f);
    glVertex3f( 1.0f,  1.0f, 1.0f);
    glVertex3f(-1.0f,  1.0f, 1.0f);

    // Face Amarela (Fundo) - z=-1.0, oposta ao Branco
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);

    // Face Vermelha (Direita) - x=1.0, oposta ao Laranja
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f,  1.0f, -1.0f);
    glVertex3f(1.0f,  1.0f,  1.0f);
    glVertex3f(1.0f, -1.0f,  1.0f);

    // Face Laranja (Esquerda) - x=-1.0, oposta ao Vermelho
    glColor3f(1.0f, 0.5f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);

    // Face Azul (Topo) - y=1.0, oposta ao Verde
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f,  1.0f);
    glVertex3f( 1.0f, 1.0f,  1.0f);
    glVertex3f( 1.0f, 1.0f, -1.0f);

    // Face Verde (Base) - y=-1.0, oposta ao Azul
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);

    glEnd();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Posiciona a camera para ver 3 faces
    gluLookAt(3.0, 3.0, 3.0,   
              0.0, 0.0, 0.0,   
              0.0, 1.0, 0.0);  
    
    drawCube();
    
    glutSwapBuffers();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(700, 700);
    glutCreateWindow("Cubo de Rubik 3D");
    
    glEnable(GL_DEPTH_TEST);

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}