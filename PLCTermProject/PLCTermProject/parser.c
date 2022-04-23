#include "reference.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

FILE* in_fp, * fopen();

int CodeLine = 1;
int nodeNumber = 1;
int value = 0;			// Value for ID only
int found = 0;
int begin = 0;			// Have we passed begin?


struct node {
	int NodeNumber;
	int RuleInUse;
	int alternative;
	int id_val;
	struct node * branchOne;		// Left branch
	struct node * branchTwo;		// Right Branch
	struct node * branchThree;		// Middle Branch
};

struct symbol 
{
	char var;
	struct symbol* branchOne;
};


struct node* newNode(int NodeNumber, int rule, int alt, int value) {
	struct node* node = (struct node*)malloc(sizeof(struct node));
	node->NodeNumber = NodeNumber;
	node->RuleInUse = rule;
	node->alternative = alt;
	node->id_val = value;
	
	node->branchOne = NULL;
	node->branchTwo = NULL;
	node->branchThree = NULL;

	return (node);
};

struct symbol* symbolNode(char variable)
{
	struct symbol* symbol = (struct symbol*)malloc(sizeof(struct symbol));
	symbol->var = variable;
	symbol->branchOne = NULL;

	return(symbol);
}

struct node* currentNode;
struct node* root;
struct node* saveExpr; // Expr specific to get back to this node
struct node* saveFactor; // Factor specific to get back to this node
struct node* saveIf;	// If specific to get back to this node
struct symbolNode* symbolcurrent;
struct symbolNode* symbolhead;



//tree to keep track of nodes

//struct node* currentNode = root->first;

/* global declarations */
/* variables */

void parse()
{
	if ((in_fp = fopen("myinput.txt", "r")) == NULL)
		printf("error - cannot open myinput.txt \n");
	else
	{
		getChar();
		lex();
		if (strcmp(lexeme, "program") == 0)
		{
			root = newNode(nodeNumber++, 1, 1, 0);

			currentNode = root;
			lex();

			if (strlen(lexeme) > 1)
			{
				printf("Illegal Symbol! Expecting only 1 character for symbol: %s at Line %d!", lexeme, CodeLine);
				exit(-1);
			}

			do
			{

				if (strcmp(lexeme, "begin") != 0)
				{
					//currentNode = root->first;
					decl_sec();
				}
				else
				{
					//root->branchTwo = newNode(nodeNumber++, 1, 0, 0);
					currentNode = root;					// Done with Declaration side, move back to start and go down the right side now
					begin = 1;
					lex();
					stmt_sec();
				}

			} while (strcmp(lexeme, "end"));
		}
		else
		{
			printf("this program is not a valid program! Missing program keyword!\n");
			exit(-1);				// Used to exit program for error
		}

		lex();
		if (nextToken == TERMINATE)
		{
			lex();
			if (nextToken != EOF)
			{
				printf("Error, expecting end of file at Line %d!", CodeLine);
				exit(-1);
			}
			else
			{
				AltCheck(root->branchOne);
				AltCheck(root->branchTwo);
				printf("Node #\tRule#\tBranch1\tBranch2\tBranch3\tAlternative #\t Id/Int Value\n");
				printf("----------------------------------------------------------------------\n");
				printTable(root);
			}
		} 
		else
		{
			printf("Error, missing terminate keyword: ' ; ' at Line %d!", CodeLine);
			exit(-1);
		}

		
	}
}

void decl_sec()
{
	push(currentNode, 2, 1, 0);
	decl();
	while (strcmp(lexeme, "begin") != 0)
	{
		currentNode = root->branchOne;
		push(currentNode, 2, 1, 0);
		decl();
	}
	
}

void decl()

