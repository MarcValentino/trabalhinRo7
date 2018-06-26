#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void leLinhas(char *nome){
  FILE *arq;
  arq = fopen("bd", "r");
  char linha[256], *token;
  while (fgets(linha, sizeof(linha), arq)) {
        token = strtok(linha, "/");
        while(token){
          printf("%s\n", token);
          token = strtok(NULL, "/");
        }
      }
  }


int main(){
  char k[100] = "bd.txt";
  leLinha(k);
}
