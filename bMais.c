#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bMais.h"

TAB *Cria(int t){
  TAB* novo = (TAB*)malloc(sizeof(TAB));
  novo->nchaves = 0;
  novo->chave =(char**)malloc(((t*2)-1)*sizeof(char*)); //mudei de sizeof(char**) para sizeof(char*)
  int i;
  for(i=0;i<t*2-1;i++) novo->chave[i] = (char *) malloc((64)*sizeof(char));
  novo->folha=1;
  novo->filho = (TAB**)malloc(sizeof(TAB*)*(t*2));
  //int i;
  for(i=0; i<(t*2); i++) novo->filho[i] = NULL;
  novo->prox = NULL;
  Info **infos = (Info **) malloc(sizeof(Info*)*((2*t)-1));
  novo->adic = infos;
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

void ImprimeInfos(TAB *a, int andar){ //so imprime se for folha
  if(a){
    int i,j;
    for(i=0; i<=a->nchaves-1; i++){
      Imprime(a->filho[i],andar+1);
      for(j=0; j<=andar; j++) printf("   ");
      if(a->folha){
        //printf("Chave: %s\n", a->chave[i]);
        //printf("Cantor: %s\n", a->adic[i]->cantor);
        //printf("Ano: %d\n", a->adic[i]->ano);
        //printf("No Musicas: %d\n", a->adic[i]->nMusicas);
        //printf("Minutos: %d\n", a->adic[i]->minutos);
        //printf("Album: %s\n", a->adic[i]->nmAlbum);
      }
    }
    Imprime(a->filho[i],andar+1);
  }
}

TAB *Busca(TAB* arv, char *ch){
  //printf("Procurando por: ch\n");
  if(!arv){
    return arv;
  }
  int i = 0;
  while(i < arv->nchaves && strcasecmp(arv->chave[i], ch)<0) i++;
  if((i < arv->nchaves) && strcasecmp(arv->chave[i], ch)==0){
    if(arv->folha){
      printf("%s\n", arv->chave[i]);
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
  while(i < arv->nchaves && strcasecmp(arv->chave[i], chave)<0) i++;
  return no->adic[i];
  //if(!arv) return NULL;
  //int i = 0;
  //while(i < arv->nchaves && strcasecmp(arv->chave[i],chave)<0) i++;
  //if((i < arv->nchaves) && strcasecmp(ch == arv->chave[i]==0)){
  //  if(arv->folha) return arv->infos[i]; //ponteiro para as infos
  //  return BuscaInfos(arv->filho[i+1], ch);
  //}
  //return BuscaInfos(arv->filho[i], ch);
}

void AlteraUmaInfo(char *chave, TAB *arv){
  Info *infos = BuscaInfos(chave, arv);
  if(!infos) return;
  //printf("Valores originais: \n%d musicas\n%d minutos\nNome do album: %s",
  //infos->nMusicas, infos->minutos, infos->nmAlbum);

  printf("Digite os novos valores: \n");
  printf("Musicas: ");
  scanf("%d", &infos->nMusicas);
  printf("Minutos: ");
  scanf("%d", &infos->minutos);
  printf("Nome do Album: ");
  //scanf("%s", infos->nmAlbum);
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
    for(j=0;j<t;j++) strcpy(z->chave[j], y->chave[j+t-1]); //z vai ser o filho da direita
    y->nchaves = t - 1;
    for(j=x->nchaves; j>=i; j--) x->filho[j+1] = x->filho[j]; //só entra nesse for quando tem pai
    x->filho[i] = z;
    for(j=x->nchaves; j>=i; j--) strcpy(x->chave[j], x->chave[j-1]); //só entra nesse for quando tem pai
    strcpy(x->chave[i-1], y->chave[t-1]);
    x->nchaves++;
    if((y->folha)&&(z->folha)) y->prox = z;
    if(proxOrig) z->prox = proxOrig;
    return x;
  }
  z->nchaves= t-1;
  z->folha = 0;
  int j;
  for(j=0;j<t-1;j++) z->chave[j] = y->chave[j+t];
  if(!y->folha){
    for(j=0;j<t;j++){
      z->filho[j] = y->filho[j+t];
      y->filho[j+t] = NULL;
    }
  }
  y->nchaves = t - 1;
  for(j=x->nchaves; j>=i; j--) x->filho[j+1] = x->filho[j];
  x->filho[i] = z;
  for(j=x->nchaves; j>=i; j--) x->chave[j] = x->chave[j-1];
  x->chave[i-1] = y->chave[t-1];
  x->nchaves++;
  // printf("####################\n");
  // Imprime(x, 0);
  // printf("####################\n");
  return x;
}

void testeFolhas(TAB *t){
  TAB *p = t;
  while(!p->folha) p = p->filho[0];
  while(p!=NULL){
    if(p->folha) printf("eh folha\n");
    int i;
    //for(i=0;i<p->nchaves;i++) printf("%s\n", p->chave[i]);
    p = p->prox;
  }
}

TAB *Insere_Nao_Completo(TAB *arv, char *chave, Info *adic, int t){
  printf("Insere Nao Completo a chave \n");
  printf("Arvore antes de inserir chico:\n");
  int i = arv->nchaves-1;
  //printf("%d", i);
  if(arv->folha){
    printf("É folha\n");

    /*
    0: conteúdo das strings são iguais

    < 0: conteúdo da string1 é menor do que string2

    > 0: conteúdo da string1 é maior do que string2
    */
    while((i>=0) && (strcmp(chave, arv->chave[i]) < 0)) { //se chave for menor que o conteudo de no atual
      strcpy(arv->chave[i+1], arv->chave[i]);
      i--;
    }
    strcpy(arv->chave[i+1], chave);
    //printf("Nova chave inserida: %s\n", arv->chave[i+1]);
    arv->nchaves++;
    return arv;
  }//VAI SER O CASO MAIS IMPORTANTE - SÓ INSERE EM FOLHA (B+)
  while((i>=0) && (strcmp(chave, arv->chave[i]) < 0)) i--; //se chave for menor que o conteudo de no atual
  i++;
  if(arv->filho[i]->nchaves == ((2*t)-1)){
    arv = Divisao(arv, (i+1), arv->filho[i], t); //o que é i+1??? na outra era 1 só
    if(strcmp(chave, arv->chave[i]) > 0) i++; //se chave for maior que o conteudo de no atual
  }
  arv->filho[i] = Insere_Nao_Completo(arv->filho[i], chave, adic, t);
  return arv;
}


TAB *Insere(TAB *T, char *chave, Info *adic, int t){
  if(Busca(T,chave)){
    //printf("achou %s na busca\n", chave);
    return T;
  }  //modificar a funcao busca p/ char
  if(!T){
    T=Cria(t);
    //int nChars = (int) sizeof();
    //printf("%d\n", nChars);
    strcpy(T->chave[0], chave);
    T->nchaves=1;
    return T;
  }
  if(T->nchaves == (2*t)-1){
    printf("Nó cheio, tem que dividir\n");
    TAB *S = Cria(t);
    S->nchaves=0;
    S->folha = 0;
    S->filho[0] = T;
    S = Divisao(S,1,T,t); //acho que o 1 devia ser a metade de (2*t)-1 ???
    S = Insere_Nao_Completo(S,chave, adic, t);
    return S;
  }
  //printf("Vai inserir normal\n");
  T = Insere_Nao_Completo(T,chave, adic, t);
  return T;
}


TAB* remover(TAB* arv, char *ch, int t){
  if(!arv){
    printf("nao tem nada\n");
    return arv;
  }//suave

  int i, trocou = 0;
  printf("Removendo %s...\n", ch);
  for(i = 0; i<arv->nchaves &&  strcasecmp(arv->chave[i], ch) < 0; i++);
    if(strcasecmp(arv->chave[i] , ch) == 0 && !arv->folha){
      i++;
      trocou = 1;
    }
  if(i < arv->nchaves && strcasecmp(arv->chave[i], ch )== 0){ //CASOS 1
    if(arv->folha){ //CASO 1
      printf("\nCASO 1\n");
      int j;
      for(j=i; j<arv->nchaves-1;j++) strcpy(arv->chave[j], arv->chave[j+1]);
      arv->nchaves--;
      return arv;
    }
    //Não haverá remoção em nós intermediários
  }

  TAB *y = arv->filho[i], *z = NULL;
  if (y->nchaves == t-1){ //CASOS 3A e 3B
    if(y->folha){
      if((i < arv->nchaves) && (arv->filho[i+1]->nchaves >=t)){ //CASO 3A
        printf("\nCASO 3A: i menor que nchaves\n");
        z = arv->filho[i+1];
        //y->chave[t-1] = arv->chave[i];   //só para b: dar a y a chave i da arv
        int j;
        //for(j=0; j < z->nchaves-1; j++)  //ajustar chaves de z
          //z->chave[j] = z->chave[j+1];
        //z->chave[j] = 0; Rosseti
        strcpy(y->chave[y->nchaves], z->chave[0]); //pega a primeira chave do irmao da direita
        y->nchaves++;
        for(j=0; j < z->nchaves; j++)       //ajustar filhos de z
          strcpy(z->chave[j], z->chave[j+1]);
        z->nchaves--;
        strcpy(arv->chave[i], z->chave[0]); //dar a arv uma chave de z
        arv->filho[i] = remover(arv->filho[i], ch, t);
        return arv;
      }
      if((i > 0) && (!z) && (arv->filho[i-1]->nchaves >=t)){ //CASO 3A
        printf("\nCASO 3A: i igual a nchaves\n");  //remover a chave do ultimo filho
        z = arv->filho[i-1];
        int j;
        for(j = y->nchaves; j>0; j--)               //encaixar lugar da nova chave
          strcpy(y->chave[j], y->chave[j-1]);
        //for(j = y->nchaves+1; j>0; j--)             //enca(ixar lugar dos filhos da nova chave
          //y->filho[j] = y->filho[j-1];
        //y->chave[0] = arv->chave[i-1];              //dar a y a chave i da arv
        y->nchaves++;
        strcpy(arv->chave[i-1], z->chave[z->nchaves-1]);   //dar a arv uma chave de z
        strcpy(y->chave[0], z->chave[z->nchaves-1]);         //enviar ponteiro de z para o novo elemento em y
        z->nchaves--;
        arv->filho[i] = remover(y, ch, t);
        return arv;
      }
    }
    /* comentando para testar o 3a
    if(!z){ //CASO 3B - QUEBRADO-TEM QUE CONSERTAR(Funcionando só para o caso i=0)
      if(i < arv->nchaves && arv->filho[i+1]->nchaves == t-1){
        printf("\nCASO 3B: i menor que nchaves\n");
        z = arv->filho[i+1];
        int j;
        if(!y->folha){
          y->chave[t-1] = arv->chave[i];     //pegar chave [i] e coloca ao final de filho[i]
          y->nchaves++;
          for(j=0; j < t-1; j++){
            y->chave[t+j] = z->chave[j];     //passar filho[i+1] para filho[i]
            y->nchaves++;
          }

          for(j=0; j<t; j++){
            y->filho[t+j] = z->filho[j];
          }

        }else{
          for(j=0; j < t-1; j++){
            y->chave[t-1+j] = z->chave[j];     //passar filho[i+1] para filho[i]
            y->nchaves++;
          }
          arv->filho[i+1] = y; //aposto que é isso quebrando, mas estou sem forças KKKKKKKK
          //vou dormir
          //bj
        }
        for(j=i; j < arv->nchaves-1; j++){ //limpar referências de i
          arv->chave[j] = arv->chave[j+1];
          arv->filho[j+1] = arv->filho[j+2];
        }
        arv->nchaves--;
        arv = remover(arv, ch, t);
        return arv;
      }
      if((i > 0) && (arv->filho[i-1]->nchaves == t-1)){
        printf("\nCASO 3B: i igual a nchaves\n");
        z = arv->filho[i-1];
        if(i == arv->nchaves)
          z->chave[t-1] = arv->chave[i-1]; //pegar chave[i] e poe ao final de filho[i-1]
        else
          z->chave[t-1] = arv->chave[i];   //pegar chave [i] e poe ao final de filho[i-1]
        z->nchaves++;
        int j;
        for(j=0; j < t-1; j++){
          z->chave[t+j] = y->chave[j];     //passar filho[i+1] para filho[i]
          z->nchaves++;
        }
        if(!z->folha){
          for(j=0; j<t; j++){
            z->filho[t+j] = y->filho[j];
          }
        }
        arv->nchaves--;
        arv->filho[i-1] = z;
        arv = remover(arv, ch, t);
        return arv;
      }
    }*/
  }
  arv->filho[i] = remover(arv->filho[i], ch, t);
  return arv;
}


TAB* retira(TAB* arv, char *chave, int t){
  if(!arv || !Busca(arv, chave)) return arv;
  return remover(arv, chave, t);
}

