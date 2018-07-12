#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bMais.h"

TAB *Cria(int t){
  TAB* novo = (TAB*)malloc(sizeof(TAB));
  novo->nchaves = 0;
  novo->chave =(char**)malloc(((t*2)-1)*sizeof(char*));
  int i;
  for(i=0;i<t*2-1;i++) novo->chave[i] = (char *) malloc((64)*sizeof(char));
  novo->folha=1;
  novo->filho = (TAB**)malloc(sizeof(TAB*)*(t*2));
  for(i=0; i<(t*2); i++) novo->filho[i] = NULL;
  novo->prox = NULL;
  novo->adic = (Info**)malloc(sizeof(Info*)*((2*t)-1));
  for(i=0;i<(t*2)-1;i++) novo->adic[i] = (Info *) malloc(sizeof(Info));
  return novo;
}


TAB *Libera(TAB *a){
  if(a){
    if(!a->folha){
      int i;
      for(i = 0; i <= a->nchaves; i++) Libera(a->filho[i]);
    }
    free(a->chave);
    free(a->adic);
    free(a->filho);
    free(a);
    return NULL;
  }
}


void Imprime(TAB *a, int andar){
  if(a){
    int i,j;
    for(i=0; i<=a->nchaves-1; i++){
      Imprime(a->filho[i],andar+1);
      for(j=0; j<=andar; j++) printf("   ");
      printf("%s\n", a->chave[i]);
    }
    Imprime(a->filho[i],andar+1);
  }
}

void ImprimeInfos(TAB *a, int andar){
  if(a){
    int i,j;
    for(i=0; i<=a->nchaves-1; i++){
      ImprimeInfos(a->filho[i],andar+1);
      if(a->folha){
        printf("Chave: %s\n", a->chave[i]);
        printf("Cantor: %s\n", a->adic[i]->cantor);
        printf("Ano: %d\n", a->adic[i]->ano);
        printf("No Musicas: %d\n", a->adic[i]->nMusicas);
        printf("Minutos: %d\n", a->adic[i]->minutos);
        printf("Album: %s\n", a->adic[i]->nmAlbum);
      }
    }
    ImprimeInfos(a->filho[i],andar+1);
  }
}

TAB *Busca(TAB* arv, char *ch){
  if(!arv){
    return arv;
  }
  int i = 0;
  while(i < arv->nchaves && strcasecmp(arv->chave[i], ch)<0) i++;
  if((i < arv->nchaves) && strcasecmp(arv->chave[i], ch)==0){
    if(arv->folha){
      return arv;
    }
    return Busca(arv->filho[i+1], ch);
  }
  return Busca(arv->filho[i], ch);
}

Info *BuscaInfos(char *chave, TAB *arv){
  TAB *no = Busca(arv, chave);
  if(!no) return NULL;
  int i=0;
  while(i < no->nchaves && strcasecmp(no->chave[i], chave)<0) i++;
  printf("%s\nAno: %d\nMusicas: %d\nDuração: %d\nAlbum: %s\n", no->adic[i]->cantor, no->adic[i]->ano, no->adic[i]->nMusicas, no->adic[i]->minutos, no->adic[i]->nmAlbum);
  return no->adic[i];
}

void AlteraUmaInfo(char *chave, TAB *arv){
  Info *infos = BuscaInfos(chave, arv);
  if(!infos) return;
  printf("Valores originais: \n%d musicas\n%d minutos\nNome do album: %s",
  infos->nMusicas, infos->minutos, infos->nmAlbum);

  printf("Digite os novos valores: \n");
  printf("Musicas: ");
  scanf("%d", &infos->nMusicas);
  printf("Minutos: ");
  scanf("%d", &infos->minutos);
  printf("Nome do Album: ");
  char novoNm[100];
  fgets(novoNm, sizeof(novoNm), stdin);
  fgets(novoNm, sizeof(novoNm), stdin);
  strcpy(infos->nmAlbum, novoNm);
}


TAB *Inicializa(){
  return NULL;
}


