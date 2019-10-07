//-------------------------------------
// T1 - CG - 2019/2
// Larissa Magistrali, Rodrigo Silva.
//-------------------------------------
#include <iostream>
#include <cmath>
#include <cstdlib>
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
#include "SOIL/SOIL.h"
#include <fstream>
//-----------------OBJETOS--------------------------------

typedef struct {
    float r,g,b;
}Cor;

typedef struct {
    Cor Matriz [20][20];
} ModeloDeObjeto ;

unsigned int QtdDeModelos = 0;
ModeloDeObjeto Modelos[50];  // Este vetor armazena todos os modelos que forem lidos do arquivos
/*
void DesenhaModelo(unsigned Mod){
    // desenha o objeto que est� descrito na posi��o Mod do vetor Modelos
}
typedef struct {
    float tx, ty; // posicao do objeto no universo
    int id; // nro do modelo de objeto
} Instancia;

unsigned int QtdDeObjetosNoCenario  = 3;
Instancia ObjetosNoCenario[50]; // esta estrututra armazena cada inst�ncia que aparece na tela

unsigned int InstanciaPresoNoRobo = -1; // Armazena o �ndice da Instancia que est� presa na garra do Robo

void DesenhaInstancia(Instancia I){
    glPushMatrix();
        glTranslatef(I.tx, I.ty,0);
        DesenhaModelo(I.id);
    glPopMatrix();
}
void DesenhaCenario(){
    for(int i=0; i<QtdDeObjetosNoCenario; i++)
        if (i != InstanciaPresoNoRobo)
            DesenhaInstancia(ObjetosNoCenario[i]);

}
*/
//-------------------LEITURA DE ARQUIVO-----------------
void LeArquivo(string path){
    std::ifstream infile("caixa1.txt");
    int cores, i = 0;
    infile >> cores;
    cout << "Cores = " << cores << endl;
    Cor ListaCores[cores];
    while(i<cores){
        Cor c;
        infile >> i >> c.r >> c.g >> c.b;
        cout << "Cor " << i << " " << c.r << " " << c.g << " " << c.b << endl;
        ListaCores[i-1] = c;
    }
    int largura, altura, j, c = 0;
    Cor Matriz [largura][altura];
    infile >> largura >> altura;
    cout << "Largura = " << largura << " Altura = " << altura << endl;
    for(i=0; i<largura; i++){
        for(j=0; j<altura; j++){
            infile >> c;
            cout << "Matriz[" << i << "][" << j << "] = Cor " << c << endl;
            Matriz[i][j] = ListaCores[c-1];
        }
    }
}
//-------------------LEITURA DE ARQUIVO-----------------

//-------------------CALCULA PONTO-----------------
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

//-------------------ANIMATE--------------------
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

//-----------------------INIT----------------------------
//ImageClass Image;
void init(void){
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //cor de fundo
    /*int r;
    string nome = "cenario.jpg";
    r = Image.Load(nome.c_str());
    if (!r) exit(1); // Erro na carga da imagem*/
    LeArquivo("caixa1.txt");
}

