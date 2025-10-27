#include <GL/glut.h>
#include <math.h>

void reshape(int w, int h){
    // Serve pra Desenhar a cena Nas proporções corretas
    glViewport(0, 0, w, h); // Define a área da janela onde a cena vai ser desenhada (viewport).
    glMatrixMode(GL_PROJECTION); // Troca para a matriz de projeção (define como o mundo 3D/2D será projetado na tela).
    glLoadIdentity(); // Reseta a matriz atual para a identidade (remove transformações acumuladas).
    gluOrtho2D(-2, 2, -2, 2); // Define uma projeção ortográfica 2D (sistema de coordenadas do mundo).
    glMatrixMode(GL_MODELVIEW); // Troca para a matriz de modelagem/visualização (usada para transformar os objetos da cena).
    glutPostRedisplay(); // Pede ao GLUT para redesenhar a tela (força o display ser chamado de novo).
}
void line(){
    glColor3f(0.0f, 0.0f, 1.0f); // Azul
	glPushMatrix();
    
    glBegin(GL_LINES);
        glVertex2f(0, 1);
        glVertex2f(0, -1);
    
    glColor3f(1.0f, 0.0f, 1.0f); 
    glBegin(GL_LINES);  
        glVertex2f(1, 0);
        glVertex2f(-1, 0);
    
    glEnd();
    glColor3f(0.0f, 1.0f, 1.0f);
    glBegin(GL_POINTS);
    glVertex2d(1, 1);
    glEnd();
    glFlush();
}
void display(){
    glClearColor(0.0, 0.0, 0.0, 1.0);  
    glClear(GL_COLOR_BUFFER_BIT);  
    line();
    glutSwapBuffers();
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(50, 100);
    glutCreateWindow("Sol");

    //init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}
