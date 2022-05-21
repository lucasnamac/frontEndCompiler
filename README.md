# Front End Compiler

This project implement a front end of  the compiler. The first step is define a context free grammar. We know that a context free grammar G can be defined by four tuples as:

```
G= (V, T, P, S)
```

Where

T describes a finite set of terminal symbols.

V describes a finite set of non-terminal symbols

P describes a set of production rules

S is the start symbol.

Knowing this now we can specify language using it.

I don't go show specification language, only definition of context free grammar with specified language structures.

S &#8594; programa nome_programa
    block

block &#8594; begin
    variable_declaration
    command_sequence
    end

variable_declaration &#8594; ε | Type : id_lists ; | variable_declaration

id_lists &#8594; identifier ; | identifier, id_lists

command_sequence &#8594; ε | command | command_sequence

command &#8594; selection | loop | assignment

selection &#8594; if ( condition ) then block else block
               &#8594; if ( condition ) then bloco

loop &#8594; while (condition) do block
        &#8594; repeat block while ( condition )

assigment &#8594; identify := expression

condition &#8594; expression relational_operator expression

expression &#8594; identify | constant | ( expression ) | expression relational_operator expression

constant &#8594; number | character

comments &#8594; [any_word]


​    

