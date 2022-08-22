#include<stdio.h>
#include<stdlib.h>
#include <search.h>
#include<string.h>
#include "definitions.h"



// --- Declaration functions scope---
int syntacticAnalyzer(char *buffer, AuxiliarAtributte *auxiliar, struct table **st);
void ProductionS(char *buffer, AuxiliarAtributte *auxiliar, struct table **st, FILE *fp, int *identation);
void ProductionBlock(char *buffer, AuxiliarAtributte *auxiliar, struct table **st, FILE *fp, int *identation, Token *tk);
void ProductionCommandSequence(char *buffer, AuxiliarAtributte *auxiliar, struct table **st, FILE *fp, int *identation, Token *tk);
void ProductionCommand(char *buffer, AuxiliarAtributte *auxiliar, struct table **st, FILE *fp, int *identation, Token *tk);
void ProductionLoop(char *buffer, AuxiliarAtributte *auxiliar, struct table **st, FILE *fp, int *identation, Token *tk);
void ProductionAssign(char *buffer, AuxiliarAtributte *auxiliar, struct table **st, FILE *fp, int *identation, Token *tk);
void ProductionSelection(char *buffer, AuxiliarAtributte *auxiliar, struct table **st, FILE *fp, int *identation, Token *tk);
void ProductionCondition(char *buffer, AuxiliarAtributte *auxiliar, struct table **st, FILE *fp, int *identation, Token *tk);
void ProductionVariableDeclaration(char *buffer, AuxiliarAtributte *auxiliar, struct table **st, FILE *fp, int *identation, Token *tk);
void ProductionIdList(char *buffer, AuxiliarAtributte *auxiliar, struct table **st, FILE *fp, int *identation, Token *tk);
void ProductionIdListPartial(char *buffer, AuxiliarAtributte *auxiliar, struct table **st, FILE *fp, int *identation, Token *tk);
void buildTree(FILE *fp, int *identation, char *tk_name);
Token getToken(char *buffer, AuxiliarAtributte *auxiliar, struct table **st);
void ProductionSelectionLine(char *buffer, AuxiliarAtributte *auxiliar, struct table **st, FILE *fp, int *identation, Token *tk);
void ProductionExp1(char *buffer, AuxiliarAtributte *auxiliar, struct table **st, FILE *fp, int *identation, Token *tk);
void ProductionExp1Line(char *buffer, AuxiliarAtributte *auxiliar, struct table **st, FILE *fp, int *identation, Token *tk);
void ProductionExp2(char *buffer, AuxiliarAtributte *auxiliar, struct table **st, FILE *fp, int *identation, Token *tk);





Token getToken(char *buffer, AuxiliarAtributte *auxiliar, struct table **st){ 
        Token tk = lexicalAnalyzer(buffer, auxiliar, st);
        return tk;
}


void buildTree(FILE *fp, int *identation, char *tk_name){
    for(int i=0; i<*identation; i++){
        fprintf(fp, "%s", "\t");
    }

    fprintf(fp, "%s", tk_name);
    fprintf(fp, "%s", "\n");
}


void ProductionConstant(char *buffer, AuxiliarAtributte *auxliar, struct table **st, FILE *fp, int *identation, Token *tk){
    buildTree(fp, identation, (char*)"CONSTANT");
    if(strcmp(tk->name_tk, "INT")==0 || strcmp(tk->name_tk, "FLOAT")==0 || strcmp(tk->name_tk, "EXPONENTIAL")==0){
        (*identation)++;
        buildTree(fp, identation, tk->name_tk);
        (*identation)--;
    }else {
        printf("error\n");
    }
}

