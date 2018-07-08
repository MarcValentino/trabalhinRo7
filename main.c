#include <string.h>
#include "bMais.h"

int main(){
  int t = 2;
  TAB * arvore = Inicializa();
  char nmArq[128];
  printf("Digite o nome do arquivo: ");
  scanf("%s", nmArq);
  arvore = leLinhas(arvore, nmArq);
  int opt;
  char chave[200];
  char ano[5];
  while(opt != -5){
    printf("-9 para remover, 0 para debug, -1 para imprimir infos, -2 para buscar/-3 para modificar uma info, -4 para imprimir todas as obras, -5 para sair\n");
    scanf("%d", &opt);
    fgets(chave, sizeof(chave), stdin);
    if(!opt) Imprime(arvore, 0);

    else if(opt == -9){
      printf("Cantor:\n");
      fgets(chave, sizeof(chave), stdin);
      char *pos;
      if((pos=strchr(chave, '\n')) != NULL) *pos = '\0';
      printf("Ano:\n");
      fgets(ano, sizeof(ano), stdin);
      if((pos=strchr(ano, '\n')) != NULL) *pos = '\0';
      strcat(chave, ano);
      arvore = retira(arvore, chave, t);
    }
    else if(opt==-1) ImprimeInfos(arvore, 0);
    else if(opt==-2){
      //fgets(chave, sizeof(chave), stdin);
      printf("Cantor:\n");
      fgets(chave, sizeof(chave), stdin);
      char *pos;
      if((pos=strchr(chave, '\n')) != NULL) *pos = '\0';
      printf("Ano:\n");
      fgets(ano, sizeof(ano), stdin);
      if((pos=strchr(ano, '\n')) != NULL) *pos = '\0';
      strcat(chave, ano);
      Info *temp;
      temp = BuscaInfos(chave, arvore);

    }
    else if(opt==-3){
      //fgets(chave, sizeof(chave), stdin);
      printf("Cantor:\n");
      fgets(chave, sizeof(chave), stdin);
      char *pos;
      if((pos=strchr(chave, '\n')) != NULL) *pos = '\0';
      printf("Ano:\n");
      fgets(ano, sizeof(ano), stdin);
      if((pos=strchr(ano, '\n')) != NULL) *pos = '\0';
      strcat(chave, ano);
      AlteraUmaInfo(chave, arvore);
    }
    else if(opt==-4){
      printf("Cantor:\n");
      fgets(chave, sizeof(chave), stdin);
      char *pos;
      if((pos=strchr(chave, '\n')) != NULL) *pos = '\0';
      char busca[200];
      strcpy(busca, chave);
      strcat(busca, "0000");
      TAB *p = arvore;
      BuscaObras(p, chave, busca);
    }
  }
  return 0;
}
