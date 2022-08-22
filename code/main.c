#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"definitions.h"



int main(){
    struct table *st=NULL;

    AuxiliarAtributte auxiliar;
    auxiliar.ini = 0;
    auxiliar.prox = 0;
    auxiliar.positionSymbolTable = 0;
    auxiliar.currentColumn = 1;
    auxiliar.currentLine = 1;
    
    FILE* file = fopen("./tests/myprogram.txt", "r");

    if(file==NULL){
        printf("There was an error opening the file. Try again!\n");
        return 0;
    }
    
    char *buffer = (char*) malloc(sizeof(char)*4096);
    int current_state = INITIAL_STATE;

    fread(buffer, sizeof(char), 4096, file);

    //syntacticAnalyzer(buffer,  &auxiliar,  &st);
    
    while(1){
        Token tk = lexicalAnalyzer(buffer, &auxiliar, &st);
        if(strcmp(tk.name_tk, "$")==0){
            break;
        }
    }
    
    

    printSymbolTable(st);    
    free(buffer);
    fclose(file);

    return 0;
}