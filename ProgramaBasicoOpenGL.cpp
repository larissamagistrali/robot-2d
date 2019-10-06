//-------------------------------------
// T1 - CG - 2019/2
// Larissa Magistrali, Rodrigo Silva.
//-------------------------------------
#include <iostream>
#include <cmath>
#include <ctime>
using namespace std;
#ifdef WIN32
#include <windows.h>
#include <glut.h>
static DWORD last_idle_time;
#else
#include <sys/time.h>
static struct timeval last_idle_time;
#endif
#ifdef __APPLE__
#include <GLUT/glut.h>
#endif
#ifdef __linux__
#include <glut.h>
#endif
#include "ImageClass.h"
//--------------------------------------------------
float DeltaYSegC = 13.0;
unsigned char flip = 0;
float PosRobotX = 50;
//ImageClass Image,NewImage;
typedef struct{
  GLfloat x,y,z;
} Ponto;

void CalculaPonto(Ponto p, Ponto &out) {
    GLfloat ponto_novo[4];
    GLfloat matriz_gl[4][4];
    int  i;
    glGetFloatv(GL_MODELVIEW_MATRIX,&matriz_gl[0][0]);
    for(i=0; i<4; i++) {
        ponto_novo[i] = matriz_gl[0][i] * p.x +
        matriz_gl[1][i] * p.y +
        matriz_gl[2][i] * p.z +
        matriz_gl[3][i];
    }
    out.x = ponto_novo[0];
    out.y = ponto_novo[1];
    out.z = ponto_novo[2];
}
void animate(){
    static float dt;
    static float AccumTime=0;
#ifdef _WIN32
    DWORD time_now;
    time_now = GetTickCount();
    dt = (float) (time_now - last_idle_time) / 1000.0;
#else
    struct timeval time_now;
    gettimeofday(&time_now, NULL);
    dt = (float)(time_now.tv_sec  - last_idle_time.tv_sec) +
    1.0e-6*(time_now.tv_usec - last_idle_time.tv_usec);
#endif
    AccumTime +=dt;
    if (AccumTime >=3){
        cout << 1.0/dt << " FPS"<< endl;
        AccumTime = 0;
    }
    last_idle_time = time_now;
    glutPostRedisplay();
}
void init(void){
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //cor de fundo
    /*
    int r;
    string nome="cenario.jpg";
    r = Image.Load(nome.c_str()); // Carrega uma imagem
    if (!r) exit(1);
    else cout << ("img ok\n");
    NewImage.SetSize(Image.SizeX(), Image.SizeY(), Image.Channels());
    */
}
void reshape( int w, int h ){
    // Reset the coordinate system before modifying
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Define a area a ser ocupada pela área OpenGL dentro da Janela
    glViewport(0, 0, w, h);
    // Define os limites lógicos da área OpenGL dentro da Janela
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
//---------------------ROBO--------------------------
void DesenhaBase(){
    glColor3f(0.5,0.1,0);
    glBegin(GL_QUADS);
        glColor3f(0.5,0.1,0);
        glVertex3f(-4,0,0);
        glVertex3f(-4,3,0);
        glColor3f(0.5,0.1,0);
        glVertex3f(4,3,0);
        glVertex3f(4,0,0);
    glEnd();
}
void DesenhaEixos(){
    glColor3f(0,0,0);
    glBegin(GL_LINES);
        glVertex2d(0,25);
        glVertex2d(100,25);
        glVertex2d(50,0);
        glVertex2d(50,50);
    glEnd();
}
void DesenhaSegmentoA(){
    glTranslatef(0,3,0);
    //glRotatef(50,0,0,1);
    glColor3f(0.5,0.2,0);
    glBegin(GL_QUADS);
        glVertex2d(-1.5,0);
        glVertex2d(-1.5,15);
        glVertex2d(1.5,15);
        glVertex2d(1.5,0);
    glEnd();
}
void DesenhaSegmentoB(){
    Ponto p1 = {0,10,0};
    Ponto p1_new;
    glTranslatef(0,DeltaYSegC,0);
    //glRotatef(45,0,0,1);
    glColor3f(0.5,0.3,0);
    glBegin(GL_QUADS);
        glVertex2d(-1.5,0);
        glVertex2d(-1.5,15);
        glVertex2d(1.5,15);
        glVertex2d(1.5,0);
    glEnd();
    CalculaPonto(p1, p1_new);
    cout << "(" << p1_new.x << ", " << p1_new.y << ", " << p1_new.z << ")" << endl;
}
void DesenhaSegmentoC(){
    Ponto p1 = {0,12,0};
    Ponto p1_new;
    glTranslatef(0,DeltaYSegC,0);
    //glRotatef(45,0,0,1);
    glColor3f(0.5,0.1,0);
    glBegin(GL_QUADS);
        glVertex2d(-1.5,0);
        glVertex2d(-1.5,12);
        glVertex2d(1.5,12);
        glVertex2d(1.5,0);
    glEnd();
    CalculaPonto(p1, p1_new);
    cout << "(" << p1_new.x << ", " << p1_new.y << ", " << p1_new.z << ")" << endl;
}
void DesenhaRobo(){
    DesenhaBase();
    DesenhaSegmentoA();
    DesenhaSegmentoB();
    DesenhaSegmentoC();
}
//--------------------------------------------------------
void display( void ){
    // Limpa a tela coma cor de fundo
    glClear(GL_COLOR_BUFFER_BIT);
    // Define os limites lógicos da área OpenGL dentro da Janela
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Define os limites lógicos da área OpenGL dentro da Janela
    glOrtho(0,100,0,50,-1,1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // ---------------------------------------------------
    // Coloque aqui as chamadas das rotinas que desenha os objetos
    // ---------------------------------------------------
    DesenhaEixos();
    glTranslatef(PosRobotX,0,0);
    // PINHO
    if (flip)
        glRotatef(180, 0,1,0);
    DesenhaRobo();
    glutSwapBuffers();
}

void keyboard ( unsigned char key, int x, int y ){
    switch ( key ){
        case 27:          // Termina o programa qdo
            exit ( 0 );   // a tecla ESC for pressionada
            break;
        case 'y':
            break;
        // PINHO
        case ' ':
            flip = !flip;
            break;
        default:
            break;
    }
}
void arrow_keys ( int a_keys, int x, int y )
{
    switch ( a_keys )
    {
        case GLUT_KEY_RIGHT:
            PosRobotX++;
            break;
        case GLUT_KEY_LEFT:
            PosRobotX--;
            break;
        case GLUT_KEY_DOWN:
            DeltaYSegC--;
            if (DeltaYSegC<5)
                DeltaYSegC = 5;
            break;
        case GLUT_KEY_UP:
            DeltaYSegC++;
            if (DeltaYSegC>15)
                DeltaYSegC = 15;
            break;
        default:
            break;
    }
}
//----------------MAIN-------------------------------------
int  main ( int argc, char** argv ){
    glutInit            ( &argc, argv );
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB );
    glutInitWindowPosition (0,0);
    // Define o tamanho inicial da janela grafica do programa
    glutInitWindowSize  (800 , 500);
    // Cria a janela na tela, definindo o nome que aparecera na barra de título da janela.
    glutCreateWindow    ( "T1-CG-Larissa-Rodrigo" );
    // executa algumas inicializações
    init ();
    // Define que o tratador de evento para o redesenho da tela. A funcao "display"
    // será chamada automaticamente quando for necessário redesenhar a janela
    glutDisplayFunc ( display );
    glutIdleFunc(animate);
    // Define que o tratador de evento para o redimensionamento da janela. A funcao "reshape"
    // será chamada automaticamente quando o usuário alterar o tamanho da janela
    glutReshapeFunc ( reshape );
    // Define que o tratador de evento para as teclas. A funcao "keyboard"
    // será chamada automaticamente sempre o usuário pressionar uma tecla comum
    glutKeyboardFunc ( keyboard );
    // Define que o tratador de evento para as teclas especiais(F1, F2,... ALT-A,
    // ALT-B, Teclas de Seta, ...).
    // A funcao "arrow_keys" será chamada automaticamente sempre o usuário
    // pressionar uma tecla especial
    glutSpecialFunc ( arrow_keys );
    // inicia o tratamento dos eventos
    glutMainLoop ( );
    return 0;
}
