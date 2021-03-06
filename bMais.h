#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//const int t = 2;
typedef struct info{
  char cantor[100];
  int ano;
  int nMusicas;
  int minutos;
  char nmAlbum[100];
}Info;

typedef struct ArvB{
  int nchaves, folha;
  char **chave;
  Info **adic;
  struct ArvB **filho, *prox;
}TAB;

typedef struct lista{
  char chave[100];
  struct lista *prox;
}Lista;


TAB *Cria(int t);
TAB *Libera(TAB *a);
void Imprime(TAB *a, int andar);
TAB *Inicializa();
TAB *Divisao(TAB *x, int i, TAB* y, int t);
TAB *Insere_Nao_Completo(TAB *arv, char *chave, Info *adic, int t);
TAB *Insere(TAB *T, char *chave, Info *adic, int t);
TAB *remover(TAB* arv, char *chave, int t);
TAB *retira(TAB* arv, char *chave, int t);
void testeFolhas(TAB *t);
TAB *Busca(TAB* arv, char *ch);
Info *BuscaInfos(char *chave, TAB *arv);
void AlteraUmaInfo(char *chave, TAB *arv);
void ImprimeInfos(TAB *a, int andar);
void ConsertaFinal(TAB *arv);
//funcoes do arquivo.c
TAB *leLinhas(TAB *arv, char *nome);
TAB *RemoveInfosIntermediarias(TAB *arv);
Lista *BuscaObras(TAB* a, char *cantor, char *chave);
Lista *iniLista(Lista *l);
Lista *insereLista(Lista *l, char *chave);
Lista *apagarLista(Lista *l, TAB *arv, int t);
void imprimeLista(Lista *l);
