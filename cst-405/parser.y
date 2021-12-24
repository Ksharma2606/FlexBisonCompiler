%{
// check version
//Made By: Karan Sharma
//Refrence: Help from Adam Harris
//Date: 22/12/2021
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <regex.h>
#include <time.h>

#include "stack.h"
#include "symbolTable.h"
#include "AST.h"
#include "IRcode.h"
#include "MIPS.h"

extern int yylex();
extern int yyparse();
extern FILE* yyin;

// get the line and character number from the lexer file to show them in error messages 
extern int lines;
extern int chars;

void yyerror(const char* s);
int semanticCheckPassed = 1;
/* stack to keep track of the current scope */
struct stack_t* theStack = NULL;
struct stack_t* ifwhilestack = NULL;
struct stack_t* userout = NULL;
int if_counter = 1;
int while_counter = 1;
int useroutnumber = 0;
%}

%union {
	int number;
	char character;
	char* string;
	struct AST* ast;
}

// set type for all of the tokens
%token <string> ID BINOP RETURN READ WRITELN BREAK IFELSE IF ELSE WHILE VOID TYPE UNARYOP SEMICOLON STRING CHACHA
%token <character> COMMA EQ LCURL RCURL LBRACK RBRACK LPAREN RPAREN
%token <number> NUMBER
%token WRITE
%token INPUT

%printer { fprintf(yyoutput, "%s", $$); } ID;
%printer { fprintf(yyoutput, "%d", $$); } NUMBER;

// set precedence for calculation order
%right EQ
%left '+' '-'
%left '*' '/'
%left LPAREN RPAREN

// cast the type ast on all of the non-terminals
%type <ast> Program DeclList Decl VarDeclId VarDecl ParamDeclList FunDecl ParamDeclListTail	ParamDecl	Block ExprListTail ExprList Primary Expr Stmt InnerBlockList InnerBlock

%start Program

%%

// program include of a DeclList
// regex (regular expressions) used throughout for checking for correct token during IRcode generation and type checking.
Program:	DeclList 
					{ 
						/* start the AST */
						printf("\n--- Abstract Syntax Tree ---\n\n");
						makeAST($1, 0);
						printAST();
					}
;

// user can now include many Decl in that one DeclList
DeclList:	Decl DeclList
					{
						$$ = $1;
						$$->mid = $2;
					}
				|	
					{
						$$ = AST_node("");
					}
;

// different type of Decl
Decl:	VarDecl
		|	FunDecl
		|	Stmt
;

// id could be int, char, char[2], or int[2]
VarDeclId:	ID 
						{
							printf("RECOGNIZED RULE: Variable declaration || %s || Line: %d || Char: %d\n", $1, lines, chars);
						}
					| ID LBRACK NUMBER RBRACK 
						{
							printf("RECOGNIZED RULE: Array declaration || %s || Line: %d || Char: %d\n", $1, lines, chars);
							/* create ast node for array declaration */
							char str[1000];
							sprintf(str, "%d", $3);
							$$ = AST_node("ARR");
							$$->left = AST_node($1);
							$$->right = AST_node(str);
							/* check if array is declared with length of 0 */
							if ($3 < 1){
								printf("SEMANTIC ERROR: %s array has length that is smaller than one || Line: %d || Char: %d\n", $1 , lines, chars);
							}
						}
;

// variable declaration
// node example for: int x;
// type 
// 	int 
// 	x
// print error message if the semicolon is missing
VarDecl:	TYPE VarDeclId SEMICOLON
					{
						/* create node for variable declaration*/
						$$ = AST_node("TYPE");
						$$->left = AST_node($1);
						$$->right = $2;

						// Symbol Table
						symTabAccess();
						/* check if variable is already declared in the same scope */
						int inSymTab;

						if (strcmp($2->nodeType, "ARR") == 0)
						{
							inSymTab = found($2->left->nodeType, top(theStack));
						}
						else{
							inSymTab = found($2->nodeType, top(theStack));
						}

						if (strcmp($2->nodeType, "ARR") == 0)
						{
							printf("looking for %s in symtab - found: %d \n", $2->left->nodeType, inSymTab);
						}
						else{
							printf("looking for %s in symtab - found: %d \n", $2->nodeType, inSymTab);
						}
						/* if variable has been declared, add them to the symbol table now */
						if (inSymTab == 0) 
						{
							if (strcmp($2->nodeType, "ARR") == 0){

								addItem($2->left->nodeType, "Var", $1, $2->right->nodeType, top(theStack), "", "");
							}
							else {
								addItem($2->nodeType, "Var", $1, "", top(theStack), "", "");
							}
						}
						/* if the vairiable has been declared, print SEMANTIC ERROR */
						else
						{
							if (strcmp($2->nodeType, "ARR") == 0)
							{
								printf("SEMANTIC ERROR: Var %s is already in the symbol table || Line: %d || Char: %d\n", $2->left->nodeType, lines, chars);
							}
							else{					
								printf("SEMANTIC ERROR: Var %s is already in the symbol table || Line: %d || Char: %d\n", $2->nodeType, lines, chars);
							}
						}
						/* show symbol table */
						showSymTable();
					}
				| TYPE VarDeclId 
					{
						printf("SYNTAX ERROR: Missing SEMICOLON || Line: %d || Char: %d\n", lines, chars);
					}
;

// allow multiple variables in function parameter
ParamDeclList:	ParamDeclListTail
							|	
								{
									$$ = AST_node("EMPTY PARAM");
								}
;

// grammar for function
// node example for: 
// void main()
//   {
//   int i;
// }
// FUNC
//    void
//    main
//       PARAM
//          EMPTY PARAM
//       BLOCK
//          TYPE
//             int
//             i

FunDecl:	TYPE ID LPAREN 
					{						
						// Symbol Table
						symTabAccess();
						/* check if function has been declared before */
						int inSymTab = found($2, top(theStack));
						printf("looking for %s in symtab - found: %d \n", $2, inSymTab);
						/* if function has not been declared */
						if (inSymTab == 0) 
						{
							/* add to symbol table */
							addItem($2, "Func", $1, "",top(theStack), "", "");
						}
						/* if function has been declared */
						else{
							/* print error message */
							printf("SEMANTIC ERROR: Var %s is already in the symbol table || Line: %d || Char: %d\n", $2, lines, chars);
						}
						/* print symbol table */
						showSymTable();
						/* change the current scope */
						push(theStack, $2);

						// IR code
						// Sum:
						char* line;
						char line1[500] = "";
						strcat(line1, $2);
						strcat(line1, ":");
						line = line1;
						writeIR(line1);

						// MIPS code
						fprintf(MIPS, "%s", $2);
						fprintf(MIPS, ":\n");
						if (strcmp($2, "main") != 0)
						{
							fprintf(MIPS, "addi $sp, $sp, -4\n");
							fprintf(MIPS, "sw $ra, 0($sp)\n");
						} else{
							emitStartTimer();
						}
					}
					ParamDeclList RPAREN Block
					{
						/* after the program finished parsing the function, we go back global scope*/
						printf("RECOGNIZED RULE: Function declaration || %s || Line: %d || Char: %d\n", $2, lines, chars);
						/* create ast node for function */
						$$ = AST_node("FUNC");
						$$->left = AST_node($1);
						$$->right = AST_node($2);
						$$->right->left = AST_node("PARAM");
						$$->right->left->left = $5;
						$$->right->right = AST_node("BLOCK");
						$$->right->right->left = $7;

						// IR code
						// jr $ra
						// .end Sum
						char* line;
						char line1[500] = "";
						strcat(line1, "jr $ra");
						line = line1;
						writeIR(line1);
						char line2[500] = "";
						strcat(line2, ".end ");
						strcat(line2, $2);
						line = line2;
						writeIR(line2);
						
						// MIPS code
						if (strcmp(top(theStack), "main") != 0){
							fprintf(MIPS, ".end %s\n", top(theStack));
						}
						pop(theStack);
						if_counter = 0;
						while_counter = 0;
					}
;

// allow multiple variables in function parameter
// handle the ast for multiple variables in function parameter
// node example for: 
// (int a[], int low, int high)
// PARAM
//          COMMA
//             TYPE
//                int
//                ARR
//                   a
//             COMMA
//                TYPE
//                   int
//                   low
//                TYPE
//                   int
//                   high
ParamDeclListTail:	ParamDecl
									| ParamDecl COMMA ParamDeclListTail
										{
											/* create node for parameters */
											$$ = AST_node("COMMA");
											$$->left = $1;
											$$->right = $3;
										}
;

// create ast node and grammar for the parameter variable declaration
ParamDecl:	TYPE ID
						{
							printf("RECOGNIZED RULE: Parameter declaration || %s || Line: %d || Char: %d\n", $2, lines, chars);
							$$ = AST_node("TYPE");
							$$->left = AST_node($1);
							$$->right = AST_node($2);
							// Symbol Table
							symTabAccess();
							/* check if varible has been declared */
							int inSymTab = found($2, top(theStack));
							printf("looking for %s in symtab - found: %d \n", $2, inSymTab);
							/* if variable hasn't been declared, add them to symbol table */
							if (inSymTab == 0) 
							{
								addItem($2, "Var", $1, "", top(theStack), top(theStack),"");
							}
							/* if variable has been declared, print error message*/
							else
								printf("SEMANTIC ERROR: Var %s is already in the symbol table || Line: %d || Char: %d", $2, lines, chars);
							showSymTable();
						}
					| TYPE ID LBRACK NUMBER RBRACK
						{
							/* ast node to array parameter varibles*/
							printf("RECOGNIZED RULE: Parameter array declaration || %s || Line: %d || Char: %d\n", $2, lines, chars);
							$$ = AST_node("TYPE");
							$$->left = AST_node($1);
							$$->right = AST_node("ARR");
							$$->right->left = AST_node($2);

							
							// Symbol Table
							symTabAccess();
							/* check if varible has been declared */
							int inSymTab = found($2, top(theStack));
							printf("looking for %s in symtab - found: %d \n", $2, inSymTab);
							/* if variable hasn't been declared, add them to symbol table */
							if (inSymTab == 0) 
							{
								char str[1000];
								sprintf(str, "%d", $4);
								addItem($2, "Var", $1, str, top(theStack), top(theStack),"");
							}
							/* if variable has been declared, print error message*/
							else
								printf("SEMANTIC ERROR: Var %s is already in the symbol table || Line: %d || Char: %d", $2, lines, chars);
							showSymTable();
						}
;

// this could be the grammar of the block of a function, a if statement, or a while statement
// node example for: 
// {int i;}
//       BLOCK
//          TYPE
//             int
//             i
Block:	LCURL InnerBlockList RCURL 
				{
					printf("RECOGNIZED RULE: Block || Line: %d || Char: %d\n", lines, chars);
					$$ = $2;
				}
			|	LCURL RCURL 
				{
					printf("SYNTAX ERROR: Empty Block || Line: %d || Char: %d\n", lines, chars);
					$$ = AST_node("");
				}
;

// allow all many VarDecl and Stmt to be included in our block
// all VarDecl and Stmt should be connected to each other via the mid pointer but are not under the hierarchy of each other
InnerBlockList:	InnerBlock InnerBlockList
								{
									$$ = $1;
									$$->mid = $2;
								}
							|	
								{
									$$ = AST_node("");
								}
;

// allow both VarDecl and Stmt in our block
InnerBlock:	VarDecl
					|	Stmt
;

// could be used in function call
// allow many variable input in the parameter of the function call using the COMMA node
ExprListTail:	Expr
						|	Expr COMMA ExprListTail
							{
								$$ = AST_node("COMMA");
								$$->left = $1;
								$$->right = $3;
							}
;

// so that we could many variable input in the parameter of the function call
ExprList:	ExprListTail
				|	
				{
					$$ = AST_node("EMPTY PARAM");
				}
;