void ProductionTerm(char *buffer, AuxiliarAtributte *auxiliar, struct table **st, FILE *fp, int *identation, Token *tk){
    buildTree(fp, identation, (char*)"TERM");
    //printf("o que chega em term %s", tk->name_tk);
    if(strcmp(tk->name_tk, "OPEN_PARENTHESES")==0){
        (*identation)++;
        buildTree(fp, identation, tk->name_tk);
        *tk = getToken(buffer, auxiliar, st);
        ProductionExp1(buffer, auxiliar, st, fp, identation, tk);
        *tk = getToken(buffer, auxiliar, st);
        if(strcmp(tk->name_tk, "CLOSE_PARENTHESES")==0){
            buildTree(fp, identation, tk->name_tk);
        }
        else{
            printf("error. expected close parentheses\n");
        }
        (*identation)--;
    }
    else if(strcmp(tk->name_tk, "IDENTIFIER")==0){
        (*identation)++;
        buildTree(fp, identation, tk->name_tk);
        (*identation)--;
    }
    else{
        (*identation)++;
        ProductionConstant(buffer, auxiliar, st, fp, identation, tk);
        (*identation)--;
    }
}

void ProductionExp3Line(char *buffer, AuxiliarAtributte *auxiliar, struct table **st, FILE *fp, int *identation, Token *tk){
    buildTree(fp, identation, (char*)"EXP3'");
    if(strcmp(tk->name_tk, "ARITHEMETIC_OP")==0 && strcmp(tk->attr, "^")==0){
        (*identation)++;
        buildTree(fp, identation, tk->name_tk);
        while(strcmp(tk->name_tk, "OPEN_PARENTHESES")==0 || strcmp(tk->name_tk, "IDENTIFIER")==0 || strcmp(tk->name_tk, "INT")==0 || strcmp(tk->name_tk, "CHARACTER")==0 ){
            buildTree(fp, identation, tk->name_tk);
            ProductionTerm(buffer, auxiliar, st, fp, identation, tk);
            *tk = getToken(buffer, auxiliar, st);
        }
        (*identation)--;
    }
    else{
        (*identation)++;
        buildTree(fp, identation, (char*)"ε");
        (*identation)--;
    }
}


void ProductionExp3(char *buffer, AuxiliarAtributte *auxiliar, struct table **st, FILE *fp, int *identation, Token *tk){
    buildTree(fp, identation, (char*) "EXP3");
    (*identation)++;
    ProductionTerm(buffer, auxiliar, st, fp, identation, tk);
    ProductionExp3Line(buffer, auxiliar, st, fp, identation, tk);
    (*identation)--;
}

void ProductionExp2Line(char *buffer, AuxiliarAtributte *auxiliar, struct table **st, FILE *fp, int *identation, Token *tk){
    buildTree(fp, identation, (char*)"EXP2'");
    *tk = getToken(buffer, auxiliar, st);
    //printf("aqui chego lendo %s\n", tk->name_tk);
    if(strcmp(tk->name_tk, "ARITHEMETIC_OP")==0 && strcmp(tk->attr, "*")==0){
        (*identation)++;
        buildTree(fp, identation, tk->name_tk);
        *tk = getToken(buffer, auxiliar, st);
        while(strcmp(tk->name_tk, "OPEN_PARENTHESES")==0 || strcmp(tk->name_tk, "IDENTIFIER")==0 || strcmp(tk->name_tk, "INT")==0 || strcmp(tk->name_tk, "CHARACTER")==0){
            ProductionExp3(buffer, auxiliar, st, fp, identation, tk);
        }
        (*identation)--;

    }
    else if(strcmp(tk->name_tk, "ARITHEMETIC_OP")==0 && strcmp(tk->attr, "/")==0){
        (*identation)++;
        buildTree(fp, identation, tk->name_tk);
        *tk = getToken(buffer, auxiliar, st);
        while(strcmp(tk->name_tk, "OPEN_PARENTHESES")==0 || strcmp(tk->name_tk, "IDENTIFIER")==0 || strcmp(tk->name_tk, "INT")==0 || strcmp(tk->name_tk, "CHARACTER")==0){
            ProductionExp3(buffer, auxiliar, st, fp,identation, tk);
        }
        (*identation)--;
    }
    else{
        (*identation)++;
        buildTree(fp, identation, (char*)"ε");
        (*identation)--;
    }
}

void ProductionExp2(char *buffer, AuxiliarAtributte *auxiliar, struct table **st, FILE *fp, int *identation, Token *tk){
    buildTree(fp, identation, (char*)"EXP2");
    (*identation)++;
    ProductionExp3(buffer, auxiliar, st, fp, identation, tk);
    ProductionExp2Line(buffer, auxiliar, st, fp, identation, tk);
    (*identation)--;
}

