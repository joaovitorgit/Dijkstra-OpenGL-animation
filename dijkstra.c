/*Trabalho Pratico 2
Grupo: Anna Luiza Pereira Rosa - 2019004090
       Joao Vitor de Faria - 2019006030
       Wesley da Silva Ribeiro - 2019006307
*/

// Bibliotecas
#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<time.h>

// Variaveis Globais
GLsizei wh = 1020, ww = 1080;	// Tamanho da Janela
void dijkstra();				// Dijkstra
float PI = 3.14285714286;		// Valor de Pi
int radius = 30;				// Radianos do círculo
int nodeCount = 0;				// Número de nós na janela
int max_num_vertices = 26;				//Número máximo de nós que podem ser criados
int adj_matriz[26][26];			//Matriz de adjacência
int vertices_da_arestaCount = 0;			//Número de nós selecionados para desenhar a linha
int vertice_origem_criado = 0;		//Nó raíz/origem
int vertice_destino_criado = 0;	//Nó destino
int dijkstra_rodando = 0;			//Começo do Dijkstra
int instruction = 1; 			//Instruções para display

//Struct de um nó
struct node{
	int id;
	int coordenada_x;
	int coordenada_y;
} nodes[26], vertices_da_aresta[2], vertice_origem, vertice_destino;

// Cabecalho das funcoes
int calculaDistancia(struct node a, struct node b);
int noRepeat(int x, int y);
void getCoordenadasPerpendiculares(int *x, int *y);
void escreveDistancia(char *text, int x, int y);
void escreverLabel(char text, int x, int y);
void desenhaVertice(float cx, float cy);
void getMidPoint(int *mid_x, int *mid_y);
void desenhaAresta(char color);
void mouse(int botao, int estado, int x, int y);
void reshape(GLsizei w, GLsizei h);
void init();
void display();
void inicializaMatrizAdj();
void keyboard(unsigned char key, int x, int y);
int getVerticeMaisProximo(int *distancia_da_origem, int *visitados);
void desenhaRota(int n1, int n2);
void delay(int number_of_seconds);
void dijkstra();

//Calcula a distância entre dois nós
int calculaDistancia(struct node a, struct node b){
	return (int) sqrt(pow(abs(a.coordenada_x - b.coordenada_x), 2) + pow(abs(a.coordenada_y - b.coordenada_y), 2));
}

//Verfica se dois nó se cruzam para criar um novo nó ou selecionar um nó
int noRepeat(int x, int y){
	if(!nodeCount)
		return 1;

	struct node temp = {nodeCount, x, y};

	for(int i = 0; i < nodeCount; i++){
		if(calculaDistancia(temp, nodes[i]) < 2*radius){
			vertices_da_aresta[vertices_da_arestaCount] = nodes[i];
			return 0;
		}
	}
	return 1;
}

//Obtem as coordenadas para mostrar o texto
void getCoordenadasPerpendiculares(int *x, int *y){
	int x1, x2, y1, y2;

	x1 = vertices_da_aresta[0].coordenada_x;
	x2 = vertices_da_aresta[1].coordenada_x;
	y1 = vertices_da_aresta[0].coordenada_y;
	y2 = vertices_da_aresta[1].coordenada_y;

	float diff = (x2 - x1)? 0.0001 : x2 - x1;
	float slope = ((float)(y2 - y1)) / (diff);
	float perpendicularSlope = -1*(1 / slope);

	*x = *x + 25;
	*y = *y + perpendicularSlope * (*x) + 7;
}

//Escreve a distância entre dois nós na tela
void escreveDistancia(char *text, int x, int y){
	if(instruction){
		glColor3f(1.0, 0.0, 0.0);
	} else {
		glColor3f(1.0, 1.0, 1.0);
	}
    glRasterPos2i(x,y);
    int len = strlen(text);
    for(int i = 0; i < len; i++){
        glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18 , text[i]);
    }
    glFlush();
}

//Escreve a ordem dos nós
void escreverLabel(char text, int x, int y){
	glColor3f(1.0, 1.0, 1.0);
    glRasterPos2i(x,y);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24 , text);
}