TAB *Divisao(TAB *x, int i, TAB* y, int t){ //o i é a posição que vai entrar o z, novo nó da direita
  TAB *z=Cria(t);
  if(y->folha){
    TAB *proxOrig = y->prox; //auxiliar que guarda valor do proximo no dividido
    z->nchaves= t;
    z->folha = 1;
    int j;
    for(j=0;j<t;j++) {
      strcpy(z->chave[j], y->chave[j+t-1]); //z vai ser o filho da direita
      z->adic[j] = y->adic[j+t-1];

    }
    y->nchaves = t - 1;
    for(j=x->nchaves; j>=i; j--) x->filho[j+1] = x->filho[j];
    x->filho[i] = z;
    for(j=x->nchaves; j>=i; j--){
      strcpy(x->chave[j], x->chave[j-1]);
      x->adic[j] = x->adic[j-1];
    }
    strcpy(x->chave[i-1], y->chave[t-1]);
    x->adic[i-1] = y->adic[t-1];
    x->nchaves++;
    if((y->folha)&&(z->folha)) y->prox = z;
    if(proxOrig) z->prox = proxOrig;
    return x;
  }
  z->nchaves= t-1;
  z->folha = 0;
  int j;
  for(j=0;j<t-1;j++){
    strcpy(z->chave[j], y->chave[j+t]);
  }
  if(!y->folha){
    for(j=0;j<t;j++){
      z->filho[j] = y->filho[j+t];
      y->filho[j+t] = NULL;
    }
  }
  y->nchaves = t - 1;
  for(j=x->nchaves; j>=i; j--) x->filho[j+1] = x->filho[j];
  x->filho[i] = z;
  for(j=x->nchaves; j>=i; j--){
    strcpy(x->chave[j], x->chave[j-1]);
    //x->adic[j] = x->adic[j-1];
  }
  strcpy(x->chave[i-1], y->chave[t-1]);
  //x->adic[i-1] = y->adic[t-1];
  x->nchaves++;
  return x;
}

void testeFolhas(TAB *t){
  TAB *p = t;
  while(!p->folha) p = p->filho[0];
  while(p!=NULL){
    if(p->folha) printf("eh folha\n");
    int i;
    p = p->prox;
  }
}

TAB *Insere_Nao_Completo(TAB *arv, char *chave, Info *adic, int t){
  int i = arv->nchaves-1;
  if(arv->folha){

    while((i>=0) && (strcmp(chave, arv->chave[i]) < 0)) { //se chave for menor que o conteudo de no atual
      strcpy(arv->chave[i+1], arv->chave[i]);
      arv->adic[i+1] = arv->adic[i];
      i--;
    }
    strcpy(arv->chave[i+1], chave);
    arv->adic[i+1] = adic;
    arv->nchaves++;
    return arv;
  }
  while((i>=0) && (strcmp(chave, arv->chave[i]) < 0)) i--;
  i++;
  if(arv->filho[i]->nchaves == ((2*t)-1)){
    arv = Divisao(arv, (i+1), arv->filho[i], t);
    if(strcmp(chave, arv->chave[i]) > 0) i++;
  }
  arv->filho[i] = Insere_Nao_Completo(arv->filho[i], chave, adic, t);
  return arv;
}


TAB *Insere(TAB *T, char *chave, Info *adic, int t){
  if(Busca(T,chave)){
    return T;
  }
  if(!T){
    T=Cria(t);
    strcpy(T->chave[0], chave);
    T->adic[0]->ano = adic->ano;
    T->adic[0]->nMusicas = adic->nMusicas;
    T->adic[0]->minutos = adic->minutos;
    strcpy(T->adic[0]->cantor, adic->cantor);
    strcpy(T->adic[0]->nmAlbum,adic->nmAlbum);

    T->nchaves=1;
    return T;
  }
  if(T->nchaves == (2*t)-1){
    TAB *S = Cria(t);
    S->nchaves=0;
    S->folha = 0;
    S->filho[0] = T;
    S = Divisao(S,1,T,t);
    S = Insere_Nao_Completo(S,chave, adic, t);
    return S;
  }
  T = Insere_Nao_Completo(T,chave, adic, t);
  return T;
}

void ConsertaFinal(TAB *arv){
  while(!arv->folha) arv = arv->filho[arv->nchaves];
  arv->prox = NULL;
}

