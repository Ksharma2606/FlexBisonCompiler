//Made By: Karan Sharma
//Refrence: Help from Adam Harris
//Date: 22/12/2021
//Abstract Syntax Tree Implementation
#include <string.h>

// structure of the node
// mid branch is for the node to connect to other nodes that are on the same level
// IRcode is for all IR related information
struct AST{
	char nodeType[50000];
	struct AST * left;
	struct AST * mid;
	struct AST * right;
	char IRcode[50000];
};

// create new node
struct AST * AST_node(char nodeType[50000]){
	struct AST* ASTnode = malloc(sizeof(struct AST));
	strcpy(ASTnode->nodeType, nodeType);
	return ASTnode;
}

// save the ast in a string to print out whenever we want 
char str[500000];

// recursive function to create the tree by concatenating string with the str variable
void makeAST(struct AST* tree, int level){
	// if the tree doesn't exist, do nothing and return
	if (tree == NULL)
		{
			return;
		}

	// get on the right level to print out the node
	for (int ii = 0; ii < level; ii++)
	{
		strcat (str, "   ");
	}

	// concat the node type of the ast node
	strcat (str, tree->nodeType);
  strcat (str,"\n");
	
	// go to the left node if it exists and repeat the process in the makeAST function
	if(tree->left != NULL) 
	{
		level += 1;
		makeAST(tree->left, level);
	} 
	else return;

	// go to the right node if it exists and repeat the process in the makeAST function
	if(tree->right != NULL)
	{ 
		makeAST(tree->right, level);
	} 
	else return;

	// go to the mid node if it exists and repeat the process in the makeAST function
	// notice how the makeAST is called with the "level -1" variable and not the level variable
	// this is to keep all of the stmt in the same scope on the same level in our ast tree
	if(tree->mid != NULL)
	{ 
		int midLevel = level -1;
		makeAST(tree->mid, midLevel);
	} 
	else return;

}

// print out the ast by the end of the analysis
void printAST(){
	printf ("%s",str);
}



