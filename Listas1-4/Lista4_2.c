// Compilar (Linux):
// gcc checker.c -lGL -lGLU -lglut -lm -o checker

#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

#define N 8

GLubyte checkerImage[N][N][3];
GLuint texID;
int mode = 1; // 1 = não deformado, 2 = deformado

// Cria o tabuleiro 8x8
void makeCheckerImage() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int c = ((i + j) % 2) ? 255 : 0; // alterna preto/branco
            checkerImage[i][j][0] = (GLubyte)c;
            checkerImage[i][j][1] = (GLubyte)c;
            checkerImage[i][j][2] = (GLubyte)c;
        }
    }
}

void initTexture() {
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, N, N, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, checkerImage);
}

// === 1️⃣ Paralelogramo sem deformar o padrão ===
void drawParallelogramUndeformed() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texID);

    float angle = 30.0 * M_PI / 180.0;
    float offset = 0.8f / tan(angle);

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-0.8f, -0.8f);
        glTexCoord2f(1.0f, 0.0f); glVertex2f( 0.8f, -0.8f);
        glTexCoord2f(1.0f, 1.0f); glVertex2f( 0.8f + offset,  0.8f);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-0.8f + offset,  0.8f);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

// === 2️⃣ Paralelogramo com padrão deformado ===
void drawParallelogramDeformed() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texID);

    float angle = 30.0 * M_PI / 180.0;
    float offset = 0.8f / tan(angle);

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);          glVertex2f(-0.8f, -0.8f);
        glTexCoord2f(1.0f, 0.0f);          glVertex2f( 0.8f, -0.8f);
        glTexCoord2f(1.0f + offset, 1.0f); glVertex2f( 0.8f + offset,  0.8f);
        glTexCoord2f(0.0f + offset, 1.0f); glVertex2f(-0.8f + offset,  0.8f);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (mode == 1)
        drawParallelogramUndeformed();
    else
        drawParallelogramDeformed();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case '1': mode = 1; glutPostRedisplay(); break;
        case '2': mode = 2; glutPostRedisplay(); break;
        case 27: exit(0); // ESC
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Tabuleiro de Xadrez - Paralelogramo");

    makeCheckerImage();
    initTexture();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