{
	push(currentNode,3,1, 0);
	id_list();
	if(nextToken == DECLARE)
	{
		lex();
		if (strcmp(lexeme, "int") != 0)
		{
			printf("Error, expecting type declaration: int at Line %d!", CodeLine);
			exit(-1);
		}
		else
		{
			lex();
			if (nextToken != TERMINATE)
			{
				printf("Error, missing terminate keyword: ' ; ' at Line %d!", CodeLine);
				exit(-1);
			}
		}
		
	}
	else
	{
		printf("Error, expecting a declaration: ' : ' at Line %d!", CodeLine);
		exit(-1);
	}
	lex();
}

void id_list()
{	
	push(currentNode, 4, 1, 0);
	id();

	while (nextToken == COMMA)
	{
		push(currentNode, 4, 1, 0);
		lex();

		if (strlen(lexeme) > 1)
		{
			printf("Illegal Symbol! Expecting only 1 character for symbol: %s at Line %d!", lexeme, CodeLine);
			exit(-1);
		}

		id();
	}

}

void id()
{
	

	if (nextToken == IDENT)
	{

		char temp = tolower(lexeme[0]);

		if (begin == 0)									// Still in Declaration so adding symbol to the table
		{
			found = search(temp);					// Check if the symbol has already been added to the table
			if (found == 0)
			{
				if (symbolhead == NULL)					// Is this the first symbol of the table?
				{
					symbolhead = symbolNode(temp);
					symbolcurrent = symbolhead;
				}
				else
					pushSymbol(symbolcurrent, temp);
			}
			else
			{
				printf("Error, symbol already exists! %s declared at Line %d!", lexeme, CodeLine);
				exit(-1);
			}
		}
		else											// Passed Declaration so begin proper search here
		{
			found = search(temp);

			if (found == 1)
				found = 0;			// reset found because symbol was found
			else
			{
				printf("Error, unable to find symbol: %s at Line %d!", lexeme, CodeLine);
				exit(-1);
			}
		}

		

		switch (temp)
		{
		case 'a':
			value = 1;
			break;
		case 'b':
			value = 2;
			break;
		case 'c':
			value = 3;
			break;
		case 'd':
			value = 4;
			break;
		case 'e':
			value = 5;
			break;
		case 'f':
			value = 6;
			break;
		case 'g':
			value = 7;
			break;
		case 'h':
			value = 8;
			break;
		case 'i':
			value = 9;
			break;
		case 'j':
			value = 10;
			break;
		case 'k':
			value = 11;
			break;
		case 'l':
			value = 12;
			break;
		case 'm':
			value = 13;
			break;
		case 'n':
			value = 14;
			break;
		case 'o':
			value = 15;
			break;
		case 'p':
			value = 16;
			break;
		case 'q':
			value = 17;
			break;
		case 'r':
			value = 18;
			break;
		case 's':
			value = 19;
			break;
		case 't':
			value = 20;
			break;
		case 'u':
			value = 21;
			break;
		case 'v':
			value = 22;
			break;
		case 'w':
			value = 23;
			break;
		case 'x':
			value = 24;
			break;
		case 'y':
			value = 25;
			break;
		case 'z':
			value = 26;
			break;
		default:
			value = 0;
			break;
		}

	
		push(currentNode, 5, 0, value);
		lex();
		
	}
	else
	{
		printf("Error, unable to parse ID, unknown ID identifier: ' %s ' at Line %d!",lexeme, CodeLine);
		exit(-1);
	}
}

void stmt_sec()
{
	push(currentNode, 6, 1, 0);
	stmt();
	while (strcmp(lexeme, "else") != 0 && strcmp(lexeme, "end") != 0)
	{
		currentNode = root->branchTwo;
		push(currentNode, 6, 1, 0);
		stmt();
	}
}