void ProductionExp1Line(char *buffer, AuxiliarAtributte *auxiliar, struct table **st, FILE *fp, int *identation, Token *tk){
    buildTree(fp, identation, (char*)"EXP1'");
    if(strcmp(tk->name_tk, "ARITHEMETIC_OP")==0 && strcmp(tk->attr, "+")==0){
        (*identation)++;
        buildTree(fp, identation, tk->name_tk);
        (*identation)--;
        *tk = getToken(buffer, auxiliar, st);
        while(strcmp(tk->name_tk, "OPEN_PARENTHESES")==0 || strcmp(tk->name_tk, "IDENTIFIER")==0 || strcmp(tk->name_tk, "INT")==0 || strcmp(tk->name_tk, "CHARACTER")==0){
            ProductionExp2(buffer, auxiliar, st, fp, identation, tk);
        }
        (*identation)--;

    }
    else if(strcmp(tk->name_tk, "ARITHEMETIC_OP")==0 && strcmp(tk->attr, "-")==0){
        (*identation)++;
        buildTree(fp, identation, tk->name_tk);
        *tk = getToken(buffer, auxiliar, st);
        while(strcmp(tk->name_tk, "OPEN_PARENTHESES")==0 || strcmp(tk->name_tk, "IDENTIFIER")==0 || strcmp(tk->name_tk, "INT")==0 || strcmp(tk->name_tk, "CHARACTER")==0){
            //*tk = getToken(buffer, auxiliar, st);
            ProductionExp2(buffer, auxiliar, st, fp,identation, tk);
        }
        (*identation)--;
    }
    else{
        (*identation)++;
        buildTree(fp, identation, (char*)"ε");
        (*identation)--;
    }
}


void ProductionExp1(char *buffer, AuxiliarAtributte *auxiliar, struct table **st, FILE *fp, int *identation, Token *tk){
    buildTree(fp, identation, (char*)"EXP1");
    (*identation)++;
    ProductionExp2(buffer, auxiliar, st, fp, identation, tk);
    ProductionExp1Line(buffer, auxiliar, st, fp, identation, tk);
    (*identation)--;
}


void ProductionIdListPartial(char *buffer, AuxiliarAtributte *auxiliar, struct table **st, FILE *fp, int *identation, Token *tk){
    *tk = getToken(buffer, auxiliar, st);
    buildTree(fp,  identation, (char*)"ID_LIST_PARTIAL");
    (*identation)++;
    if(strcmp(tk->name_tk, "COMMA")==0){
        buildTree(fp,  identation, tk->name_tk);
        ProductionIdList(buffer, auxiliar, st, fp, identation, tk);
        (*identation)--;
        return;
    }else{
        buildTree(fp,  identation, (char*)"ε");
        (*identation)--;
    }
    return;
}

void ProductionIdList(char *buffer, AuxiliarAtributte *auxiliar, struct table **st, FILE *fp, int *identation, Token *tk){
    *tk= getToken(buffer, auxiliar, st);
    buildTree(fp, identation, (char*)"ID_LIST");   
    if(strcmp(tk->name_tk, "IDENTIFIER")==0){
        (*identation)++;
        buildTree(fp, identation, tk->name_tk);
        ProductionIdListPartial(buffer, auxiliar, st, fp, identation, tk);
        (*identation)--;
        return;
    }
    else{
        printf("Error in line %d and column %d. Was expected token \"IDENTIFIER\"\n", auxiliar->currentLine, auxiliar->currentColumn);
    }
    return;

}

