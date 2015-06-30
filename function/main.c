#include <stdio.h>
#include <stdlib.h>
#include <assert.h> 
#include <string.h>

#include "trad.h"


void verif_et_recup_arg(int nb, char *arg[], int nb_wanted, char *chaine){
  if(nb != nb_wanted){
    printf("Usage : line nom_file\n");
    exit(1);
  }
  strcpy(chaine, arg[1]);
}

int main(int argc, char *argv[]){
  FILE *file_2; 
  int line=100000;
  char read_line[30];
  char nom_file_2[255];
  int nb_line=0;
  
  verif_et_recup_arg(argc, argv, 2, nom_file_2);
  /*==========================Ouverture du file=============================================*/
  file_2 = fopen(nom_file_2, "r"); // ouvrir en lecture
  if(file_2== NULL){
    printf("\nImpossible d'ouvrir le file %s\n", nom_file_2);
    exit(1);
  }
  printf("\n.............. Ouverture du file %s\n", nom_file_2);
  /*==========================\Ouverture du file=============================================*/
  
  /*==========================Transfert ligne txt vers table=============================================*/
  char **table = calloc(line,sizeof(char *));
  int len = 0;
  int i = 0;
  while(fgets(read_line, 512, file_2) != NULL){
    len = strlen(read_line)+1;
    table[i]= calloc(len*len,sizeof(char));
      strncpy(table[i],read_line, len);
      i++;
      nb_line++;
  }
  /*==========================\Transfert ligne txt vers table=============================================*/
  FILE* file = NULL;
 
  file = fopen("test.txt", "w");
  
  if (file != NULL){     
    display(table, nb_line,file); // Ecriture du caractere A
    fclose(file);
    }
  
  printf("\nTout s'est bien passe ===> copie dans test.txt \n\n");
  /*==========================Fermeture du file=============================================*/
  
  if(fclose(file_2) == EOF) {
    printf("Probleme de fermeture du file %s", nom_file_2);
    exit(1);
  }
  printf(".............. Fermeture du file %s\n", nom_file_2);
  /*==========================Liberation memoire=============================================*/
  for(int i=0; i<line; i++){
    free(table[i]);
  }
  free(table);
  return 0;
}

