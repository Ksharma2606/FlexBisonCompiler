//Made By: Karan Sharma
//Refrence: Help from Adam Harris
//Date: 22/12/2021
//Symbol table header
#include <string.h>
FILE * IRcode;
FILE * MIPS;

struct Entry
{
	int itemID;
	char itemName[50];  //the name of the identifier
	char itemKind[8];  //is it a function or a variable? or array?
	char itemType[8];  // Is it int, char, etc.?
	char arrayLength[50]; //length of array
	char scope[50];     // global, or the name of the function
	char funcID[50];			//ID number for a function to manage local variables.
	char itemValue[50]; //value of the identifier
};

// create table if struct
struct Entry symTabItems[100];

int symTabIndex = 0;

void symTabAccess(void){
	printf("::::> Symbol table accessed.\n");
}

// add item of variable to our table
void addItem(char itemName[50], char itemKind[8], char itemType[8], char arrayLength[50], char scope[50], char funcID[50], char itemValue[50]){
		symTabItems[symTabIndex].itemID = symTabIndex;
		strcpy(symTabItems[symTabIndex].itemName, itemName);
		strcpy(symTabItems[symTabIndex].itemKind, itemKind);
		strcpy(symTabItems[symTabIndex].itemType, itemType);
		strcpy(symTabItems[symTabIndex].arrayLength, arrayLength);
		strcpy(symTabItems[symTabIndex].scope, scope);
		strcpy(symTabItems[symTabIndex].funcID, funcID);
		strcpy(symTabItems[symTabIndex].itemValue, itemValue);
		symTabIndex++;
}

// show our table
void showSymTable(){
	printf("itemID            itemName            itemKind            itemType             ArrayLength            itemScope            funcID           itemValue\n");
	printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	for (int i=0; i<symTabIndex; i++){
		printf("%d        %10s        %14s        %14s        %10s        %19s        %16s       %4s\n",symTabItems[i].itemID, symTabItems[i].itemName, symTabItems[i].itemKind, symTabItems[i].itemType, symTabItems[i].arrayLength, symTabItems[i].scope, symTabItems[i].funcID, symTabItems[i].itemValue);
	}
	

	printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
}

// Lookup an identifier in the symbol table
int found(char itemName[50], char scope[50]){
	// loops throught all row in our table, looking for matching item name and scope
	for(int i=0; i<symTabIndex; i++){
		int str1 = strcmp(symTabItems[i].itemName, itemName);
		int str2 = strcmp(symTabItems[i].scope,scope);
		if( str1 == 0 && str2 == 0){
			return 1; // found the ID in the table
		}
	}
	return 0;
}

// return number of variables needed in the parameter of a function
int numberOfVarInParameter(char funcName[50]){
	int ans = 0;
	for (int i = 0; i<symTabIndex; i++){
		if (strcmp(symTabItems[i].funcID, funcName) == 0)
		{
			ans++;
		}
	}
	return ans;
}

// get type of a variable
char* getType(char itemName[50], struct stack_t *theStack) {
	// check if variable has been declared in the current scope, if not move to the next scope and search
	int inSymTab = 0;
	struct stack_entry *entry = malloc(sizeof *entry); 
	entry = theStack->head;
	while (entry != NULL){
		inSymTab = found(itemName, entry->data);
		if (inSymTab != 0){
			break;
		}
		entry = entry->next;
	}
	if (entry != NULL){
		// once we have the scope that the variable was declared in, search for matching item name and scope
		for(int i=0; i<symTabIndex; i++){
			int str1 = strcmp(symTabItems[i].itemName, itemName);
			int str2 = strcmp(symTabItems[i].scope,entry->data);
			if( str1 == 0 && str2 == 0){
				char type[100];
				char* typeAdd;
				// get type and array length if available
				strcpy(type, symTabItems[i].itemType);
				strcat(type, symTabItems[i].arrayLength);
				typeAdd = type;
				return typeAdd;
			}
		}
	}
	return "";
}

