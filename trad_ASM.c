#include <stdio.h>
#include <stdlib.h>
#include <assert.h> 
#include <string.h>
#include <stdbool.h>

int variable(char ** table, int i, int j){
  int k=j;
  int len = strlen(table[i]);  
  char * ch_nb=calloc(10,sizeof(char)); 
  //save numéro   
  while(j<len){
    ch_nb[j-k]=table[i][j];
    j++;
  }
  int tmp = atoi(ch_nb);
  free(ch_nb);
  return tmp;
}

void call_1(char ** table, int i, int arg, FILE * file){
  int j=5;
  int k=5;
  int len = strlen(table[i]);
  char * ch=calloc(50,sizeof(char));
  //save instr
  while(j<len-1){
    ch[j-k]=table[i][j];
    j++;
  }        
  char tmp[10]="";
  sprintf(tmp,"%d",arg);
  char * cha=calloc(50,sizeof(char));
  strcpy(cha,ch);
  fputs(cha, file);
  fputc(' ',file);
  fputs(tmp,file);
  fputc('\n',file);
  free(cha);      
  free(ch);   
}

void call_2(char ** table, int i, int arg_1, int arg_2, FILE * file){
  int j=5;
  int k=5;
  int len = strlen(table[i]);
  char * ch=calloc(50,sizeof(char));
  //save instr
  while(j<len-1){
    ch[j-k]=table[i][j];
    j++;
  }       
  char tmp_1[10]="";
  sprintf(tmp_1,"%d",arg_1);
  char tmp_2[10]="";
  sprintf(tmp_2,"%d",arg_2);
  char * cha=calloc(50,sizeof(char));
  strcpy(cha,ch);
  fputs(cha, file);
  fputc(' ',file);
  fputs(tmp_1,file);
  fputc(' ',file);
  fputs(tmp_2,file);
  fputc('\n',file);
  free(cha); 
  free(ch);        
}

void test_fun (char ** table, int * arg, int *nb, int i, int *test, int *item, int *push, FILE * file){
    //Si on rencontre un pushf, on l'enregistre dans la pile
    if(!strcmp(table[i], "call robot_reset\n")){
      fputs("robot_reset\n",file);  
    }

    /*========pushf===============*/
    if(!strncmp(table[i], "pushf ",5)){
      int j=5; 
      //save numéro   
      arg[*nb]= variable(table,i,j);
      (*nb)++;
      (*push)++;
      
    }
    else if(push>0){
      if(!strncmp(table[i],"call",4)){
        if(!strcmp(table[i],"call robot_leg_leds\n")
            ||!strcmp(table[i],"call robot_turn\n")
            ||!strcmp(table[i],"call robot_move_x\n")
            ||!strcmp(table[i],"call robot_move_y\n")){
          call_2(table,i,arg[(*nb)-2],arg[(*nb)-1], file);
          (*nb)--;
          (*nb)--;
          (*push)--;
          (*push)--;
        }
        else if(!strncmp(table[i],"call",4)){
          call_1(table,i,arg[(*nb)-1], file);
          (*nb)--;
          (*push)--; 
        }
      }//end call
      else if (!strcmp(table[i],"add\n")){
        int n=0;
        for(int i =0; i < 10;i++){
          if(arg[i]!=0){
            n++;
          }
        }
        if(n==2){
          *item+=arg[(*nb)-2]+arg[(*nb)-1];
          (*nb)--;
          (*nb)--;
          (*push)--;
          (*push)--;       
        }
        else{
          *item+=arg[(*nb)-1];
          (*nb)--;
          (*push)--;   
        }
      }
    }//end if push
  }
void if_true(char ** table, int * arg, int *nb, int *i, int *test, int *item, int *push, FILE * file){
  bool b = true;
  while(b){    
    test_fun(table, arg, &(*nb), (*i), &(*test), &(*item), &(*push), file);
    if(!strncmp(table[*i],"else_",5)){
      b=false;
    }   
    (*i)++; 
  }
  while(!b){        
    if(!strncmp(table[*i],"if_end_",7)){
      b=true;
    }
    (*i)++; //bon nombre item
  }
}
void if_false(char ** table, int * arg, int *nb, int *i, int *test, int *item, int *push, FILE * file){
  bool b = true;
  while(b){  
    (*i)++;    //bon nombre push
    if(!strncmp(table[*i],"else_",5)){
      b=false;
    }  
  }
  while(!b){   
    (*i)++;  //bon nombre item 
    test_fun(table, arg, &(*nb), (*i), &(*test), &(*item), &(*push), file);
    if(!strncmp(table[*i],"if_end_",7)){
      b=true;
    }  
  }
}


void display(char ** table, int nb_line, FILE *file){
  int * arg = calloc(1000,sizeof(int));
  int nb = 50;
  int i = 0;
  int item=0;
  int test=0;
  int push=0;
  while(i<nb_line){
    if(!strncmp(table[i], "stops",4)){
      fputs("stop\n",file);
      break;
    }
    test_fun(table, arg, &nb, i, &test, &item, &push, file);
    //========begin repeat===============*/
    if(!strncmp(table[i], "repeat_:",7)){
      int cmp=arg[nb-1]-1;
      nb--;
      int end=0;
      int begin=i;
      i++;
      //bool b =true;
      while(cmp>0){     
        if(!strncmp(table[i], "stops",4)){
          fputs("stop\n",file);
          break;
        }
        test_fun(table, arg, &nb, i, &test, &item, &push, file);
        if(!strcmp(table[i],"teste\n")){
          test=arg[nb-1];
          nb--;
          push--; 
          if(test==item){
            if_true(table, arg, &nb, &i, &test, &item, &push, file);
          }
          else{
            if_false(table, arg, &nb, &i, &test, &item, &push, file);
          }    
        }//fin teste 
        i++;
        if(!strncmp(table[i], "jmp repeat_",11)){
          cmp--;
          i=begin;
        }    
      }//end while 
      if(!strcmp(table[i],"smash\n")){
        i=begin+end;
      }
      if(!strcmp(table[i],"kills\n")){
        break;
      }
    } //end repeat   

    i++;
  }//end while fonction
  free(arg);
}
void verif_et_recup_arg(int nb, char *arg[], int nb_wanted, char *chaine);

int main(int argc, char *argv[]) {
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
 
    if (file != NULL)
    {     
        display(table, nb_line,file); // Écriture du caractère A
        fclose(file);
    }
  
    printf("\nTout s'est bien passé ===> copié dans test.txt \n\n");
  /*==========================Fermeture du file=============================================*/
  
  if(fclose(file_2) == EOF) {
    printf("Probleme de fermeture du file %s", nom_file_2);
    exit(1);
  }
  printf(".............. Fermeture du file %s\n", nom_file_2);
/*==========================Libération mémoire=============================================*/
  for(int i=0; i<line; i++){
    free(table[i]);
  }
  free(table);
  return 0;
}

void verif_et_recup_arg(int nb, char *arg[], int nb_wanted, char *chaine)
{
  if(nb != nb_wanted){
    printf("Usage : line nom_file\n");
    exit(1);
  }

  strcpy(chaine, arg[1]);
}