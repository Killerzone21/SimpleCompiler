/**********************   PLCTermProject.c  ********************
*
*  Purpose: A lexical analyzer system for simple arithmetic expressions
*
************************************************************/

#include "reference.h"
#include <stdio.h>
#include <ctype.h>

FILE* in_fp, * fopen();


/*****************************************************/
/* lookup - a function to lookup operators and parentheses
and return the token */
int lookup(char ch) {
	switch (ch) {
	case '(':
		addChar();
		nextToken = LEFT_PAREN;
		break;
	case ')':
		addChar();
		nextToken = RIGHT_PAREN;
		break;
	case '+':
		addChar();
		nextToken = ADD_OP;
		break;
	case '-':
		addChar();
		nextToken = SUB_OP;
		break;
	case '*':
		addChar();
		nextToken = MULT_OP;
		break;
	case '<':
		addChar();
		nextToken = LESS_THAN;
		break;
	case '>':
		addChar();
		nextToken = GREATER_THAN;
		break;
	case '=':
		addChar();
		nextToken = EQUALS;
		break;
	case ',':
		addChar();
		nextToken = COMMA;
		break;
	case ':':
		addChar();
		nextToken = DECLARE;
		break;
	case ';':
		addChar();
		nextToken = TERMINATE;
		break;
	default:
		addChar();
		nextToken = EOF;
		break;
	}
	return nextToken;
}
/*****************************************************/
/* addChar - a function to add nextChar to lexeme */
void addChar()
{
	if (lexLen <= 98)
	{
		lexeme[lexLen++] = nextChar;
		lexeme[lexLen] = 0;
	}
	else
		printf("Error - lexeme is too long \n");
}
/*****************************************************/
/* getChar - a function to get the next character of
input and determine its character class */
void getChar()
{
	if ((nextChar = getc(in_fp)) != EOF)
	{
		if (nextChar == '\n')
		{
			CodeLine++;
		}

		if (isalpha(nextChar))
			charClass = LETTER;
		else if (isdigit(nextChar))
			charClass = DIGIT;
		else charClass = UNKNOWN;
	}
	else
		charClass = EOF;
}
/*****************************************************/
/* getNonBlank - a function to call getChar until it
returns a non-whitespace character */
void getNonBlank() {
	while (isspace(nextChar))
		getChar();
}

/*****************************************************/
/* lex - a simple lexical analyzer for arithmetic
expressions */
int lex() {
	lexLen = 0;
	getNonBlank();
	switch (charClass) {
		/* Parse identifiers */
	case LETTER:
		addChar();
		getChar();
		while (charClass == LETTER || charClass == DIGIT) {
			addChar();
			getChar();
		}
		/* Check if the word is a reserved word */
		if (strcmp(lexeme, "program") == 0 || (strcmp(lexeme, "begin") == 0 || strcmp(lexeme, "end") == 0 ||
			strcmp(lexeme, "if") == 0 || strcmp(lexeme, "then") == 0 || strcmp(lexeme, "else") == 0 || 
			strcmp(lexeme, "input") == 0 || strcmp(lexeme, "output") == 0 || strcmp(lexeme, "int") == 0 ||
			strcmp(lexeme, "while") == 0 || strcmp(lexeme, "loop") == 0))
		{
			nextToken = RESERVED_WORD;
		}
		else
			nextToken = IDENT;
		break;
		/* Parse integer literals */
	case DIGIT:
		addChar();
		getChar();
		while (charClass == DIGIT) {
			addChar();
			getChar();
		}
		nextToken = INT_LIT;
		break;
		/* Parentheses and operators */
	case UNKNOWN:
		lookup(nextChar);
		getChar();
		if(strcmp(lexeme, ":") == 0  && charClass == UNKNOWN)
		{
			addChar();
			getChar();
		}
		if (strcmp(lexeme, ":=") == 0)
		{
			nextToken = ASSIGN_OP;
		}
		if (strcmp(lexeme, "<") == 0 && charClass == UNKNOWN)
		{
			addChar();
			getChar();
		}
		if (strcmp(lexeme, "<>") == 0)
		{
			nextToken = NOT_EQUAL;
		}

		break;
		/* EOF */
	case EOF:
		nextToken = EOF;
		lexeme[0] = 'E';
		lexeme[1] = 'O';
		lexeme[2] = 'F';
		lexeme[3] = 0;
		break;
	} /* End of switch */
	return nextToken;
} /* End of function lex */