void ProductionVariableDeclaration(char *buffer, AuxiliarAtributte *auxiliar, struct table **st, FILE *fp, int *identation, Token *tk){
    *tk = getToken(buffer, auxiliar, st);
    buildTree(fp, identation, (char*)"VARIABLE_DECLARATION");
    (*identation)++;
    while(strcmp(tk->name_tk, "TYPE")==0){
        buildTree(fp, identation, tk->name_tk);
        *tk = getToken(buffer, auxiliar, st);
        if(strcmp(tk->name_tk, "TWO_POINTS")==0){
            buildTree(fp, identation, tk->name_tk);
            ProductionIdList(buffer, auxiliar, st, fp, identation, tk);
            if(strcmp(tk->name_tk, "SEMICOLON")==0){
                buildTree(fp, identation, tk->name_tk);
                
                *tk = getToken(buffer, auxiliar, st);
            }
            else{
                printf("Error in line %d and column %d. Was expected token \"SEMICOLON\"\n", auxiliar->currentLine, auxiliar->currentColumn);
                return;
            }
        }
        else{
            printf("Error in line %d and column %d. Was expected token \"TWO_POINTS\"\n", auxiliar->currentLine, auxiliar->currentColumn);
        }
    }
    (*identation)--;
    return;
}

void ProductionCondition(char *buffer, AuxiliarAtributte *auxiliar, struct table **st, FILE *fp, int *identation, Token *tk){
    buildTree(fp, identation, (char*)"CONDITION");
    (*identation)++;
    *tk = getToken(buffer, auxiliar, st);
    ProductionExp1(buffer, auxiliar, st, fp, identation, tk);
    (*identation)--;
    if(strcmp(tk->name_tk, "RELOP")==0){
        (*identation)++;
        buildTree(fp, identation, tk->name_tk);
        *tk = getToken(buffer, auxiliar, st);
        ProductionExp1(buffer, auxiliar, st, fp, identation, tk);
        //printf("o que passa aqui %s\n", tk->name_tk);
        (*identation)--;
    }
}

void ProductionSelectionLine(char *buffer, AuxiliarAtributte *auxiliar, struct table **st, FILE *fp, int *identation, Token *tk){
    if(strcmp(tk->name_tk, "ELSE")==0){
        (*identation)++;
        buildTree(fp, identation, tk->name_tk);
        *tk = getToken(buffer, auxiliar, st);
        (*identation)++;
        ProductionBlock(buffer, auxiliar, st, fp, identation, tk);
        (*identation)--;
        (*identation)--;
    }
    else{
        return;
    }
}

void ProductionSelection(char *buffer, AuxiliarAtributte *auxiliar, struct table **st, FILE *fp, int *identation, Token *tk){
    *tk = getToken(buffer, auxiliar, st);
    if(strcmp(tk->name_tk, "OPEN_PARENTHESES")==0){
        buildTree(fp, identation, tk->name_tk);
        ProductionCondition(buffer, auxiliar, st, fp, identation, tk);
        if(strcmp(tk->name_tk, "CLOSE_PARENTHESES")==0){
            buildTree(fp, identation, tk->name_tk);
            *tk = getToken(buffer, auxiliar, st);
            if(strcmp(tk->name_tk, "THEN")==0){
                buildTree(fp, identation, tk->name_tk);
                *tk = getToken(buffer, auxiliar, st);
                ProductionBlock(buffer, auxiliar, st, fp, identation, tk);
                ProductionSelectionLine(buffer, auxiliar, st, fp, identation, tk);
            }
        }
    }
}

void ProductionAssign(char *buffer, AuxiliarAtributte *auxiliar, struct table **st, FILE *fp, int *identation, Token *tk){
    *tk = getToken(buffer, auxiliar, st);
    if(strcmp(tk->name_tk, "ASSIGN")==0){
        buildTree(fp, identation, tk->name_tk);
        *tk = getToken(buffer, auxiliar, st);
        ProductionExp1(buffer, auxiliar, st, fp, identation, tk);
        if(strcmp(tk->name_tk, "SEMICOLON")==0){
            buildTree(fp, identation, tk->name_tk);
            return;
        }
        else{
            printf("Error in line %d and column %d. Was expected token \"SEMICOLON\"\n", auxiliar->currentLine, auxiliar->currentColumn);
            return;
        }
    }

}