// Primary is used in expression, could be id, number, array, function call, and so on
Primary:	ID
					{
						/* create ats node for ID */
						$$ = AST_node($1);

						// Symbol Table
						symTabAccess();
						/* check if id has been declared */
						int inSymTab = 0;
						struct stack_entry *entry; 
						/* if id has not been declared in the current scope, search in the previous scope */
						entry = theStack->head;
						while (entry != NULL){
							inSymTab = found($1, entry->data);
							if (inSymTab != 0){
								break;
							}
							entry = entry->next;
						}
						printf("looking for %s in symtab - found: %d \n", $1, inSymTab);
						/* if variable has not been declared */
						if (inSymTab == 0) 
						{
							printf("SEMANTIC ERROR: Varible %s was not declared || Line: %d || Char: %d\n", $1, lines, chars);
						}		
						/* IR code generation */
						strcpy($$->IRcode, $1);
					}
				|	NUMBER
					{
						/* node for number */
						char str[1000];
						sprintf(str, "%d", $1);
						$$ = AST_node(str);
						/* IR code generation */
						strcpy($$->IRcode, str);
					}
				|	CHACHA
					{
						/* node for character */
						$$ = AST_node($1);	
						/* IR code generation */
						strcpy($$->IRcode, $1);
					}
				|	STRING
					{
						/* node for string */
						$$ = AST_node($1);
						/* IR code generation */
						strcpy($$->IRcode, $1);
					}
				|	LPAREN Expr RPAREN
					{
						$$ = $2;
					}
				|	COMMA ID 
					{
						// MIPS code
						// push parameter onto the stack
						// loops throught all row in our table, looking for matching scope
						
						for(int i=0; i<symTabIndex; i++){
							char *ret;
							ret = strstr(symTabItems[i].scope,$2);
							if( ret ){
								char *reg = getRegister();
								// #start func call add, push onto stack
								// lw $t0, addhehe_f
								// addiu $sp, $sp, -4                      #move stack pointer
								// sw $t0, 0($sp)                          #save to stack
								fprintf(MIPS, "lw %s, %s_%s\naddiu $sp, $sp, -4\nsw %s, 0($sp)\n",reg, symTabItems[i].scope, symTabItems[i].itemName, reg);
								freeReg(reg);
							}
						}
					}
					LPAREN ExprList RPAREN
					{
						/* node for function call */
						$$ = AST_node($2);
						$$->left = $5;
						$$->right = AST_node("");
				
						// Symbol Table
						symTabAccess();
						/* check if function has been declared */
						int inSymTab = found($2, "global");
						printf("looking for %s in symtab - found: %d \n", $2, inSymTab);
						/* if function has not been declared, print error message */
						if (inSymTab == 0) 
						{
							printf("SEMANTIC ERROR: : Varible %s was not declared || Line: %d || Char: %d\n", $2, lines, chars);
						}
						/* get number of parameter in funciton */
						int numOfVar = numberOfVarInParameter($2);
						/* to check how many variable that user passed into the function call */
						struct AST* holder = $5;
						// check if type is void
						if (strcmp(getType($2, theStack), "void") == 0){
							printf("SEMANTIC ERROR: function call is used as an expression, the function must return a result || Line: %d || Char: %d\n", lines, chars);
						}

						// if function call has no varible in the parameter but function requires at least one 
						// if function requires just one varible in the parameter but the function call has more than 1 variable
						// if function requires no variable in the parameter but the function call has at least 1 variable
						// if function requires at least 2 in the parameter but the function call has less than 2 variables
						if ((numOfVar == 1 && strcmp(holder->nodeType, "COMMA") == 0) || (numOfVar == 0 && strcmp($5->nodeType, "EMPTY PARAM") != 0 || (numOfVar > 1 && strcmp(holder->nodeType, "COMMA") != 0))){
							printf("SEMANTIC ERROR: Parameter size for function %s is incorrect, expected %d variables || Line: %d || Char: %d\n", $2, numberOfVarInParameter($2), lines, chars);
						}
						/* if user did not pass any variable and function is not a void function */
						else if (strcmp($5->nodeType, "EMPTY PARAM") == 0){
							if (numOfVar != 0){
								printf("SEMANTIC ERROR: Parameter size for function %s is incorrect, expected %d variables || Line: %d || Char: %d\n", $2, numberOfVarInParameter($2), lines, chars);
							}
						}
						/* if function needs one variable in the parameter and function call has one variable in the parameter also */
						else if (strcmp(holder->nodeType, "COMMA") != 0 && strcmp(holder->nodeType, "EMPTY PARAM") != 0 && numOfVar == 1){
							char** funcPara = getVarInPara($2);
							/* check if the type is correct */
							if (strcmp(funcPara[0], getType($5->nodeType, theStack)) != 0){
								printf("SEMANTIC ERROR: Function call with incorrect argument type || Line: %d || Char: %d\n", lines, chars);
							}
						}
						else{
							struct AST* holder = $5;
							int index = 0;
							char** funcPara = getVarInPara($2);		
							/* get type in an array */
							/* check with type of function parameters */
							while (holder != NULL){					
								// check if variable is declared
								int inSymTab = 0;
								struct stack_entry *entry = malloc(sizeof *entry); 
								entry = theStack->head;
								while (entry != NULL){
									inSymTab = found(holder->left->nodeType, entry->data);
									if (inSymTab != 0){
										break;
									}
									if (strcmp(holder->right->nodeType, "COMMA") != 0){
										inSymTab = found(holder->left->nodeType, entry->data);
										if (inSymTab != 0){
											break;
										}
									}
									entry = entry->next;
								}
								// check if variable type is matched
								if (inSymTab == 1){			
									if (strcmp(funcPara[index], getType(holder->left->nodeType, theStack)) != 0){
										printf("SEMANTIC ERROR: Function call with incorrect argument type. Function asks for %s at index %d, function call uses %s %s || Line: %d || Char: %d\n", funcPara[index], index, getType(holder->left->nodeType, theStack), holder->left->nodeType, lines, chars);
										break;
									}
									index += 1;
									if (strcmp(holder->right->nodeType, "COMMA") == 0){
										holder = holder->right;
									}
									else{
										if (strcmp(funcPara[index], getType(holder->right->nodeType, theStack)) != 0){
											printf("SEMANTIC ERROR: Function call with incorrect argument type. Function asks for %s at index %d, function call uses %s %s || Line: %d || Char: %d\n", funcPara[index], index, getType(holder->right->nodeType, theStack),holder->right->nodeType, lines, chars);
										}
										if (index+1 != numberOfVarInParameter($2)){
											printf("SEMANTIC ERROR: Parameter size for function %s is incorrect, expected %d variables || Line: %d || Char: %d\n", $2, numberOfVarInParameter($2), lines, chars);
										}
										break;
									}
								}				
								else{
									break;
								}				
							}
						}

						showSymTable();
						

						// IR code
						int currentA = 0;
						if (strcmp(holder->nodeType, "COMMA") != 0 && strcmp(holder->nodeType, "EMPTY PARAM") != 0){
							// lw $a0, A
							char* line;
							char line1[500] = "";
							strcat(line1, "lw ");
							strcat(line1, "$a");
							char str[1000];
							sprintf(str, "%d", currentA);
							strcat(line1, str);
							strcat(line1, ", ");
							strcat(line1, holder->IRcode);
							line = line1;
							writeIR(line1);

							// MIPS code
							char * reg = getRegister();
							// la $a0, addhehe_f   
					
							char** funcParaName = getVarNameInPara($2);
							fprintf(MIPS, "la $a0, %s_%s\n", $2, funcParaName[currentA]);  
							
							if (strcmp(getExprType(holder->IRcode), "id") == 0){
          			// lw $t0, main_b                              #load variable(s) for use	
								char* scope = getScope(holder->IRcode, theStack);
								fprintf(MIPS, "lw %s, %s_%s\n", reg, scope, holder->IRcode);
							}
							else if (strcmp(getExprType(holder->IRcode), "int") == 0){
								// li $t0, 2
								fprintf(MIPS, "li %s, %s\n", reg, holder->IRcode);    
							}
							else{
								freeReg(reg);
								reg = holder->IRcode;			
							}
							// move $a1, $t0                               #set new value
    		      // sw $a1, 0($a0)        
							fprintf(MIPS, "move $a1, %s\nsw $a1, 0($a0)\n", reg);
							freeReg(reg);
						}
						else if (strcmp($5->nodeType, "EMPTY PARAM") != 0){
							while (holder != NULL){					
								// lw $a0, A
								char* line;
								char line1[500] = "";
								strcat(line1, "lw ");
								strcat(line1, "$a");
								char str[1000];
								sprintf(str, "%d", currentA);
								strcat(line1, str);
								strcat(line1, ", ");
								strcat(line1, holder->left->IRcode);
								line = line1;
								writeIR(line1);

								// MIPS code
								char * reg = getRegister();
								// la $a0, addhehe_f   
								char** funcParaName = getVarNameInPara($2);
								fprintf(MIPS, "la $a0, %s_%s\n", $2, funcParaName[currentA]);  
		
								if (strcmp(getExprType(holder->left->IRcode), "id") == 0){
									// lw $t0, main_b                              #load variable(s) for use	
									char* scope = getScope(holder->left->IRcode, theStack);
									fprintf(MIPS, "lw %s, %s_%s\n", reg, scope, holder->left->IRcode);
								}
								else if (strcmp(getExprType(holder->left->IRcode), "int") == 0){
									// li $t0, 2
									fprintf(MIPS, "li %s, %s\n", reg, holder->left->IRcode);    
								}
								else{
									freeReg(reg);
									reg = holder->left->IRcode;			
								}
								// move $a1, $t0                               #set new value
								// sw $a1, 0($a0)        
								fprintf(MIPS, "move $a1, %s\nsw $a1, 0($a0)\n", reg);
								freeReg(reg);
								currentA += 1;
								if (strcmp(holder->right->nodeType, "COMMA") == 0){
									holder = holder->right;
								}
								else{
									// lw $a0, A
									char* line;
									char line1[500] = "";
									strcat(line1, "lw ");
									strcat(line1, "$a");
									char str[1000];
									sprintf(str, "%d", currentA);
									strcat(line1, str);
									strcat(line1, ", ");
									strcat(line1, holder->right->IRcode);
									line = line1;
									writeIR(line1);
									// MIPS code
									char * reg = getRegister();
									// la $a0, addhehe_f   
									char** funcParaName = getVarNameInPara($2);
									fprintf(MIPS, "la $a0, %s_%s\n", $2, funcParaName[currentA]);  
									if (strcmp(getExprType(holder->right->IRcode), "id") == 0){
										// lw $t0, main_b                              #load variable(s) for use	
										char* scope = getScope(holder->right->IRcode, theStack);
										fprintf(MIPS, "lw %s, %s_%s\n", reg, scope, holder->right->IRcode);
									}
									else if (strcmp(getExprType(holder->right->IRcode), "int") == 0){
										// li $t0, 2
										fprintf(MIPS, "li %s, %s\n", reg, holder->right->IRcode);    
									}
									else{
										freeReg(reg);
										reg = holder->right->IRcode;			
									}
									// move $a1, $t0                               #set new value
									// sw $a1, 0($a0)        
									fprintf(MIPS, "move $a1, %s\nsw $a1, 0($a0)\n", reg);
									freeReg(reg);
									currentA += 1;
									break;
								}		
							}
						}
						// IR
						// jal Sum
						char* line;
						char line1[500] = "";
						strcat(line1, "jal ");
						strcat(line1, $2);
						line = line1;
						writeIR(line1);
						
						
						// MIPS
						//  jal addhehe                           #call function
						fprintf(MIPS, "jal %s\n", $2);

						// pop parameter onto the stack
						// loops throught all row in our table, looking for matching scope
						for(int i=symTabIndex-1; i>=0; i--){
							char *ret;
							ret = strstr(symTabItems[i].scope,$2);
							if( ret ){
								char * reg = getRegister();
								// lw $t0, 0($sp)                              #store in register
								// addiu $sp, $sp, 4                           #move stack pointer
								// la $a0, addhehe_f                           #access address
								// move $a1, $t0                               #set new value
								// sw $a1, 0($a0)  
								fprintf(MIPS, "lw %s, 0($sp)\naddiu $sp, $sp, 4\nla $a0, %s_%s\nmove $a1, %s\nsw $a1, 0($a0)\n", reg, symTabItems[i].scope, symTabItems[i].itemName, reg);
								freeReg(reg);
							}
						}
						strcpy($$->IRcode, "$v0");
					}
				|	ID LBRACK Expr RBRACK
					{
						/* node for array element */
						$$ = AST_node("ARR");
						$$->left = AST_node($1);
						$$->right = $3;
						/* if variable is not an array */
						if (!isArray($1, theStack)){
							printf("SEMANTIC ERROR: Variable must be an array variable || Line: %d || Char: %d\n", lines, chars);
						}

						/* check if $3 is an int */
						char exprType[50]; 
						/* get type for binop expression */
						if ((strcmp($3->nodeType, "!") == 0) || (strcmp($3->nodeType, "==") == 0) || (strcmp($3->nodeType, "!=") == 0) || (strcmp($3->nodeType, "<=") == 0) || (strcmp($3->nodeType, ">=") == 0) || (strcmp($3->nodeType, "&&") == 0) || (strcmp($3->nodeType, "||") == 0) || (strcmp($3->nodeType, "<") == 0) || (strcmp($3->nodeType, ">") == 0)){
							strcpy(exprType, "bool");
						}
						else if ((strcmp($3->nodeType, "+") == 0) || (strcmp($3->nodeType, "-") == 0) || (strcmp($3->nodeType, "*") == 0) || (strcmp($3->nodeType, "/") == 0)){
							strcpy(exprType, "int");
						}
						/* get type for array */
						else if ((strcmp($3->nodeType, "ARR") == 0)){			
							strcpy(exprType, getTypeForArr($3->left->nodeType, theStack));				
						}
						else{
							/* get type for id */
							regex_t reg;
							const char *regex="^[A-Za-z][A-Za-z0-9]*";
							int ret;
							char err[1024];
							ret = regcomp(&reg, regex, REG_EXTENDED);
							if (ret != 0) {
								regerror(ret, &reg, err, 1024);
								return 1;
							}
							int return_value;
							return_value = regexec(&reg, $3->nodeType , 0, NULL, 0);
							regfree(&reg);
							if (return_value == 0){
								strcpy(exprType, getType($3->nodeType, theStack));
							}
							else{
								/* get type for number */
								regex_t reg;
								const char *regex="^-?[0-9]+";
								int ret;
								char err[1024];
								//Read data into variable filecontent
								ret = regcomp(&reg, regex, REG_EXTENDED);
								if (ret != 0) {
									regerror(ret, &reg, err, 1024);
									return 1;
								}
								int return_value;
								return_value = regexec(&reg, $3->nodeType , 0, NULL, 0);
								regfree(&reg);
								if (return_value == 0){
									strcpy(exprType, "int");
								}
								else{
									/* get type for character */
									regex_t reg;
									const char *regex="'[a-zA-Z]'";
									int ret;
									char err[1024];
									ret = regcomp(&reg, regex, REG_EXTENDED);
									if (ret != 0) {
										regerror(ret, &reg, err, 1024);
										return 1;
									}
									int return_value;
									return_value = regexec(&reg, $3->nodeType , 0, NULL, 0);
									regfree(&reg);
									if (return_value == 0){
										strcpy(exprType, "char");
									}
									else{
										strcpy(exprType, ""); 
									}
								}
							}
						}
						/* if expr type is not int, print error message */
						if (strcmp(exprType, "int") != 0){
							printf("SEMANTIC ERROR: The type of expression must be int || Line: %d || Char: %d\n", lines, chars);
						}
						
						// IR code
						// char *reg = getRegister();
						// emitArray($3->IRcode, reg , $1);
						// strcpy($$->IRcode, reg);

						if (strcmp(top(theStack), "main") == 0){
							if (strcmp(getExprType($3->IRcode), "int") == 0){
								// add var onto the symbol table
								char varNameHolder[50];
								strcpy(varNameHolder, $1);
								strcat(varNameHolder, "[");
								strcat(varNameHolder, $3->IRcode);
								strcat(varNameHolder, "]");
								strcpy($$->IRcode, getValue(varNameHolder, theStack));
							}
							else if (strcmp(getExprType($3->IRcode), "id") == 0){
								// add var onto the symbol table
								char varNameHolder[50];
								strcpy(varNameHolder, $1);
								strcat(varNameHolder, "[");
								char * index = getValue($3->IRcode, theStack);
								strcat(varNameHolder, index);
								strcat(varNameHolder, "]");
								strcpy($$->IRcode, getValue(varNameHolder, theStack));												
							}
						}
						else{	
							char * reg = getRegister();
						

							if (strcmp(getExprType($3->IRcode), "int") == 0){
								// li $t0, 2
								fprintf(MIPS,"li %s, %s\n", reg, $3->IRcode);
							}
							else if (strcmp(getExprType($3->IRcode), "id") == 0){
								char* scope = getScope($3->IRcode, theStack);
								// lw $t0, addhehe_f
								fprintf(MIPS,"lw %s, %s_%s\n", reg, scope, $3->IRcode);
							}
							else{
								freeReg(reg);
								reg = $3->IRcode;
							}
							
							
							char * reg2 = getRegister();
							char* scope = getScope($1, theStack);
							// li $t2, 4                                   #4 bits per word
							// mult $t1, $t2                               #calculate bit-index
							// mflo $t2                                    #obtain bit-index
							// lw $t1, glob_X($t2)   							
							fprintf(MIPS,"li %s, 4\nmult %s, %s\nmflo %s\nlw %s, %s_%s(%s)\n", reg2, reg, reg2, reg2, reg, scope, $1, reg2);
							fprintf(IRcode," %s = %s[%s]\n", reg, $1, $3->IRcode); 
							freeReg(reg2);
							strcpy($$->IRcode, reg); 
							
						}
					}
;

