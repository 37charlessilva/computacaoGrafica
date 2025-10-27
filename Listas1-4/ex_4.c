#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
const GLdouble viewPoints[8][3] = {
    {3.0, 4.0, 3.0},   
    {-3.0, 4.0, 3.0},  
    {-3.0, 4.0, -3.0}, 
    {3.0, 4.0, -3.0},  
    {3.0, -4.0, 3.0},  
    {-3.0, -4.0, 3.0}, 
    {-3.0, -4.0, -3.0},
    {3.0, -4.0, -3.0}  
};

int currentView = 0;

float zoom_v = 1.0f;
float fov = 45.0f;

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(fov, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
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
    
    GLdouble upvetor = 1;
    if(currentView > 3){
        upvetor *= -1;
    }
    // Posiciona a camera para ver 3 faces

    gluLookAt(viewPoints[currentView][0], viewPoints[currentView][1], viewPoints[currentView][2],
              0.0, 0.0, 0.0,
              0.0, upvetor, 0.0);
    
    drawCube();
    
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    
    switch (key) {
        case 'v':
            
            currentView = 0;
            break;
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':

            currentView = key - '1';
            break;

        case 'i':
            fov -= 5.0;
            if (fov < 35.0f){
                fov = 35.0f;
            }
           
            break;
        case 'o':
            fov += 5.0f;
            if (fov > 160.0f){
                fov = 160.0f;
            }
            break;
        default:
            return; 
    }
    // Redesenhar pra fazer o zoom
    reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
    glutPostRedisplay(); 
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(700, 700);
    glutCreateWindow("Cubo de Rubik 3D");
    
    glEnable(GL_DEPTH_TEST);

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}    