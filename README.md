# Front End Compiler

This project implement a front end of  the compiler. The first step is define a context free grammar. We know that a context free grammar G can be defined by four tuples as:

'''
G= (V, T, P, S)  
'''

Where

T describes a finite set of terminal symbols.
V describes a finite set of non-terminal symbols
P describes a set of production rules
S is the start symbol.

Knowing this now we can specify language using it.

I don't go show specification language, only definition of context free grammar with specified language structures.


S &rarr #programa nome_programa
    block

block &rarr begin
    variable_declaration
    command_sequence
    end

variable_declaration &rarr &epsilon | Type : id_lists ; | variable_declaration
id_lists &rarr identifier ; | identifier, id_lists
command_sequence &rarr &epsilon | command | command_sequence
command &rarr selection | loop | assignment
selection &rarr if ( condition ) then block else block
          &rarr if ( condition ) then bloco
loop &rarr while (condition) do block
          &rarr repeat block while ( condition )
assigment &rarr identify := expression
condition &rarr expression relational_operator expression
expression &rarr identify | constant | ( expression ) | expression relational_operator expression
constant &rarr number | character
comments &rarr [any_word]


    

