#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bMais.h"

TAB *Cria(int t){
  printf("criando\n");
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
  novo->adic = (Info**)malloc(sizeof(Info*)*((2*t)-1));
  for(i=0;i<(t*2)-1;i++) novo->adic[i] = (Info *) malloc(sizeof(Info));
  printf("terminou de criar\n");
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
      ImprimeInfos(a->filho[i],andar+1);
      for(j=0; j<=andar; j++) printf("   ");
      //if(a->folha){
        printf("Chave: %s\n", a->chave[i]);
        printf("Cantor: %s\n", a->adic[i]->cantor);
        printf("Ano: %d\n", a->adic[i]->ano);
        printf("No Musicas: %d\n", a->adic[i]->nMusicas);
        printf("Minutos: %d\n", a->adic[i]->minutos);
        printf("Album: %s\n", a->adic[i]->nmAlbum);
      //}
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
  while(i < arv->nchaves && strcasecmp(arv->chave[i], chave)<0) i++;
  return no->adic[i];
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
  scanf("%s", infos->nmAlbum);
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
      printf("===== ANO %d\n", z->adic[j]->ano );
      z->adic[j] = y->adic[j+t-1];
      printf("===== ANO %d\n", z->adic[j]->ano );

    }
    y->nchaves = t - 1;
    for(j=x->nchaves; j>=i; j--) x->filho[j+1] = x->filho[j]; //só entra nesse for quando tem pai
    x->filho[i] = z;
    for(j=x->nchaves; j>=i; j--){
      strcpy(x->chave[j], x->chave[j-1]); //só entra nesse for quando tem pai
      x->adic[j] = x->adic[j-1];
    }
    strcpy(x->chave[i-1], y->chave[t-1]);
    printf("===== ANO %d\n", x->adic[j]->ano );

    x->adic[i-1] = y->adic[t-1];
    printf("===== ANO %d\n", x->adic[j]->ano );

    x->nchaves++;
    if((y->folha)&&(z->folha)) y->prox = z;
    if(proxOrig) z->prox = proxOrig;
    return x;
  }
  z->nchaves= t-1;
  z->folha = 0;
  int j;
  for(j=0;j<t-1;j++){
    z->chave[j] = y->chave[j+t];
    printf("===== ANO %d\n", z->adic[j]->ano );

    z->adic[j] = y->adic[j+t];

    printf("===== ANO %d\n", z->adic[j]->ano );

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
    x->chave[j] = x->chave[j-1];
    x->adic[j] = x->adic[j-1];
  }
  strcpy(x->chave[i-1], y->chave[t-1]);
  x->adic[i-1] = y->adic[t-1];
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
    printf("arvore vazia\n");
    printf("inserir %d no cantor\n", adic->ano);
    T=Cria(t);
    strcpy(T->chave[0], chave);
    T->adic[0]->ano = adic->ano;
    T->adic[0]->nMusicas = adic->nMusicas;
    T->adic[0]->minutos = adic->minutos;
    strcpy(T->adic[0]->cantor, adic->cantor);
    strcpy(T->adic[0]->nmAlbum,adic->nmAlbum);

    //FALTA CANTOR E NM DO ALBUM

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
  T = Insere_Nao_Completo(T,chave, adic, t);

  return T;
}


void BuscaObras(TAB* a, char *cantor){
  if(!a) return;
  if(a->folha){
    int i;
    int acabou = 0;
    while(!acabou){
      for(i=0; i<(a->nchaves); i++){
        if(strcmp(a->adic[i]->cantor, cantor)==0){
          printf("%s\n", a->adic[i]->nmAlbum);
        }
      }
      if(a->prox == NULL){
        acabou = 1;
      }
      else{
        a = a->prox;
      }
    }
    
  }
  while(a->filho[0]){
    BuscaObras(a->filho[0], cantor);
  }
}


TAB *RemoveInfosIntermediarias(TAB *arv){
  if (!arv) return arv;
  else if(arv->folha) return arv;
  int i;
  printf("removendo de %s\n",arv->chave);
  for (i=0; i<(arv->nchaves)-1;i++) {
    arv->filho[i] = RemoveInfosIntermediarias(arv->filho[i]);
  }
  //printf("====================================\n");
  //printf("Ano antes %d\n", arv->adic->ano);
  for (i=0; i<(arv->nchaves)-1;i++) {
    arv->adic[i]->ano = -1;
  }

  return arv;
  //printf("Ano depois %d\n", arv->adic->ano);
}

