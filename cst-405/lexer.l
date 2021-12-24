%option noyywrap

%{
//Made By: Karan Sharma
//Refrence: Help from Adam Harris
//Date: 22/12/2021
#include <stdio.h>
#include <string.h>

#define YY_DECL int yylex()
#include "parser.tab.h"

// keep track of the current line and character number on the line that the lexer is scanning to
int words = 0;
int chars = 0;
int lines = 1;


// create regex expression to recognize words and symbols
// make comments in the code possible
// include all of the words that could be in our c-- code
%}
CHACHA      '[a-zA-Z]'
STRING      \"(\\.|[^"\\])*\"
letter      [a-zA-Z]
digit       [0-9]
ID          {letter}({letter}|{digit})*
delim       [ \t\n]
NUMBER      {digit}+(\.{digit}+)?(E[+\-]?{digit}+)?
ws          {delim}+


%%
"/*"    				{
							int c;
							while((c = input()) != 0) {
								if(c == '*') {
									if((c = input()) == '/')
										break;
									else
										unput(c);
								}
							}
						}
						
"int"	{words++; chars += strlen(yytext);
			printf("%s : TYPE || Line: %d || Char: %d\n", yytext,lines,chars);
			yylval.string = strdup(yytext); 
			return TYPE;
		}

"float" {words++; chars += strlen(yytext);
			printf("%s : TYPE || Line: %d || Char: %d\n", yytext,lines,chars);
			yylval.string = strdup(yytext); 
			return TYPE;
		}

"bool"	{words++; chars += strlen(yytext);
			printf("%s : TYPE || Line: %d || Char: %d\n", yytext,lines,chars);
			yylval.string = strdup(yytext); 
			return TYPE;
		}

"char"	{words++; chars += strlen(yytext);
			printf("%s : TYPE || Line: %d || Char: %d\n", yytext,lines,chars);
			yylval.string = strdup(yytext); 
			return TYPE;
		}

"void"	{words++; chars += strlen(yytext);
			printf("%s : TYPE || Line: %d || Char: %d\n", yytext,lines,chars);
			yylval.string = strdup(yytext); 
			return TYPE;
		}

"return"	{words++; chars += strlen(yytext);
			printf("%s : RETURN|| Line: %d || Char: %d\n", yytext,lines,chars);
			yylval.string = strdup(yytext); 
			return RETURN;
		}

"write"	{words++; chars += strlen(yytext);
			printf("%s : KEYWORD|| Line: %d || Char: %d\n", yytext,lines,chars);
			yylval.string = strdup(yytext); 
			return WRITE;
		}

"read"	{words++; chars += strlen(yytext);
			printf("%s : READ|| Line: %d || Char: %d\n", yytext,lines,chars);
			yylval.string = strdup(yytext); 
			return READ;
		}

"writeln"	{words++; chars += strlen(yytext);
			printf("%s : WRITELN|| Line: %d || Char: %d\n", yytext,lines,chars);
			yylval.string = strdup(yytext); 
			return WRITELN;
			}

"break"	{words++; chars += strlen(yytext);
			printf("%s : BREAK|| Line: %d || Char: %d\n", yytext,lines,chars);
			yylval.string = strdup(yytext); 
			return BREAK;
		}

"ifelse" 	{words++; chars += strlen(yytext);
			printf("%s : IFELSE|| Line: %d || Char: %d\n", yytext,lines,chars);
			yylval.string = strdup(yytext); 
			return IFELSE;
			}

"if"	{words++; chars += strlen(yytext);
			printf("%s : IF|| Line: %d || Char: %d\n", yytext,lines,chars);
			yylval.string = strdup(yytext); 
			return IF;
		}

"else"	{words++; chars += strlen(yytext);
			printf("%s : ELSE|| Line: %d || Char: %d\n", yytext,lines,chars);
			yylval.string = strdup(yytext); 
			return ELSE;
		}

"while"	{words++; chars += strlen(yytext);
			printf("%s : WHILE|| Line: %d || Char: %d\n", yytext,lines,chars);
			yylval.string = strdup(yytext); 
			return WHILE;
		}

{ID}	{words++; chars += strlen(yytext);
			  printf("%s : IDENTIFIER|| Line: %d || Char: %d\n", yytext,lines,chars);
			  yylval.string = strdup(yytext); 
			  return ID;
		}
			
{NUMBER}		{words++; chars += strlen(yytext);
			  printf("%s : NUMBER|| Line: %d || Char: %d\n", yytext,lines,chars);
			  yylval.number = atoi(strdup(yytext)); 
			  return NUMBER;
			}
			

{STRING}	{words++; chars += strlen(yytext);
			  printf("%s : STRING|| Line: %d || Char: %d\n", yytext,lines,chars);
			  yylval.string = strdup(yytext); 
			  return STRING;
		}

