#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"definitions.h"


int addLast(struct table **st, char* name_tk, char* lexeme, int position){
    struct table *node = (struct table*) malloc(sizeof(struct table));
    node->name_tk = (char*) malloc(sizeof(name_tk));
    node->name_tk = name_tk;
    node->lexeme = (char*) malloc(sizeof(lexeme));
    node->lexeme = lexeme;
    node->position = position;
    node->prox = NULL;

    if(*st==NULL){
        *st = node;
        return 1;
    }
    else{
        struct table *lastNode = *st;
        while(lastNode->prox!=NULL){
            lastNode = lastNode->prox;
        }
        lastNode->prox = node;
        return 1;
    }
    return 0;
    

}

void printSymbolTable(struct table *st){
    struct table *tmp = st;
    
    printf("------------------Symbol table----------------\n");
    printf(" Position |\tToken name |\tLexeme\n");
    
    while(tmp != NULL){
        printf("%d\t\t%s\t\t%s\n", tmp->position, tmp->name_tk, tmp->lexeme);
        tmp = tmp->prox;
    }
    
}

int exists(struct table *st, char *lexeme){
    struct table *tmp = st;
    while(tmp!= NULL){
        if(strcmp(tmp->lexeme, lexeme)==0) return 1;
        tmp = tmp->prox;
    }
    return 0;
}

int getPosition(struct table *st, char *lexeme){
    struct table *tmp = st;
    while(tmp!=NULL){
        if(strcmp(tmp->lexeme, lexeme)==0){
            return tmp->position;
        }
        tmp=tmp->prox;
    }
    return -1;    
}
