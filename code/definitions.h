#define INITIAL_STATE 1

//transition token programa
#define S19 19
#define S20 20
#define S21 21
#define S22 22
#define S23 23
#define S24 24
#define S25 25
#define S26 26
#define S27 27

//trasition token character

#define S15 15
#define S16 16
#define S17 17

//transition token begin
#define S34 34
#define S35 35
#define S36 36
#define S37 37
#define S38 38
#define S39 39

//transition token equal
#define S10 10

//transition token neg
#define S8 8
#define S9 9

//transition token > or >=
#define S11 11
#define S12 12
#define S13 13

//transition token < or <=
#define S5 5
#define S6 6
#define S7 7

//transition token = or :
#define S60 60
#define S61 61
#define S62 62

//transition token number
#define S67 67
#define S4 4
#define S69 69
#define S72 72
#define S70 70
#define S74 74
#define S73 73
#define S71 71
#define S75 75

//transition token id
#define S2 2
#define S3 3

//transition token operator arithimetic
#define S103 103
#define S104 104
#define S105 105
#define S106 106
#define S102 102

//transition token char
#define S51 51
#define S52 52
#define S53 53
#define S54 54
#define S55 55

//transition token while
#define S89 89
#define S90 90
#define S91 91
#define S92 92
#define S93 93
#define S94 94

//transition token colon
#define S63 63

//transition token space tabulation and new line
#define S108 108

//transition token comments
#define S64S111 64111
#define S111 111
#define S112 112

//transition token semicolon
#define S59 59

//transition token open parentheses
#define S58 58

//transition token close parenthses
#define S57 57

//transition token float
#define S45 45
#define S46 46
#define S47 47
#define S48 48
#define S49 49
#define S50 50

//transition token then
#define S114 114
#define S115 115
#define S116 116
#define S117 117
#define S118 118

//transition tokens else and end
#define S29S96 2996
#define S97 97
#define S98 98
#define S99 99
#define S100 100
#define S30 30
#define S31 31
#define S32 32

//transition token do
#define S85 85
#define S86 86
#define S87 87

//transition tokens int and if
#define S41S120 41120
#define S42 42
#define S43 43
#define S44 44
#define S121 121
#define S122 122

//transition token repeat
#define S77 77
#define S78 78
#define S79 79
#define S80 80
#define S81 81
#define S82 82
#define S83 83


typedef struct tk{
    char *name_tk;
    char *attr;
}Token;

struct table{
    int position;
    char *lexeme;
    char *name_tk;
    struct table *prox;
};


int addLast(struct table **st, char* name_tk, char* lexeme, int position);

void printSymbolTable(struct table  *st);

int exists(struct table *st, char *lexeme);