{CHACHA}	{words++; chars += strlen(yytext);
			  printf("%s : CHACHA|| Line: %d || Char: %d\n", yytext,lines,chars);
			  yylval.string = strdup(yytext); 
			  return CHACHA;
		}
		
";"		{chars++;
		  printf("%s : SEMICOLON|| Line: %d || Char: %d\n", yytext,lines,chars);
		  yylval.string = strdup(yytext); 
		  return SEMICOLON;
		}
		
"="		{chars++;
		  printf("%s : EQ|| Line: %d || Char: %d\n", yytext,lines,chars);
		  yylval.string = strdup(yytext); 
		  return EQ;
		}
		
"{"		{chars++;
		  printf("%s : LCURL|| Line: %d || Char: %d\n", yytext,lines,chars);
		  yylval.string = strdup(yytext); 
		  return LCURL;
		}

"}"		{chars++;
		  printf("%s : RCURL || Line: %d || Char: %d\n", yytext,lines,chars);
		  yylval.string = strdup(yytext); 
		  return RCURL;
		}

"["		{chars++;
		  printf("%s : LBRACK|| Line: %d || Char: %d\n", yytext,lines,chars);
		  yylval.string = strdup(yytext); 
		  return LBRACK;
		}

"]"		{chars++;
		  printf("%s : RBRACK|| Line: %d || Char: %d\n", yytext,lines,chars);
		  yylval.string = strdup(yytext); 
		  return RBRACK;
		}

"("		{chars++;
		  printf("%s : LPAREN|| Line: %d || Char: %d\n", yytext,lines,chars);
		  yylval.string = strdup(yytext); 
		  return LPAREN;
		}

")"		{chars++;
		  printf("%s : RPAREN|| Line: %d || Char: %d\n", yytext,lines,chars);
		  yylval.string = strdup(yytext); 
		  return RPAREN;
		}

","		{chars++;
		  printf("%s : COMMA|| Line: %d || Char: %d\n", yytext,lines,chars);
		  yylval.string = strdup(yytext); 
		  return COMMA;
		}

"+"		{chars++;
		  printf("%s : PLUS|| Line: %d || Char: %d\n", yytext,lines,chars);
		  yylval.string = strdup(yytext); 
		  return yytext[0];
		}

"-"		{chars++;
		  printf("%s : MINUS|| Line: %d || Char: %d\n", yytext,lines,chars);
		  yylval.string = strdup(yytext); 
		  return yytext[0];
		}

"*"		{chars++;
		  printf("%s : MULT|| Line: %d || Char: %d\n", yytext,lines,chars);
		  yylval.string = strdup(yytext); 
		  return yytext[0];
		}

"/"		{chars++;
		  printf("%s : DIVIDE|| Line: %d || Char: %d\n", yytext,lines,chars);
		  yylval.string = strdup(yytext); 
		  return yytext[0];
		}

"=="		{chars += 2;
		  printf("%s : BINOP|| Line: %d || Char: %d\n", yytext,lines,chars);
		  yylval.string = strdup(yytext); 
		  return BINOP;
		}

"!="		{chars += 2;
		  printf("%s : BINOP|| Line: %d || Char: %d\n", yytext,lines,chars);
		  yylval.string = strdup(yytext); 
		  return BINOP;
		}

"<="		{chars += 2;
		  printf("%s : BINOP|| Line: %d || Char: %d\n", yytext,lines,chars);
		  yylval.string = strdup(yytext); 
		  return BINOP;
		}

">="		{chars += 2;
		  printf("%s : BINOP|| Line: %d || Char: %d\n", yytext,lines,chars);
		  yylval.string = strdup(yytext); 
		  return BINOP;
		}

"&&"		{chars += 2;
		  printf("%s : BINOP|| Line: %d || Char: %d\n", yytext,lines,chars);
		  yylval.string = strdup(yytext); 
		  return BINOP;
		}

"||"		{chars += 2;
		  printf("%s : BINOP|| Line: %d || Char: %d\n", yytext,lines,chars);
		  yylval.string = strdup(yytext); 
		  return BINOP;
		}

"<"		{chars++;
		  printf("%s : BINOP|| Line: %d || Char: %d\n", yytext,lines,chars);
		  yylval.string = strdup(yytext); 
		  return BINOP;
		}

">"		{chars++;
		  printf("%s : BINOP|| Line: %d || Char: %d\n", yytext,lines,chars);
		  yylval.string = strdup(yytext); 
		  return BINOP;
		}

"!"		{chars++;
		  printf("%s : UNARYOP|| Line: %d || Char: %d\n", yytext,lines,chars);
		  yylval.string = strdup(yytext); 
		  return UNARYOP;
		}

[\r\n]	{lines++; chars=0;}
[ \t]	{chars++;}
.		{chars++;
         printf("%s : Unrecognized symbol at line %d char %d\n", yytext,lines,chars);
		}
		
%%