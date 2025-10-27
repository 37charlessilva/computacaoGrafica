#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

#define PI 3.142

GLenum errorCheck (void) {
    GLenum code;
    const GLubyte *string;

    code = glGetError(); // Retorna o identificador do erro ocorrido
    if(code != GL_NO_ERROR) {
        string = gluErrorString(code); // Traduz o erro para texto/1 Vvalor GLenum
        fprintf(stderr, "Open error: %s\n", string);
    }
    return code;
}

void init(void){
    glClearColor(0.0, 0.0, 0.0, 0.0); // Define cor de fundo da janela (Preto)
    
    glMatrixMode(GL_PROJECTION);      // Define que vamos trabalhar com projeções
    gluOrtho2D(0.0, 200.0, 0.0, 150.0); // Define uma projeção ortográfica 2D
    
    errorCheck(); // Verifica se houve erro
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, 0, h, -1, 1); // sistema de coordenadas = pixels da tela

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}



void drawSun(void){
    int pontas = 15;            // número de raios
    float raio_maior = 120.0f;
    float raio_menor = 60.0f;
    float cx = 200.0f;
    float cy = 150.0f;

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 0.0);

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);

    for(int c = 0; c <= pontas * 2; c++){ 
        float angulo = 2.0 * PI * c / (pontas);
        float raio = (c % 2 == 0) ? raio_maior : raio_menor;
        float x = cx + raio * cos(angulo);
        float y = cy + raio * sin(angulo);
        glVertex2f(x, y);
    }

    glEnd();
    glFlush();
    errorCheck();
}



int main(int argc, char ** argv){
    glutInit(&argc, argv);                              // Inicializa GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);        // Modo de exibição: um buffer + RGB
    glutInitWindowPosition(50, 100);                    // Posição da janela
    glutInitWindowSize(400, 300);                       // Tamanho da janela
    glutCreateWindow("An Example OpenGL Program");      // Cria a janela com título
    
    init();                                             // Inicialização do OpenGL
    

    glutDisplayFunc(drawSun);                           // Registra função de desenho
    glutReshapeFunc(reshape);                           // Redimensiona janela  

    glutMainLoop();                                     // Inicia loop principal de eventos
    return 0;
}


// gcc teste.c -o programa -lGL -lGLU -lglut