//Desenha o nó, dadas as coordenadas
void desenhaVertice(float cx, float cy){

  //Quadrado puxado do telhado
  glBegin(GL_QUADS);
  glColor3f(0.9f, 0.5f, 0.2f);
  glVertex2d(cx+90,cy + 40);    //superior direito
  glVertex2d(cx+120,cy + 0);     //inferior direito
  glVertex2d(cx+40, cy + 0);     //inferior esquerdo
  glVertex2d(cx+25, cy + 40);    //superior esquerdo
  glEnd();

   //Quadro principal da casa
  glBegin(GL_QUADS);
  glEnable(GL_LINE_SMOOTH);
  //glVertex2d(center.first + halfside, center.second + halfside);
  glColor3f(0.7f, 0.9f, 1.0f);

  glVertex2d(cx+110, cy +0 ); // superior direito
  glVertex2d(cx+110, cy -20 );  // inferior direito
  glVertex2d(cx+40, cy -20 );    // inferior esquerdo
  glVertex2d(cx+40, cy +0);  // superior esquerdo
  glEnd();

   //Quadrado puxado da casa
  glBegin(GL_QUADS);
  glColor3f(0.6f, 0.8f, 0.9f);
  glVertex2d(cx+40, cy +0);  //superior direito
  glVertex2d(cx+40,cy - 20); // inferior direito
  glVertex2d(cx+3, cy );      //inferior esquerdo       -> NAO ALTERAR
  glVertex2d(cx+3, cy +15);     //superior esquerdo
  glEnd();

  //Triangulo puxado do telhado
  glBegin(GL_TRIANGLES);
  glColor3f(0.8f, 0.4f, 0.1f);
  glVertex2d(cx+25, cy +40); // cima
  glVertex2d(cx+40,cy + 0); //inferior direito
  glVertex2d(cx-2, cy + 17); //inferior esquerdo
  glEnd();

  // PORTA
  glBegin(GL_QUADS);
  glColor3f(0.5f, 0.2f, 0.2f);
  glVertex2d(cx+31,cy + 0);   //superior direito
  glVertex2d(cx+31,cy + -15);   //inferior direito
  glVertex2d(cx+20,cy + -10);   //inferior esquerdo
  glVertex2d(cx+20,cy + 5);   //superior esquerdo
  glEnd();

  //Quadro janela
  glBegin(GL_QUADS);
  glColor3f(0.0f, 0.5f, 0.5f);
  glVertex2d(cx+85,cy + -2);   //superior direito
  glVertex2d(cx+85,cy + -15);    //inferior direito
  glVertex2d(cx+55, cy + -15);    //inferior esquerdo
  glVertex2d(cx+55,cy + -2);   //superior esquerdo
  glEnd();

  glBegin(GL_LINES);
  glColor3f(0.0f, 0.3f, 0.3f);
  glVertex2i(cx+55,cy + -9); //superior esquerdo
  glVertex2i(cx+85,cy + -9); // inferior direito
  glEnd();

  glBegin(GL_LINES);
  glColor3f(0.0f, 0.3f, 0.3f);
  glVertex2i(cx+70,cy + -2);     //superior direito
  glVertex2i(cx+70,cy +-15);      //inferior esquerdo
  glEnd();

  glFlush();
}

// Define as coordenadas do ponto medio para os argumentos
void getMidPoint(int *mid_x, int *mid_y)
{
	*mid_x = (vertices_da_aresta[0].coordenada_x + vertices_da_aresta[1].coordenada_x)/2;
	*mid_y = (vertices_da_aresta[0].coordenada_y + vertices_da_aresta[1].coordenada_y)/2;
}

// Desenha o caminho entre dois vertices
void desenhaAresta(char color){
	// Define a cor inicial dos caminhos: cinza
	if(color == 'N' || color == 'R')
		glColor3f(0.3, 0.3, 0.3);

	if(color == 'D')
		glColor3f(0.8, 0.8, 0.8);

	if(color == 'M')
		glColor3f(0.4, 1.0, 0.1);

  // Desenha o caminho entre os nos selecionados.
  // Os nos selecionados estao armazenados em vertices_da_aresta.
	glBegin(GL_LINES);
		glVertex2f(vertices_da_aresta[0].coordenada_x, vertices_da_aresta[0].coordenada_y);
		glVertex2f(vertices_da_aresta[1].coordenada_x, vertices_da_aresta[1].coordenada_y);
	glEnd();
	glFlush();

  // Ponto médio do segmento de linha para exibir a distância
	int mid_x, mid_y;
	char distanceString[10];
	// Pega  coordenada do mid
	getMidPoint(&mid_x, &mid_y);


  // Pega id e key dos nos para a adj_matriz
	int id1 = vertices_da_aresta[0].id;
	int id2 = vertices_da_aresta[1].id;
  // Calcula a distancia entre os nos
	int distancia = calculaDistancia(vertices_da_aresta[0], vertices_da_aresta[1]);

	// Armazena a distancia na matriz de adjacencia
	adj_matriz[id1][id2] = distancia;
	adj_matriz[id2][id1] = distancia;

	// Converte a distancia em string
	sprintf(distanceString, "%d",distancia);

	// Escreve a distancia na tela
	getCoordenadasPerpendiculares(&mid_x, &mid_y);
	escreveDistancia(distanceString, mid_x, mid_y);

	glFlush();

	// Redesenha os dois vertices
	escreverLabel('A' + vertices_da_aresta[0].id, vertices_da_aresta[0].coordenada_x - 5, vertices_da_aresta[0].coordenada_y - 14);
	escreverLabel('A' + vertices_da_aresta[1].id, vertices_da_aresta[1].coordenada_x - 5, vertices_da_aresta[1].coordenada_y - 14);

	glFlush();

	
}

