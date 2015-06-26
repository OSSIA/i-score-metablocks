#ifndef _TEST_FUN_H_
#define _TEST_FUN_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h> 
#include <string.h>

int variable(char ** table, int i, int j);

void call_1(char ** table, int i, int arg, FILE * file);

void call_2(char ** table, int i, int arg_1, int arg_2, FILE * file);

void test_fun (char ** table, int * arg, int *nb, int i, int *test, int *item, int *push, FILE * file);

void if_true(char ** table, int * arg, int *nb, int *i, int *test, int *item, int *push, FILE * file);

void if_false(char ** table, int * arg, int *nb, int *i, int *test, int *item, int *push, FILE * file);

void test_condition(char ** table, int * arg,int  *nb,int  *i, int * test, int *item, int *push, FILE * file);

#endif