// expression that we could include in our statement list
Expr:	Primary
		| READ LPAREN ID RPAREN SEMICOLON 
			{
				$$ = AST_node("READ");
				$$->left = AST_node($3);
				$$->right = AST_node("");
				printf("RECOGNIZED RULE: READ || %s || Line: %d || Char: %d\n", $3, lines, chars);
				if(strcmp(getType($3,theStack), "int") == 0){
					emitReadForInt($3, getScope($3, theStack));
				} else {
					printf("\n\nWARNING: MIPS not currently generating for char input!!!\n\n");
					emitReadForChar($3, getScope($3, theStack));
				}
			}
		| READ LPAREN RPAREN SEMICOLON
			{
				printf("SYNTAX ERROR: Missing ID in Input || Line: %d || Char: %d\n", lines, chars);
			}
		| READ LPAREN ID SEMICOLON
			{
				printf("SYNTAX ERROR: Missing RPAREN after ID || Line: %d || Char: %d\n", lines, chars);
			}
		| READ ID RPAREN SEMICOLON
			{
				printf("SYNTAX ERROR: Missing LPAREN before ID|| Line: %d || Char: %d\n", lines, chars);
			}
		| READ RPAREN ID RPAREN
			{
				printf("SYNTAX ERROR: Missing SEMICOLON || Line: %d || Char: %d\n", lines, chars);
			}
		|	UNARYOP Expr
		{
			/* node for !Expr */
			$$ = AST_node($1);
			$$->left = $2;

			/* check out code comments on "ID LBRACK Expr RBRACK" rule */
			char exprType[50]; 
			if ((strcmp($2->nodeType, "!") == 0) || (strcmp($2->nodeType, "==") == 0) || (strcmp($2->nodeType, "!=") == 0) || (strcmp($2->nodeType, "<=") == 0) || (strcmp($2->nodeType, ">=") == 0) || (strcmp($2->nodeType, "&&") == 0) || (strcmp($2->nodeType, "||") == 0) || (strcmp($2->nodeType, "<") == 0) || (strcmp($2->nodeType, ">") == 0)){
				strcpy(exprType, "bool");
			}
			else if ((strcmp($2->nodeType, "+") == 0) || (strcmp($2->nodeType, "-") == 0) || (strcmp($2->nodeType, "*") == 0) || (strcmp($2->nodeType, "/") == 0)){
				strcpy(exprType, "int");
			}
			else if ((strcmp($2->nodeType, "ARR") == 0)){			
				strcpy(exprType, getTypeForArr($2->left->nodeType, theStack));				
			}
			else{
				regex_t reg;
				const char *regex="^[A-Za-z][A-Za-z0-9]*";
				int ret;
				char err[1024];
				//Read data into variable filecontent
				ret = regcomp(&reg, regex, REG_EXTENDED);
				if (ret != 0) {
					regerror(ret, &reg, err, 1024);
					return 1;
				}
				int return_value;
				return_value = regexec(&reg, $2->nodeType , 0, NULL, 0);
				regfree(&reg);
				if (return_value == 0){
					strcpy(exprType, getType($2->nodeType, theStack));
				}
				else{
					regex_t reg;
					const char *regex="^-?[0-9]+";
					int ret;
					char err[1024];
					//Read data into variable filecontent
					ret = regcomp(&reg, regex, REG_EXTENDED);
					if (ret != 0) {
						regerror(ret, &reg, err, 1024);
						return 1;
					}
					int return_value;
					return_value = regexec(&reg, $2->nodeType , 0, NULL, 0);
					regfree(&reg);
					if (return_value == 0){
						strcpy(exprType, "int");
					}
					else{
						/* get type for character */
						regex_t reg;
						const char *regex="'[a-zA-Z]'";
						int ret;
						char err[1024];
						ret = regcomp(&reg, regex, REG_EXTENDED);
						if (ret != 0) {
							regerror(ret, &reg, err, 1024);
							return 1;
						}
						int return_value;
						return_value = regexec(&reg, $2->nodeType , 0, NULL, 0);
						regfree(&reg);
						if (return_value == 0){
							strcpy(exprType, "char");
						}
						else{
							strcpy(exprType, ""); 
						}
					}
				}
			}
			/* if the expr type is not a boolean, print error message */
			if (strcmp(exprType, "bool") != 0){
				printf("SEMANTIC ERROR: The type of expression must be bool || Line: %d || Char: %d\n", lines, chars);
			}


			/*IR code for UNARYOP*/
			
			regex_t reg;
			const char *regex="^[A-Za-z][A-Za-z0-9]*";
			int ret;
			char err[1024];
			//Read data into variable filecontent
			ret = regcomp(&reg, regex, REG_EXTENDED);
			if (ret != 0) {
				regerror(ret, &reg, err, 1024);
				return 1;
			}
			int return_value;
			return_value = regexec(&reg, $2->IRcode , 0, NULL, 0);
			regfree(&reg);
			// if $2->IRcode match the pattern
			if (return_value == 0){
				strcpy($$->IRcode, $2->IRcode);
				char* line;
				char line1[500] = "";
				strcat(line1, $$->IRcode);
				strcat(line1, " = ");
				strcat(line1, "NOT ");
				strcat(line1, $2->IRcode);
				line = line1;
				writeIR(line1);
			}
		}
		|	Expr BINOP Expr
		{
			/* node for binop */
			$$ = AST_node($2);
			$$->left = $1;
			$$->right = $3;
			
			/* check out code comments on "ID LBRACK Expr RBRACK" rule */
			char exprType[50]; 
			if ((strcmp($3->nodeType, "!") == 0) || (strcmp($3->nodeType, "==") == 0) || (strcmp($3->nodeType, "!=") == 0) || (strcmp($3->nodeType, "<=") == 0) || (strcmp($3->nodeType, ">=") == 0) || (strcmp($3->nodeType, "&&") == 0) || (strcmp($3->nodeType, "||") == 0) || (strcmp($3->nodeType, "<") == 0) || (strcmp($3->nodeType, ">") == 0)){
				strcpy(exprType, "bool");
			}
			else if ((strcmp($3->nodeType, "+") == 0) || (strcmp($3->nodeType, "-") == 0) || (strcmp($3->nodeType, "*") == 0) || (strcmp($3->nodeType, "/") == 0)){
				strcpy(exprType, "int");
			}
			else if ((strcmp($3->nodeType, "ARR") == 0)){			
				strcpy(exprType, getTypeForArr($3->left->nodeType, theStack));				
			}
			else{
				regex_t reg;
				const char *regex="^[A-Za-z][A-Za-z0-9]*"; 
				int ret;
				char err[1024];
				//Read data into variable filecontent
				ret = regcomp(&reg, regex, REG_EXTENDED);
				if (ret != 0) {
					regerror(ret, &reg, err, 1024);
					return 1;
				}
				int return_value;
				return_value = regexec(&reg, $3->nodeType , 0, NULL, 0);
				regfree(&reg);
				if (return_value == 0){
					strcpy(exprType, getType($3->nodeType, theStack));
				}
				else{
					regex_t reg;
					const char *regex="^-?[0-9]+";
					int ret;
					char err[1024];
					//Read data into variable filecontent
					ret = regcomp(&reg, regex, REG_EXTENDED);
					if (ret != 0) {
						regerror(ret, &reg, err, 1024);
						return 1;
					}
					int return_value;
					return_value = regexec(&reg, $3->nodeType , 0, NULL, 0);
					regfree(&reg);
					if (return_value == 0){
						strcpy(exprType, "int");
					}
					else{
						/* get type for character */
						regex_t reg;
						const char *regex="'[a-zA-Z]'";
						int ret;
						char err[1024];
						ret = regcomp(&reg, regex, REG_EXTENDED);
						if (ret != 0) {
							regerror(ret, &reg, err, 1024);
							return 1;
						}
						int return_value;
						return_value = regexec(&reg, $3->nodeType , 0, NULL, 0);
						regfree(&reg);
						if (return_value == 0){
							strcpy(exprType, "char");
						}
						else{
							strcpy(exprType, ""); 
						}
					}
				}
			}
			
			/* if binop if && or ||, expect boolean expr */
			if (strcmp($2, "&&") == 0 || strcmp($2, "||") == 0){
				if (strcmp(exprType, "bool") != 0){
					printf("SEMANTIC ERROR: The type of expression must be boolean || Line: %d || Char: %d\n", lines, chars);
				}
			}
			/*  if binop if not && and ||, expect int expr*/
			else{
				if (strcmp(exprType, "int") != 0){
					printf("SEMANTIC ERROR: The type of expression must be int || Line: %d || Char: %d\n", lines, chars);
				}
			}
			/* check out code comments on "ID LBRACK Expr RBRACK" rule */
			char exprType2[50];
			if ((strcmp($1->nodeType, "!") == 0) || (strcmp($1->nodeType, "==") == 0) || (strcmp($1->nodeType, "!=") == 0) || (strcmp($1->nodeType, "<=") == 0) || (strcmp($1->nodeType, ">=") == 0) || (strcmp($1->nodeType, "&&") == 0) || (strcmp($1->nodeType, "||") == 0) || (strcmp($1->nodeType, "<") == 0) || (strcmp($1->nodeType, ">") == 0)){
				strcpy(exprType2, "bool");
			}
			else if ((strcmp($1->nodeType, "+") == 0) || (strcmp($1->nodeType, "-") == 0) || (strcmp($1->nodeType, "*") == 0) || (strcmp($1->nodeType, "/") == 0)){
				strcpy(exprType2, "int");
			}
			else if ((strcmp($1->nodeType, "ARR") == 0)){			
				strcpy(exprType2, getTypeForArr($1->left->nodeType, theStack));				
			}
			else{
				regex_t reg;
				const char *regex="^[A-Za-z][A-Za-z0-9]*";
				int ret;
				char err[1024];
				//Read data into variable filecontent
				ret = regcomp(&reg, regex, REG_EXTENDED);
				if (ret != 0) {
					regerror(ret, &reg, err, 1024);
					return 1;
				}
				int return_value;
				return_value = regexec(&reg, $1->nodeType , 0, NULL, 0);
				regfree(&reg);
				if (return_value == 0){
					strcpy(exprType2, getType($1->nodeType, theStack));
				}
				else{
					regex_t reg;
					const char *regex="^-?[0-9]+";
					int ret;
					char err[1024];
					//Read data into variable filecontent
					ret = regcomp(&reg, regex, REG_EXTENDED);
					if (ret != 0) {
						regerror(ret, &reg, err, 1024);
						return 1;
					}
					int return_value;
					return_value = regexec(&reg, $1->nodeType , 0, NULL, 0);
					regfree(&reg);
					if (return_value == 0){
						strcpy(exprType2, "int");
					}
					else{
						/* get type for character */
						regex_t reg;
						const char *regex="'[a-zA-Z]'";
						int ret;
						char err[1024];
						ret = regcomp(&reg, regex, REG_EXTENDED);
						if (ret != 0) {
							regerror(ret, &reg, err, 1024);
							return 1;
						}
						int return_value;
						return_value = regexec(&reg, $1->nodeType , 0, NULL, 0);
						regfree(&reg);
						if (return_value == 0){
							strcpy(exprType2, "char");
						}
						else{
							strcpy(exprType2, ""); 
						}
					}
				}
			}
			/* do same thing with the $3 expr */
			if (strcmp($2, "&&") == 0 || strcmp($2, "||") == 0){
				if (strcmp(exprType2, "bool") != 0){
					printf("SEMANTIC ERROR: The type of expression must be boolean || Line: %d || Char: %d\n", lines, chars);
				}
			}
			else{
				if (strcmp(exprType2, "int") != 0){
					printf("SEMANTIC ERROR: The type of expression must be int || Line: %d || Char: %d\n", lines, chars);
				}
			}

	
			char * reg = getRegister();
			char * reg2 = getRegister();

			if (strcmp(getExprType($1->IRcode), "int") == 0){
				// li $t0, 2
				fprintf(MIPS,"li %s, %s\n", reg, $1->IRcode);
			}
			else if (strcmp(getExprType($1->IRcode), "id") == 0){
				char* scope = getScope($1->IRcode, theStack);
				// lw $t0, addhehe_f
				fprintf(MIPS,"lw %s, %s_%s\n", reg, scope, $1->IRcode);
			}
			else{
				freeReg(reg);
				reg = $1->IRcode;
			}

			if (strcmp(getExprType($3->IRcode), "int") == 0){
				// li $t0, 2
				fprintf(MIPS,"li %s, %s\n", reg2, $3->IRcode);
			}
			else if (strcmp(getExprType($3->IRcode), "id") == 0){
				char* scope = getScope($3->IRcode, theStack);
				// lw $t0, addhehe_f
				fprintf(MIPS,"lw %s, %s_%s\n", reg2, scope, $3->IRcode);
			}
			else{
				freeReg(reg2);
				reg2 = $3->IRcode;			
			}
			// char *ret;
			// ret = strstr("==",$2);
			if (strcmp("==",$2) == 0){
				// bne $t0, $t1, else_addNum_if_1
				fprintf(MIPS,"bne %s, %s, else_%s\n", reg, reg2, top(theStack));
			}
			else {
				// char *ret;
				// ret = strstr("!=",$2);
				if (strcmp("!=",$2) == 0){
					// beq $t0, $t1, else_addNum_if_1
					fprintf(MIPS,"beq %s, %s, else_%s\n", reg, reg2, top(theStack));
				}
				else {
					// char *ret;
					// ret = strstr("<=",$2);
					if (strcmp("<=",$2) == 0){
						// bgt $t0, $t1, else_addNum_if_1
						fprintf(MIPS,"bgt %s, %s, else_%s\n", reg, reg2, top(theStack));
					}
					else{
						// char *ret;
						// ret = strstr(">=",$2);
						if (strcmp(">=",$2) == 0){
							// blt $t0, $t1, else_addNum_if_1
							fprintf(MIPS,"blt %s, %s, else_%s\n", reg, reg2, top(theStack));
						}
						else{
							// char *ret;
							// ret = strstr("<",$2);
							if (strcmp("<",$2) == 0){
								// bge $t0, $t1, else_addNum_if_1
								fprintf(MIPS,"bge %s, %s, else_%s\n", reg, reg2, top(theStack));
							}
							else{
								// char *ret;
								// ret = strstr(">",$2);
								if (strcmp(">",$2) == 0){
									// ble $t0, $t1, else_addNum_if_1
									fprintf(MIPS,"ble %s, %s, else_%s\n", reg, reg2, top(theStack));
								}
							}
						}
					}
				}
			}
			freeReg(reg);
			freeReg(reg2);
			strcpy($$->IRcode, reg); 
			fprintf(IRcode," %s = %s %s %s\n", reg, $1->IRcode, $2, $3->IRcode);
		}
		|	Expr '+' Expr
			{
				/* node for + op */
				$$ = AST_node("+");
				$$->left = $1;
				$$->right = $3;

				struct AST* node = $1;
				/* check out code comments on "ID LBRACK Expr RBRACK" rule */
				char exprType[50]; 
				if ((strcmp(node->nodeType, "!") == 0) || (strcmp(node->nodeType, "==") == 0) || (strcmp(node->nodeType, "!=") == 0) || (strcmp(node->nodeType, "<=") == 0) || (strcmp(node->nodeType, ">=") == 0) || (strcmp(node->nodeType, "&&") == 0) || (strcmp(node->nodeType, "||") == 0) || (strcmp(node->nodeType, "<") == 0) || (strcmp(node->nodeType, ">") == 0)){
					strcpy(exprType, "bool");
				}
				else if ((strcmp(node->nodeType, "+") == 0) || (strcmp(node->nodeType, "-") == 0) || (strcmp(node->nodeType, "*") == 0) || (strcmp(node->nodeType, "/") == 0)){
					strcpy(exprType, "int");
				}
				else if ((strcmp(node->nodeType, "ARR") == 0)){			
					strcpy(exprType, getTypeForArr(node->left->nodeType, theStack));				
				}
				else{
					regex_t reg;
					const char *regex="^[A-Za-z][A-Za-z0-9]*";
					int ret;
					char err[1024];
					//Read data into variable filecontent
					ret = regcomp(&reg, regex, REG_EXTENDED);
					if (ret != 0) {
						regerror(ret, &reg, err, 1024);
						return 1;
					}
					int return_value;
					return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
					regfree(&reg);
					if (return_value == 0){
						strcpy(exprType, getType(node->nodeType, theStack));
					}
					else{
						regex_t reg;
						const char *regex="^-?[0-9]+";
						int ret;
						char err[1024];
						//Read data into variable filecontent
						ret = regcomp(&reg, regex, REG_EXTENDED);
						if (ret != 0) {
							regerror(ret, &reg, err, 1024);
							return 1;
						}
						int return_value;
						return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
						regfree(&reg);
						if (return_value == 0){
							strcpy(exprType, "int");
						}
						else{
              regex_t reg;
              const char *regex="'[a-zA-Z]'";
              int ret;
              char err[1024];
              //Read data into variable filecontent
              ret = regcomp(&reg, regex, REG_EXTENDED);
              if (ret != 0) {
                regerror(ret, &reg, err, 1024);
                return 1;
              }
              int return_value;
              return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
              regfree(&reg);
              if (return_value == 0){
                strcpy(exprType, "char");
              }
              else{
                strcpy(exprType, ""); 
              }
            }
          }
        }
				/* if expr type is not int, print error message */
				if (strcmp(exprType, "int") != 0){
					printf("SEMANTIC ERROR: The type of expression must be int || Line: %d || Char: %d\n", lines, chars);
				}				
				
				node = $3;
				/* check out code comments on "ID LBRACK Expr RBRACK" rule */
				if ((strcmp(node->nodeType, "!") == 0) || (strcmp(node->nodeType, "==") == 0) || (strcmp(node->nodeType, "!=") == 0) || (strcmp(node->nodeType, "<=") == 0) || (strcmp(node->nodeType, ">=") == 0) || (strcmp(node->nodeType, "&&") == 0) || (strcmp(node->nodeType, "||") == 0) || (strcmp(node->nodeType, "<") == 0) || (strcmp(node->nodeType, ">") == 0)){
					strcpy(exprType, "bool");
				}
				else if ((strcmp(node->nodeType, "+") == 0) || (strcmp(node->nodeType, "-") == 0) || (strcmp(node->nodeType, "*") == 0) || (strcmp(node->nodeType, "/") == 0)){
					strcpy(exprType, "int");
				}
				else if ((strcmp(node->nodeType, "ARR") == 0)){			
					strcpy(exprType, getTypeForArr(node->left->nodeType, theStack));				
				}
				else{
					regex_t reg;
					const char *regex="^[A-Za-z][A-Za-z0-9]*";
					int ret;
					char err[1024];
					//Read data into variable filecontent
					ret = regcomp(&reg, regex, REG_EXTENDED);
					if (ret != 0) {
						regerror(ret, &reg, err, 1024);
						return 1;
					}
					int return_value;
					return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
					regfree(&reg);
					if (return_value == 0){
						strcpy(exprType, getType(node->nodeType, theStack));
					}
					else{
						regex_t reg;
						const char *regex="^-?[0-9]+";
						int ret;
						char err[1024];
						//Read data into variable filecontent
						ret = regcomp(&reg, regex, REG_EXTENDED);
						if (ret != 0) {
							regerror(ret, &reg, err, 1024);
							return 1;
						}
						int return_value;
						return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
						regfree(&reg);
						if (return_value == 0){
							strcpy(exprType, "int");
						}
						else{
              regex_t reg;
              const char *regex="'[a-zA-Z]'";
              int ret;
              char err[1024];
              //Read data into variable filecontent
              ret = regcomp(&reg, regex, REG_EXTENDED);
              if (ret != 0) {
                regerror(ret, &reg, err, 1024);
                return 1;
              }
              int return_value;
              return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
              regfree(&reg);
              if (return_value == 0){
                strcpy(exprType, "char");
              }
              else{
                strcpy(exprType, ""); 
              }
            }
          }
        }
				/* if expr type is not int, print error message */
				if (strcmp(exprType, "int") != 0){
					printf("SEMANTIC ERROR: The type of expression must be int || Line: %d || Char: %d\n", lines, chars);
				}		




				// /* IR code generation */
				
				if (strcmp(top(theStack), "main") == 0){

					regex_t reg;
					const char *regex="^-?[0-9]+";
					int ret;
					char err[1024];
					//Read data into variable filecontent
					ret = regcomp(&reg, regex, REG_EXTENDED);
					if (ret != 0) {
						regerror(ret, &reg, err, 1024);
						return 1;
					}
					int return_value;
					return_value = regexec(&reg, $1->IRcode , 0, NULL, 0);
					regfree(&reg);
					
					regex_t reg2;
					const char *regex2="^-?[0-9]+";
					int ret2;
					char err2[1024];
					//Read data into variable filecontent
					ret2 = regcomp(&reg2, regex2, REG_EXTENDED);
					if (ret2 != 0) {
						regerror(ret2, &reg2, err2, 1024);
						return 1;
					}
					int return_value2;
					return_value2 = regexec(&reg2, $3->IRcode , 0, NULL, 0);
					regfree(&reg2);

					if (return_value == 0 && return_value2 == 0){
						float left;
						sscanf($1->IRcode, "%f", &left);
						float right;
						sscanf($3->IRcode, "%f", &right);
						float ans = left + right;
						int int_ans = (int)ans;					
						sprintf($$->IRcode, "%d", int_ans);
					}
					else if (return_value != 0 && return_value2 == 0){
						float left;
						char value[50];
						strcpy(value, getValue($1->IRcode, theStack));
						sscanf(value, "%f", &left);
						float right;
						sscanf($3->IRcode, "%f", &right);
						float ans = left + right;
						int int_ans = (int)ans;			
						sprintf($$->IRcode, "%d", int_ans);
					}
					else if (return_value == 0 && return_value2 != 0){
						float left;
						sscanf($1->IRcode, "%f", &left);
						float right;
						char value[50];
						strcpy(value, getValue($3->IRcode, theStack));
						sscanf(value, "%f", &right);
						float ans = left + right;
						int int_ans = (int)ans;					
						sprintf($$->IRcode, "%d", int_ans);
					}
					else if (return_value != 0 && return_value2 != 0){
						float left;
						char value[50];
						strcpy(value, getValue($1->IRcode, theStack));
						sscanf(value, "%f", &left);
						float right;
						char value1[50];
						strcpy(value1, getValue($3->IRcode, theStack));
						sscanf(value1, "%f", &right);
						float ans = left + right;
						int int_ans = (int)ans;					
						sprintf($$->IRcode, "%d", int_ans);
					}
				}
				else{
					char * reg = getRegister();
					char * reg2 = getRegister();
					
					if (strcmp(getExprType($1->IRcode), "int") == 0){
						if (strcmp($1->IRcode, "0") != 0){
							// li $t0, 2
							fprintf(MIPS,"li %s, %s\n", reg, $1->IRcode);
						}						
						else{
							freeReg(reg);
							reg = "";
						}
					}
					else if (strcmp(getExprType($1->IRcode), "id") == 0){
						char* scope = getScope($1->IRcode, theStack);
						// lw $t0, addhehe_f
						fprintf(MIPS,"lw %s, %s_%s\n", reg, scope, $1->IRcode);
					}
					else{
						freeReg(reg);
						reg = $1->IRcode;
					}

					if (strcmp(getExprType($3->IRcode), "int") == 0){
						if (strcmp($3->IRcode, "0") != 0){
						// li $t0, 2
						fprintf(MIPS,"li %s, %s\n", reg2, $3->IRcode);
						}
						else{
							freeReg(reg2);
							reg2 = "";
						}
					}
					else if (strcmp(getExprType($3->IRcode), "id") == 0){
						char* scope = getScope($3->IRcode, theStack);
						// lw $t0, addhehe_f
						fprintf(MIPS,"lw %s, %s_%s\n", reg2, scope, $3->IRcode);
					}
					else{
						freeReg(reg2);
						reg2 = $3->IRcode;			
					}

					// add $t0, $t0, $t1
					if (strcmp(reg, "") != 0 && strcmp(reg2, "") != 0)
					{
						fprintf(MIPS,"add %s, %s, %s\n", reg, reg, reg2);
						freeReg(reg2);
						strcpy($$->IRcode, reg); 
						fprintf(IRcode," %s = %s + %s\n", reg, $1->IRcode, $3->IRcode);
					}
					else if (strcmp(reg, "") == 0 && strcmp(reg2, "") != 0){
						freeReg(reg);
						strcpy($$->IRcode, reg2); 
					}
					else if (strcmp(reg, "") != 0 && strcmp(reg2, "") == 0){
						freeReg(reg2);
						strcpy($$->IRcode, reg); 
					}
					else{
						// move $t0, $zero 
						reg = getRegister();
						fprintf(MIPS,"move %s, $zero\n", reg);						
						strcpy($$->IRcode, reg); 
					}
				}
			}
		|	Expr '-' Expr
			{
				/* node for - op */
				$$ = AST_node("-");
				$$->left = $1;
				$$->right = $3;
				
				/* check out code comments on "ID LBRACK Expr RBRACK" rule */
				struct AST* node = $1;
				char exprType[50]; 
				if ((strcmp(node->nodeType, "!") == 0) || (strcmp(node->nodeType, "==") == 0) || (strcmp(node->nodeType, "!=") == 0) || (strcmp(node->nodeType, "<=") == 0) || (strcmp(node->nodeType, ">=") == 0) || (strcmp(node->nodeType, "&&") == 0) || (strcmp(node->nodeType, "||") == 0) || (strcmp(node->nodeType, "<") == 0) || (strcmp(node->nodeType, ">") == 0)){
					strcpy(exprType, "bool");
				}
				else if ((strcmp(node->nodeType, "+") == 0) || (strcmp(node->nodeType, "-") == 0) || (strcmp(node->nodeType, "*") == 0) || (strcmp(node->nodeType, "/") == 0)){
					strcpy(exprType, "int");
				}
				else if ((strcmp(node->nodeType, "ARR") == 0)){			
					strcpy(exprType, getTypeForArr(node->left->nodeType, theStack));				
				}
				else{
					regex_t reg;
					const char *regex="^[A-Za-z][A-Za-z0-9]*";
					int ret;
					char err[1024];
					//Read data into variable filecontent
					ret = regcomp(&reg, regex, REG_EXTENDED);
					if (ret != 0) {
						regerror(ret, &reg, err, 1024);
						return 1;
					}
					int return_value;
					return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
					regfree(&reg);
					if (return_value == 0){
						strcpy(exprType, getType(node->nodeType, theStack));
					}
					else{
						regex_t reg;
						const char *regex="^-?[0-9]+";
						int ret;
						char err[1024];
						//Read data into variable filecontent
						ret = regcomp(&reg, regex, REG_EXTENDED);
						if (ret != 0) {
							regerror(ret, &reg, err, 1024);
							return 1;
						}
						int return_value;
						return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
						regfree(&reg);
						if (return_value == 0){
							strcpy(exprType, "int");
						}
						else{
              regex_t reg;
              const char *regex="'[a-zA-Z]'";
              int ret;
              char err[1024];
              //Read data into variable filecontent
              ret = regcomp(&reg, regex, REG_EXTENDED);
              if (ret != 0) {
                regerror(ret, &reg, err, 1024);
                return 1;
              }
              int return_value;
              return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
              regfree(&reg);
              if (return_value == 0){
                strcpy(exprType, "char");
              }
              else{
                strcpy(exprType, ""); 
              }
            }
          }
        }
				/* if expr type is not int, print error type */
				if (strcmp(exprType, "int") != 0){
					printf("SEMANTIC ERROR: The type of expression must be int || Line: %d || Char: %d\n", lines, chars);
				}				
				/* check out code comments on "ID LBRACK Expr RBRACK" rule */
				node = $3;
				if ((strcmp(node->nodeType, "!") == 0) || (strcmp(node->nodeType, "==") == 0) || (strcmp(node->nodeType, "!=") == 0) || (strcmp(node->nodeType, "<=") == 0) || (strcmp(node->nodeType, ">=") == 0) || (strcmp(node->nodeType, "&&") == 0) || (strcmp(node->nodeType, "||") == 0) || (strcmp(node->nodeType, "<") == 0) || (strcmp(node->nodeType, ">") == 0)){
					strcpy(exprType, "bool");
				}
				else if ((strcmp(node->nodeType, "+") == 0) || (strcmp(node->nodeType, "-") == 0) || (strcmp(node->nodeType, "*") == 0) || (strcmp(node->nodeType, "/") == 0)){
					strcpy(exprType, "int");
				}
				else if ((strcmp(node->nodeType, "ARR") == 0)){			
					strcpy(exprType, getTypeForArr(node->left->nodeType, theStack));				
				}
				else{
					regex_t reg;
					const char *regex="^[A-Za-z][A-Za-z0-9]*";
					int ret;
					char err[1024];
					//Read data into variable filecontent
					ret = regcomp(&reg, regex, REG_EXTENDED);
					if (ret != 0) {
						regerror(ret, &reg, err, 1024);
						return 1;
					}
					int return_value;
					return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
					regfree(&reg);
					if (return_value == 0){
						strcpy(exprType, getType(node->nodeType, theStack));
					}
					else{
						regex_t reg;
						const char *regex="^-?[0-9]+";
						int ret;
						char err[1024];
						//Read data into variable filecontent
						ret = regcomp(&reg, regex, REG_EXTENDED);
						if (ret != 0) {
							regerror(ret, &reg, err, 1024);
							return 1;
						}
						int return_value;
						return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
						regfree(&reg);
						if (return_value == 0){
							strcpy(exprType, "int");
						}
						else{
              regex_t reg;
              const char *regex="'[a-zA-Z]'";
              int ret;
              char err[1024];
              //Read data into variable filecontent
              ret = regcomp(&reg, regex, REG_EXTENDED);
              if (ret != 0) {
                regerror(ret, &reg, err, 1024);
                return 1;
              }
              int return_value;
              return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
              regfree(&reg);
              if (return_value == 0){
                strcpy(exprType, "char");
              }
              else{
                strcpy(exprType, ""); 
              }
            }
          }
        }
				/* if expr type is not int, print error message */
				if (strcmp(exprType, "int") != 0){
					printf("SEMANTIC ERROR: The type of expression must be int || Line: %d || Char: %d\n", lines, chars);
				}


				// /* IR code generation */
				
				if (strcmp(top(theStack), "main") == 0){
					regex_t reg;
					const char *regex="^-?[0-9]+";
					int ret;
					char err[1024];
					//Read data into variable filecontent
					ret = regcomp(&reg, regex, REG_EXTENDED);
					if (ret != 0) {
						regerror(ret, &reg, err, 1024);
						return 1;
					}
					int return_value;
					return_value = regexec(&reg, $1->IRcode , 0, NULL, 0);
					regfree(&reg);
					
					regex_t reg2;
					const char *regex2="^-?[0-9]+";
					int ret2;
					char err2[1024];
					//Read data into variable filecontent
					ret2 = regcomp(&reg2, regex2, REG_EXTENDED);
					if (ret2 != 0) {
						regerror(ret2, &reg2, err2, 1024);
						return 1;
					}
					int return_value2;
					return_value2 = regexec(&reg2, $3->IRcode , 0, NULL, 0);
					regfree(&reg2);

					if (return_value == 0 && return_value2 == 0){
						float left;
						sscanf($1->IRcode, "%f", &left);
						float right;
						sscanf($3->IRcode, "%f", &right);
						float ans = left - right;
						int int_ans = (int)ans;					
						sprintf($$->IRcode, "%d", int_ans);
					}
					else if (return_value != 0 && return_value2 == 0){
						float left;
						char value[50];
						strcpy(value, getValue($1->IRcode, theStack));
						sscanf(value, "%f", &left);
						float right;
						sscanf($3->IRcode, "%f", &right);
						float ans = left - right;
						int int_ans = (int)ans;			
						sprintf($$->IRcode, "%d", int_ans);
					}
					else if (return_value == 0 && return_value2 != 0){
						float left;
						sscanf($1->IRcode, "%f", &left);
						float right;
						char value[50];
						strcpy(value, getValue($3->IRcode, theStack));
						sscanf(value, "%f", &right);
						float ans = left - right;
						int int_ans = (int)ans;					
						sprintf($$->IRcode, "%d", int_ans);
					}
					else if (return_value != 0 && return_value2 != 0){
						float left;
						char value[50];
						strcpy(value, getValue($1->IRcode, theStack));
						sscanf(value, "%f", &left);
						float right;
						char value1[50];
						strcpy(value1, getValue($3->IRcode, theStack));
						sscanf(value1, "%f", &right);
						float ans = left - right;
						int int_ans = (int)ans;					
						sprintf($$->IRcode, "%d", int_ans);
					}
				}
				else{
					char * reg = getRegister();
					char * reg2 = getRegister();
					if (strcmp($1->IRcode, $3->IRcode) == 0){
						freeReg(reg2);
						strcpy($$->IRcode, reg);
						fprintf(MIPS,"move %s, $zero\n", reg);						
						strcpy($$->IRcode, reg); 
					}
					else{
						if (strcmp(getExprType($1->IRcode), "int") == 0){
							// li $t0, 2
							fprintf(MIPS,"li %s, %s\n", reg, $1->IRcode);
						}
						else if (strcmp(getExprType($1->IRcode), "id") == 0){
							char* scope = getScope($1->IRcode, theStack);
							// lw $t0, addhehe_f
							fprintf(MIPS,"lw %s, %s_%s\n", reg, scope, $1->IRcode);
						}
						else{
							freeReg(reg);
							reg = $1->IRcode;
						}

						if (strcmp(getExprType($3->IRcode), "int") == 0){
							// li $t0, 2
							fprintf(MIPS,"li %s, %s\n", reg2, $3->IRcode);
						}
						else if (strcmp(getExprType($3->IRcode), "id") == 0){
							char* scope = getScope($3->IRcode, theStack);
							// lw $t0, addhehe_f
							fprintf(MIPS,"lw %s, %s_%s\n", reg2, scope, $3->IRcode);
						}
						else{
							freeReg(reg2);
							reg2 = $3->IRcode;			
						}

						// sub $t0, $t0, $t1
						fprintf(MIPS,"sub %s, %s, %s\n", reg, reg, reg2);
						freeReg(reg2);
						strcpy($$->IRcode, reg); 
						fprintf(IRcode," %s = %s - %s\n", reg, $1->IRcode, $3->IRcode);
					}
				}
			}		
		|	Expr '*' Expr
			{
				/* node for * op */
				$$ = AST_node("*");
				$$->left = $1;
				$$->right = $3;
				
				/* check out code comments on "ID LBRACK Expr RBRACK" rule */
				struct AST* node = $1;
				char exprType[50]; 
				if ((strcmp(node->nodeType, "!") == 0) || (strcmp(node->nodeType, "==") == 0) || (strcmp(node->nodeType, "!=") == 0) || (strcmp(node->nodeType, "<=") == 0) || (strcmp(node->nodeType, ">=") == 0) || (strcmp(node->nodeType, "&&") == 0) || (strcmp(node->nodeType, "||") == 0) || (strcmp(node->nodeType, "<") == 0) || (strcmp(node->nodeType, ">") == 0)){
					strcpy(exprType, "bool");
				}
				else if ((strcmp(node->nodeType, "+") == 0) || (strcmp(node->nodeType, "-") == 0) || (strcmp(node->nodeType, "*") == 0) || (strcmp(node->nodeType, "/") == 0)){
					strcpy(exprType, "int");
				}
				else if ((strcmp(node->nodeType, "ARR") == 0)){			
					strcpy(exprType, getTypeForArr(node->left->nodeType, theStack));				
				}
				else{
					regex_t reg;
					const char *regex="^[A-Za-z][A-Za-z0-9]*";
					int ret;
					char err[1024];
					//Read data into variable filecontent
					ret = regcomp(&reg, regex, REG_EXTENDED);
					if (ret != 0) {
						regerror(ret, &reg, err, 1024);
						return 1;
					}
					int return_value;
					return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
					regfree(&reg);
					if (return_value == 0){
						strcpy(exprType, getType(node->nodeType, theStack));
					}
					else{
						regex_t reg;
						const char *regex="^-?[0-9]+";
						int ret;
						char err[1024];
						//Read data into variable filecontent
						ret = regcomp(&reg, regex, REG_EXTENDED);
						if (ret != 0) {
							regerror(ret, &reg, err, 1024);
							return 1;
						}
						int return_value;
						return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
						regfree(&reg);
						if (return_value == 0){
							strcpy(exprType, "int");
						}
						else{
              regex_t reg;
              const char *regex="'[a-zA-Z]'";
              int ret;
              char err[1024];
              //Read data into variable filecontent
              ret = regcomp(&reg, regex, REG_EXTENDED);
              if (ret != 0) {
                regerror(ret, &reg, err, 1024);
                return 1;
              }
              int return_value;
              return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
              regfree(&reg);
              if (return_value == 0){
                strcpy(exprType, "char");
              }
              else{
                strcpy(exprType, ""); 
              }
            }
          }
        }
				if (strcmp(exprType, "int") != 0){
					printf("SEMANTIC ERROR: The type of expression must be int || Line: %d || Char: %d\n", lines, chars);
				}				
				/* check out code comments on "ID LBRACK Expr RBRACK" rule */
				node = $3;
				if ((strcmp(node->nodeType, "!") == 0) || (strcmp(node->nodeType, "==") == 0) || (strcmp(node->nodeType, "!=") == 0) || (strcmp(node->nodeType, "<=") == 0) || (strcmp(node->nodeType, ">=") == 0) || (strcmp(node->nodeType, "&&") == 0) || (strcmp(node->nodeType, "||") == 0) || (strcmp(node->nodeType, "<") == 0) || (strcmp(node->nodeType, ">") == 0)){
					strcpy(exprType, "bool");
				}
				else if ((strcmp(node->nodeType, "+") == 0) || (strcmp(node->nodeType, "-") == 0) || (strcmp(node->nodeType, "*") == 0) || (strcmp(node->nodeType, "/") == 0)){
					strcpy(exprType, "int");
				}
				else if ((strcmp(node->nodeType, "ARR") == 0)){			
					strcpy(exprType, getTypeForArr(node->left->nodeType, theStack));				
				}
				else{
					regex_t reg;
					const char *regex="^[A-Za-z][A-Za-z0-9]*";
					int ret;
					char err[1024];
					//Read data into variable filecontent
					ret = regcomp(&reg, regex, REG_EXTENDED);
					if (ret != 0) {
						regerror(ret, &reg, err, 1024);
						return 1;
					}
					int return_value;
					return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
					regfree(&reg);
					if (return_value == 0){
						strcpy(exprType, getType(node->nodeType, theStack));
					}
					else{
						regex_t reg;
						const char *regex="^-?[0-9]+";
						int ret;
						char err[1024];
						//Read data into variable filecontent
						ret = regcomp(&reg, regex, REG_EXTENDED);
						if (ret != 0) {
							regerror(ret, &reg, err, 1024);
							return 1;
						}
						int return_value;
						return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
						regfree(&reg);
						if (return_value == 0){
							strcpy(exprType, "int");
						}
						else{
              regex_t reg;
              const char *regex="'[a-zA-Z]'";
              int ret;
              char err[1024];
              //Read data into variable filecontent
              ret = regcomp(&reg, regex, REG_EXTENDED);
              if (ret != 0) {
                regerror(ret, &reg, err, 1024);
                return 1;
              }
              int return_value;
              return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
              regfree(&reg);
              if (return_value == 0){
                strcpy(exprType, "char");
              }
              else{
                strcpy(exprType, ""); 
              }
            }
          }
        }
				if (strcmp(exprType, "int") != 0){
					printf("SEMANTIC ERROR: The type of expression must be int || Line: %d || Char: %d\n", lines, chars);
				}	


				// /* IR code generation */

				if (strcmp(top(theStack), "main") == 0){
					regex_t reg;
					const char *regex="^-?[0-9]+";
					int ret;
					char err[1024];
					//Read data into variable filecontent
					ret = regcomp(&reg, regex, REG_EXTENDED);
					if (ret != 0) {
						regerror(ret, &reg, err, 1024);
						return 1;
					}
					int return_value;
					return_value = regexec(&reg, $1->IRcode , 0, NULL, 0);
					regfree(&reg);
					
					regex_t reg2;
					const char *regex2="^-?[0-9]+";
					int ret2;
					char err2[1024];
					//Read data into variable filecontent
					ret2 = regcomp(&reg2, regex2, REG_EXTENDED);
					if (ret2 != 0) {
						regerror(ret2, &reg2, err2, 1024);
						return 1;
					}
					int return_value2;
					return_value2 = regexec(&reg2, $3->IRcode , 0, NULL, 0);
					regfree(&reg2);

					if (return_value == 0 && return_value2 == 0){
						float left;
						sscanf($1->IRcode, "%f", &left);
						float right;
						sscanf($3->IRcode, "%f", &right);
						float ans = left * right;
						int int_ans = (int)ans;					
						sprintf($$->IRcode, "%d", int_ans);
					}
					else if (return_value != 0 && return_value2 == 0){
						float left;
						char value[50];
						strcpy(value, getValue($1->IRcode, theStack));
						sscanf(value, "%f", &left);
						float right;
						sscanf($3->IRcode, "%f", &right);
						float ans = left * right;
						int int_ans = (int)ans;			
						sprintf($$->IRcode, "%d", int_ans);
					}
					else if (return_value == 0 && return_value2 != 0){
						float left;
						sscanf($1->IRcode, "%f", &left);
						float right;
						char value[50];
						strcpy(value, getValue($3->IRcode, theStack));
						sscanf(value, "%f", &right);
						float ans = left * right;
						int int_ans = (int)ans;					
						sprintf($$->IRcode, "%d", int_ans);
					}
					else if (return_value != 0 && return_value2 != 0){
						float left;
						char value[50];
						strcpy(value, getValue($1->IRcode, theStack));
						sscanf(value, "%f", &left);
						float right;
						char value1[50];
						strcpy(value1, getValue($3->IRcode, theStack));
						sscanf(value1, "%f", &right);
						float ans = left * right;
						int int_ans = (int)ans;					
						sprintf($$->IRcode, "%d", int_ans);
					}
				}
				else{
					char * reg = getRegister();
					char * reg2 = getRegister();

					if (strcmp(getExprType($1->IRcode), "int") == 0){
						if (strcmp($1->IRcode, "1") != 0){
							// li $t0, 2
							fprintf(MIPS,"li %s, %s\n", reg, $1->IRcode);
						}
						else{
							freeReg(reg);
							reg = "";
						}
					}
					else if (strcmp(getExprType($1->IRcode), "id") == 0){
						char* scope = getScope($1->IRcode, theStack);
						// lw $t0, addhehe_f
						fprintf(MIPS,"lw %s, %s_%s\n", reg, scope, $1->IRcode);
					}
					else{
						freeReg(reg);
						reg = $1->IRcode;
					}

					if (strcmp(getExprType($3->IRcode), "int") == 0){
						if (strcmp($3->IRcode, "1") != 0){
							// li $t0, 2
							fprintf(MIPS,"li %s, %s\n", reg2, $3->IRcode);
						}
						else{
							freeReg(reg2);
							reg2 = "";
						}
					}
					else if (strcmp(getExprType($3->IRcode), "id") == 0){
						char* scope = getScope($3->IRcode, theStack);
						// lw $t0, addhehe_f
						fprintf(MIPS,"lw %s, %s_%s\n", reg2, scope, $3->IRcode);
					}
					else{
						freeReg(reg2);
						reg2 = $3->IRcode;			
					}

					// mul $t0, $t0, $t1
					if (strcmp(reg, "") != 0 && strcmp(reg2, "") != 0)
					{
						fprintf(MIPS,"mul %s, %s, %s\n", reg, reg, reg2);
						freeReg(reg2);
						strcpy($$->IRcode, reg); 
						fprintf(IRcode," %s = %s * %s\n", reg, $1->IRcode, $3->IRcode);
					}
					else if (strcmp(reg, "") == 0 && strcmp(reg2, "") != 0){
						freeReg(reg);
						strcpy($$->IRcode, reg2); 
					}
					else if (strcmp(reg, "") != 0 && strcmp(reg2, "") == 0){
						freeReg(reg2);
						strcpy($$->IRcode, reg); 
					}
					else{
						// li $t0, 1 
						reg = getRegister();
						fprintf(MIPS,"li %s, 1\n", reg);
						strcpy($$->IRcode, reg); 
					}
				}
			}
		|	Expr '/' Expr
			{
				/* node for / op */
				$$ = AST_node("/");
				$$->left = $1;
				$$->right = $3;
				
				/* check out code comments on "ID LBRACK Expr RBRACK" rule */
				struct AST* node = $1;
				char exprType[50]; 
				if ((strcmp(node->nodeType, "!") == 0) || (strcmp(node->nodeType, "==") == 0) || (strcmp(node->nodeType, "!=") == 0) || (strcmp(node->nodeType, "<=") == 0) || (strcmp(node->nodeType, ">=") == 0) || (strcmp(node->nodeType, "&&") == 0) || (strcmp(node->nodeType, "||") == 0) || (strcmp(node->nodeType, "<") == 0) || (strcmp(node->nodeType, ">") == 0)){
					strcpy(exprType, "bool");
				}
				else if ((strcmp(node->nodeType, "+") == 0) || (strcmp(node->nodeType, "-") == 0) || (strcmp(node->nodeType, "*") == 0) || (strcmp(node->nodeType, "/") == 0)){
					strcpy(exprType, "int");
				}
				else if ((strcmp(node->nodeType, "ARR") == 0)){			
					strcpy(exprType, getTypeForArr(node->left->nodeType, theStack));				
				}
				else{
					regex_t reg;
					const char *regex="^[A-Za-z][A-Za-z0-9]*";
					int ret;
					char err[1024];
					//Read data into variable filecontent
					ret = regcomp(&reg, regex, REG_EXTENDED);
					if (ret != 0) {
						regerror(ret, &reg, err, 1024);
						return 1;
					}
					int return_value;
					return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
					regfree(&reg);
					if (return_value == 0){
						strcpy(exprType, getType(node->nodeType, theStack));
					}
					else{
						regex_t reg;
						const char *regex="^-?[0-9]+";
						int ret;
						char err[1024];
						//Read data into variable filecontent
						ret = regcomp(&reg, regex, REG_EXTENDED);
						if (ret != 0) {
							regerror(ret, &reg, err, 1024);
							return 1;
						}
						int return_value;
						return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
						regfree(&reg);
						if (return_value == 0){
							strcpy(exprType, "int");
						}
						else{
              regex_t reg;
              const char *regex="'[a-zA-Z]'";
              int ret;
              char err[1024];
              //Read data into variable filecontent
              ret = regcomp(&reg, regex, REG_EXTENDED);
              if (ret != 0) {
                regerror(ret, &reg, err, 1024);
                return 1;
              }
              int return_value;
              return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
              regfree(&reg);
              if (return_value == 0){
                strcpy(exprType, "char");
              }
              else{
                strcpy(exprType, ""); 
              }
            }
          }
        }
				if (strcmp(exprType, "int") != 0){
					printf("SEMANTIC ERROR: The type of expression must be int || Line: %d || Char: %d\n", lines, chars);
				}				
				/* check out code comments on "ID LBRACK Expr RBRACK" rule */				
				node = $3;
				if ((strcmp(node->nodeType, "!") == 0) || (strcmp(node->nodeType, "==") == 0) || (strcmp(node->nodeType, "!=") == 0) || (strcmp(node->nodeType, "<=") == 0) || (strcmp(node->nodeType, ">=") == 0) || (strcmp(node->nodeType, "&&") == 0) || (strcmp(node->nodeType, "||") == 0) || (strcmp(node->nodeType, "<") == 0) || (strcmp(node->nodeType, ">") == 0)){
					strcpy(exprType, "bool");
				}
				else if ((strcmp(node->nodeType, "+") == 0) || (strcmp(node->nodeType, "-") == 0) || (strcmp(node->nodeType, "*") == 0) || (strcmp(node->nodeType, "/") == 0)){
					strcpy(exprType, "int");
				}
				else if ((strcmp(node->nodeType, "ARR") == 0)){			
					strcpy(exprType, getTypeForArr(node->left->nodeType, theStack));				
				}
				else{
					regex_t reg;
					const char *regex="^[A-Za-z][A-Za-z0-9]*";
					int ret;
					char err[1024];
					//Read data into variable filecontent
					ret = regcomp(&reg, regex, REG_EXTENDED);
					if (ret != 0) {
						regerror(ret, &reg, err, 1024);
						return 1;
					}
					int return_value;
					return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
					regfree(&reg);
					if (return_value == 0){
						strcpy(exprType, getType(node->nodeType, theStack));
					}
					else{
						regex_t reg;
						const char *regex="^-?[0-9]+";
						int ret;
						char err[1024];
						//Read data into variable filecontent
						ret = regcomp(&reg, regex, REG_EXTENDED);
						if (ret != 0) {
							regerror(ret, &reg, err, 1024);
							return 1;
						}
						int return_value;
						return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
						regfree(&reg);
						if (return_value == 0){
							strcpy(exprType, "int");
						}
						else{
              regex_t reg;
              const char *regex="'[a-zA-Z]'";
              int ret;
              char err[1024];
              //Read data into variable filecontent
              ret = regcomp(&reg, regex, REG_EXTENDED);
              if (ret != 0) {
                regerror(ret, &reg, err, 1024);
                return 1;
              }
              int return_value;
              return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
              regfree(&reg);
              if (return_value == 0){
                strcpy(exprType, "char");
              }
              else{
                strcpy(exprType, ""); 
              }
            }
          }
        }
				if (strcmp(exprType, "int") != 0){
					printf("SEMANTIC ERROR: The type of expression must be int || Line: %d || Char: %d\n", lines, chars);
				}			

				


				// /* IR code generation */
				
				if (strcmp(top(theStack), "main") == 0){
					regex_t reg;
					const char *regex="^-?[0-9]+";
					int ret;
					char err[1024];
					//Read data into variable filecontent
					ret = regcomp(&reg, regex, REG_EXTENDED);
					if (ret != 0) {
						regerror(ret, &reg, err, 1024);
						return 1;
					}
					int return_value;
					return_value = regexec(&reg, $1->IRcode , 0, NULL, 0);
					regfree(&reg);
					
					regex_t reg2;
					const char *regex2="^-?[0-9]+";
					int ret2;
					char err2[1024];
					//Read data into variable filecontent
					ret2 = regcomp(&reg2, regex2, REG_EXTENDED);
					if (ret2 != 0) {
						regerror(ret2, &reg2, err2, 1024);
						return 1;
					}
					int return_value2;
					return_value2 = regexec(&reg2, $3->IRcode , 0, NULL, 0);
					regfree(&reg2);

					if (return_value == 0 && return_value2 == 0){
						float left;
						sscanf($1->IRcode, "%f", &left);
						float right;
						sscanf($3->IRcode, "%f", &right);
						float ans = left / right;
						int int_ans = (int)ans;					
						sprintf($$->IRcode, "%d", int_ans);
					}
					else if (return_value != 0 && return_value2 == 0){
						float left;
						char value[50];
						strcpy(value, getValue($1->IRcode, theStack));
						sscanf(value, "%f", &left);
						float right;
						sscanf($3->IRcode, "%f", &right);
						float ans = left / right;
						int int_ans = (int)ans;			
						sprintf($$->IRcode, "%d", int_ans);
					}
					else if (return_value == 0 && return_value2 != 0){
						float left;
						sscanf($1->IRcode, "%f", &left);
						float right;
						char value[50];
						strcpy(value, getValue($3->IRcode, theStack));
						sscanf(value, "%f", &right);
						float ans = left / right;
						int int_ans = (int)ans;					
						sprintf($$->IRcode, "%d", int_ans);
					}
					else if (return_value != 0 && return_value2 != 0){
						float left;
						char value[50];
						strcpy(value, getValue($1->IRcode, theStack));
						sscanf(value, "%f", &left);
						float right;
						char value1[50];
						strcpy(value1, getValue($3->IRcode, theStack));
						sscanf(value1, "%f", &right);
						float ans = left / right;
						int int_ans = (int)ans;					
						sprintf($$->IRcode, "%d", int_ans);
					}
				}
				else{
					char * reg = getRegister();
					char * reg2 = getRegister();

					if (strcmp(getExprType($1->IRcode), "int") == 0){
						// li $t0, 2
						fprintf(MIPS,"li %s, %s\n", reg, $1->IRcode);
					}
					else if (strcmp(getExprType($1->IRcode), "id") == 0){
						char* scope = getScope($1->IRcode, theStack);
						// lw $t0, addhehe_f
						fprintf(MIPS,"lw %s, %s_%s\n", reg, scope, $1->IRcode);
					}
					else{
						freeReg(reg);
						reg = $1->IRcode;
					}

					if (strcmp(getExprType($3->IRcode), "int") == 0){
						if (strcmp($3->IRcode, "1") != 0){
							// li $t0, 2
							fprintf(MIPS,"li %s, %s\n", reg2, $3->IRcode);
						}
						else{
							freeReg(reg2);
							reg2 = "";
						}
					}
					else if (strcmp(getExprType($3->IRcode), "id") == 0){
						char* scope = getScope($3->IRcode, theStack);
						// lw $t0, addhehe_f
						fprintf(MIPS,"lw %s, %s_%s\n", reg2, scope, $3->IRcode);
					}
					else{
						freeReg(reg2);
						reg2 = $3->IRcode;			
					}

					if (strcmp(reg2, "") != 0){				
						// div $t0, $t1
						// mflo $t0
						fprintf(MIPS,"div %s, %s\n", reg, reg2);
						fprintf(MIPS,"mflo %s\n", reg);
						freeReg(reg2);
						strcpy($$->IRcode, reg); 
						fprintf(IRcode," %s = %s / %s\n", reg, $1->IRcode, $3->IRcode);
					}
					else {
						strcpy($$->IRcode, reg); 
					}
				}

			}
		|	ID EQ Expr
			{	
				printf("RECOGNIZED RULE: Variable Value Assignment || %s || Line: %d || Char: %d\n", $1, lines, chars);
				$$ = AST_node("EQ");
				$$->left = AST_node($1);
				$$->right = $3;

				// Symbol Table
				symTabAccess();
				int inSymTab = 0;
				struct stack_entry *entry = malloc(sizeof *entry); 
				entry = theStack->head;
				while (entry != NULL){
					inSymTab = found($1, entry->data);
					if (inSymTab != 0){
						break;
					}
					entry = entry->next;
				}
				printf("looking for %s in symtab - found: %d \n", $1, inSymTab);
				if (inSymTab == 0) 
				{
					printf("SEMANTIC ERROR: Varible %s was not declared || Line: %d || Char: %d\n", $1, lines, chars);
				}	

				struct AST* node = $3;
				char exprTypeForIR[50] = "";
				char exprType[50]; 
				if ((strcmp(node->nodeType, "!") == 0) || (strcmp(node->nodeType, "==") == 0) || (strcmp(node->nodeType, "!=") == 0) || (strcmp(node->nodeType, "<=") == 0) || (strcmp(node->nodeType, ">=") == 0) || (strcmp(node->nodeType, "&&") == 0) || (strcmp(node->nodeType, "||") == 0) || (strcmp(node->nodeType, "<") == 0) || (strcmp(node->nodeType, ">") == 0)){
					strcpy(exprType, "bool");
				}
				else if ((strcmp(node->nodeType, "+") == 0) || (strcmp(node->nodeType, "-") == 0) || (strcmp(node->nodeType, "*") == 0) || (strcmp(node->nodeType, "/") == 0)){
					strcpy(exprType, "int");
				}
				else if ((strcmp(node->nodeType, "ARR") == 0)){			
					strcpy(exprType, getTypeForArr(node->left->nodeType, theStack));
					strcpy(exprTypeForIR, "arr");				
				}
				else{
					regex_t reg;
					const char *regex="^[A-Za-z][A-Za-z0-9]*";
					int ret;
					char err[1024];
					//Read data into variable filecontent
					ret = regcomp(&reg, regex, REG_EXTENDED);
					if (ret != 0) {
						regerror(ret, &reg, err, 1024);
						return 1;
					}
					int return_value;
					return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
					regfree(&reg);
					if (return_value == 0){
						strcpy(exprType, getType(node->nodeType, theStack));
					}
					else{
						regex_t reg;
						const char *regex="^-?[0-9]+";
						int ret;
						char err[1024];
						//Read data into variable filecontent
						ret = regcomp(&reg, regex, REG_EXTENDED);
						if (ret != 0) {
							regerror(ret, &reg, err, 1024);
							return 1;
						}
						int return_value;
						return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
						regfree(&reg);
						if (return_value == 0){
							strcpy(exprType, "int");
						}
						else{
							regex_t reg;
							const char *regex="'[a-zA-Z]'";
							int ret;
							char err[1024];
							//Read data into variable filecontent
							ret = regcomp(&reg, regex, REG_EXTENDED);
							if (ret != 0) {
								regerror(ret, &reg, err, 1024);
								return 1;
							}
							int return_value;
							return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
							regfree(&reg);
							if (return_value == 0){
								strcpy(exprType, "char");
							}
							else{
								strcpy(exprType, "");	
								strcpy(exprTypeForIR, "");	
							}
						}
					}
				}
			
				char idType[50]; 
				strcpy(idType, getType($1, theStack));
				if (strcmp(exprType, idType) != 0){
					printf("SEMANTIC ERROR: The operands of EQ op must have the same type || Line: %d || Char: %d\n", lines, chars);
				}






				
				// IR code
			
				setVar($1, $$->right->IRcode);
				regex_t reg;
				const char *regex="^-?[0-9]+";
				int ret;
				char err[1024];
				//Read data into variable filecontent
				ret = regcomp(&reg, regex, REG_EXTENDED);
				if (ret != 0) {
					regerror(ret, &reg, err, 1024);
					return 1;
				}
				int return_value;
				return_value = regexec(&reg, node->IRcode , 0, NULL, 0);
				regfree(&reg);
				if (return_value == 0){
					char* scope = getScope($1, theStack);
					assignNumber($1, $3->IRcode, scope);
					setValue($1, $3->IRcode, theStack);
					showSymTable();
				}
				else{
					regex_t reg;
					const char *regex="^[$][tv][0-9]$";
					int ret;
					char err[1024];
					//Read data into variable filecontent
					ret = regcomp(&reg, regex, REG_EXTENDED);
					if (ret != 0) {
						regerror(ret, &reg, err, 1024);
						return 1;
					}
					int return_value;
					return_value = regexec(&reg, node->IRcode , 0, NULL, 0);
					regfree(&reg);
					if (return_value == 0){
						char* scope = getScope($1, theStack);
						assignReg($1, $3->IRcode, scope);
					}
					else{
						char* scopeL = getScope($1, theStack);
						char* scopeR = getScope($3->IRcode, theStack);
						assignID($1, $3->IRcode, scopeL, scopeR);
						char value[50];
						strcpy(value, getValue($3->IRcode, theStack));
						setValue($1, value, theStack);
						showSymTable();
					}
				}

			}

		| ID LBRACK Expr RBRACK EQ Expr
			{
				printf("RECOGNIZED RULE: Variable Array Value Assignment:  || %s || Line: %d || Char: %d\n", $1, lines, chars);
				$$ = AST_node("EQ");
				$$->left = AST_node("ARR");
				$$->left->left = AST_node($1);
				$$->left->right = $3;
				$$->right = $6;

				if (!isArray($1, theStack)){
					printf("SEMANTIC ERROR: Variable must be an array variable || Line: %d || Char: %d\n", lines, chars);
				}

				struct AST* node = $3;
				char exprType[50]; 
				if ((strcmp(node->nodeType, "!") == 0) || (strcmp(node->nodeType, "==") == 0) || (strcmp(node->nodeType, "!=") == 0) || (strcmp(node->nodeType, "<=") == 0) || (strcmp(node->nodeType, ">=") == 0) || (strcmp(node->nodeType, "&&") == 0) || (strcmp(node->nodeType, "||") == 0) || (strcmp(node->nodeType, "<") == 0) || (strcmp(node->nodeType, ">") == 0)){
					strcpy(exprType, "bool");
				}
				else if ((strcmp(node->nodeType, "+") == 0) || (strcmp(node->nodeType, "-") == 0) || (strcmp(node->nodeType, "*") == 0) || (strcmp(node->nodeType, "/") == 0)){
					strcpy(exprType, "int");
				}
				else if ((strcmp(node->nodeType, "ARR") == 0)){			
					strcpy(exprType, getTypeForArr(node->left->nodeType, theStack));				
				}
				else{
					regex_t reg;
					const char *regex="^[A-Za-z][A-Za-z0-9]*";
					int ret;
					char err[1024];
					//Read data into variable filecontent
					ret = regcomp(&reg, regex, REG_EXTENDED);
					if (ret != 0) {
						regerror(ret, &reg, err, 1024);
						return 1;
					}
					int return_value;
					return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
					regfree(&reg);
					if (return_value == 0){
						strcpy(exprType, getType(node->nodeType, theStack));
					}
					else{
						regex_t reg;
						const char *regex="^-?[0-9]+";
						int ret;
						char err[1024];
						//Read data into variable filecontent
						ret = regcomp(&reg, regex, REG_EXTENDED);
						if (ret != 0) {
							regerror(ret, &reg, err, 1024);
							return 1;
						}
						int return_value;
						return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
						regfree(&reg);
						if (return_value == 0){
							strcpy(exprType, "int");
						}
					else{	
              regex_t reg;
              const char *regex="'[a-zA-Z]'";
              int ret;
              char err[1024];
              //Read data into variable filecontent
              ret = regcomp(&reg, regex, REG_EXTENDED);
              if (ret != 0) {
                regerror(ret, &reg, err, 1024);
                return 1;
              }
              int return_value;
              return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
              regfree(&reg);
              if (return_value == 0){
                strcpy(exprType, "char");
              }
              else{
                strcpy(exprType, ""); 
              }
            }
          }
        }
				if (strcmp(exprType, "int") != 0){
					printf("SEMANTIC ERROR: The type of expression must be int || Line: %d || Char: %d\n", lines, chars);
				}				

				node = $6;
				if ((strcmp(node->nodeType, "!") == 0) || (strcmp(node->nodeType, "==") == 0) || (strcmp(node->nodeType, "!=") == 0) || (strcmp(node->nodeType, "<=") == 0) || (strcmp(node->nodeType, ">=") == 0) || (strcmp(node->nodeType, "&&") == 0) || (strcmp(node->nodeType, "||") == 0) || (strcmp(node->nodeType, "<") == 0) || (strcmp(node->nodeType, ">") == 0)){
					strcpy(exprType, "bool");
				}
				else if ((strcmp(node->nodeType, "+") == 0) || (strcmp(node->nodeType, "-") == 0) || (strcmp(node->nodeType, "*") == 0) || (strcmp(node->nodeType, "/") == 0)){
					strcpy(exprType, "int");
				}
				else if ((strcmp(node->nodeType, "ARR") == 0)){			
					strcpy(exprType, getTypeForArr(node->left->nodeType, theStack));				
				}
				else{
					regex_t reg;
					const char *regex="^[A-Za-z][A-Za-z0-9]*";
					int ret;
					char err[1024];
					//Read data into variable filecontent
					ret = regcomp(&reg, regex, REG_EXTENDED);
					if (ret != 0) {
						regerror(ret, &reg, err, 1024);
						return 1;
					}
					int return_value;
					return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
					regfree(&reg);
					if (return_value == 0){
						strcpy(exprType, getType(node->nodeType, theStack));
					}
					else{
						regex_t reg;
						const char *regex="^-?[0-9]+";
						int ret;
						char err[1024];
						//Read data into variable filecontent
						ret = regcomp(&reg, regex, REG_EXTENDED);
						if (ret != 0) {
							regerror(ret, &reg, err, 1024);
							return 1;
						}
						int return_value;
						return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
						regfree(&reg);
						if (return_value == 0){
							strcpy(exprType, "int");
						}
					else{
              regex_t reg;
              const char *regex="'[a-zA-Z]'";
              int ret;
              char err[1024];
              //Read data into variable filecontent
              ret = regcomp(&reg, regex, REG_EXTENDED);
              if (ret != 0) {
                regerror(ret, &reg, err, 1024);
                return 1;
              }
              int return_value;
              return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
              regfree(&reg);
              if (return_value == 0){
                strcpy(exprType, "char");
              }
              else{
                strcpy(exprType, ""); 
              }
            }
          }
        }
				char idType[50]; 
				strcpy(idType, getTypeForArr($1, theStack));
				if (strcmp(exprType, idType) != 0){
					printf("SEMANTIC ERROR: The operands of EQ op must have the same type || Line: %d || Char: %d\n", lines, chars);
				}				
				
				// // IR code
				char* line;
				char line1[500] = "";
				strcat(line1, $1);
				strcat(line1, "[");
				strcat(line1, $3->IRcode);
				strcat(line1,"]");
				line = line1;
				setVar(line1, $$->right->IRcode);
				freeReg($3->IRcode);

				char * reg = getRegister();
				char * reg2 = getRegister();

				if (strcmp(getExprType($3->IRcode), "int") == 0){
					assignArrayWithNumInBrackets($3->IRcode, reg);
				}
				else if (strcmp(getExprType($3->IRcode), "id") == 0){
					char* scope = getScope($3->IRcode, theStack);
					assignArrayWithIdInBrackets($3->IRcode, scope, reg);
				}
				else{
					assignArrayWithRegInBrackets($3->IRcode, reg);
				}
				
				if (strcmp(getExprType($6->IRcode), "int") == 0){
					assignArrayToInt($6->IRcode, reg2);
					if (strcmp(getExprType($3->IRcode), "int") == 0){
						// add var onto the symbol table
						char varNameHolder[90];
						strcpy(varNameHolder, $1);
						strcat(varNameHolder, "[");
						strcat(varNameHolder, $3->IRcode);
						strcat(varNameHolder, "]");
						
						char* varScope = getScope($1, theStack);
						
						char * varType = getTypeForArr($1, theStack);

						if (found(varNameHolder, varScope) == 0){
							addItem(varNameHolder, "Var", varType, "", varScope, "", $6->IRcode);
						}
						else{
							setValue(varNameHolder, $6->IRcode, theStack);
						}
						
					}
					else if (strcmp(getExprType($3->IRcode), "id") == 0){
						// add var onto the symbol table
						char varNameHolder[90];
						strcpy(varNameHolder, $1);
						strcat(varNameHolder, "[");
						char * index = getValue($3->IRcode, theStack);
						strcat(varNameHolder, index);
						strcat(varNameHolder, "]");
						
						char* varScope = getScope($1, theStack);
						
						char * varType = getTypeForArr($1, theStack);
						
						if (found(varNameHolder, varScope) == 0){
							addItem(varNameHolder, "Var", varType, "", varScope, "", $6->IRcode);
						}
						else{
							setValue(varNameHolder, $6->IRcode, theStack);
						}

					}
				}
				else if (strcmp(getExprType($6->IRcode), "id") == 0){
					char* scope = getScope($6->IRcode, theStack);
					assignArrayToId($6->IRcode, scope, reg2);

					if (strcmp(getExprType($3->IRcode), "int") == 0){
						// add var onto the symbol table
						char varNameHolder[90];
						strcpy(varNameHolder, $1);
						strcat(varNameHolder, "[");
						strcat(varNameHolder, $3->IRcode);
						strcat(varNameHolder, "]");
						
						char* varScope = getScope($1, theStack);
						
						char * varType = getTypeForArr($1, theStack);
						
						char * varValue = getValue($6->IRcode, theStack);

						if (found(varNameHolder, varScope) == 0){
							addItem(varNameHolder, "Var", varType, "", varScope, "", varValue);
						}
						else{
							setValue(varNameHolder, varValue, theStack);
						}
					}
					else if (strcmp(getExprType($3->IRcode), "id") == 0){
						// add var onto the symbol table
						char varNameHolder[90];
						strcpy(varNameHolder, $1);
						strcat(varNameHolder, "[");
						char * index = getValue($3->IRcode, theStack);
						strcat(varNameHolder, index);
						strcat(varNameHolder, "]");
						
						char* varScope = getScope($1, theStack);
						
						char * varType = getTypeForArr($1, theStack);
						
						char * varValue = getValue($6->IRcode, theStack);

						if (found(varNameHolder, varScope) == 0){
							addItem(varNameHolder, "Var", varType, "", varScope, "", varValue);
						}
						else{
							setValue(varNameHolder, varValue, theStack);
						}
					}
				}
				else{
					assignArrayToReg($6->IRcode, reg2);
				}
				char* scope = getScope($1, theStack);
				assignArrayToExpr($1, scope, reg, reg2);
				freeReg(reg);
				freeReg(reg2);
				
			}
		|	ID EQ
			{
				printf("SYNTAX ERROR: Missing Expr in Variable Value Assignment || Line: %d || Char: %d\n", lines, chars);
			}
		|	ID LBRACK Expr RBRACK EQ
		{
			printf("SYNTAX ERROR: Missing Expr in Variable Array Value Assignment || Line: %d || Char: %d\n", lines, chars);
		}