// Funcao para receber as entradas do mouse
void mouse(int botao, int estado, int x, int y){
	// Primeiramente limpa as instrucoes
	if(instruction)	{
		instruction = 0;
		glClear(GL_COLOR_BUFFER_BIT);
	}

  // Ignorar comandos do mouse caso o Dijkstra ja esteja rodando.
	if(dijkstra_rodando){
		return;
	}

	// Arrumar o sistema de coordenadas
	y = wh-y;

	// Clique esquerdo: Criar vertices ou conectar vertices
	if(botao==GLUT_LEFT_BUTTON && estado==GLUT_DOWN)	{


		// Caso nao tenha clicado no mesmo vertice
		if (noRepeat(x, y))
		{
			// Nao desenha caso haja mais de 26 vertices
			if(nodeCount >= 26)
			{
				return;
			}

			// Desenha o vertice
			desenhaVertice(x, y);
			vertices_da_arestaCount = 0;
			// Define as coordenadas do novo Vertice
			nodes[nodeCount].coordenada_x = x;
			nodes[nodeCount].coordenada_y = y;
			nodes[nodeCount].id = nodeCount;

			// Aumenta o cont de vertices
			nodeCount++;
		}
		// Desenha aresta
		else
		{
			if(vertices_da_arestaCount == 1)
			{
				desenhaAresta('N');
				vertices_da_arestaCount = 0;
			}
			else
			{
				vertices_da_arestaCount += 1;
			}
		}
	}

	// Clique direito: Define vertice de origem e destino
	if(botao==GLUT_RIGHT_BUTTON && estado==GLUT_DOWN && (!vertice_origem_criado || !vertice_destino_criado))
	{
		// Caso o vertices estejam criados
		if(nodeCount)
		{
      // Caso um vertice estiver clicado, vertices_da_aresta[0] ira conte-lo
      if(!noRepeat(x, y))
			{
				// Caso o Vertice de origem nao esteja definido
				if(!vertice_origem_criado)
				{
					vertice_origem = vertices_da_aresta[0];
					// Define o Vertice de origem
					vertice_origem_criado = 1;
					// Altera a cor do vertice de origem
					desenhaVertice(vertice_origem.coordenada_x, vertice_origem.coordenada_y);
				}
				else
				{
					// Caso o Vertice de origem ainda nao esteja definido
					if(((vertice_origem.coordenada_x - vertices_da_aresta[0].coordenada_x) != 0) || ((vertice_origem.coordenada_y - vertices_da_aresta[0].coordenada_y) != 0 ))
					{
						vertice_destino = vertices_da_aresta[0];
						// Cria o no destino
						vertice_destino_criado = 1;
						// Altera a cor do no de destino
						desenhaVertice(vertice_destino.coordenada_x, vertice_destino.coordenada_y);

					}
				}

			}
		}
	}

}


// Funcao para fazer leitura de comandos do teclado(enter que inicia o Dijkstra)
void keyboard(unsigned char key, int x, int y){
	

	// Nao inicializa caso os vertices de origem e destino nao estejam definidos
	if(!vertice_origem_criado || !vertice_destino_criado)
	{
		printf("Vertices de origem| destino nao visitados\n");
		return;
	}
	// Inicia Dijkstra apos a leitura do Enter.
	if((int)key == 13)
	{
		dijkstra_rodando = 1;
		dijkstra();
	}
}

// Retorna distancia minima ate um vertice nao selecionado.
int getVerticeMaisProximo(int *distancia_da_origem, int *visitados){
	int vertice_minimo = -1;
	int distancia_minima = 99999;

	// Percorre todos os vertices
	for(int i = 0; i < nodeCount; i++)
	{
    // Escolhe um vertice caso ele nao esteja selecionado mas, no momento, tenha uma distancia menor.
    if(visitados[i] != 1 && distancia_da_origem[i] < distancia_minima)
		{
			vertice_minimo = i;
			distancia_minima = distancia_da_origem[i];
		}
	}

	// Retorna o Vertice com distancia minima
	return vertice_minimo;
}

