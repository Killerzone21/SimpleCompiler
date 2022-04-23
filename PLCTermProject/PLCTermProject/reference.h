


/* Global declarations */
/* Variables */
int charClass;
char lexeme[100];
char nextChar;
int lexLen;
int token;
int nextToken;
extern int CodeLine;



/* Function declarations */
void addChar();
void getChar();
void getNonBlank();
int lex();
void parse();

void decl_sec();
void decl();
void id_list();
void id();
void stmt_sec();
void stmt();
void assign();
void ifstmt();
void whilestmt();
void inputstmt();
void outputstmt();
void expr();
void factor();
void operand();
void INT();
void comp();
void printTable(struct node* root);
void push(int CurrentNode, int rule, int alt, int value);
void pushThirdBranch(int CurrentNode, int rule, int alt, int value);
void AltCheck(struct node* currentNode);

void pushSymbol(struct symbol* symbol, char variable);
struct symbol* search(char variable);

/* Character classes */

#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

/* Token codes */

#define INT_LIT 10
#define IDENT 11
#define DECLARE 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define EQUALS 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
#define LESS_THAN 27
#define GREATER_THAN 28
#define NOT_EQUAL 29
#define COMMA 30
#define ASSIGN_OP 40
#define RESERVED_WORD 41
#define TERMINATE 98