void ProductionLoop(char *buffer, AuxiliarAtributte *auxiliar, struct table **st, FILE *fp, int *identation, Token *tk){
    //printf("valor no repeat %s\n", tk->name_tk);
    if(strcmp(tk->name_tk, "WHILE")==0){
        buildTree(fp, identation, tk->name_tk);
        *tk = getToken(buffer, auxiliar, st);
        if(strcmp(tk->name_tk, "OPEN_PARENTHESES")==0){
            ProductionCondition(buffer, auxiliar, st, fp, identation, tk);
            //*tk = getToken(buffer, auxiliar, st);
            if(strcmp(tk->name_tk, "CLOSE_PARENTHESES")==0){
                buildTree(fp, identation, tk->name_tk);
                *tk = getToken(buffer, auxiliar, st);
                //printf("entao aqui e end %s\n", tk->name_tk);
                
                if(strcmp(tk->name_tk, "DO")==0){
                    buildTree(fp, identation, tk->name_tk);
                    //buildTree(fp, identation, (char*)"BLOCK");
                    *tk = getToken(buffer, auxiliar, st);
                    ProductionBlock(buffer, auxiliar, st, fp, identation, tk);
                }
                else{
                    printf("Error in line %d and column %d. Was expected token \"DO\" \n", auxiliar->currentLine, auxiliar->currentColumn);
                    return;
                }
            }
            else{
                printf("Error in line %d and column %d. Was expected token \"CLOSE_PARENTHESES\"\n", auxiliar->currentLine, auxiliar->currentColumn);
            }
        }
        else{
            printf("Error in line %d and column %d. Was expected token \"OPEN_PARENTHSES\"\n", auxiliar->currentLine, auxiliar->currentColumn);
        }
        //*tk=getToken(buffer, auxiliar, st);
    }
    else if(strcmp(tk->name_tk, "REPEAT")==0){
        buildTree(fp, identation, tk->name_tk);
        *tk =getToken(buffer, auxiliar, st);
        ProductionBlock(buffer, auxiliar, st, fp, identation, tk);   
        if(strcmp(tk->name_tk, "WHILE")==0){
            (*identation)++;
            buildTree(fp, identation, tk->name_tk);
            *tk = getToken(buffer, auxiliar, st);
            if(strcmp(tk->name_tk, "OPEN_PARENTHESES")==0){
                buildTree(fp, identation, tk->name_tk);
                ProductionCondition(buffer, auxiliar, st, fp, identation, tk);
                //*tk = getToken(buffer, auxiliar, st);
                //printf("o que cai aqui %s\n", tk->name_tk);
                if(strcmp(tk->name_tk, "CLOSE_PARENTHESES")==0){
                    buildTree(fp, identation, tk->name_tk);
                    *tk = getToken(buffer, auxiliar, st);
                    return;
                }
                else{
                    printf("Error in line %d and column %d. Was expected token \"CLOSE_PARENTHSES\"\n", auxiliar->currentLine, auxiliar->currentColumn);
                }
            }
            else{
                printf("Error in line %d and column %d. Was expected token \"OPEN_PARENTHSES\"\n", auxiliar->currentLine, auxiliar->currentColumn);
            }
            (*identation)--;
        }
        else{
            printf("Error in line %d and column %d. Was expected token \"WHILE\"\n", auxiliar->currentLine, auxiliar->currentColumn);
        }

    }
    else{
        printf("Error in line %d and column %d. Was expected tokens \"REPEAT\" or \"WHILE\"\n", auxiliar->currentLine, auxiliar->currentColumn);
    }
}

void ProductionCommand(char *buffer, AuxiliarAtributte *auxiliar, struct table **st, FILE *fp, int *identation, Token *tk){

    if(strcmp(tk->name_tk,"IF" )== 0){
        (*identation)++;
        buildTree(fp, identation, (char*)"SELECTION");
        (*identation)++;   
        buildTree(fp, identation, tk->name_tk);
        ProductionSelection(buffer, auxiliar, st, fp, identation, tk);
        (*identation)--;
    }
    else if(strcmp(tk->name_tk, "WHILE")==0 || strcmp(tk->name_tk, "REPEAT")==0){
        (*identation)++;
        buildTree(fp, identation, (char*)"LOOP");
        (*identation)++;
        ProductionLoop(buffer, auxiliar, st, fp, identation, tk);
        (*identation)--;
        //printf("valor que sai da loop function %s\n", tk->name_tk);
        //*tk = getToken(buffer, auxiliar, st);
    }
    else if(strcmp(tk->name_tk, "IDENTIFIER")==0){
        (*identation)++;
        buildTree(fp, identation, (char*)"ASSIGNMENT");
        (*identation)++;
        buildTree(fp, identation, tk->name_tk);
        ProductionAssign(buffer, auxiliar, st, fp, identation, tk);
        (*identation)--;
        *tk = getToken(buffer, auxiliar, st);
    }
    else{
        printf("Error in line %d and column %d. Was expected tokens \"IF\" or \"WHILE\" or \"IDENTIFIER\"\n", auxiliar->currentLine, auxiliar->currentColumn);
    }
    (*identation)--;
}