Lista *BuscaObras(TAB* a, char *cantor, char *chave){
  int i;
  Lista *l = iniLista(l);
  while(!a->folha){
    for(i=0;i < a->nchaves && strcasecmp(a->chave[i], chave)<0;i++);
    a = a->filho[i];
  }
  int j=0;
  while(strcasecmp(a->adic[j]->cantor, cantor)<0){
    j++;
    if(j==a->nchaves){
      j = 0;
      a = a->prox;
    }
  }
  while(j<a->nchaves && !strcasecmp(a->adic[j]->cantor, cantor) && a){
    l = insereLista(l, a->chave[j]);
    printf("%s\n%d\n%d\n%d\n%s\n", a->adic[j]->cantor, a->adic[j]->ano, a->adic[j]->nMusicas, a->adic[j]->minutos, a->adic[j]->nmAlbum);
    j++;
    if(j==a->nchaves && a->prox){
      a = a->prox;
      j = 0;
    }
  }
  return l;
}


TAB *RemoveInfosIntermediarias(TAB *arv){
  if (!arv) return arv;
  else if(arv->folha) return arv;
  int i;
  for (i=0; i<(arv->nchaves)-1;i++) {
    arv->filho[i] = RemoveInfosIntermediarias(arv->filho[i]);
  }
  for (i=0; i<(arv->nchaves)-1;i++) {
    arv->adic[i]->ano = -1;
  }

  return arv;
}

