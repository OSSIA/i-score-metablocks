#include <stdio.h>
#include <stdlib.h>
#include <assert.h> 
#include <string.h>
#include <stdbool.h>
#include "test_fun.h"


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
  fputs(ch, file);
  fputc(' ',file);
  fputs(tmp,file);
  fputc('\n',file);      
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
  fputs(ch, file);
  fputc(' ',file);
  fputs(tmp_1,file);
  fputc(' ',file);
  fputs(tmp_2,file);
  fputc('\n',file); 
  free(ch);        
}

void test_fun (char ** table, int * arg, int *nb, int i, int *test, int *item, int *push, FILE * file){
    //Si on rencontre un pushf, on l'enregistre dans la pile
    int chrono;
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

    if(!strcmp(table[i], "call chrono_create\n")){
      fputs("chrono_create\n",file);
      while(strcmp(table[i], "add\n")){
        i++;
      }
      if(!strcmp(table[i], "add\n")){
      chrono= variable(table,--i,5);
      } 
    }
    
    if(!strcmp(table[i], "call chrono_waitv\n")){
      call_1(table,i,chrono,file);
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

  
        else if(strcmp(table[i], "call chrono_waitv\n")){
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


void test_condition(char ** table, int * arg,int  *nb,int  *i, int * test, int *item, int *push, FILE * file){
  if(!strcmp(table[*i],"teste\n")){
    (*test)=arg[(*nb)-1];
    (*nb)--;
    (*push)--; 
    if(*test==*item){
      if_true(table, arg, &(*nb), &(*i), &(*test), &(*item), &(*push), file);
    }
    else{
      if_false(table, arg, &(*nb), &(*i), &(*test), &(*item), &(*push), file);
    }    
  }//fin teste

  if(!strcmp(table[*i],"testne\n")){
    (*test)=arg[(*nb)-1];
    (*nb)--;
    (*push)--; 
    if(*test!=*item){
      if_true(table, arg, &(*nb), &(*i), &(*test), &(*item), &(*push), file);
    }
    else{
      if_false(table, arg, &(*nb), &(*i), &(*test), &(*item), &(*push), file);
    }    
  }//fin testNe

  if(!strcmp(table[*i],"testl\n")){
    (*test)=arg[(*nb)-1];
    (*nb)--;
    (*push)--; 
    if(*test<*item){
      if_true(table, arg, &(*nb), &(*i), &(*test), &(*item), &(*push), file);
    }
    else{
      if_false(table, arg, &(*nb), &(*i), &(*test), &(*item), &(*push), file);
    }    
  }//fin testL

  if(!strcmp(table[*i],"testle\n")){
    (*test)=arg[(*nb)-1];
    (*nb)--;
    (*push)--; 
    if(*test<=*item){
      if_true(table, arg, &(*nb), &(*i), &(*test), &(*item), &(*push), file);
    }
    else{
      if_false(table, arg, &(*nb), &(*i), &(*test), &(*item), &(*push), file);
    }    
  }//fin testLE
  if(!strcmp(table[*i],"testg\n")){
    (*test)=arg[(*nb)-1];
    (*nb)--;
    (*push)--; 
    if(*test>*item){
      if_true(table, arg, &(*nb), &(*i), &(*test), &(*item), &(*push), file);
    }
    else{
      if_false(table, arg, &(*nb), &(*i), &(*test), &(*item), &(*push), file);
    }    
  }//fin testG
  if(!strcmp(table[*i],"testge\n")){
    (*test)=arg[(*nb)-1];
    (*nb)--;
    (*push)--; 
    if(*test>=*item){
      if_true(table, arg, &(*nb), &(*i), &(*test), &(*item), &(*push), file);
    }
    else{
      if_false(table, arg, &(*nb), &(*i), &(*test), &(*item), &(*push), file);
    }    
  }//fin testGE
}