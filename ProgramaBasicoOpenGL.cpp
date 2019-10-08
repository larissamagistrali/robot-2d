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
#include <dirent.h>
#include <string>
float gravidade = 0.15, friccao = 0.1;
//-----------------OBJETOS--------------------------------

typedef struct
{
    float r, g, b, alpha;
} Cor;

typedef struct
{
    int altura;
    int largura;
    Cor cores[100][100];
} ModeloDeObjeto;

unsigned int QtdDeModelos = 0;
ModeloDeObjeto Modelos[50]; // Este vetor armazena todos os modelos que forem lidos do arquivos

void DesenhaModelo(unsigned Mod)
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    int i, j;
    ModeloDeObjeto mdo = Modelos[Mod];
    float dx = -mdo.largura / 4., dy = mdo.altura / 2. - 0.5;
    //cout << "Quad " << Mod << " " << mdo.largura << " " << mdo.altura << endl;
    for (i = 0; i < mdo.largura; i++)
    {
        for (j = 0; j < mdo.altura; j++)
        {
            glBegin(GL_QUADS);
            glColor4ub(mdo.cores[i][j].r, mdo.cores[i][j].g, mdo.cores[i][j].b, mdo.cores[i][j].alpha);
            glVertex3f(dx, dy, 0);
            glVertex3f(dx + 0.5, dy, 0);
            glVertex3f(dx + 0.5, dy + 0.5, 0);
            glVertex3f(dx, dy + 0.5, 0);
            glEnd();
            //cout << "Quad " << Mod << " " << i << " " << j << " " << mdo.cores[i][j].r << " " << mdo.cores[i][j].g << " " << mdo.cores[i][j].b << " " << dx << " " << dy << endl;
            dx += 0.5;
        }
        dy -= 0.5;
        dx = -mdo.largura / 4.;
    }
    glDisable(GL_BLEND);
}
typedef struct
{
    float tx, ty; // posicao do objeto no universo
    int id;       // nro do modelo de objeto
    bool movel;   // robo pode pegar
    float dy = 0.5;
} Instancia;
unsigned int QtdDeObjetosNoCenario = 0;
Instancia ObjetosNoCenario[50]; // esta estrututra armazena cada inst�ncia que aparece na tela

int InstanciaPresoNoRobo = -1; // Armazena o �ndice da Instancia que est� presa na garra do Robo

void DesenhaInstancia(Instancia &I, int instId)
{
    if (I.movel && instId != InstanciaPresoNoRobo)
    {
        cout << "movel" << endl;
        if (I.ty <= 0)
        {
            cout << "friccao" << endl;
            I.dy = -I.dy * friccao;
        }
        else
        {
            cout << "gravidade" << endl;
            I.dy = gravidade + I.dy;
        }
        I.ty = I.ty - I.dy;
        if (I.ty < 0)
            I.ty = 0;
    }
    glPushMatrix();
    glTranslatef(I.tx, I.ty, 0);
    DesenhaModelo(I.id);
    glPopMatrix();
    glPointSize(5);
    glColor3f(1, 0, 0);
    glBegin(GL_POINTS);
    glVertex2d(I.tx, I.ty);
    glEnd();
    glPointSize(1);
}
void DesenhaCenario()
{
    for (int i = 0; i < QtdDeObjetosNoCenario; i++)
        DesenhaInstancia(ObjetosNoCenario[i], i);
}

//-------------------LEITURA DE ARQUIVO-----------------

//
// ARQUIVO CENÁRIO:
// <QUANTIDADE DE INSTÂNCIAS>
// <ID DO MODELO> <POSIÇÃO X> <POSIÇÃO Y> <0 OU 1 - ROBÔ PODE PEGAR>
// <ID DO MODELO> <POSIÇÃO X> <POSIÇÃO Y> <0 OU 1 - ROBÔ PODE PEGAR>
//
void LeArquivoCenario(string path)
{
    std::ifstream infile(path.c_str());
    int instancias, i = 0;
    infile >> instancias;
    while (i < instancias)
    {
        int idMod, x, y, p;
        infile >> idMod >> x >> y >> p;
        cout << "Instância " << i << " " << idMod << " " << x << " " << y << " " << p << endl;
        Instancia inst;
        inst.id = idMod;
        inst.tx = x;
        inst.ty = y;
        inst.movel = p == 1;
        ObjetosNoCenario[QtdDeObjetosNoCenario++] = inst;
        i++;
    }
}

