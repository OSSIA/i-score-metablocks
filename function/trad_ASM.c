#include <stdio.h>
#include <stdlib.h>
#include <assert.h> 
#include <string.h>
#include <stdbool.h>
#include "trad.h"
#include "test_fun.h"

void display(char ** table, int nb_line, FILE *file){
  int * arg = calloc(1000,sizeof(int));
  int nb = 500;
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
      int cmp=arg[nb-1];
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
        test_condition(table, arg,&nb,&i, &test, &item, &push, file);
        i++;
        if(!strncmp(table[i], "jmp repeat_",11)){
          cmp--;
          i=begin;
        }    
      }//end while repeat

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

