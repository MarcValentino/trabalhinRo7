#include <string.h>
#include "bMais.h"

int main(int argc, char *argv[]){
  int t = 2;
  TAB * arvore = Inicializa();
  char nmArq[128];
  printf("Digite o nome do arquivo: ");
  scanf("%s", nmArq);
  arvore = leLinhas(arvore, nmArq);

  Imprime(arvore, 0);
  printf("\n");
  retira(arvore, "Marcelo Valentino3000", t);
  Imprime(arvore, 0);
  printf("\n");
  retira(arvore, "Paulinho da Viola1968", t);
  Imprime(arvore, 0);
  printf("\n");
  retira(arvore, "Cassia Eller2006", t);
  Imprime(arvore, 0);
  printf("\n");
  retira(arvore, "Red Hot Chili Peppers2013", t);
  Imprime(arvore, 0);
  printf("\n");
  retira(arvore, "Red Hot Chili Peppers2006", t);
  Imprime(arvore, 0);
  printf("\n");
  retira(arvore, "Red Hot Chili Peppers2016", t);
  Imprime(arvore, 0);

  /*
  int num = 0, from, to;
  while(num != -1){
    printf("Digite um numero para adicionar. 0 para imprimir. -9 para remover, -2 para testeFolhas e -1 para sair\n");
    scanf("%i", &num);
    if(num == -9){
      scanf("%d", &from);
      //arvore = retira(arvore, from, t);
      Imprime(arvore,0);
    }
    else if(num == -1){
      printf("\n");
      Imprime(arvore,0);
      Libera(arvore);
      return 0;
    }else if(num == -2){
      testeFolhas(arvore);
      printf("\n");
    }
    else if(!num){
      printf("\n");
      Imprime(arvore,0);
    }
    //else arvore = Insere(arvore, num, t);
    printf("\n\n");
  }
  */

}