void LeArquivoModelo(ModeloDeObjeto &mod, const char *path)
{
    std::ifstream infile(path);
    int cores, i = 0;
    infile >> cores;
    cout << "Cores = " << cores << endl;
    Cor ListaCores[cores] = {};
    while (i < cores)
    {
        Cor c;
        infile >> i >> c.r >> c.g >> c.b >> c.alpha;
        cout << "Cor " << i << " " << c.r << " " << c.g << " " << c.b << " " << c.alpha << endl;
        ListaCores[i - 1] = c;
    }
    int largura, altura, j, c = 0;
    infile >> largura >> altura;
    mod.altura = altura;
    mod.largura = largura;
    Cor Matriz[largura][altura] = {};
    cout << "Largura = " << largura << " Altura = " << altura << endl;
    for (i = 0; i < largura; i++)
    {
        for (j = 0; j < altura; j++)
        {
            infile >> c;
            cout << "Matriz[" << i << "][" << j << "] = Cor " << c << endl;
            Matriz[i][j] = ListaCores[c - 1];
        }
    }
    for (i = 0; i < largura; i++)
    {
        for (j = 0; j < altura; j++)
        {
            mod.cores[i][j] = Matriz[i][j];
        }
    }
    infile.close();
}

void CarregaCenario()
{
    DIR *dir;
    struct dirent *lsdir;
    char path[15];
    strcpy(path, "./objetos/");
    dir = opendir(path);
    while ((lsdir = readdir(dir)) != NULL)
    {
        char *dot = strrchr(lsdir->d_name, '.');
        if (dot && !strcmp(dot, ".txt"))
        {
            ModeloDeObjeto mod;
            char filePath[50];
            strcpy(filePath, "./objetos/");
            strcat(filePath, lsdir->d_name);
            LeArquivoModelo(mod, filePath);
            Modelos[QtdDeModelos++] = mod;
        }
    }
    closedir(dir);
    LeArquivoCenario("cenario.txt");
}

//-------------------CALCULA PONTO-----------------
typedef struct
{
    GLfloat x, y, z;
} Ponto;