// get type of an array variable, excluding the length of the array
char* getTypeForArr(char itemName[50], struct stack_t *theStack) {
	// check code comment in getType method
	int inSymTab = 0;
	struct stack_entry *entry = malloc(sizeof *entry); 
	entry = theStack->head;
	while (entry != NULL){
		inSymTab = found(itemName, entry->data);
		if (inSymTab != 0){
			break;
		}
		entry = entry->next;
	}
	if (entry != NULL){
		for(int i=0; i<symTabIndex; i++){
			int str1 = strcmp(symTabItems[i].itemName, itemName);
			int str2 = strcmp(symTabItems[i].scope,entry->data);
			if( str1 == 0 && str2 == 0){
				char type[100];
				char* typeAdd;
				// just get the item type and not the array length
				strcpy(type, symTabItems[i].itemType);
				typeAdd = type;
				return typeAdd;
			}
		}
	}
	return "";
}

// return an array of variable type needed in the parameter of a function
char** getVarInPara(char funcName[50]) {
	// create that array
	char ** varArr = malloc(100 * sizeof(char*));
	for (int i =0 ; i < 100; ++i)
			varArr[i] = malloc(50 * sizeof(char));
	// get the variable with the matching functionID 
	int currentIndex = 0;
	for(int ii=0; ii<symTabIndex; ii++){
		int str1 = strcmp(symTabItems[ii].funcID, funcName);
		if( str1 == 0 ){
			// add the item type and the arraylength to the array
			strcpy(varArr[currentIndex], symTabItems[ii].itemType);
			strcat(varArr[currentIndex], symTabItems[ii].arrayLength);
			currentIndex++;
		}
	}	
	// return the array
	return varArr;
}

char** getVarNameInPara(char funcName[50]) {
	// create that array
	char ** varArr = malloc(100 * sizeof(char*));
	for (int i =0 ; i < 100; ++i)
			varArr[i] = malloc(50 * sizeof(char));
	// get the variable with the matching functionID 
	int currentIndex = 0;
	for(int ii=0; ii<symTabIndex; ii++){
		int str1 = strcmp(symTabItems[ii].funcID, funcName);
		if( str1 == 0 ){
			// add the item type and the arraylength to the array
			strcpy(varArr[currentIndex], symTabItems[ii].itemName);
			currentIndex++;
		}
	}	
	// return the array
	return varArr;
}

// check if a variable is an array 
bool isArray (char itemName[50], struct stack_t *theStack){
	// check if it is a variable in our table first
	int inSymTab = 0;
	struct stack_entry *entry = malloc(sizeof *entry); 
	entry = theStack->head;
	while (entry != NULL){
		inSymTab = found(itemName, entry->data);
		if (inSymTab != 0){
			break;
		}
		entry = entry->next;
	}
	// if the variable is in our table 
	if (entry != NULL){
		for(int i=0; i<symTabIndex; i++){
			// find the matching item name and scope
			int str1 = strcmp(symTabItems[i].itemName, itemName);
			int str2 = strcmp(symTabItems[i].scope,entry->data);
			if( str1 == 0 && str2 == 0){
				// if array length of that variable is 0, it is not an array
				if (strcmp(symTabItems[i].arrayLength, "") == 0){
					return false;
				}
				else{
					return true;
				}
			}
		}
	}
	return false;
}

// get scope of a variable
char* getScope(char itemName[50], struct stack_t *theStack) {
	// check if variable has been declared in the current scope, if not move to the next scope and search
	int inSymTab = 0;
	struct stack_entry *entry = malloc(sizeof *entry); 
	entry = theStack->head;
	while (entry != NULL){
		inSymTab = found(itemName, entry->data);
		if (inSymTab != 0){
			break;
		}
		entry = entry->next;
	}
	if (entry != NULL){
		return entry->data;
	}
	else{
		return "";
	}
	
}


char * isArrayElement(char * itemName){
	regex_t reg;
	const char *regex="\\]$";
	int ret;
	char err[1024];
	//Read data into variable filecontent
	ret = regcomp(&reg, regex, REG_EXTENDED);
	if (ret != 0) {
		regerror(ret, &reg, err, 1024);
		return "1";
	}
	int return_value;
	return_value = regexec(&reg, itemName , 0, NULL, 0);
	regfree(&reg);
	if (return_value == 0){
		return "1";
	}
	else{
		return "0";
	}
}


