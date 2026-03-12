# Simulador de Robô 2D

<img src="https://github.com/larissamagistrali/robot-2d/blob/master/print.png" alt="Simulador de Robô 2D" height=400>

## Descrição

Simulador de um robô manipulador 2D desenvolvido em OpenGL com física de gravidade e fricção. O robô pode se movimentar horizontalmente e controlar seus segmentos articulados para pegar e soltar objetos no cenário.

## Características

- 🤖 Robô manipulador com braço articulado
- 📦 Sistema de física com gravidade e fricção
- 🎮 Controles interativos via teclado
- 🎨 Objetos e cenários customizáveis através de arquivos de texto
- 🔄 Detecção de colisões
- 🖼️ Renderização de objetos usando modelos de pixels

## Controles

### Movimentação do Robô

- **Seta Direita** ➡️ - Move o robô para a direita
- **Seta Esquerda** ⬅️ - Move o robô para a esquerda

### Controle do Braço

- **Q** - Rotaciona o segmento C no sentido horário (máx: 135°)
- **W** - Rotaciona o segmento C no sentido anti-horário (mín: -135°)
- **A** - Rotaciona o segmento B no sentido horário (máx: 120°)
- **S** - Rotaciona o segmento B no sentido anti-horário (mín: -120°)

### Ações

- **Espaço** - Pegar/Soltar objeto

### Outros

- **ESC** - Sair do programa

## Arquivos de Configuração

### Modelos de Objetos

Os arquivos de modelo (`.txt`) definem a aparência dos objetos usando uma matriz de pixels com valores RGBA:

```
<largura> <altura>
<r> <g> <b> <alpha>
<r> <g> <b> <alpha>
...
```

### Arquivo de Cenário

O arquivo `cenario.txt` define as instâncias de objetos no cenário:

```
<quantidade de instâncias>
<ID do modelo> <posição X> <posição Y> <0 ou 1 - móvel>
...
```

- O último parâmetro indica se o robô pode pegar o objeto (1) ou não (0)

## Compilação e Execução

### Pré-requisitos

- OpenGL
- GLUT (FreeGLUT)
- Biblioteca SOIL (incluída no projeto)
- Compilador C++ (g++, clang, etc.)

### macOS (usando Xcode)

```bash
open OpenGL.xcodeproj
```

### Linux

```bash
g++ ProgramaBasicoOpenGL.cpp ImageClass.cpp TextureClass.cpp SOIL/*.cpp \
    -lGL -lGLU -lglut -o robot2d
./robot2d
```

### Windows (Code::Blocks)

```bash
# Abrir o projeto OpenGL.cbp no Code::Blocks
```

## Estrutura do Projeto

```
.
├── ProgramaBasicoOpenGL.cpp  # Código principal
├── ImageClass.cpp/h          # Classe para manipulação de imagens
├── TextureClass.cpp/h        # Classe para texturas
├── SOIL/                     # Biblioteca de carregamento de imagens
├── objetos/                  # Modelos de objetos (.txt)
│   ├── caixa1.txt
│   ├── caixa2.txt
│   ├── prateleira1.txt
│   └── ...
├── cenario.txt               # Configuração do cenário
└── Imagens/                  # Recursos de imagem

```

## Física do Simulador

O simulador implementa física básica:

- **Gravidade**: 0.1 unidades
- **Fricção**: 0.05 unidades
- Os objetos móveis caem quando suspensos
- Objetos colidem com o chão e outros objetos
- Movimento suavizado por delta time (dt)

## Autores

Larissa Magistrali, Rodrigo Silva

**Projeto acadêmico** - T1 - Computação Gráfica (2019/2)