TAB* remover(TAB* arv, char *ch, int t){
  if(!arv){
    //printf("nao tem nada\n");
    return arv;
  }

  int i, trocou = 0;
  //printf("Removendo %s...\n", ch);
  for(i = 0; i<arv->nchaves &&  strcasecmp(arv->chave[i], ch) < 0; i++);
  if(i < arv->nchaves && strcasecmp(arv->chave[i], ch )== 0){ //CASO 1
    if(arv->folha){ //CASO 1
      //printf("\nCASO 1\n");
      int j;
      for(j=i; j<arv->nchaves-1;j++){
        strcpy(arv->chave[j], arv->chave[j+1]);
        arv->adic[j] = arv->adic[j+1];
      }
      arv->nchaves--;
      return arv;
    }
    i++;
  }

  TAB *y = arv->filho[i], *z = NULL;
  if (y->nchaves == t-1){ //CASOS 3A e 3B
    if((i < arv->nchaves) && (arv->filho[i+1]->nchaves >=t)){ //CASO 3A
      //printf("\nCASO 3A: i menor que nchaves\n");
      z = arv->filho[i+1];
      if(!y->folha){
        strcpy(y->chave[t-1], arv->chave[i]);
        strcpy(arv->chave[i], z->chave[0]);
      }
      else{
        strcpy(y->chave[t-1], z->chave[0]);
        y->adic[t-1] = z->adic[0];
        strcpy(arv->chave[i], z->chave[1]);
      }
      int j;
      y->nchaves++;
      for(j=0; j < z->nchaves-1; j++){       //ajustar filhos de z
        strcpy(z->chave[j], z->chave[j+1]);
        if(z->folha) z->adic[j] = z->adic[j+1];
      }
      y->filho[y->nchaves] = z->filho[0];
      for(j=0;j<z->nchaves;j++) z->filho[j] = z->filho[j+1];
      z->nchaves--;
      arv->filho[i] = remover(arv->filho[i], ch, t);
      return arv;
    }
    if((i > 0) && (!z) && (arv->filho[i-1]->nchaves >=t)){ //CASO 3A
      //printf("\nCASO 3A: i igual a nchaves\n");  //remover a chave do ultimo filho
      z = arv->filho[i-1];
      int j;
      for(j = y->nchaves; j>0; j--){               //encaixar lugar da nova chave
        strcpy(y->chave[j], y->chave[j-1]);
        if(y->folha)y->adic[j] = y->adic[j-1];
      }
      for(j = y->nchaves+1; j>0; j--) y->filho[j] = y->filho[j-1];
      if(!y->folha){
				strcpy(y->chave[0], arv->chave[i-1]);
				strcpy(arv->chave[i-1], z->chave[z->nchaves-1]);
				y->filho[0] = z->filho[z->nchaves];
			}
			else{
				strcpy(y->chave[0], z->chave[z->nchaves-1]);
				y->adic[0] = z->adic[z->nchaves-1];
        strcpy(arv->chave[i-1], z->chave[z->nchaves-1]);
      }

      y->nchaves++;
      z->nchaves--;
      arv->filho[i] = remover(y, ch, t);
      return arv;
    }
    //}

    if(!z){
      if(i < arv->nchaves && arv->filho[i+1]->nchaves == t-1){
        //printf("\nCASO 3B: i menor que nchaves\n");
        z = arv->filho[i+1];
        int j;
        if(!y->folha){
          strcpy(y->chave[t-1], arv->chave[i]);     //pegar chave[i] e coloca ao final de filho[i]
          y->nchaves++;
          for(j=0; j < t-1; j++){
            strcpy(y->chave[t+j], z->chave[j]);     //passar filho[i+1] para filho[i]
            y->nchaves++;
          }

          for(j=0; j<t; j++){
            y->filho[t+j] = z->filho[j];
          }

        }else{
          for(j=0; j < t-1; j++){
            strcpy(y->chave[t-1+j], z->chave[j]);
            y->adic[t-1+j] = z->adic[j];
            y->nchaves++;
          }
          y->prox = z->prox;
          arv->filho[i+1] = y;

        }
        for(j=i; j < arv->nchaves-1; j++){
          strcpy(arv->chave[j], arv->chave[j+1]);
          arv->filho[j+1] = arv->filho[j+2];
        }
        arv->nchaves--;
        arv = remover(arv, ch, t);
        return arv;
      }

      if((i > 0) && (arv->filho[i-1]->nchaves == t-1)){
        //printf("\nCASO 3B: i igual a nchaves\n");
        z = arv->filho[i-1];
        if(!z->folha){
          if(i == arv->nchaves){
            strcpy(z->chave[t-1], arv->chave[i-1]); //pegar chave[i] e poe ao final de filho[i-1]
          }
          else{
            strcpy(z->chave[t-1], arv->chave[i]);   //pegar chave [i] e poe ao final de filho[i-1]
          }
          z->nchaves++;
        }

        int nchAtual = z->nchaves;
        int j;
        for(j=0; j < t-1; j++){
          strcpy(z->chave[j+nchAtual], y->chave[j]);//passar filho[i+1] para filho[i]
          if(z->folha) z->adic[j+nchAtual] = y->adic[j];
          z->nchaves++;
        }
        if(!z->folha){
          for(j=0;j<t; j++){
            z->filho[t+j] = y->filho[j];
          }
        }
        else{
          z->prox = y->prox;
        }
        arv->nchaves--;
        arv->filho[i-1] = z;
        arv = remover(arv, ch, t);
        return arv;
      }

    }

  }
  arv->filho[i] = remover(arv->filho[i], ch, t);
  return arv;
}


TAB* retira(TAB* arv, char *chave, int t){
  if(!arv || !Busca(arv, chave)) return arv;
  return remover(arv, chave, t);
}

Lista *iniLista(Lista *l){
  return NULL;
}

Lista *insereLista(Lista *l, char *chave){
  if(!l){
    Lista *temp = (Lista *) malloc(sizeof(Lista));
    strcpy(temp->chave, chave);
    temp->prox = NULL;
    l = temp;
    return l;
  }
  Lista *p = l;
  while(p->prox) p = p->prox;
  Lista *temp = (Lista *) malloc(sizeof(Lista));
  strcpy(temp->chave, chave);
  temp->prox = NULL;
  p->prox = temp;
  return l;
}

Lista *apagarLista(Lista *l, TAB *arv, int t){
    Lista *temp = NULL;
    while(l){
      arv = retira(arv, l->chave, t);
      temp = l;
      l = l->prox;
      free(temp);
    }
    return l;
}

void imprimeLista(Lista *l){
  Lista *p = l;
  while(p){
    printf("%s\n", p->chave);
    p = p->prox;
  }
}