void ProductionCommandSequence(char *buffer, AuxiliarAtributte *auxiliar, struct table **st, FILE *fp, int *identation, Token *tk){
    buildTree(fp, identation, (char*)"COMMAND_SEQUENCE");
    while(strcmp(tk->name_tk, "IF")==0 || strcmp(tk->name_tk, "WHILE")==0 || strcmp(tk->name_tk, "REPEAT")==0 || strcmp(tk->name_tk, "IDENTIFIER")==0){
        ProductionCommand(buffer, auxiliar, st, fp, identation, tk);
    }
}

void ProductionBlock(char *buffer, AuxiliarAtributte *auxiliar, struct table **st, FILE *fp, int *identation, Token *tk){  
    
    if(strcmp(tk->name_tk, "BEGIN")==0){
        buildTree(fp, identation, tk->name_tk);
        ProductionVariableDeclaration(buffer, auxiliar, st, fp, identation, tk);
        //printf("o valor que chega aqui e %s\n", tk->name_tk);
        ProductionCommandSequence(buffer, auxiliar, st, fp, identation, tk);
        //printf("o valor que chega aqui e %s\n", tk->name_tk);
        if(strcmp(tk->name_tk, "END")==0){
            (*identation)++;
            buildTree(fp, identation, tk->name_tk);
            (*identation)--;
            *tk = getToken(buffer, auxiliar, st);
        }else{
            printf("Error in line %d and column %d. Was expected token \"END\"\n", auxiliar->currentLine, auxiliar->currentColumn);    
        }
    }
    else{
        printf("%s\n", tk->name_tk);
        printf("Error in line %d and column %d. Was expected token \"BEGIN\"\n", auxiliar->currentLine, auxiliar->currentColumn);
        return;
    }
}

void ProductionS(char *buffer, AuxiliarAtributte *auxiliar, struct table **st, FILE *fp, int *identation){
    Token tk = getToken(buffer, auxiliar, st);   
    if(strcmp(tk.name_tk, "PROGRAMA")==0){
        buildTree(fp, identation, tk.name_tk);
        tk = getToken(buffer, auxiliar, st);
        if(strcmp(tk.name_tk, "IDENTIFIER")==0){
            buildTree(fp, identation, tk.name_tk);
            tk = getToken(buffer, auxiliar, st);
            buildTree(fp, identation, (char*)"BLOCK"); 
            (*identation)++;
            ProductionBlock(buffer, auxiliar, st, fp, identation, &tk);
            (*identation)--;
        }
        else{
            printf("Error in line %d and column %d. Was expected token \"IDENTIFIER\"\n", auxiliar->currentLine, auxiliar->currentColumn);
        }
    }
    else{
        printf("Error in line %d and column %d. Was expected token \"PROGRAMA\"\n", auxiliar->currentLine, auxiliar->currentColumn);
    }
   
}

int syntacticAnalyzer(char *buffer, AuxiliarAtributte *auxiliar, struct table **st){
    
    FILE *fp = fopen("./tests/syntacticTree.txt", "w");
    int identation=0;

    if(fp==NULL){
        printf("Error in create syntactic tree. Please again\n");
        return 0;
    }
    fprintf(fp, "%s", "S\n");
    identation++;
    ProductionS(buffer, auxiliar, st, fp, &identation);
    identation--;
    
    fclose(fp);
    return 0;  
}