void stmt()
{
	
	if (nextToken == IDENT)
	{
		push(currentNode, 7, 1, 0);
		assign();
	}
		
	else if (nextToken == RESERVED_WORD)
	{
		if (strcmp(lexeme, "if") == 0)
		{
			push(currentNode, 7, 2, 0);
			ifstmt();
		}
		else if (strcmp(lexeme, "while") == 0)
		{
			push(currentNode, 7, 3, 0);
			whilestmt();
		}
		else if (strcmp(lexeme, "input") == 0)
		{
			push(currentNode, 7, 4, 0);
			inputstmt();
		}
		else if (strcmp(lexeme, "output") == 0)
		{
			push(currentNode, 7, 5, 0);
			outputstmt();
		}
		else
		{
			printf("Error, unable to parse statement, unknown reserved word: ' %s ' at Line %d!", lexeme, CodeLine);
			exit(-1);
		}
	}
	else
	{
		printf("Error, unable to parse statement, unknown statement type: ' %s ' at Line %d!", lexeme, CodeLine);
		exit(-1);
	}
	
}

void assign()
{
	push(currentNode, 8, 1, 0);
	id();
	if (nextToken == ASSIGN_OP)
	{
		lex();
		expr();
	}
	else
	{
		printf("Error, inappropriate assignment of variable, need this ' := ' at Line %d!", CodeLine);
		exit(-1);
	}
	if (nextToken != TERMINATE)
	{
		printf("Error, missing terminate keyword: ' ; ' at Line %d!", CodeLine);
		exit(-1);
	}
	//CodeLine++;
	lex();

}

void inputstmt()
{
	push(currentNode, 11, 1, 0);
	lex();
	id_list();
	if (nextToken != TERMINATE)
	{
		printf("Error, missing terminate keyword: ' ; ' at Line %d!", CodeLine);
		exit(-1);
	}
	//CodeLine++;
	lex();
}

void whilestmt()
{
	push(currentNode, 10, 1, 0);
	lex();
	comp();
	if (strcmp(lexeme, "loop") == 0)
	{
		push(currentNode, 10, 1, 0);
		lex();
		stmt_sec();
		if (strcmp(lexeme, "end") == 0)
		{
			lex();
			if (strcmp(lexeme, "loop") != 0)
			{
				printf("Error, missing reserved_word: ' loop ' at Line %d!", CodeLine);
				exit(-1);
			}

		}
	}
	else
	{
		printf("Error, missing reserved_word: ' loop ' at Line %d!", CodeLine);
		exit(-1);
	}
	lex();
	if (nextToken != TERMINATE)
	{
		printf("Error, missing terminate keyword: ' ; ' at Line %d!", CodeLine);
		exit(-1);
	}
	//CodeLine++;
	lex();
}

void outputstmt()
{
	push(currentNode, 12, 1, 0);
	lex();
	id_list();
	if (nextToken != TERMINATE)
	{
		printf("Error, missing terminate keyword: ' ; ' at Line %d!", CodeLine);
		exit(-1);
	}
	//CodeLine++;
	lex();
}
 

void expr()
{
	push(currentNode, 13, 1, 0);
	saveExpr = currentNode;
	factor();
	while (nextToken == ADD_OP || nextToken == SUB_OP)
	{
		currentNode = saveExpr;
		lex();
		expr();
	}

}

void factor()
{
	push(currentNode, 14, 1, 0);
	saveFactor = currentNode;
	operand();
	while (nextToken == MULT_OP)
	{
		currentNode = saveFactor;
		lex();
		factor();
	}
}

void operand()
{
	push(currentNode, 15, 1, 0);
	if (nextToken == INT_LIT)
		INT();
	else if (nextToken == IDENT)
		id();
	else if (nextToken == LEFT_PAREN)
	{
		lex();
		expr();
		if (nextToken == RIGHT_PAREN)
		{
			lex();
		}
		else
		{
			printf("Error, missing type declaration: ')' at Line %d!", CodeLine);
			exit(-1);
		}
	}
	else
	{
		printf("Error, unable to parse operation, unknown type identifier: ' %s ' at Line %d!", lexeme, CodeLine);
		exit(-1);
	}
}

