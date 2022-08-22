#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"definitions.h"


int nextchar(char *buffer, int prox, char *c){

    if(buffer[prox]!='\0'){
        *c= buffer[prox];
        return 1;
    }
    else return 0;
}


char* getLexeme(char *buffer, int ini, int prox){
    char *lexeme = (char*) malloc(sizeof(((prox)-(ini))+1));
    for(int i=ini; i<prox; i++){
        strncat(lexeme, &buffer[i], 1);
    }
    return lexeme;
} 


Token lexicalAnalyzer(char *buffer, AuxiliarAtributte *auxiliar, struct table **st){
    int current_state = INITIAL_STATE;
    char c;
    Token tk;
    int aux;
    int tmp;

    while(1){
        
        if(nextchar(buffer, auxiliar->prox, &c)==0){
            tk.name_tk=(char*)"$";
            tk.attr = (char*)"";
            return tk;
        }
        //printf("current state %d and letter read %c\n", current_state, c);
        switch (current_state){
            
            case INITIAL_STATE:
                
                if(c=='p'){
                    current_state = S19;
                    auxiliar->prox++;
                }
                
                else if(c=='\n' || c=='\t' || c==' '){
                    //printf("cai aqui\n");
                    current_state = S108;               
                }
                else if(c=='['){
                    current_state = S64S111;
                    auxiliar->prox++;
                }
                else if(c==';'){
                    current_state = S59;
                }
                else if(c=='('){
                    current_state = S58;
                }
                else if(c==')'){
                    current_state = S57;
                }
                else if(c=='f'){
                    current_state = S45;
                    auxiliar->prox++;
                }
                else if(c=='t'){
                    current_state = S114;
                    auxiliar->prox++;
                }
                else if(c=='e'){
                    current_state = S29S96;
                    auxiliar->prox++;
                }
                else if(c=='d'){
                    current_state = S85;
                    auxiliar->prox++;
                }
                else if(c=='i'){
                    current_state = S41S120;
                    auxiliar->prox++;
                }
                else if(c=='r'){
                    current_state = S77;
                    auxiliar->prox++;
                }
                else if(c=='\''){
                    current_state = S15;
                    auxiliar->prox++;
                }
                else if(c=='b'){
                    current_state = S34;
                    auxiliar->prox++;
                }
                else if(c=='w'){
                    current_state = S89;
                    auxiliar->prox++;
                }
                else if(c=='c'){
                    current_state = S51;
                    auxiliar->prox++;
                }

                else if(c=='='){
                    current_state = S10;;
                }

                else if(isdigit(c)>0){
                    current_state = S67;
                    auxiliar->prox++;
                }

                else if(c==':'){
                    current_state = S60;
                    auxiliar->prox++;
                }
                else if(c==','){
                    current_state = S63;;
                }

                else if(c=='~'){
                    current_state = S8;
                    auxiliar->prox++;
                }
                else if(c=='+'){
                    current_state = S103;
                }
                else if(c=='-'){
                    current_state = S104;
                }
                else if(c=='/'){
                    current_state = S105;
                }
                else if(c=='*'){
                    current_state = S106;
                }
                else if(c=='^'){
                    current_state = S102;
                }
                
                else if(isalpha(c)!=0 || c=='_'){
                    current_state = S2;
                    auxiliar->prox++;
                }

                else if(c=='<'){
                    current_state = S5;
                    auxiliar->prox++;
 
                }
                
                else if(c=='>'){
                    current_state = S11;
                    auxiliar->prox++;

                }
                else{
                    printf("token not recognized -> %c in position %dl %dc \n", c,  auxiliar->currentLine, auxiliar->currentColumn);
                    tk.name_tk = (char*)"$";
                    tk.attr = (char*)"";


                    return tk;       
                }
                auxiliar->currentColumn++;
                
            break;

            case S19:
                if(c=='r'){
                    current_state = S20;
                }
                else{
                    current_state = S2;
                }
                auxiliar->prox++;
                auxiliar->currentColumn++;
            break;

            case S20:
                if(c=='o'){
                    current_state = S21;

                }
                else{
                    current_state = S2;
                    
                }
                auxiliar->prox++;
                auxiliar->currentColumn++;

            break;
            case S21:
                if(c=='g'){
                    current_state = S22;
                }
                else{
                    current_state = S2;                  
                }
                auxiliar->prox++;
                auxiliar->currentColumn++;

            break;

            case S22:
                if(c=='r'){
                    current_state = S23;
                }
                else{
                    current_state = S2;

                }
                auxiliar->prox++;
                auxiliar->currentColumn++;
            break;

            case S23:
                if(c=='a'){
                    current_state = S24;
                }
                else{
                    current_state = S2;
                }
                auxiliar->prox++;
                auxiliar->currentColumn++;
            break;

            case S24:
                if(c=='m'){
                    current_state = S25;
                }
                else{
                    current_state = S2;
                }
                auxiliar->prox++;
                auxiliar->currentColumn++;

            break;

            case S25:
                    if(c=='a'){
                    current_state = S26;       
                }
                else{
                    current_state = S2;    
                    
                }
                auxiliar->prox++;
                auxiliar->currentColumn++;
            break;

            case S26: //Look ahead 
                if(isalnum(c)==0 || c!='_' || c=='\0'){ 
                    current_state = S27;
                }
                else{
                    current_state = S2;
                    auxiliar->prox++;
                }
                
            break;

            case S27://Final state*
                tk.name_tk = (char*)"PROGRAMA";
                tk.attr= (char*) "none";
                current_state = INITIAL_STATE;
                printf("Token found in position: %dl %dc  -> <%s,%s>\n", auxiliar->currentLine, auxiliar->currentColumn, tk.name_tk, tk.attr);
                //(*prox)++; Apaguei agora
                auxiliar->ini=auxiliar->prox;
                return tk;
            
            break;

            
            case S108:
                if(c=='\n'){
                    auxiliar->currentLine++;
                    auxiliar->currentColumn=1;
                }
                
                current_state = INITIAL_STATE;
                auxiliar->prox++;
                auxiliar->ini = auxiliar->prox;
            break;

            case S15:
                if(isalpha(c)!=0){
                    current_state = S16;
                }
                auxiliar->prox++;
                auxiliar->currentColumn++;
            break;
            
            case S16:
                if(c=='\''){
                current_state = S17;
                }
                auxiliar->currentColumn++;
            break;

            case S17: //Final state
                tk.name_tk = (char*)"CHARACTER";
                current_state = INITIAL_STATE;
                tk.attr= getLexeme(buffer, auxiliar->ini, auxiliar->prox);
                printf("Token found in position: %dl %dc  -> <%s,%s>\n", auxiliar->currentLine, auxiliar->currentColumn, tk.name_tk, tk.attr);
                auxiliar->prox++;
                auxiliar->ini = auxiliar->prox;
                return tk;
            break;
            
            case S34:
                if(c=='e'){
                    current_state = S35;
                    auxiliar->prox++;
                }else{
                    current_state  = S2;
                }
                
                auxiliar->currentColumn++;
            break;

            case S35:
                if(c=='g'){
                    current_state = S36;
                }
                else{
                    current_state = S2;
                }
                auxiliar->prox++;
                auxiliar->currentColumn++;
            break;

            case S36:
                if(c=='i'){
                    current_state = S37;
                }
                else{
                    current_state = S2;
                }
                auxiliar->prox++;
                auxiliar->currentColumn++;
            break;

            case S37:
                if(c=='n'){
                    current_state = S38;
                }
                else{
                    current_state = S2;
                }
                auxiliar->prox++;
                auxiliar->currentColumn++;
            break;

            case S38: //Look ahead
                
                if(isalpha(c)== 0 || isalnum(c)==0 || c!='_'){ //Look ahead
                    current_state = S39;
                }
                else{
                    current_state = S2;
                }
            break;

            case S39: //Final state
                tk.name_tk = (char*)"BEGIN";
                tk.attr =  (char*)"none";
                current_state = INITIAL_STATE;
                printf("Token found in position: %dl %dc  -> <%s,%s>\n", auxiliar->currentLine, auxiliar->currentColumn, tk.name_tk, tk.attr);
                //(*prox)++;
                auxiliar->ini=auxiliar->prox;
                return tk;
            
            break;

            case S10: // Final state
                tk.name_tk = (char*)"RELOP";
                tk.attr = (char*) "EQ";
                current_state = INITIAL_STATE;
                printf("Token found in position: %dl %dc  -> <%s,%s>\n", auxiliar->currentLine, auxiliar->currentColumn, tk.name_tk, tk.attr);
                auxiliar->prox++;
                auxiliar->ini=auxiliar->prox;
                return tk;
            break;

            case S8:
                if(c=='='){
                    current_state = S9;
                }
                auxiliar->currentColumn++;
            break;

            case S9:  //Final state token: ~=
                if(c=='='){
                    tk.name_tk = (char*)"RELOP";
                    tk.attr = (char*) "NE";
                    current_state = INITIAL_STATE;
                    printf("Token found in position: %dl %dc  -> <%s,%s>\n", auxiliar->currentLine, auxiliar->currentColumn, tk.name_tk, tk.attr);
                    auxiliar->prox++;
                    auxiliar->ini=auxiliar->prox;
                }
                auxiliar->currentColumn++;
                return tk;
            break;

            case S11: //Look ahead
        
                if(c=='='){
                    current_state = S12;
                }
                else{
                    current_state = S13;
                }
            break;

            case S12://Final state
                tk.name_tk = (char*)"RELOP";
                tk.attr = (char*) "GE";
                current_state=INITIAL_STATE;
                printf("Token found in position: %dl %dc  -> <%s,%s>\n", auxiliar->currentLine, auxiliar->currentColumn, tk.name_tk, tk.attr);
                //(*prox)++;
                auxiliar->ini=auxiliar->prox;
                return tk;
            break;

            case S13://Final state
                tk.name_tk = (char*)"RELOP";
                tk.attr = (char*) "GT";
                current_state=INITIAL_STATE;
                printf("Token found in position: %dl %dc  -> <%s,%s>\n", auxiliar->currentLine, auxiliar->currentColumn, tk.name_tk, tk.attr);
                //(*prox)++;
                auxiliar->ini=auxiliar->prox;
                return tk;
            break;

            case S5:

                if(c=='='){
                    current_state= S6;
                }else{
                    current_state = S7;
                }
                auxiliar->currentColumn++;

            break;

            case S6://Final state
                tk.name_tk = (char*)"RELOP";
                tk.attr = (char*) "LE";
                current_state=INITIAL_STATE;
                printf("Token found in position: %dl %dc  -> <%s,%s>\n", auxiliar->currentLine, auxiliar->currentColumn, tk.name_tk, tk.attr);
                auxiliar->prox++;
                auxiliar->ini=auxiliar->prox;
                return tk;
            break;
            
            case S7://Final state
                tk.name_tk = (char*)"RELOP";
                tk.attr = (char*) "LT";
                current_state=INITIAL_STATE;
                printf("Token found in position: %dl %dc  -> <%s,%s>\n", auxiliar->currentLine, auxiliar->currentColumn, tk.name_tk, tk.attr);
                //(*prox)++;
                auxiliar->ini=auxiliar->prox;
                return tk;
            break;
            
            case S60: //Look ahead
                
                if(c=='='){
                    current_state = S62;
                }
                else{
                    current_state = S61;
                    //(*prox)--;
                }
            break;

            case S62: //Final state
                tk.name_tk = (char*)"ASSIGN";
                tk.attr = (char*) "none";
                current_state=INITIAL_STATE;
                printf("Token found in position: %dl %dc  -> <%s,%s>\n", auxiliar->currentLine, auxiliar->currentColumn, tk.name_tk, tk.attr);
                auxiliar->prox++;
                auxiliar->ini=auxiliar->prox;
                return tk;
            break;

            case S61: //Final state
                tk.name_tk = (char*)"TWO_POINTS";
                tk.attr = (char*)"none";
                current_state=INITIAL_STATE;
                printf("Token found in position: %dl %dc  -> <%s,%s>\n", auxiliar->currentLine, auxiliar->currentColumn, tk.name_tk, tk.attr);
                //(*prox)++;
                auxiliar->ini=auxiliar->prox;
                return tk;
            break;

            case S67:
                if(isdigit(c)>0){
                    current_state = S67;
                    auxiliar->prox++;
                }
                else if(c=='.'){
                    current_state = S69;
                    auxiliar->prox++;
                }
                else if(c=='E'|| c=='e'){
                    current_state = S72;
                    auxiliar->prox++;
                
                }else if(c=='_' || (isalpha(c)!=0 && c!='E' && c!='e')){
                    printf("Error in line %d and %d column\n", auxiliar->currentLine, auxiliar->currentColumn);
                    current_state = INITIAL_STATE;
                    tk.name_tk = (char*)"$";
                    return tk;
                }else{
                    current_state = S4;
                }
                auxiliar->currentColumn++;
            break;

            case S69:
                if(isdigit(c)>0){
                    current_state = S70;   
                }
                auxiliar->prox++;
                auxiliar->currentColumn++;
            break;

            case S72:
                if(isdigit(c)>0){
                    current_state = S74;
                }
                else if(c=='+' | c=='-'){
                    current_state = S73;
                }
                auxiliar->prox++;
                auxiliar->currentColumn++;
            break;

            case S4:
                tk.name_tk = (char*)"INT";
                tk.attr = (char*)malloc(sizeof(auxiliar->positionSymbolTable));
                sprintf(tk.attr, "%d", auxiliar->positionSymbolTable);
                current_state=INITIAL_STATE;
                //Check if position alredy exists in symbol table before of call 
                if(exists(*st, getLexeme(buffer, auxiliar->ini, auxiliar->prox))==0){
                    addLast(st, tk.name_tk, getLexeme(buffer, auxiliar->ini, auxiliar->prox), auxiliar->positionSymbolTable);
                    auxiliar->positionSymbolTable++;
                }else{
                    tmp  = getPosition(*st, getLexeme(buffer, auxiliar->ini, auxiliar->prox));
                    sprintf(tk.attr,"%d", tmp);
                }
            
                printf("Token found in position: %dl %dc  -> <%s,%s>\n", auxiliar->currentLine, auxiliar->currentColumn, tk.name_tk, tk.attr);
                //(*prox)++;
                auxiliar->ini=auxiliar->prox;
                return tk;
            break;

            case S70:
                
                if(isdigit(c)>0){
                    current_state = S70;
                    auxiliar->prox++;
                }
                else if(c=='E' || c=='e'){
                    current_state= S72;
                    auxiliar->prox++;
                }else{
                    current_state = S71;
                }
                auxiliar->currentColumn++;
                break;
            
            case S74:
                        
                if(isdigit(c)>0){
                    current_state = S74;
                    auxiliar->prox++;
                }
                else{
                    current_state = S75;
                }
                auxiliar->currentColumn++;
            break;

            case S73:
                if(isdigit(c)>0){
                    current_state = S74;
                }
                auxiliar->prox++;
                auxiliar->currentColumn++;
            break;

            case S71:
                tk.name_tk = (char*)"FLOAT";
                tk.attr = (char*)malloc( sizeof(auxiliar->positionSymbolTable));
                sprintf(tk.attr, "%d", auxiliar->positionSymbolTable);
                current_state=INITIAL_STATE;
                //Check if position alredy exists in symbol table before of call 
                
                
                if(exists(*st, getLexeme(buffer, auxiliar->ini, auxiliar->prox))==0){
                    addLast(st, tk.name_tk, getLexeme(buffer, auxiliar->ini, auxiliar->prox), auxiliar->positionSymbolTable);
                    auxiliar->positionSymbolTable++;
                }else{
                    tmp  = getPosition(*st, getLexeme(buffer, auxiliar->ini, aux));
                    sprintf(tk.attr,"%d", tmp);
                }
                
                printf("Token found in position: %dl %dc  -> <%s,%s>\n", auxiliar->currentLine, auxiliar->currentColumn, tk.name_tk, tk.attr);
                //(*prox)++;
                auxiliar->ini=auxiliar->prox;
                return tk;
            break;

            case S75:
                tk.name_tk = (char*)"EXPONENTIAL";
                tk.attr = (char*)malloc( sizeof(auxiliar->positionSymbolTable));
                sprintf(tk.attr, "%d", auxiliar->positionSymbolTable);
                current_state=INITIAL_STATE;
                //Check if position alredy exists in symbol table before of call 
                
                
                if(exists(*st, getLexeme(buffer, auxiliar->ini, auxiliar->prox))==0){
                    addLast(st, tk.name_tk, getLexeme(buffer, auxiliar->ini, auxiliar->prox), auxiliar->positionSymbolTable);
                    auxiliar->positionSymbolTable++;
                }else{
                    tmp  = getPosition(*st, getLexeme(buffer, auxiliar->ini, aux));
                    sprintf(tk.attr,"%d", tmp);
                }
                

                
                printf("Token found in position: %dl %dc  -> <%s,%s>\n", auxiliar->currentLine, auxiliar->currentColumn, tk.name_tk, tk.attr);
                //(*prox)++;
                auxiliar->ini=auxiliar->prox;
                return tk;
            break;

            case S103:
                tk.name_tk = (char*)"ARITHEMETIC_OP";
                tk.attr = (char*) "+";
                current_state=INITIAL_STATE;
                printf("Token found in position: %dl %dc  -> <%s,%s>\n", auxiliar->currentLine, auxiliar->currentColumn, tk.name_tk, tk.attr);
                auxiliar->prox++;
                auxiliar->ini=auxiliar->prox;
                auxiliar->currentColumn++;
                return tk;

            case S104:
                tk.name_tk = (char*)"ARITHEMETIC_OP";
                tk.attr = (char*)"-";
                current_state=INITIAL_STATE;
                printf("Token found in position: %dl %dc  -> <%s,%s>\n", auxiliar->currentLine, auxiliar->currentColumn, tk.name_tk, tk.attr);
                auxiliar->prox++;
                auxiliar->ini=auxiliar->prox;
                auxiliar->currentColumn++;
                return tk;
            
            case S105:
                tk.name_tk = (char*)"ARITHEMETIC_OP";
                tk.attr = (char*)"/";
                current_state=INITIAL_STATE;
                printf("Token found in position: %dl %dc  -> <%s,%s>\n", auxiliar->currentLine, auxiliar->currentColumn, tk.name_tk, tk.attr);
                auxiliar->prox++;
                auxiliar->ini=auxiliar->prox;
                auxiliar->currentColumn++;
                return tk;
            break;

            case S106:
                tk.name_tk = (char*)"ARITHEMETIC_OP";
                tk.attr = (char*) "*";
                current_state=INITIAL_STATE;
                printf("Token found in position: %dl %dc  -> <%s,%s>\n", auxiliar->currentLine, auxiliar->currentColumn, tk.name_tk, tk.attr);
                auxiliar->prox++;
                auxiliar->ini=auxiliar->prox;
                auxiliar->currentColumn++;
                return tk;
            break;
        
            case S102:
                tk.name_tk = (char*)"ARITHEMETIC_OP";
                tk.attr = (char*) "^";
                current_state=INITIAL_STATE;
                printf("Token found in position: %dl %dc  -> <%s,%s>\n", auxiliar->currentLine, auxiliar->currentColumn, tk.name_tk, tk.attr);
                auxiliar->prox++;
                auxiliar->ini=auxiliar->prox;
                auxiliar->currentColumn++;;
                return tk;
            break;

            case S51:
                if(c=='h'){
                    current_state = S52;
                }else{
                    current_state = S2;
                }
                auxiliar->prox++;
                auxiliar->currentColumn++;
            break;

            case S52:
                if(c=='a'){
                    current_state = S53;
                }else{
                    current_state=S2;
                }
                auxiliar->prox++;
                auxiliar->currentColumn++;
            break;

            case S53:
                if(c=='r'){
                    current_state = S54;
                }else{
                    current_state=S2;
                }
                auxiliar->prox++;
                auxiliar->currentColumn++;
            break;

            case S54:
                
                if(isalnum(c)==0 || c!='_'){
                   current_state = S55; 
                }
                auxiliar->currentColumn++;
            break;

            case S55:
                tk.name_tk = (char*)"TYPE";
                tk.attr = (char*) "none";
                current_state=INITIAL_STATE;
                printf("Token found in position: %dl %dc  -> <%s,%s>\n", auxiliar->currentLine, auxiliar->currentColumn, tk.name_tk, tk.attr);
                //(*prox)++;
                auxiliar->ini=auxiliar->prox;
                return tk;
            break;

            case S89: //
                if(c=='h'){
                    current_state = S90;
                    auxiliar->prox++;
                }
                else{
                    current_state = S2;
                }
                //
                auxiliar->currentColumn++;
            break;

            case S90:
                if(c=='i'){
                    current_state = S91;
                }else{
                    current_state = S2;
                }
                auxiliar->prox++;
                auxiliar->currentColumn++;
            break;

            case S91:
                if(c=='l'){
                    current_state = S92;
                }else{
                    current_state = S2;
                }
                auxiliar->prox++;
                auxiliar->currentColumn++;
            break;

            case S92:
                if(c=='e'){
                    current_state = S93;
                }else{
                    current_state = S2;
                }
                auxiliar->prox++;
                auxiliar->currentColumn++;
            break;

            case S93:
                           
                if(isalnum(c)==0 || c!='_'){
                   current_state = S94; 
                }else{
                    current_state = S2;
                }
                auxiliar->currentColumn++;
            break;

            case S94:
                tk.name_tk = (char*)"WHILE";
                tk.attr= (char*) "none";
                current_state=INITIAL_STATE;
                printf("Token found in position: %dl %dc  -> <%s,%s>\n", auxiliar->currentLine, auxiliar->currentColumn, tk.name_tk, tk.attr);
                auxiliar->ini=auxiliar->prox;
                return tk;
            break;

            case S63:
                tk.name_tk = (char*)"COMMA";
                tk.attr= (char*) "none";
                current_state=INITIAL_STATE;
                printf("Token found in position: %dl %dc  -> <%s,%s>\n", auxiliar->currentLine, auxiliar->currentColumn, tk.name_tk, tk.attr);
                auxiliar->prox++;
                auxiliar->ini=auxiliar->prox;
                return tk;
            break;
            
            case S64S111:
                if(c!=']'){
                    current_state = S111;
                }
                auxiliar->prox++;
                auxiliar->currentColumn++;
            break;

            case S111:
                if(c!=']'){
                    current_state = S111;
                    auxiliar->prox++;
                }else{
                    current_state = S112;
                }
                auxiliar->currentColumn++;
                
            break;

            case S112:
                auxiliar->prox++; //Ignore token
                current_state = INITIAL_STATE;
                auxiliar->currentColumn++;
            break;

            case S59:
                tk.name_tk = (char*)"SEMICOLON";
                tk.attr= (char*) "none";
                current_state=INITIAL_STATE;
                printf("Token found in position: %dl %dc  -> <%s,%s>\n", auxiliar->currentLine, auxiliar->currentColumn, tk.name_tk, tk.attr);
                auxiliar->prox++;
                auxiliar->ini=auxiliar->prox;
                //auxiliar->currentLine++;
                return tk;
            break;

            case S58:
                tk.name_tk = (char*)"OPEN_PARENTHESES";
                tk.attr= (char*) "none";
                current_state=INITIAL_STATE;
                printf("Token found in position: %dl %dc  -> <%s,%s>\n", auxiliar->currentLine, auxiliar->currentColumn, tk.name_tk, tk.attr);
                auxiliar->prox++;
                auxiliar->ini=auxiliar->prox;
                return tk;
            break;

            case S57:
                tk.name_tk = (char*)"CLOSE_PARENTHESES";
                tk.attr= (char*) "none";
                current_state=INITIAL_STATE;
                printf("Token found in position: %dl %dc  -> <%s,%s>\n", auxiliar->currentLine, auxiliar->currentColumn, tk.name_tk, tk.attr);
                auxiliar->prox++;
                auxiliar->ini=auxiliar->prox;
                return tk;
            break;

            case S45:
                if(c=='l'){
                    current_state = S46;
                }else{
                    current_state = S2;
                }
                auxiliar->prox++;
                auxiliar->currentColumn++;
            break;

            case S46:
                if(c=='o'){
                    current_state= S47;
                }else{
                    current_state = S2;
                }
                auxiliar->prox++;
                auxiliar->currentColumn++;
            break;

            case S47:
                if(c=='a'){
                    current_state = S48;
                }else{
                    current_state = S2;
                }
                auxiliar->prox++;
                auxiliar->currentColumn++;
            break;

            case S48:
                if(c=='t'){
                    current_state = S49;
                }else{
                    current_state = S2;
                }
                auxiliar->prox++;
                auxiliar->currentColumn++;
            break;

            case S49:
                
                if(isalnum(c)==0 || c!='_'){
                    current_state = S50;
                }else{
                    current_state = S2;
                }
                auxiliar->currentColumn++;
            break;

            case S50:
                tk.name_tk = (char*)"TYPE";
                tk.attr= (char*) "none";
                current_state=INITIAL_STATE;
                printf("Token found in position: %dl %dc  -> <%s,%s>\n", auxiliar->currentLine, auxiliar->currentColumn, tk.name_tk, tk.attr);
                //(*prox)++;
                auxiliar->ini=auxiliar->prox;
                return tk;
            break;

            case S114:
                if(c=='h'){
                    current_state = S115; 
                }else{
                    current_state = S2;
                }
                auxiliar->prox++;
                auxiliar->currentColumn++;
            break;

            case S115:
                if(c=='e'){
                    current_state = S116;
                }else{
                    current_state = S2;
                }
                auxiliar->prox++;
                auxiliar->currentColumn++;
            break;

            case S116:
                if(c=='n'){
                    current_state = S117;
                }else{
                    current_state = S2;
                }
                auxiliar->prox++;
                auxiliar->currentColumn++;
            break;

            case S117:
                
                if(isalnum(c)==0 || c=='_'){
                    current_state = S118;
                }else{
                    current_state = S2;
                }
            break;

            case S118:
                tk.name_tk = (char*)"THEN";
                tk.attr= (char*) "none";
                current_state=INITIAL_STATE;
                printf("Token found in position: %dl %dc  -> <%s,%s>\n", auxiliar->currentLine, auxiliar->currentColumn, tk.name_tk, tk.attr);
                //(*prox)++;
                auxiliar->ini=auxiliar->prox;
                return tk;
            break;

            case S29S96:
                if(c=='l'){
                    current_state = S97;
                }
                else if(c=='n'){
                    current_state = S30;
                }else{
                    current_state = S2;
                }
                auxiliar->prox++;
                auxiliar->currentColumn++;
            break;

            case S97:
                if(c=='s'){
                    current_state = S98;
                }else{
                    current_state = S2;
                }
                auxiliar->prox++;
                auxiliar->currentColumn++;
            break;

            case S98:
                if(c=='e'){
                    current_state = S99;
                }else{
                    current_state = S2;
                }
                auxiliar->prox++;
                auxiliar->currentColumn++;
            break;

            case S99:
                if(isalnum(c)==0 || c=='_'){
                    current_state = S100;
                }else{
                    current_state = S2;
                    auxiliar->prox++;
                }
                auxiliar->currentColumn++;
            break;

            case S100:
                tk.name_tk = (char*)"ELSE";
                tk.attr= (char*) "none";
                current_state=INITIAL_STATE;
                printf("Token found in position: %dl %dc  -> <%s,%s>\n", auxiliar->currentLine, auxiliar->currentColumn, tk.name_tk, tk.attr);
                //(*prox)++;
                auxiliar->ini=auxiliar->prox;
                return tk;
            break;

            case S30:
                if(c=='d'){
                    current_state = S31;
                }else{
                    current_state = S2;
                }
                auxiliar->prox++;
                auxiliar->currentColumn++;
            break;

            case S31:
                
                if(isalnum(c)==0 || c!='_'){
                    current_state = S32;
                }else{
                    current_state = S2;
                    
                }
                auxiliar->prox++;
                auxiliar->currentColumn++;
            break;

            case S32:
                tk.name_tk = (char*)"END";
                tk.attr= (char*) "none";
                current_state=INITIAL_STATE;
                printf("Token found in position: %dl %dc  -> <%s,%s>\n", auxiliar->currentLine, auxiliar->currentColumn, tk.name_tk, tk.attr);
                //(*prox)++;
                auxiliar->ini=auxiliar->prox;
                return tk;
            break;

            case S85:
                if(c=='o'){
                    current_state = S86;
                }else{
                    current_state = S2;
                }
                auxiliar->prox++;
                auxiliar->currentColumn++;
            break;

            case S86:
                
                if(isalnum(c)==0 || c!='_'){
                    current_state = S87;
                }else{
                    current_state = S2;
                    auxiliar->prox++;
                }
                auxiliar->currentColumn++;
            break;

            case S87:
                tk.name_tk = (char*)"DO";
                tk.attr= (char*) "none";
                current_state=INITIAL_STATE;
                printf("Token found in position: %dl %dc  -> <%s,%s>\n", auxiliar->currentLine, auxiliar->currentColumn, tk.name_tk, tk.attr);
                //(*prox)++;
                auxiliar->ini=auxiliar->prox;
                return tk;
            break;

            case S41S120:
                if(c=='n'){
                    current_state = S42;
                }
                else if(c=='f'){
                    current_state = S121;
                }else{
                    current_state = S2;
                }
                auxiliar->prox++;
                auxiliar->currentColumn++;
            
            break;
            
            case S42:
                if(c=='t'){
                    current_state = S43;
                }else{
                    current_state = S2;
                    
                }
                auxiliar->prox++;
                auxiliar->currentColumn++;
            break;

            case S43:
                //nextchar(buffer, *prox, &c);
                if(isalnum(c)==0 || c!='_'){
                    current_state = S44;
                }
                else{
                    current_state = S2;
                    auxiliar->prox++;
                }
                auxiliar->currentColumn++;
            break;

            case S44:
                tk.name_tk = (char*)"TYPE";
                tk.attr= (char*) "none";
                current_state=INITIAL_STATE;
                printf("Token found in position: %dl %dc  -> <%s,%s>\n", auxiliar->currentLine, auxiliar->currentColumn, tk.name_tk, tk.attr);
                //(*prox)++;
                auxiliar->ini=auxiliar->prox;
                return tk;
            break;

            case S121:
                
                if(isalnum(c)==0 || c!='_'){
                    current_state= S122;
                }else{
                    current_state = S2;
                    auxiliar->prox++;
                }
                auxiliar->currentColumn++;
            break;

            case S122:
                tk.name_tk = (char*)"IF";
                tk.attr= (char*) "none";
                current_state=INITIAL_STATE;
                printf("Token found in position: %dl %dc  -> <%s,%s>\n", auxiliar->currentLine, auxiliar->currentColumn, tk.name_tk, tk.attr);
                auxiliar->ini=auxiliar->prox;
                return tk;
            break;

            case S77:
                if(c=='e'){
                    current_state = S78;
                }else{
                    current_state = S2;
                }
                auxiliar->prox++;
                auxiliar->currentColumn++;
            break;
            
            case S78:
                if(c=='p'){
                    current_state = S79;
                }else{
                    current_state = S2;
                }
                auxiliar->prox++;
                auxiliar->currentColumn++;
            break;

            case S79:
                if(c=='e'){
                    current_state = S80;
                }else{
                    current_state = S2;
                }
                auxiliar->prox++;
                auxiliar->currentColumn++;
            break;

            case S80:
                if(c=='a'){
                    current_state = S81;
                }else{
                    current_state = S2;
                }
                auxiliar->prox++;
                auxiliar->currentColumn++;
            break;

            case S81:
                if(c=='t'){
                    current_state = S82;
                }else{
                    current_state = S2;
                }
                auxiliar->prox++;
                auxiliar->currentColumn++;
            break;

            case S82:
                
                if(isalnum(c)==0 || c!='_'){
                    current_state = S83;
                }else{
                    current_state = S2;
                    auxiliar->prox++;
                }
                auxiliar->currentColumn++;
            break;

            case S83:
                tk.name_tk = (char*)"REPEAT";
                tk.attr= (char*) "none";
                current_state=INITIAL_STATE;
                printf("Token found in position: %dl %dc  -> <%s,%s>\n",  auxiliar->currentLine, auxiliar->currentColumn, tk.name_tk, tk.attr);
                //(*prox)++;
                auxiliar->ini=auxiliar->prox;
                return tk;
            break;

            case S2:
                if(isalpha(c)!=0 || c=='_' || isdigit(c)>0){
                    current_state = S2;
                    auxiliar->prox++;    
                }else{
                    current_state = S3;
                }
                
                auxiliar->currentColumn++;
            break;

            case S3:
                tk.name_tk = (char*)"IDENTIFIER";
                current_state=INITIAL_STATE;
                aux =  (auxiliar->prox);
                tk.attr = (char*)malloc( sizeof(auxiliar->positionSymbolTable));
                //Check if position alredy exists in symbol table before of call 
                
                if(exists(*st, getLexeme(buffer, auxiliar->ini, aux))==0){    
                    sprintf(tk.attr,"%d", auxiliar->positionSymbolTable);
                    addLast(st, (char*)"IDENTIFIER", getLexeme(buffer, auxiliar->ini, aux), auxiliar->positionSymbolTable);
                    auxiliar->positionSymbolTable++;
                }else{
                    tmp  = getPosition(*st, getLexeme(buffer, auxiliar->ini, aux));
                    sprintf(tk.attr,"%d", tmp);
                }
                
                printf("Token found in position: %dl %dc  -> <%s,%s>\n", auxiliar->currentLine, auxiliar->currentColumn, tk.name_tk, tk.attr);
                //(*prox)++;
                auxiliar->ini=auxiliar->prox;
                return tk;
            break;            
          
            default:
                printf("%s - The token isn't recogninzed\n", getLexeme(buffer, auxiliar->ini, auxiliar->prox));
            break;
        
        }
    }
}