// create variable section in mips code
void addData(int useroutnumber, struct stack_t *userout){
		// loops throught all row in our table, looking for matching item name and scope
	for(int i=0; i<symTabIndex; i++){
		if (strcmp(isArrayElement(symTabItems[i].itemName), "0") == 0){
			if (strcmp(symTabItems[i].itemKind, "Var") == 0){
				if (strcmp(symTabItems[i].itemType, "int") == 0){
					if (strcmp(symTabItems[i].arrayLength, "") == 0){
						fprintf(MIPS, ".data\n");
						fprintf(MIPS, "%s_%s: .word 0\n", symTabItems[i].scope ,symTabItems[i].itemName);
					}
					else{
						fprintf(MIPS, ".data\n");
						fprintf(MIPS, "%s_%s: .word 0:%s\n", symTabItems[i].scope ,symTabItems[i].itemName, symTabItems[i].arrayLength);
					}
				}
				else if (strcmp(symTabItems[i].itemType, "float") == 0){
					fprintf(MIPS, ".data\n");
					fprintf(MIPS, "%s: .float 0.0\n", symTabItems[i].itemName);
				}
				else if (strcmp(symTabItems[i].itemType, "char") == 0){
					fprintf(MIPS, ".data\n");
					fprintf(MIPS, "%s_%s: .asciiz \"\"\n", symTabItems[i].scope, symTabItems[i].itemName);
				}
			}
		}
	}
	//add section for newline character
	fprintf(MIPS, ".data\n");
	fprintf(MIPS, "newline: .asciiz \"\\n\"\n");
	for(int i = useroutnumber; i > 0; i--){		
		fprintf(MIPS, ".data\n");
		fprintf(MIPS, "%s: .asciiz ", top(userout));
		pop(userout);
		fprintf(MIPS, "%s\n", top(userout));
		pop(userout);
	}
	fprintf(MIPS, ".data\n");
	fprintf(MIPS, "start_time: .word 0\n");
	fprintf(MIPS, "end_time: .word 0\n");
	fprintf(MIPS, "duration: .word 0\n");
	fprintf(MIPS, "TIMER_MSG_SRT: .asciiz \"\\n\\nExecuted in: \"\n");
	fprintf(MIPS, "TIMER_MSG_END: .asciiz \" milliseconds\"\n");

	
}



void setValue (char itemName[50], char itemValue[50], struct stack_t *theStack){
	// check if variable has been declared in the current scope, if not move to the next scope and search
	int inSymTab = 0;
	struct stack_entry *entry = malloc(sizeof *entry); 
	entry = theStack->head;
	while (entry != NULL){
		inSymTab = found(itemName, entry->data);
		if (inSymTab != 0){
			break;
		}
		entry = entry->next;
	}
	if (entry != NULL){
		// once we have the scope that the variable was declared in, search for matching item name and scope
		for(int i=0; i<symTabIndex; i++){
			int str1 = strcmp(symTabItems[i].itemName, itemName);
			int str2 = strcmp(symTabItems[i].scope,entry->data);
			if( str1 == 0 && str2 == 0){
				strcpy(symTabItems[i].itemValue, itemValue);					
			}
		}
	}
	else{
		printf("Error: Variable %s has not been declared\n", itemName);
	}
}

// get value of a variable
char* getValue(char itemName[50], struct stack_t *theStack) {
	// check if variable has been declared in the current scope, if not move to the next scope and search
	int inSymTab = 0;
	struct stack_entry *entry = malloc(sizeof *entry); 
	entry = theStack->head;
	while (entry != NULL){
		inSymTab = found(itemName, entry->data);
		if (inSymTab != 0){
			break;
		}
		entry = entry->next;
	}
	if (entry != NULL){
		// once we have the scope that the variable was declared in, search for matching item name and scope
		for(int i=0; i<symTabIndex; i++){
			int str1 = strcmp(symTabItems[i].itemName, itemName);
			int str2 = strcmp(symTabItems[i].scope,entry->data);
			if( str1 == 0 && str2 == 0){			
				char valueHolder[100];
				char* value;
				// get type and array length if available
				strcpy(valueHolder, symTabItems[i].itemValue);
				value = valueHolder;
				return value;
			}
		}
	}
	return "";
}
