// Compilar (Linux): gcc checker.c -lGL -lGLU -lglut -o checker

#include <GL/glut.h>
#include <stdlib.h>

#define N 8

GLubyte checkerImage[N][N][3];
GLuint texID;

void makeCheckerImage() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int c = ((i + j) % 2) ? 255 : 0; // 0 = preto, 255 = branco
            checkerImage[i][j][0] = (GLubyte)c;
            checkerImage[i][j][1] = (GLubyte)c;
            checkerImage[i][j][2] = (GLubyte)c;
        }
    }
}

void initTexture() {
    glGenTextures(1, &texID); // Inicia textura
    glBindTexture(GL_TEXTURE_2D, texID); // Ativa esse textura

    // Filtros; usar NEAREST para manter blocos nítidos
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // Evita repetição estranha nas bordas
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Carrega a imagem (8x8)
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, N, N, 0, GL_RGB, GL_UNSIGNED_BYTE, checkerImage);
}

void drawRectangle(void){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texID);

    // Desenha um quadrado com coordenadas de textura (0,0) -> (1,1)
    glBegin(GL_QUADS);
      glTexCoord2f(0.0f, 0.0f); glVertex2f(-0.8f, -0.8f);
      glTexCoord2f(1.0f, 0.0f); glVertex2f( 0.8f, -0.8f);
      glTexCoord2f(1.0f, 1.0f); glVertex2f( 0.8f,  0.8f);
      glTexCoord2f(0.0f, 1.0f); glVertex2f(-0.8f,  0.8f);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawRectangle();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // coordenadas 2D simples
    gluOrtho2D(-1,1,-1,1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Tabuleiro de xadres");
    makeCheckerImage();
    initTexture();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