void INT()
{
		if (strlen(lexeme) > 1)
		{
			printf("Illegal Number! Expecting only positive single digit numbers: %s at Line %d!", lexeme, CodeLine);
			exit(-1);
		}

		int temp = (int)(lexeme[0]);

		switch (temp)
		{
			case '1':
				value = 1;
				break;
			case '2':
				value = 2;
				break;
			case '3':
				value = 3;
				break;
			case '4':
				value = 4;
				break;
			case '5':
				value = 5;
				break;
			case '6':
				value = 6;
				break;
			case '7':
				value = 7;
				break;
			case '8':
				value = 8;
				break;
			case '9':
				value = 9;
				break;
			default:
				value = 0;
				break;

		}
	

	push(currentNode, 16, 1, value);
	lex();
}

void ifstmt()
{
	push(currentNode, 9, 1, 0);
	saveIf = currentNode;
	lex();
	comp();
	if (strcmp(lexeme, "then") == 0)
	{
		//CodeLine++;
		currentNode = saveIf;
		push(currentNode, 9, 0, 0);
		lex();
		stmt_sec();

		if (strcmp(lexeme, "else") == 0)
		{
			//CodeLine++;
			currentNode = saveIf;
			pushThirdBranch(currentNode, 9, 0, 0);
			lex();
			stmt_sec();
		}
		if (strcmp(lexeme, "end") == 0)
		{
			lex();
			if (strcmp(lexeme, "if") != 0)
			{
				printf("Error, missing reserved_word: ' if ' at Line %d!", CodeLine);;
				exit(-1);
			}
			
		} 
		else
		{
			printf("Error, missing reserved_word: ' end ' at Line %d!", CodeLine);
			exit(-1);
		}
	}
	else
	{
		printf("Error, missing reserved_word: ' then ' at Line %d!", CodeLine);
		exit(-1);
	}
	lex();
	if (nextToken != TERMINATE)
	{
		printf("Error, missing terminate keyword: ' ; ' at Line %d!", CodeLine);
		exit(-1);
	}
	//CodeLine++;
	lex();
}

void comp()
{
	if(nextToken == LEFT_PAREN)
	{
		lex();
		operand();
		while (nextToken != RIGHT_PAREN)
		{
			switch (nextToken)
			{
			case EQUALS:
				push(currentNode, 17, 1, 0);
				lex();
				operand();
				break;
			case NOT_EQUAL:
				push(currentNode, 17, 2, 0);
				lex();
				operand();
				break;
			case LESS_THAN:
				push(currentNode, 17, 4, 0);
				lex();
				operand();
				break;
			case GREATER_THAN:
				push(currentNode, 17, 3, 0);
				lex();
				operand();
				break;
			default:
				printf("Error, unable to parse comparison, missing: ' ) ' at Line %d!", CodeLine - 1);
				exit(-1);
			}
		}

	}
	else
	{
		printf("Missing type declaration: ' ( ' at Line %d!", CodeLine);
		exit(-1);
	}
	//CodeLine++;
	lex();
}

/*****************************************************/
//push - Handles adding new nodes to the branches based on specific rules

void push(struct node* node, int rule, int alt, int value)
{
	if (node == root && root->branchOne == NULL)					// Check if we are at the root
	{
		node->branchOne = newNode(nodeNumber++, rule, alt, value);
		currentNode = node->branchOne;
		return;
	}
	else if(node == root && root->branchTwo == NULL)				// If root has one branch already, move on to the next (Root will not have more than two branches)
	{
		node->branchTwo = newNode(nodeNumber++, rule, alt, value);
		currentNode = node->branchTwo;
		return;
	}
	else															// Else, we are not currently working on the root
	{

		if (node->branchOne == NULL)
		{
			node->branchOne = newNode(nodeNumber++, rule, alt, value);
			if (value == 0)							// Check if this is not an ID node, move to the next branch. Else, just return and do not move ahead. Also, check for then (If statement should have COMP and STMT_SEC as its own children)
				currentNode = node->branchOne;
			return;
		}
		else if(node->branchTwo == NULL)
		{
			node->branchTwo = newNode(nodeNumber++, rule, alt, value);
			currentNode = node->branchTwo;
			return;
		}
		else
		{
			push(node->branchTwo, rule, alt, value);				// If both branches are in use, we want to advance to the child node's right
		}
	}
}