//-----------------------RESHAPE-------------------------
void reshape( int w, int h ){
    // Reset the coordinate system before modifying
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Define a area a ser ocupada pela �rea OpenGL dentro da Janela
    glViewport(0, 0, w, h);
    // Define os limites l�gicos da �rea OpenGL dentro da Janela
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
//---------------------ROBO------------------------------
float DeltaYSegC = 13.0;
float PosRobotX = 50;
float RotRobotSegB = 0;
float RotRobotSegC = 0;

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
void DesenhaSegmentoA(){
    glTranslatef(0,3,0);
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
    glRotatef(RotRobotSegB,0,0,1);
    glColor3f(0.5,0.3,0);
    glBegin(GL_QUADS);
        glVertex2d(-1.5,-1);
        glVertex2d(-1.5,14);
        glVertex2d(1.5,14);
        glVertex2d(1.5,-1);
    glEnd();
    //CalculaPonto(p1, p1_new);
    //out << "(" << p1_new.x << ", " << p1_new.y << ", " << p1_new.z << ")" << endl;
}
void DesenhaSegmentoC(){
    Ponto p1 = {0,12,0};
    Ponto p1_new;
    glTranslatef(0,DeltaYSegC,0);
    glRotatef(RotRobotSegC,0,0,1);
    glColor3f(0.5,0.1,0);
    glBegin(GL_QUADS);
        glVertex2d(-1.5,-1);
        glVertex2d(-1.5,11);
        glVertex2d(1.5,11);
        glVertex2d(1.5,-1);
    glEnd();
    //CalculaPonto(p1, p1_new);
    //cout << "(" << p1_new.x << ", " << p1_new.y << ", " << p1_new.z << ")" << endl;
}
void DesenhaRobo(){
    DesenhaBase();
    DesenhaSegmentoA();
    DesenhaSegmentoB();
    DesenhaSegmentoC();
}
//-----------------EIXOS----------------------------------
void DesenhaEixos(){
    glColor3f(0,0,0);
    glBegin(GL_LINES);
        glVertex2d(0,25);
        glVertex2d(100,25);
        glVertex2d(50,0);
        glVertex2d(50,50);
    glEnd();
}

//------------------DISPLAY----------------------------------
void display( void ){
    // Limpa a tela coma cor de fundo
    glClear(GL_COLOR_BUFFER_BIT);
    // Define os limites l�gicos da �rea OpenGL dentro da Janela
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Define os limites l�gicos da �rea OpenGL dentro da Janela
    glOrtho(0,100,0,50,-1,1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // ---------------------------------------------------
    // Coloque aqui as chamadas das rotinas que desenha os objetos
    // ---------------------------------------------------
    DesenhaEixos();
    glTranslatef(PosRobotX,0,0);
    DesenhaRobo();
    glutSwapBuffers();
}
//----------------COMANDOS-----------------------------------------
void keyboard ( unsigned char key, int x, int y ){
    switch ( key ){
        case 27:          // Termina o programa qdo
            exit ( 0 );   // a tecla ESC for pressionada
            break;
        case 'q':
            RotRobotSegC = RotRobotSegC+15;
            if (RotRobotSegC>135)
                RotRobotSegC = 135;
            break;
        case 'w':
            RotRobotSegC = RotRobotSegC-15;
            if (RotRobotSegC<-135)
                RotRobotSegC = -135;
            break;
        case 'a':
            RotRobotSegB = RotRobotSegB+15;
            if (RotRobotSegB>120)
                RotRobotSegB = 120;
            break;
        case 's':
            RotRobotSegB = RotRobotSegB-15;
            if (RotRobotSegB<-120)
                RotRobotSegB = -120;
            break;
        default:
            break;
    }
}
void arrow_keys ( int a_keys, int x, int y ){
    switch ( a_keys )    {
        case GLUT_KEY_RIGHT:
            if(PosRobotX+1<=96)
            PosRobotX++;
            break;//
        case GLUT_KEY_LEFT:
            if(PosRobotX-1>=4)
            PosRobotX--;
            break;
        case GLUT_KEY_DOWN:
            /*DeltaYSegC--;
            if (DeltaYSegC<5)
                DeltaYSegC = 5;*/
            break;
        case GLUT_KEY_UP:
            /*DeltaYSegC++;
            if (DeltaYSegC>15)
                DeltaYSegC = 15;*/
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
    glutInitWindowSize  (800 , 500);
    glutCreateWindow    ( "T1-CG-Larissa-Rodrigo" );
    init ();
    glutDisplayFunc ( display );
    glutIdleFunc(animate);
    glutReshapeFunc ( reshape );
    glutKeyboardFunc ( keyboard );
    glutSpecialFunc ( arrow_keys );
    glutMainLoop ( );
    return 0;
}