void CalculaPonto(Ponto p, Ponto &out)
{
    GLfloat ponto_novo[4];
    GLfloat matriz_gl[4][4];
    int i;
    glGetFloatv(GL_MODELVIEW_MATRIX, &matriz_gl[0][0]);
    for (i = 0; i < 4; i++)
    {
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
void animate()
{
    static float dt;
    static float AccumTime = 0;
#ifdef _WIN32
    DWORD time_now;
    time_now = GetTickCount();
    dt = (float)(time_now - last_idle_time) / 1000.0;
#else
    struct timeval time_now;
    gettimeofday(&time_now, NULL);
    dt = (float)(time_now.tv_sec - last_idle_time.tv_sec) +
         1.0e-6 * (time_now.tv_usec - last_idle_time.tv_usec);
#endif
    AccumTime += dt;
    if (AccumTime >= 3)
    {
        cout << 1.0 / dt << " FPS" << endl;
        AccumTime = 0;
    }
    last_idle_time = time_now;
    glutPostRedisplay();
}

//-----------------------INIT----------------------------
//ImageClass Image;
void init(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //cor de fundo
    /*int r;
    string nome = "cenario.jpg";
    r = Image.Load(nome.c_str());
    if (!r) exit(1); // Erro na carga da imagem*/
    CarregaCenario();
}

//-----------------------RESHAPE-------------------------
void reshape(int w, int h)
{
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
bool espacoPressionado = true;

void DesenhaBase()
{
    glColor3f(0.5, 0.1, 0);
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.1, 0);
    glVertex3f(-4, 0, 0);
    glVertex3f(-4, 3, 0);
    glColor3f(0.5, 0.1, 0);
    glVertex3f(4, 3, 0);
    glVertex3f(4, 0, 0);
    glEnd();
}
void DesenhaSegmentoA()
{
    glTranslatef(0, 3, 0);
    glColor3f(0.5, 0.1, 0);
    glBegin(GL_QUADS);
    glVertex2d(-1.5, 0);
    glVertex2d(-1.5, 15);
    glVertex2d(1.5, 15);
    glVertex2d(1.5, 0);
    glEnd();
}
void DesenhaSegmentoB()
{
    Ponto p1 = {0, 10, 0};
    Ponto p1_new;
    glTranslatef(0, DeltaYSegC, 0);
    glRotatef(RotRobotSegB, 0, 0, 1);
    glColor3f(0.5, 0.1, 0);
    glBegin(GL_QUADS);
    glVertex2d(-1.5, -1);
    glVertex2d(-1.5, 14);
    glVertex2d(1.5, 14);
    glVertex2d(1.5, -1);
    glEnd();
    //CalculaPonto(p1, p1_new);
    //out << "(" << p1_new.x << ", " << p1_new.y << ", " << p1_new.z << ")" << endl;
}
void DesenhaSegmentoC()
{
    Ponto p1 = {0, 12, 0};
    Ponto p1_new;
    glTranslatef(0, DeltaYSegC, 0);
    glRotatef(RotRobotSegC, 0, 0, 1);
    glColor3f(0.5, 0.1, 0);
    glBegin(GL_QUADS);
    glVertex2d(-1.5, -1);
    glVertex2d(-1.5, 11);
    glVertex2d(1.5, 11);
    glVertex2d(1.5, -1);
    glEnd();
    //CalculaPonto(p1, p1_new);
    //cout << "(" << p1_new.x << ", " << p1_new.y << ", " << p1_new.z << ")" << endl;
}
void DesenhaRobo()
{
    glTranslatef(PosRobotX, 0, 0);
    DesenhaBase();
    DesenhaSegmentoA();
    DesenhaSegmentoB();
    DesenhaSegmentoC();

    // Ponto da garra no S.R.O.: (0,11)
    Ponto pg = {0, 11, 0};
    Ponto pg_new;
    CalculaPonto(pg, pg_new);
    glPointSize(5);
    glColor3f(1, 0, 0);
    glBegin(GL_POINTS);
    glVertex2d(0, 11);
    glEnd();
    glPointSize(1);

    if (espacoPressionado)
    {
        cout << "espaco" << endl;
        if (InstanciaPresoNoRobo == -1) // Não há caixas na garra, tentar pegar uma
        {
            for (int i = 0; i < QtdDeObjetosNoCenario; i++)
            {
                if (!ObjetosNoCenario[i].movel)
                    continue;
                float a = (ObjetosNoCenario[i].tx - Modelos[ObjetosNoCenario[i].id].largura / 2.);
                float b = (ObjetosNoCenario[i].tx + Modelos[ObjetosNoCenario[i].id].largura / 2.);
                float c = (ObjetosNoCenario[i].ty - Modelos[ObjetosNoCenario[i].id].altura / 2.);
                float d = (ObjetosNoCenario[i].ty + Modelos[ObjetosNoCenario[i].id].altura / 2.);
                if ((a <= pg_new.x && pg_new.x <= b) && (c <= pg_new.y && pg_new.y <= d))
                {
                    cout << "pega caixa" << endl;
                    InstanciaPresoNoRobo = i;
                    break;
                }
            }
        }
        else // Há caixas na garra, soltar
        {
            cout << "solta caixa" << endl;
            InstanciaPresoNoRobo = -1;
        }
    }
    if (InstanciaPresoNoRobo != -1)
    {
        ObjetosNoCenario[InstanciaPresoNoRobo].tx = pg_new.x;
        ObjetosNoCenario[InstanciaPresoNoRobo].ty = pg_new.y;
    }

    espacoPressionado = false;
}
//-----------------EIXOS----------------------------------
void DesenhaEixos()
{
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2d(0, 25);
    glVertex2d(100, 25);
    glVertex2d(50, 0);
    glVertex2d(50, 50);
    glEnd();
}

//------------------DISPLAY----------------------------------
void display(void)
{
    // Limpa a tela coma cor de fundo
    glClear(GL_COLOR_BUFFER_BIT);
    // Define os limites l�gicos da �rea OpenGL dentro da Janela
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Define os limites l�gicos da �rea OpenGL dentro da Janela
    glOrtho(0, 100, 0, 50, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    DesenhaCenario();
    DesenhaEixos();
    DesenhaRobo();
    glutSwapBuffers();
}
//----------------COMANDOS-----------------------------------------
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:     // Termina o programa qdo
        exit(0); // a tecla ESC for pressionada
        break;
    case 'q':
        RotRobotSegC = RotRobotSegC + 15;
        if (RotRobotSegC > 135)
            RotRobotSegC = 135;
        break;
    case 'w':
        RotRobotSegC = RotRobotSegC - 15;
        if (RotRobotSegC < -135)
            RotRobotSegC = -135;
        break;
    case 'a':
        RotRobotSegB = RotRobotSegB + 15;
        if (RotRobotSegB > 120)
            RotRobotSegB = 120;
        break;
    case 's':
        RotRobotSegB = RotRobotSegB - 15;
        if (RotRobotSegB < -120)
            RotRobotSegB = -120;
        break;
    case ' ':
        espacoPressionado = true;
    default:
        break;
    }
}
void arrow_keys(int a_keys, int x, int y)
{
    switch (a_keys)
    {
    case GLUT_KEY_RIGHT:
        if (PosRobotX + 1 <= 96)
            PosRobotX++;
        break; //
    case GLUT_KEY_LEFT:
        if (PosRobotX - 1 >= 4)
            PosRobotX--;
        break;
    default:
        break;
    }
}
//----------------MAIN-------------------------------------
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(800, 500);
    glutCreateWindow("T1-CG-Larissa-Rodrigo");
    init();
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(arrow_keys);
    glutMainLoop();
    return 0;
}
