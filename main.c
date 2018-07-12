#include <string.h>
#include "bMais.h"

int main(){
  int t = 2;
  Lista *l;
  TAB * arvore = Inicializa();
  char nmArq[128];
  printf("Digite o nome do arquivo: ");
  scanf("%s", nmArq);
  arvore = leLinhas(arvore, nmArq);
  if(!arvore) return 0;
  int opt;
  char chave[200];
  char ano[5];
  while(opt != 6){
    printf("0)Remover\n1)Imprimir\n2)Buscar\n3)Modificar uma info\n4)Imprimir obras de um artista\n5)Remover obras de uma artista\n6)Sair\n");
    scanf("%d", &opt);
    fgets(chave, sizeof(chave), stdin);

    if(!opt){
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
    else if(opt==1) ImprimeInfos(arvore, 0);
    else if(opt==2){
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
      printf("%s\n", chave);
      temp = BuscaInfos(chave, arvore);

    }
    else if(opt==3){
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
    else if(opt==4){
      printf("Cantor:\n");
      fgets(chave, sizeof(chave), stdin);
      char *pos;
      if((pos=strchr(chave, '\n')) != NULL) *pos = '\0';
      char busca[200];
      strcpy(busca, chave);
      strcat(busca, "0000");
      TAB *p = arvore;
      l = BuscaObras(p, chave, busca);
      //imprimeLista(l);
    }
    else if(opt==5){
      printf("Cantor:\n");
      fgets(chave, sizeof(chave), stdin);
      char *pos;
      if((pos=strchr(chave, '\n')) != NULL) *pos = '\0';
      char busca[200];
      strcpy(busca, chave);
      strcat(busca, "0000");
      TAB *p = arvore;
      l = BuscaObras(p, chave, busca);
      l = apagarLista(l, arvore, t);
    }
  }
  return 0;
}