// Implementacao do algoritmo de Dijkstra
void dijkstra(){

	// Salva a distancia de todos vertice a partir do vertice de origem
	int distancia_da_origem[26];

	// Armazena os vertices conectados ao vertice atual
	int prev[26];

	// Armazena se um vertice foi visitado ou nao
	int visitados[26];

	// O vertice atual
	int vertice_atual;

  // Inicializa as distancia como 9999, os vertices como nao visitados e nao conectados.
	for(int i = 0; i < nodeCount; i++)
	{
		distancia_da_origem[i] = 99999;
		prev[i] = -1;
		visitados[i] = -1;
	}

	// Define a distancia do vertice raiz ate ele mesmo como 0
	distancia_da_origem[vertice_origem.id] = 0;

	for(int i = 0; i < nodeCount; i++)
	{
		// Obtem o vertice nao selecionado com distancia minima
		vertice_atual = getVerticeMaisProximo(distancia_da_origem, visitados);

    
		if(vertice_atual == -1)
			break;

		visitados[vertice_atual] = 1;


		// Percorre todos os nos vizinhos
		for(int j = 0; j < nodeCount; j++)
		{
			// Caso o vertice vizinho nao tenha sido visitado
			if(visitados[j] != 1)
			{
			// Se a distancia do no atual + a distancia da matriz de adjacencia do vizinho for menor que a distancia ate origem do vizinho
      	 	if((distancia_da_origem[vertice_atual] + adj_matriz[vertice_atual][j]) < distancia_da_origem[j])
				{
					// Descobrimo um caminho mais curto ate o no vizinho. Logo, atribuimos esse novo valor a variavel distancia_da_origem
					distancia_da_origem[j] = distancia_da_origem[vertice_atual] + adj_matriz[vertice_atual][j];
					// Caso o vertice nao seja precedente do vertice atual
					if(prev[j] != -1)
					{	

						vertices_da_aresta[0] = nodes[prev[j]];
						vertices_da_aresta[1] = nodes[j];
						delay(700);
						desenhaAresta('R');

						delay(700);
						vertices_da_aresta[0] = nodes[vertice_atual];
						desenhaAresta('D');
					}
					else
					{
						delay(700);
						vertices_da_aresta[1] = nodes[j];
						vertices_da_aresta[0] = nodes[vertice_atual];
						desenhaAresta('D');
					}
					// Passamos a execucao para o no vizinho
					prev[j] = vertice_atual;
				}
			}
		}

	}

	while(1)
	{	
		if(prev[vertice_destino.id] == -1)
			break;
		delay(500);
		desenhaRota(vertice_destino.id, prev[vertice_destino.id]);
		vertice_destino = nodes[prev[vertice_destino.id]];
	}
}


// Controla o tamanho da tela
void reshape(GLsizei width, GLsizei height){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, 0, height);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, width, height);
	ww = width;
	wh = height;
}

// Inicializacao da tela
void init(){
	glViewport(0,0,ww,wh);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, ww, 0, wh);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0.0, 0.0, 0.0, 1);
	glColor3f(1.0, 1.0, 1.0);
	// glPointSize(0);
	 glLineWidth(5);
}

// Definicao do Display
void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glFlush();
}

// Define como 99999 a distancia entre todos os vertices salvos na matriz de adjacencia.
void inicializaMatrizAdj(){
	for(int i = 0; i < max_num_vertices; i++){
		for(int j = 0; j < max_num_vertices; j++){
			adj_matriz[i][j] = 99999;
		}
	}
}



// Funcao main
int main(int argc, char **argv){
	inicializaMatrizAdj();

	glutInit(&argc, argv);
	glutInitWindowSize(ww, wh);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("Trabalho Pratico 02");
	init();
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}





// Desenha a rota entre o verticem de origem e destino
void desenhaRota(int n1, int n2){
	vertices_da_aresta[0] = nodes[n1];
	vertices_da_aresta[1] = nodes[n2];

	desenhaAresta('M');
}



void delay(int number_of_seconds){
    // Converte em milissegundos
    int milli_seconds = 1000 * number_of_seconds;

    // Inicia o tempo
    clock_t start_time = clock();

    // Loop enquanto nao alcancar o tempo
    while (clock() < start_time + milli_seconds);
}

