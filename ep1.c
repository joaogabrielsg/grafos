#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXV 150
#define INFINITO 10000

/* Exercício Programa da Disciplina de Grafos
   Curso Engenharia da Computação   */



/* Autores
    Daniel Silva
    Italo Bruno
    João Gabriel
    José Yuri
    Robson
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

void imprimeCaminho(int origem, int destino, int *listaAnteriores, double *listaDistancia){
	int i = 0; 
	printf("\nCaminho mínimo do vértice %d para o vértice %d: \n",
			origem, destino);
	
	i = destino;
	printf("%d", i);
	i = listaAnteriores[i-1];
	
	while(i !=-1) {
		printf(" <- %d", i+1);
		i = listaAnteriores[i];
	}
	printf("\nCusto = %d\n", (int)listaDistancia[destino-1]);
}

void dijkstra(int vertices, int origem, int destino, int *custos){ 
	int i = 0; 		   //contador
	int v = 0;         //variável auxiliar vértice v
	int listaAnteriores[MAXV];     //vetor dos predecessores 
	int z[MAXV];       //vértices para os quais se conhece o caminho mínimo
	double min;        //variável auxiliar 
	double listaDistancia[MAXV]; //vetor com os custos dos caminhos 
	
	//Inicialização
	for(i = 0; i < vertices; i++){
		if(custos[i] != -1){
			listaAnteriores[i] = origem-1; 
			listaDistancia[i] = custos[i];
		}
		else{
			listaAnteriores[i] = -1;
			listaDistancia[i] = INFINITO;
		}
		z[i] = 0;
	}
	z[origem-1] = 1;    
	listaDistancia[origem-1] = 0; 

	//Insere o novo vértice que se conhece o caminho mínimo no conjunto z  
	while(v != destino-1 && min != INFINITO){ 
		min = INFINITO; 
		
		for(i = 0; i < vertices; i++){
			if(z[i] == 0){ 
				if(listaDistancia[i] >= 0 && listaDistancia[i] < min){ 
					min = listaDistancia[i]; 
					v = i; 
				}
			}
		}

		//Distâncias dos novos vizinhos de z
		if(min != INFINITO && v != destino-1){ 
			z[v] = 1; 
			for(i = 0; i < vertices; i++)
				if(z[i] == 0){ 
					if(custos[v*vertices+i] != -1 && listaDistancia[v]+custos[v*vertices+i] < listaDistancia[i]){ 
						listaDistancia[i] = listaDistancia[v]+custos[v*vertices+i]; 
						listaAnteriores[i] = v; 
					}
				}
		}
  }//Fim de while(v != destino-1 && min != INFINITO)

  //Imprime caminho mínimo de origem a destino
	if(min == INFINITO)
		printf("\nNão existe caminho entre os vértices %d e %d.\n", origem, destino);
	else
		imprimeCaminho(origem, destino, listaAnteriores, listaDistancia);
}//dijkstra

int main(){

	int vertices = 0;   	//quantidade de vértices do grafo
	int arcos    = 0; 		//quantidade de arcos do grafo
	int origem   = 0;     	//vértice origem dijkstra
	int destino  = 0;    	//vértice destino dijkstra
	int origemU  = 0;    	//vértice origem de cada arco do grafo
	int destinoV = 0;   	//vértice destino de cada arco do grafo
	int *custos  = NULL; 	//lista de adjacências 
	int i = 0;				//variável auxiliar
	int j = 0;				//variável auxiliar

	FILE *arquivo = NULL;
	char caminhoDoArquivo[50];

	while(arquivo == NULL){
		printf("Insira o caminho do arquivo e pressione Enter: \n");
		fgets(caminhoDoArquivo, sizeof(caminhoDoArquivo), stdin);
		//Remove o último caractere do caminho, pois o fgets armazena a quebra de linha '\n'
		char *p_chr = strchr(caminhoDoArquivo, '\n'); 
		if(p_chr != NULL) 
			*p_chr = '\0';
		arquivo = fopen(caminhoDoArquivo, "r");
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