/*****************************************************/
/* pushThidBranch- Based on our grammar rules, only if/else has a third branch so this function is specific to that */

void pushThirdBranch(struct node* node, int rule, int alt, int value)		// Specific for if-else statement
{
		node->branchThree = newNode(nodeNumber++, rule, alt, value);
		currentNode = node->branchThree;
		return;
}
/*****************************************************/
/* pushSymbol- Adding Symbol to the Table */

void pushSymbol(struct symbol* symbol, char variable)		// Add the variable to the symbol table
{
	symbol->branchOne = symbolNode(variable);
	symbolcurrent = symbol->branchOne;
	return;
}

/*****************************************************/
/* search - Symbol searcher that checks for the symbol to see if it exists or not */

struct symbol* search(char variable)
{

	if (symbolhead == NULL)
	{
		return 0;
	}

	struct symbol* search = symbolhead;								// Start at head

	while (search->var != variable)
	{
		if (search->branchOne == NULL)
		{
			return 0;
		}
		else
			search = search->branchOne;
	}

	return 1;
}


/*****************************************************/
/* printTable - Table printer, goes through the tree and prints out the nodes */

void printTable(struct node* root) {
 	if (root == NULL) {
		return;
	}

	struct node* PrintNode = root;

	int firstBranch = PrintNode->branchOne == NULL ? 0 : PrintNode->branchOne->NodeNumber;
	int secondBranch = PrintNode->branchTwo == NULL ? 0 : PrintNode->branchTwo->NodeNumber;
	int thirdBranch = PrintNode->branchThree == NULL ? 0 : PrintNode->branchThree->NodeNumber;

	if(PrintNode-> id_val == 0)
		printf("%d\t%d\t%d\t%d\t%d\t%d\n", PrintNode->NodeNumber, PrintNode->RuleInUse, firstBranch, secondBranch, thirdBranch, PrintNode->alternative);
	else
		printf("%d\t%d\t%d\t%d\t%d\t%d\t\t%d\n", PrintNode->NodeNumber, PrintNode->RuleInUse, firstBranch, secondBranch, thirdBranch, PrintNode->alternative, PrintNode -> id_val);

	printTable(PrintNode->branchOne);
	printTable(PrintNode->branchTwo);
	printTable(PrintNode->branchThree);
	
	
}

/*****************************************************/
/* printTable - Go through the nodes and properly assign alternative rules. Check for a right branch and whether its the proper rule, if so, it must be the alternative rule. 
				This will also check for the if else statement. If that has a third branch, assign it to the 2nd alternative. Then go down until you reach the end */
void AltCheck(struct node* currentNode)
{
	if (currentNode == NULL)
	{
		return;
	}

	struct node* checkNode = currentNode;
	
	if (checkNode->alternative == 1)
	{
		if (checkNode->branchTwo != NULL && (checkNode->RuleInUse != 3 && checkNode->RuleInUse != 7 && checkNode->RuleInUse != 8 && checkNode->RuleInUse != 9 && checkNode->RuleInUse != 10 && checkNode->RuleInUse != 11 && checkNode->RuleInUse != 12 && checkNode->RuleInUse != 15 && checkNode->RuleInUse != 17))
		{
			checkNode->alternative++;
		}
		else if (checkNode->RuleInUse == 9 && checkNode->branchThree != NULL)
		{
			checkNode->alternative = 2;
		}
	}
	AltCheck(checkNode->branchOne);
	AltCheck(checkNode->branchTwo);

}