;

// different kind of Stmt in our grammar
// include if statement, and while loop
Stmt:	SEMICOLON
			{
				$$ = AST_node($1);
			}
		|	Expr SEMICOLON
		|	Expr 
			{
				printf("SYNTAX ERROR: Missing SEMICOLON || Line: %d || Char: %d\n", lines, chars);
			}
		|	RETURN Expr SEMICOLON 
			{
				$$ = AST_node("RETURN");
				$$->left = $2;
				printf("RECOGNIZED RULE: RETURN || Line: %d || Char: %d\n", lines, chars);

				struct AST* node = $2;
				char exprType[50]; 
				if ((strcmp(node->nodeType, "!") == 0) || (strcmp(node->nodeType, "==") == 0) || (strcmp(node->nodeType, "!=") == 0) || (strcmp(node->nodeType, "<=") == 0) || (strcmp(node->nodeType, ">=") == 0) || (strcmp(node->nodeType, "&&") == 0) || (strcmp(node->nodeType, "||") == 0) || (strcmp(node->nodeType, "<") == 0) || (strcmp(node->nodeType, ">") == 0)){
					strcpy(exprType, "bool");
				}
				else if ((strcmp(node->nodeType, "+") == 0) || (strcmp(node->nodeType, "-") == 0) || (strcmp(node->nodeType, "*") == 0) || (strcmp(node->nodeType, "/") == 0)){
					strcpy(exprType, "int");
				}
				else if ((strcmp(node->nodeType, "ARR") == 0)){			
					strcpy(exprType, getTypeForArr(node->left->nodeType, theStack));				
				}
				else{
					regex_t reg;
					const char *regex="^[A-Za-z][A-Za-z0-9]*";
					int ret;
					char err[1024];
					//Read data into variable filecontent
					ret = regcomp(&reg, regex, REG_EXTENDED);
					if (ret != 0) {
						regerror(ret, &reg, err, 1024);
						return 1;
					}
					int return_value;
					return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
					regfree(&reg);
					if (return_value == 0){
						strcpy(exprType, getType(node->nodeType, theStack));
					}
					else{
						regex_t reg;
						const char *regex="^-?[0-9]+";
						int ret;
						char err[1024];
						//Read data into variable filecontent
						ret = regcomp(&reg, regex, REG_EXTENDED);
						if (ret != 0) {
							regerror(ret, &reg, err, 1024);
							return 1;
						}
						int return_value;
						return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
						regfree(&reg);
						if (return_value == 0){
							strcpy(exprType, "int");
						}
						else{
              regex_t reg;
              const char *regex="'[a-zA-Z]'";
              int ret;
              char err[1024];
              //Read data into variable filecontent
              ret = regcomp(&reg, regex, REG_EXTENDED);
              if (ret != 0) {
                regerror(ret, &reg, err, 1024);
                return 1;
              }
              int return_value;
              return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
              regfree(&reg);
              if (return_value == 0){
                strcpy(exprType, "char");
              }
              else{
                strcpy(exprType, ""); 
              }
            }
          }
        }
				char funcType[50];
				strcpy(funcType, getType(top(theStack), theStack));
				if (strcmp(exprType, funcType) != 0){
					printf("SEMANTIC ERROR: The expression in a return statement must have the same type as the declared result type of the enclosing function definition. Function type: %s. Return: %s || Line: %d || Char: %d\n",funcType, exprType, lines, chars);
				}
				// IR code
				// v0 = $2->IRcode
				freeReg($2->IRcode);
				char* line;
				char line1[500] = "";
				strcat(line1, "v0 = ");
				strcat(line1, $2->IRcode);
				line = line1;
				writeIR(line1);


				// MIPS code
				char * scope = top(theStack);
				if (strcmp(scope,"main") != 0){
					
					char * reg = getRegister();
					if (strcmp(getExprType($2->IRcode), "int") == 0){
						// li $t0, 2
						fprintf(MIPS,"li %s, %s\n", reg, $2->IRcode);
					}
					else if (strcmp(getExprType($2->IRcode), "id") == 0){
						char* scope = getScope($2->IRcode, theStack);
						// lw $t0, addhehe_f
						fprintf(MIPS,"lw %s, %s_%s\n", reg, scope, $2->IRcode);
					}
					else{
						freeReg(reg);
						reg = $2->IRcode;
					}
					// lw $v0, main_b
					fprintf(MIPS,"move $v0, %s\n", reg);
					fprintf(MIPS, "j return_func\n");
					freeReg(reg);
				}			
				else{						
					if (strcmp(scope, "main") == 0)
					{
						emitEndTimer();
					}
					fprintf(MIPS, "j end_%s\n", scope);
				}

			}
		|	RETURN SEMICOLON
			{
				// MIPS code
				char * scope = top(theStack);
				if (strcmp(scope,"main") != 0){
					fprintf(MIPS, "j return_func\n");
				}			
				else{
					if (strcmp(scope, "main") == 0)
					{
						emitEndTimer();
					}
					fprintf(MIPS, "j end_%s\n", scope);
				}
				
				$$ = AST_node("RETURN");
				printf("RECOGNIZED RULE: RETURN || Line: %d || Char: %d\n", lines, chars);
				if (strcmp(getType(top(theStack), theStack), "void") != 0){
					printf("SEMANTIC ERROR: A return statement must not have a return value unless it appears in the body of a function that is declared to return a value. || Line: %d || Char: %d\n", lines, chars);
				}
			}
		|	RETURN Expr  
			{
				printf("SYNTAX ERROR: Missing SEMICOLON || Line: %d || Char: %d\n", lines, chars);
			}
		| WRITE Expr SEMICOLON 
			{
				$$ = AST_node("WRITE");
				$$->left = $2;
				$$->right = AST_node("");
				printf("RECOGNIZED RULE: WRITE || Line: %d || Char: %d\n", lines, chars);
				char c [400];
				strcpy(c, $2->IRcode);
				if (c[0] == '"'){
					emitWrite($2->IRcode);
					useroutnumber = emitMIPSWriteForString($2->IRcode, userout, useroutnumber);
				}
				else{
					/* check out code comments on "ID LBRACK Expr RBRACK" rule */
					struct AST* node = $2;
					char exprType[50]; 
					if ((strcmp(node->nodeType, "!") == 0) || (strcmp(node->nodeType, "==") == 0) || (strcmp(node->nodeType, "!=") == 0) || (strcmp(node->nodeType, "<=") == 0) || (strcmp(node->nodeType, ">=") == 0) || (strcmp(node->nodeType, "&&") == 0) || (strcmp(node->nodeType, "||") == 0) || (strcmp(node->nodeType, "<") == 0) || (strcmp(node->nodeType, ">") == 0)){
						strcpy(exprType, "bool");
					}
					else if ((strcmp(node->nodeType, "+") == 0) || (strcmp(node->nodeType, "-") == 0) || (strcmp(node->nodeType, "*") == 0) || (strcmp(node->nodeType, "/") == 0)){
						strcpy(exprType, "int");
					}
					else if ((strcmp(node->nodeType, "ARR") == 0)){			
						strcpy(exprType, getTypeForArr(node->left->nodeType, theStack));				
					}
					else{
						regex_t reg;
						const char *regex="^[A-Za-z][A-Za-z0-9]*";
						int ret;
						char err[1024];
						//Read data into variable filecontent
						ret = regcomp(&reg, regex, REG_EXTENDED);
						if (ret != 0) {
							regerror(ret, &reg, err, 1024);
							return 1;
						}
						int return_value;
						return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
						regfree(&reg);
						if (return_value == 0){
							strcpy(exprType, getType(node->nodeType, theStack));
						}
						else{
							regex_t reg;
							const char *regex="^-?[0-9]+";
							int ret;
							char err[1024];
							//Read data into variable filecontent
							ret = regcomp(&reg, regex, REG_EXTENDED);
							if (ret != 0) {
								regerror(ret, &reg, err, 1024);
								return 1;
							}
							int return_value;
							return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
							regfree(&reg);
							if (return_value == 0){
								strcpy(exprType, "int");
							}
							else{
								regex_t reg;
								const char *regex="'[a-zA-Z]'";
								int ret;
								char err[1024];
								//Read data into variable filecontent
								ret = regcomp(&reg, regex, REG_EXTENDED);
								if (ret != 0) {
									regerror(ret, &reg, err, 1024);
									return 1;
								}
								int return_value;
								return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
								regfree(&reg);
								if (return_value == 0){
									strcpy(exprType, "char");
								}
								else{
									strcpy(exprType, ""); 
								}
							}
						}
					}
					if (strcmp(exprType, "int") == 0){
						emitWriteForInt($2->IRcode);
						emitMIPSWriteForInt($2->IRcode, theStack, getScope($2->IRcode, theStack));
					}
					else{
						emitWrite($2->IRcode);
						useroutnumber = emitMIPSWriteForString($2->IRcode, userout, useroutnumber);
					}	
				}
			}
		|	WRITE Expr 
			{
				printf("SYNTAX ERROR: Missing SEMICOLON || Line: %d || Char: %d\n", lines, chars);
			}
		| WRITELN SEMICOLON
			{
				$$ = AST_node("WRITELN");
				$$->left = AST_node("");
				$$->right = AST_node("");
				printf("RECOGNIZED RULE: WRITELN || Line: %d || Char: %d\n", lines, chars);
				emitWriteLnForString("\"\"");
				emitWriteNewLine();
			}
		|	WRITELN Expr SEMICOLON
			{
				$$ = AST_node("WRITELN");
				$$->left = $2;
				$$->right = AST_node("");
				printf("RECOGNIZED RULE: WRITELN || Line: %d || Char: %d\n", lines, chars);
				char c [400];
				strcpy(c, $2->IRcode);
				if (c[0] == '"'){
					emitWriteLnForString($2->IRcode);
					useroutnumber = emitWriteNewLineForString($2->IRcode, userout, useroutnumber);
				}
				else{
					/* check out code comments on "ID LBRACK Expr RBRACK" rule */
					struct AST* node = $2;
					char exprType[50]; 
					if ((strcmp(node->nodeType, "!") == 0) || (strcmp(node->nodeType, "==") == 0) || (strcmp(node->nodeType, "!=") == 0) || (strcmp(node->nodeType, "<=") == 0) || (strcmp(node->nodeType, ">=") == 0) || (strcmp(node->nodeType, "&&") == 0) || (strcmp(node->nodeType, "||") == 0) || (strcmp(node->nodeType, "<") == 0) || (strcmp(node->nodeType, ">") == 0)){
						strcpy(exprType, "bool");
					}
					else if ((strcmp(node->nodeType, "+") == 0) || (strcmp(node->nodeType, "-") == 0) || (strcmp(node->nodeType, "*") == 0) || (strcmp(node->nodeType, "/") == 0)){
						strcpy(exprType, "int");
					}
					else if ((strcmp(node->nodeType, "ARR") == 0)){			
						strcpy(exprType, getTypeForArr(node->left->nodeType, theStack));				
					}
					else{
						regex_t reg;
						const char *regex="^[A-Za-z][A-Za-z0-9]*";
						int ret;
						char err[1024];
						//Read data into variable filecontent
						ret = regcomp(&reg, regex, REG_EXTENDED);
						if (ret != 0) {
							regerror(ret, &reg, err, 1024);
							return 1;
						}
						int return_value;
						return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
						regfree(&reg);
						if (return_value == 0){
							strcpy(exprType, getType(node->nodeType, theStack));
						}
						else{
							regex_t reg;
							const char *regex="^-?[0-9]+";
							int ret;
							char err[1024];
							//Read data into variable filecontent
							ret = regcomp(&reg, regex, REG_EXTENDED);
							if (ret != 0) {
								regerror(ret, &reg, err, 1024);
								return 1;
							}
							int return_value;
							return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
							regfree(&reg);
							if (return_value == 0){
								strcpy(exprType, "int");
							}
							else{
								regex_t reg;
								const char *regex="'[a-zA-Z]'";
								int ret;
								char err[1024];
								//Read data into variable filecontent
								ret = regcomp(&reg, regex, REG_EXTENDED);
								if (ret != 0) {
									regerror(ret, &reg, err, 1024);
									return 1;
								}
								int return_value;
								return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
								regfree(&reg);
								if (return_value == 0){
									strcpy(exprType, "char");
								}
								else{
									strcpy(exprType, ""); 
								}
							}
						}
					}
					// if we are writing a number
					if (strcmp(exprType, "int") == 0){
						emitWriteLnForInt($2->IRcode);
						emitWriteNewLineForInt($2->IRcode, theStack, getScope($2->IRcode, theStack));
					}
					// if we are writing something else
					else{
						emitWriteLn($2->IRcode);
						emitWriteNewLine();
					}	
				}
			}
		|	WRITELN Expr
			{
				printf("SYNTAX ERROR: Missing SEMICOLON || Line: %d || Char: %d\n", lines, chars);
			}
		| BREAK SEMICOLON
			{
				$$ = AST_node("BREAK");
				$$->left = AST_node("");
				$$->right = AST_node("");
				printf("RECOGNIZED RULE: BREAK || Line: %d || Char: %d\n", lines, chars);
				if (strcmp(top(theStack), "while") != 0){
					printf("SEMANTIC ERROR: All break statements must be contained within the body of a loop || Line: %d || Char: %d\n", lines, chars);
				}
			}
		|	BREAK
			{
				printf("SYNTAX ERROR: Missing SEMICOLON || Line: %d || Char: %d\n", lines, chars);
			}
		|	IFELSE
			{
				// addNum_if_1:
				fprintf(MIPS, "%s_if_%d:\n", top(theStack), if_counter);
				char currentScope[1024];
				snprintf(currentScope, sizeof(currentScope), "%s_if_%d", top(theStack), if_counter);
				push(theStack, currentScope);
				if_counter++;
			}
			LPAREN Expr 
			{
				emitStartIF();
			}
			RPAREN
			{
				emitMidIFELSE($4->IRcode); emitIFBLOCK();
			}
			Stmt 
			{
				emitEndIFELSEBLOCK(); 
				// j end_else_addNum_if_1
				fprintf(MIPS, "j end_else_%s\n", top(theStack));
			}
			ELSE 
			{
				emitELSEBLOCK();
				// else_addNum_if_1:
				fprintf(MIPS, "else_%s:\n", top(theStack));
			}
			Stmt 
			{
				emitEndELSEBLOCK();freeReg($4->IRcode);
				// end_else_addNum_if_1: 
				fprintf(MIPS, "end_else_%s:\n", top(theStack));
				pop(theStack);
			}
			{
				printf("RECOGNIZED RULE: IF-ELSE-STMT || Line: %d || Char: %d\n", lines, chars);
				$$ = AST_node("IFELSE");
				$$->left = $4;
				$$->right = AST_node("IFELSE-TAIL");
				$$->right->left = $8;
				$$->right->right = $12;

				struct AST* node = $4;
				char exprType[50]; 
				if ((strcmp(node->nodeType, "!") == 0) || (strcmp(node->nodeType, "==") == 0) || (strcmp(node->nodeType, "!=") == 0) || (strcmp(node->nodeType, "<=") == 0) || (strcmp(node->nodeType, ">=") == 0) || (strcmp(node->nodeType, "&&") == 0) || (strcmp(node->nodeType, "||") == 0) || (strcmp(node->nodeType, "<") == 0) || (strcmp(node->nodeType, ">") == 0)){
					strcpy(exprType, "bool");
				}
				else if ((strcmp(node->nodeType, "+") == 0) || (strcmp(node->nodeType, "-") == 0) || (strcmp(node->nodeType, "*") == 0) || (strcmp(node->nodeType, "/") == 0)){
					strcpy(exprType, "int");
				}
				else if ((strcmp(node->nodeType, "ARR") == 0)){			
					strcpy(exprType, getTypeForArr(node->left->nodeType, theStack));				
				}
				else{
					regex_t reg;
					const char *regex="^[A-Za-z][A-Za-z0-9]*";
					int ret;
					char err[1024];
					//Read data into variable filecontent
					ret = regcomp(&reg, regex, REG_EXTENDED);
					if (ret != 0) {
						regerror(ret, &reg, err, 1024);
						return 1;
					}
					int return_value;
					return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
					regfree(&reg);
					if (return_value == 0){
						strcpy(exprType, getType(node->nodeType, theStack));
					}
					else{
						regex_t reg;
						const char *regex="^-?[0-9]+";
						int ret;
						char err[1024];
						//Read data into variable filecontent
						ret = regcomp(&reg, regex, REG_EXTENDED);
						if (ret != 0) {
							regerror(ret, &reg, err, 1024);
							return 1;
						}
						int return_value;
						return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
						regfree(&reg);
						if (return_value == 0){
							strcpy(exprType, "int");
						}
					else{
              regex_t reg;
              const char *regex="'[a-zA-Z]'";
              int ret;
              char err[1024];
              //Read data into variable filecontent
              ret = regcomp(&reg, regex, REG_EXTENDED);
              if (ret != 0) {
                regerror(ret, &reg, err, 1024);
                return 1;
              }
              int return_value;
              return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
              regfree(&reg);
              if (return_value == 0){
                strcpy(exprType, "char");
              }
              else{
                strcpy(exprType, ""); 
              }
            }
          }
        }

				if (strcmp(exprType, "bool") != 0){
					printf("SEMANTIC ERROR: The type of expression must be bool || Line: %d || Char: %d\n", lines, chars);
				}	
			}
		
		|	IF LPAREN Expr {emitStartIF();} RPAREN {emitMidIF($3->IRcode); emitIFBLOCK();} Stmt {emitEndIFBLOCK(); freeReg($3->IRcode);}
			{
				printf("RECOGNIZED RULE: IF-STMT || Line: %d || Char: %d\n", lines, chars);
				$$ = AST_node("IF");
				$$->left = $3;
				$$->right = $7;
				
				struct AST* node = $3;
				char exprType[50]; 
				if ((strcmp(node->nodeType, "!") == 0) || (strcmp(node->nodeType, "==") == 0) || (strcmp(node->nodeType, "!=") == 0) || (strcmp(node->nodeType, "<=") == 0) || (strcmp(node->nodeType, ">=") == 0) || (strcmp(node->nodeType, "&&") == 0) || (strcmp(node->nodeType, "||") == 0) || (strcmp(node->nodeType, "<") == 0) || (strcmp(node->nodeType, ">") == 0)){
					strcpy(exprType, "bool");
				}
				else if ((strcmp(node->nodeType, "+") == 0) || (strcmp(node->nodeType, "-") == 0) || (strcmp(node->nodeType, "*") == 0) || (strcmp(node->nodeType, "/") == 0)){
					strcpy(exprType, "int");
				}
				else if ((strcmp(node->nodeType, "ARR") == 0)){			
					strcpy(exprType, getTypeForArr(node->left->nodeType, theStack));				
				}
				else{
					regex_t reg;
					const char *regex="^[A-Za-z][A-Za-z0-9]*";
					int ret;
					char err[1024];
					//Read data into variable filecontent
					ret = regcomp(&reg, regex, REG_EXTENDED);
					if (ret != 0) {
						regerror(ret, &reg, err, 1024);
						return 1;
					}
					int return_value;
					return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
					regfree(&reg);
					if (return_value == 0){
						strcpy(exprType, getType(node->nodeType, theStack));
					}
					else{
						regex_t reg;
						const char *regex="^-?[0-9]+";
						int ret;
						char err[1024];
						//Read data into variable filecontent
						ret = regcomp(&reg, regex, REG_EXTENDED);
						if (ret != 0) {
							regerror(ret, &reg, err, 1024);
							return 1;
						}
						int return_value;
						return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
						regfree(&reg);
						if (return_value == 0){
							strcpy(exprType, "int");
						}
						else{
              regex_t reg;
              const char *regex="'[a-zA-Z]'";
              int ret;
              char err[1024];
              //Read data into variable filecontent
              ret = regcomp(&reg, regex, REG_EXTENDED);
              if (ret != 0) {
                regerror(ret, &reg, err, 1024);
                return 1;
              }
              int return_value;
              return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
              regfree(&reg);
              if (return_value == 0){
                strcpy(exprType, "char");
              }
              else{
                strcpy(exprType, ""); 
              }
            }
          }
        }

				if (strcmp(exprType, "bool") != 0){
					printf("SEMANTIC ERROR: The type of expression must be bool || Line: %d || Char: %d\n", lines, chars);
				}		

			}

	
		|	WHILE 
			{
				emitStartWHILE(); 
				fprintf(MIPS, "%s_while_%d:\n", top(theStack), while_counter);
				char currentScope[1024];
				snprintf(currentScope, sizeof(currentScope), "%s_while_%d", top(theStack), while_counter);
				printf("CURRENT SCOPE: %s\n", currentScope);
				push(theStack, currentScope);
				while_counter++;
			}
			LPAREN Expr RPAREN 
			{
				emitMidWHILE($4->IRcode); 
				char* scopeL = getScope($4->left->IRcode, theStack); 
				char* scopeR = getScope($4->right->IRcode, theStack); 
				emitWHILEBLOCK();
			} 
			Stmt 
			{
				emitRestartWHILE(); 
				emitEndWHILEBLOCK(); 
				freeReg($4->IRcode);

				// j addNum_while_1
				// else_addNum_while_1:
				fprintf(MIPS, "j %s\nelse_%s:\n", top(theStack), top(theStack));
		
				pop(theStack);
				$$ = AST_node("WHILE");
				$$->left = $4;
				$$->right = $7;
				printf("RECOGNIZED RULE: WHILE-LOOP || Line: %d || Char: %d\n", lines, chars);
								
				struct AST* node = $4;
				char exprType[50]; 
				if ((strcmp(node->nodeType, "!") == 0) || (strcmp(node->nodeType, "==") == 0) || (strcmp(node->nodeType, "!=") == 0) || (strcmp(node->nodeType, "<=") == 0) || (strcmp(node->nodeType, ">=") == 0) || (strcmp(node->nodeType, "&&") == 0) || (strcmp(node->nodeType, "||") == 0) || (strcmp(node->nodeType, "<") == 0) || (strcmp(node->nodeType, ">") == 0)){
					strcpy(exprType, "bool");
				}
				else if ((strcmp(node->nodeType, "+") == 0) || (strcmp(node->nodeType, "-") == 0) || (strcmp(node->nodeType, "*") == 0) || (strcmp(node->nodeType, "/") == 0)){
					strcpy(exprType, "int");
				}
				else if ((strcmp(node->nodeType, "ARR") == 0)){			
					strcpy(exprType, getTypeForArr(node->left->nodeType, theStack));				
				}
				else{
					regex_t reg;
					const char *regex="^[A-Za-z][A-Za-z0-9]*";
					int ret;
					char err[1024];
					//Read data into variable filecontent
					ret = regcomp(&reg, regex, REG_EXTENDED);
					if (ret != 0) {
						regerror(ret, &reg, err, 1024);
						return 1;
					}
					int return_value;
					return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
					regfree(&reg);
					if (return_value == 0){
						strcpy(exprType, getType(node->nodeType, theStack));
					}
					else{
						regex_t reg;
						const char *regex="^-?[0-9]+";
						int ret;
						char err[1024];
						//Read data into variable filecontent
						ret = regcomp(&reg, regex, REG_EXTENDED);
						if (ret != 0) {
							regerror(ret, &reg, err, 1024);
							return 1;
						}
						int return_value;
						return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
						regfree(&reg);
						if (return_value == 0){
							strcpy(exprType, "int");
						}
						else{
              regex_t reg;
              const char *regex="'[a-zA-Z]'";
              int ret;
              char err[1024];
              //Read data into variable filecontent
              ret = regcomp(&reg, regex, REG_EXTENDED);
              if (ret != 0) {
                regerror(ret, &reg, err, 1024);
                return 1;
              }
              int return_value;
              return_value = regexec(&reg, node->nodeType , 0, NULL, 0);
              regfree(&reg);
              if (return_value == 0){
                strcpy(exprType, "char");
              }
              else{
                strcpy(exprType, ""); 
              }
            }
          }
        }

				if (strcmp(exprType, "bool") != 0){
					printf("SEMANTIC ERROR: The type of expression must be bool || Line: %d || Char: %d\n", lines, chars);
				}		
				
			}
		|	Block
