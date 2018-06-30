#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct info{
  char cantor[100];
  int ano;
  int nMusicas;
  int minutos;
  char nmAlbum[100];
}Info;

void leLinhas(char *nome){
  FILE *arq;
  arq = fopen("bd", "r");
  char linha[256], *token;
  while (fgets(linha, sizeof(linha), arq)){
        Info *infos = (Info *) malloc(sizeof(Info));
        token = strtok(linha, "/");
        //while(token){
        //  printf("%s\n", token);
        //  token = strtok(NULL, "/");
        //}
        strcpy(infos->cantor, token);
        token = strtok(NULL, "/");
        char chave[200];
        strcpy(chave, infos->cantor);
        strcat(chave, token);
        //printf("%s\n", chave);
        infos->ano = atoi(token);
        token = strtok(NULL, "/");
        infos->nMusicas = atoi(token);
        token = strtok(NULL, "/");
        infos->minutos = atoi(token);
        token = strtok(NULL, "/");
        strcpy(infos->nmAlbum, token);
        //Insere(chave, infos, arv);
      }
  }


int main(){
  char k[100] = "bd.txt";
  leLinhas(k);
}