/*
TAB* remover(TAB* arv, int ch, int t){
  if(!arv){
    printf("nao tem nada\n");
    return arv;
  }
  Imprime(arv, 0);
  int i, trocou = 0;
  printf("Removendo %d...\n", ch);
  for(i = 0; i<arv->nchaves && arv->chave[i] < ch; i++);
  if(arv->chave[i]==ch && !arv->folha){
    i++;
    trocou = 1;
  }
  if(i < arv->nchaves && ch == arv->chave[i]){ //CASOS 1, 2A, 2B e 2C
    if(arv->folha){ //CASO 1
      printf("\nCASO 1\n");
      int j;
      for(j=i; j<arv->nchaves-1;j++) arv->chave[j] = arv->chave[j+1];
      arv->nchaves--;
      return arv;
    }
    //if(!arv->folha && arv->filho[i]->nchaves >= t){ //CASO 2A
    //  printf("\nCASO 2A\n");
    //  TAB *y = arv->filho[i];  //Encontrar o predecessor k' de k na árvore com raiz em y
    //  while(!y->folha) y = y->filho[y->nchaves];
    //  int temp = y->chave[y->nchaves-1];
    //  arv->filho[i] = remover(arv->filho[i], temp, t);
    //  //Eliminar recursivamente K e substitua K por K' em x
  //  //  arv->chave[i] = temp;
    //  return arv;
    //}
    //if(!arv->folha && arv->filho[i+1]->nchaves >= t){ //CASO 2B
    //  printf("\nCASO 2B\n");
    //  TAB *y = arv->filho[i+1];  //Encontrar o sucessor k' de k na árvore com raiz em y
  //    while(!y->folha) y = y->filho[0];
    //  int temp = y->chave[0];
    //  y = remover(arv->filho[i+1], temp, t); //Eliminar recursivamente K e substitua K por K' em x
    //  arv->chave[i] = temp;
    //  return arv;
    //}//
    //if(!arv->folha && arv->filho[i+1]->nchaves == t-1 && arv->filho[i]->nchaves == t-1){ //CASO 2C
    //  printf("\nCASO 2C\n");
    //  TAB *y = arv->filho[i];
    //  TAB *z = arv->filho[i+1];
    //  y->chave[y->nchaves] = ch;          //colocar ch ao final de filho[i]
    //  int j;
  //  //  for(j=0; j<t-1; j++)                //juntar chave[i+1] com chave[i]
    //    y->chave[t+j] = z->chave[j];
    //  for(j=0; j<=t; j++)                 //juntar filho[i+1] com filho[i]
    //    y->filho[t+j] = z->filho[j];
    //  y->nchaves = 2*t-1;
    //  for(j=i; j < arv->nchaves-1; j++)   //remover ch de arv
    //    arv->chave[j] = arv->chave[j+1];
  //    for(j=i+1; j <= arv->nchaves; j++)  //remover ponteiro para filho[i+1]
    //    arv->filho[j] = arv->filho[j+1];
    //  arv->filho[j] = NULL; //Campello
    //  arv->nchaves--;
    //  arv->filho[i] = remover(arv->filho[i], ch, t);
    //  return arv;
    //}Não haverá remoção em nós intermediários
  }

  TAB *y = arv->filho[i], *z = NULL;
  if (y->nchaves == t-1){ //CASOS 3A e 3B
    if(y->folha){
      if((i < arv->nchaves) && (arv->filho[i+1]->nchaves >=t)){ //CASO 3A
        printf("\nCASO 3A: i menor que nchaves\n");
        z = arv->filho[i+1];
        //y->chave[t-1] = arv->chave[i];   //dar a y a chave i da arv
        int j;
        //for(j=0; j < z->nchaves-1; j++)  //ajustar chaves de z
          //z->chave[j] = z->chave[j+1];
        //z->chave[j] = 0; Rosseti
        y->chave[y->nchaves] = z->chave[0];
        y->nchaves++;
        for(j=0; j < z->nchaves; j++)       //ajustar filhos de z
          z->chave[j] = z->chave[j+1];
        z->nchaves--;
        arv->chave[i] = z->chave[0];//dar a arv uma chave de z
        arv->filho[i] = remover(arv->filho[i], ch, t);
        return arv;
      }
      if((i > 0) && (!z) && (arv->filho[i-1]->nchaves >=t)){ //CASO 3A
        printf("\nCASO 3A: i igual a nchaves\n");
        z = arv->filho[i-1];
        int j;
        for(j = y->nchaves; j>0; j--)               //encaixar lugar da nova chave
          y->chave[j] = y->chave[j-1];
        //for(j = y->nchaves+1; j>0; j--)             //encaixar lugar dos filhos da nova chave
          //y->filho[j] = y->filho[j-1];
        //y->chave[0] = arv->chave[i-1];              //dar a y a chave i da arv
        y->nchaves++;
        arv->chave[i-1] = z->chave[z->nchaves-1];   //dar a arv uma chave de z
        y->chave[0] = z->chave[z->nchaves-1];         //enviar ponteiro de z para o novo elemento em y
        z->nchaves--;
        arv->filho[i] = remover(y, ch, t);
        return arv;
      }
    }

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
    }
  }
  arv->filho[i] = remover(arv->filho[i], ch, t);
  return arv;
}


TAB* retira(TAB* arv, int k, int t){
  if(!arv || !Busca(arv, k)) return arv;
  return remover(arv, k, t);
}
*/