;

%%

int main(int argc, char**argv)
{
	//timer start
	double duration = 0.0;
	clock_t start = clock();


	/* create scope stack, push global onto stack first */
	theStack = newStack();
	push(theStack, "global");
	/* create ifwhilestack */
	ifwhilestack = newStack();

	/*create stack for user output messages*/
	userout = newStack();

/*
	#ifdef YYDEBUG
		yydebug = 1;
	#endif
*/

/* Initialize files for writing IR and MIPS code */
	initIRcodeFile();
	initMIPScodeFile();
	
	// .text
	// .globl main
	// .ent main
	fprintf(MIPS,".text\n.globl main\n.ent main\n\n"); //emit start of MIPS file

	// return_func:                              
	// lw $ra, 0($sp)                          #restore return address
	// addiu $sp, $sp, 4                       #restore stack pointer
	// jr $ra                                  #jump back to return address
	// .end return_func
	fprintf(MIPS,"return_func:\nlw $ra, 0($sp)\naddiu $sp, $sp, 4\njr $ra\n.end return_func\n\n"); //emit Return function to exit function calls

/* Start compiler and create registers for use in IR and MIPS code. */
	printf("\n\n##### COMPILER STARTED #####\n\n");
	createRegisters();
	showRegisters();
	
/* Bison code for error when parsing */
	if (argc > 1){
	  if(!(yyin = fopen(argv[1], "r")))
          {
		perror(argv[1]);
		return(1);
	  }
	}
	yyparse();

/* emit end of main function to MIPS and add data section of MIPS code */
	exitMain();
	addData(useroutnumber, userout);

	//timer end
	clock_t finish = clock();
	duration += (double)(finish-start) / CLOCKS_PER_SEC;
	duration *= 1000;
	printf("\nCompiled in: %f milliseconds\n\n", duration);
	

}

//error function for parse errors
void yyerror(const char* s) {
	fprintf(stderr, "Parse error: %s\n", s);
	exit(1);
}