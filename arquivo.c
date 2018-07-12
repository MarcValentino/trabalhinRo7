#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bMais.h"

TAB *leLinhas(TAB *arv, char *nome){
  FILE *arq;
  arq = fopen(nome, "r");
  if(!arq) return NULL;
  int t = 2;
  char linha[256], *token;
  int i = 0;
  while (fgets(linha, sizeof(linha), arq)){
        Info *infos = (Info *) malloc(sizeof(Info));
        if(linha[1]=='\0') break; //teste pra ver se a string é vazia
        token = strtok(linha, "/");
        strcpy(infos->cantor, token);
        token = strtok(NULL, "/");
        char chave[200];
        strcpy(chave, infos->cantor);
        strcat(chave, token);
        infos->ano = atoi(token);
        token = strtok(NULL, "/");
        infos->nMusicas = atoi(token);
        token = strtok(NULL, "/");
        infos->minutos = atoi(token);
        token = strtok(NULL, "/");
        strcpy(infos->nmAlbum, token);
        arv = Insere(arv, chave, infos, t);
        i++;

      }
      TAB *p = arv;
      ConsertaFinal(p);
      printf("\n");
      Imprime(arv, 0);
      printf("\n");
      return arv;
  }
