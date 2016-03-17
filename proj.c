#include <stdio.h>
#include <stdlib.h> 
#include <string.h>


typedef struct pessoa{
	int id;
	struct pessoa* prox;
}Pessoa;

int numFund, maxFund, minFund;

Pessoa* add_Pessoa(int b){
  Pessoa* new= (Pessoa*)malloc(sizeof(Pessoa));
  new->id = b;
  new->prox = NULL;
  return new;
}


void Inserir_Ligacao(Pessoa *rede, int a, int b){
  Pessoa *aux=&rede[a-1];
  Pessoa *new;

  if(aux->id == -1){
    aux->id =b;} 

  else{
    new= add_Pessoa(b);
    while(aux->prox != NULL){
          aux = aux->prox;}
    new->prox = NULL;
    aux->prox = new; 
  }
}


Pessoa* criar_Rede(int N){
  int i;
  Pessoa* rede =(Pessoa*) malloc(sizeof(Pessoa)*N);
  for(i=0; i<N; i++){
    rede[i].id = -1;
    rede[i].prox = NULL;
  }
  return rede;
}


void adicionar_Ligacoes(Pessoa* rede, int L){
  int a,b,i;  
    for(i=0; i<L; i++){
    scanf("%d %d", &a, &b);
    Inserir_Ligacao(rede,a,b);
    Inserir_Ligacao(rede,b,a);
  }
}


void PontosArticulacao(Pessoa *rede, int *depth, int *low, int *visitado, int *pai, int i, int d){
  int somafilhos = 0;
  int articulado = 0;
  Pessoa *aux = &rede[i-1];
  visitado[i-1] = 1;
  depth[i-1] = d;
  low[i-1] = d;
  
  while(aux != NULL){
    int aux_id = aux->id;
    if (visitado[aux_id-1] == 0){
      pai[aux_id-1] = i;
      PontosArticulacao(rede, depth, low, visitado, pai, aux_id, d+1);
      somafilhos++;
      if (low[aux_id-1] >= depth[i-1])
	articulado = 1;
      if (low[i-1] > low[aux_id-1])
	low[i-1] = low[aux_id-1];
    }
    else if (aux_id != pai[i-1] && low[i-1] > depth[aux_id-1])
      low[i-1] = depth[aux_id-1];
    aux = aux->prox;
  }
  if((pai[i-1] != 0 && articulado == 1) || (pai[i-1] == 0 && somafilhos > 1)){
    if(i < minFund)
      minFund = i;
    if(i > maxFund)
      maxFund = i;
    numFund++;
  }
}


int main(int argc, char *argv[]){
  /*Definicao de Variaveis:               */
  int L, N;
  int *depth, *low, *visitado, *pai;
  Pessoa *rede;
  
  scanf("%d %d", &N, &L);   /*N = numero de Pessoas presentes na rede; L = numero de ligações */
  if (N<2){
    printf("Input incorreto!!\n");
    return 0;
  }
  numFund = 0;
  maxFund = -1;
  minFund = N+1;
  
  
  /* Inicialização da rede:               */
  rede = criar_Rede(N);

  /*leitura dos vertices (a,b) - passagem para a função Inserir_Ligacao.*/
  adicionar_Ligacoes(rede, L);
  
  /* Inicialização da rede:               */
  depth = (int*)malloc(sizeof(int)*N);
  low = (int*)malloc(sizeof(int)*N);
  visitado = (int*)malloc(sizeof(int)*N);
  pai = (int*)malloc(sizeof(int)*N);
  
  PontosArticulacao(rede, depth, low, visitado, pai, 1, 1);
  
  if (minFund == N+1)
    minFund = -1;
  printf("%d\n%d %d\n", numFund, minFund, maxFund);


  
  return 0;
}

