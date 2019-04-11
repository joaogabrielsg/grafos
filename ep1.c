#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define NUMERO_MAXIMO_VETORES 150
#define INFINITO 10000

/* Exercício Programa da Disciplina de Grafos
   Curso Engenharia da Computação   */



/* Autores
    Daniel Silva
    Italo Bruno
    João Gabriel
    José Yuri
    Robson Ribeiro
*/


/*  O programa desenvolvido abaixo visa implementar na linguagem C o Algoritmo de Dijkstra
	para calcular e exibir um caminho de custo mínimo. */

/* O programa funciona da seguinte maneira: Ao escrever pela linha de comando o nome de um
	arquivo (contendo a descrição de um digrafo), O arquivo fornecido ao programa deverá ter o seguinte layout:

	n m s t
	u1 v1 c1
	u2 v2 c2
	...
	um vm cm

	onde n é a quantidade de vértices, m a quantidade de arcos, s é o vértice origem, t é o vértice destino,
	ui e vi são a origem e o destino do arco i e ci é o custo da aresta i, então o programa vai utilizar o
	Algoritmo de Dijkstra para calcular um caminho de custo mínimo de s a t, posteriormente vai exibi-lo. */



//função criada para mostrar o caminho minino achado pelo algoritmo de Dijsktra
void ImprimeCaminho(int origem,int destino,int *anterior,int i,double *listaDistancias){
    printf("\nCaminho minimo do vértice %d para o vértice %d \n",origem,destino);
    i = destino;
    printf("%d" ,i);
    i = anterior[i-1];

    while(i !=-1){
        printf("<- %d",i+1);
        i =  anterior[i];
    }
    printf("\nCusto = %d\n",(int)listaDistancias[destino-1]);
}

//função do Algoritmo de Dijkstra
void dijkstra(int vertices, int origem, int destino, int *custos){
	int i = 0;                                       //variável auxiliar de index
	int verticeAuxiliar = 0;                         //variável auxiliar vértice v
	int anterior[NUMERO_MAXIMO_VETORES];             //vetor dos Anteriores
	int z[NUMERO_MAXIMO_VETORES];                    //vértices para os quais se conhece o caminho mínimo
	double valorMinimo;                              //variável auxiliar
	double listaDistancias[NUMERO_MAXIMO_VETORES];   //vetor com os custos dos caminhos

	while(i<vertices){
        if(custos[i] != -1){
            anterior[i] = origem -1;
            listaDistancias[i] = custos[i];
        }
        else{
            anterior[i] = -1;
            listaDistancias[i] = INFINITO;
        }
        z[i] = 0;
        i++;
	}
	z[origem-1] = -1;
	listaDistancias[origem-1] = 0;

	//Insere o novo vértice que se conhece o caminho mínimo no conjunto z
	while(verticeAuxiliar != destino-1 && valorMinimo != INFINITO){
		valorMinimo = INFINITO;

		for(i = 0; i < vertices; i++){
			if(z[i] == 0){
				if(listaDistancias[i] >= 0 && listaDistancias[i] < valorMinimo){
					valorMinimo = listaDistancias[i];
					verticeAuxiliar = i;
				}
			}
		}

		//Distâncias dos novos vizinhos de z
		if(valorMinimo != INFINITO && verticeAuxiliar != destino-1){
			z[verticeAuxiliar] = 1;
			for(i = 0; i < vertices; i++)
				if(z[i] == 0){
					if(custos[verticeAuxiliar*vertices+i] != -1 && listaDistancias[verticeAuxiliar]+custos[verticeAuxiliar*vertices+i] < listaDistancias[i]){
						listaDistancias[i] = listaDistancias[verticeAuxiliar]+custos[verticeAuxiliar*vertices+i];
						anterior[i] = verticeAuxiliar;
					}
				}
		}
  }

  //Verifica se existe cominho minimo, se tiver imprime
	if(valorMinimo == INFINITO)
		printf("\nNão existe caminho entre os vértices %d e %d.\n", origem, destino);
	else{
		ImprimeCaminho(origem,destino,anterior,i,listaDistancias);
	}
}

int main(){
    setlocale(LC_ALL,"Portuguese");

	int vertices = 0;   	//quantidade de vértices do grafo
	int arcos    = 0; 		//quantidade de arcos do grafo
	int origem   = 0;     	//vértice origem dijkstra
	int destino  = 0;    	//vértice destino dijkstra
	int origemU  = 0;    	//vértice origem de cada arco do grafo
	int destinoV = 0;   	//vértice destino de cada arco do grafo
	int *custos  = NULL; 	//lista de adjacências
	int i = 0;
	int j = 0;

	FILE *arquivo = NULL;
	char *NomeArq;
	NomeArq = malloc(sizeof(char) *35);
    setlocale(LC_ALL,"portuguese");

	while(arquivo == NULL){
		printf("Digite o nome do arquivo sem a extensão");
		gets(NomeArq);
		strcat(NomeArq,".txt\0");
		arquivo = fopen(NomeArq,"r");
	}

	//Lê o arquivo e armazena os valores nas variáveis
	fscanf(arquivo, "%d %d %d %d", &vertices, &arcos, &origem, &destino); //Lê a primeira linha do arquivo

	free(custos);
	custos = (int*)malloc(sizeof(int)*vertices*vertices);
	for(i = 0; i <= vertices*vertices; i++)
		custos[i] = -1;

	//Lê o arquivo a partir da segunda linha e armazena as variáveis
	for(j = 0; j < arcos; j++){
		fscanf(arquivo, "%d %d", &origemU, &destinoV);
		//Armazena os custos na lista de adjacências
		fscanf(arquivo, "%d", &custos[(origemU-1)*vertices+destinoV-1]);
	}
	fclose(arquivo);

	dijkstra(vertices, origem, destino, custos);

  return 0;
}
