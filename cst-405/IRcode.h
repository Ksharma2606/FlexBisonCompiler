//Made By: Karan Sharma
//Refrence: Help from Adam Harris
//Date: 22/12/2021
bool tRegisterBOOL[10] = {false, false, false, false, false, false, false, false, false, false};
char* tRegisterID[10] = {"$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7","$t8", "$t9"};

struct tempReg{
    char* Name;
    bool Avail;
};

struct tempReg tRegistersAvail[32];

void createRegisters(){
        for(int i = 0; i<10;i++){
            tRegistersAvail[i].Name = tRegisterID[i];
            tRegistersAvail[i].Avail = tRegisterBOOL[i];
        }
}

void showRegisters(){ 
    // fprintf(IRcode,"Register Table\n");
	// fprintf(IRcode,"Name            InUse\n");
	// fprintf(IRcode,"----------------------\n");
	// for (int i=0; i<10; i++){
    //     if(tRegistersAvail[i].Avail == false){
    //         fprintf(IRcode,"%s              FALSE\n",tRegistersAvail[i].Name);
    //     }
    //     else{
	// 	    fprintf(IRcode,"%s              TRUE\n",tRegistersAvail[i].Name);
    //     }
	// }
	// fprintf(IRcode,"----------------------\n");

}

//function to release register in use
void freeReg(char * str){
    for(int i = 0; i < 10; i++){
        if(strcmp(str, tRegistersAvail[i].Name) == 0){
            tRegistersAvail[i].Avail = false;
        }
    }
}

//function to check whether one side of an operator is a register
bool isARegister(char * str){
    for(int i = 0; i < 10; i++){
        if(strcmp(str, tRegistersAvail[i].Name) == 0){
            return true;
        }
    }
    return false;
}

//initialize the output file
void  initIRcodeFile(){
    IRcode = fopen("IRcode.ir", "w+");
}


//function for basic math functions (+ - / *) 
char * emitMath(char * op, char * id1, char * id2, bool release){
    if(release == true){
            fprintf(IRcode,"%s = %s %s %s\n", id1, id1, op, id2);
            int j;
            for(j = 0; j < 10; j++){
                if(id2 == tRegistersAvail[j].Name){
                    tRegistersAvail[j].Avail = false;
                }
            }
            showRegisters();
            return id1;
    }
    for(int i = 0; i < 10; i++){
        if(tRegistersAvail[i].Avail == false){
            fprintf(IRcode,"%s = %s %s %s\n", tRegistersAvail[i].Name, id1, op, id2);
            tRegistersAvail[i].Avail = true;
            showRegisters();
            return tRegistersAvail[i].Name;
        }
    }
    return "";
}

//function for variable assignment
void setVar(char * id1, char * id2){
    fprintf(IRcode,"%s = %s\n", id1, id2);
        for(int j = 0; j < 10; j++){
            if(strcmp(id2, tRegistersAvail[j].Name) == 0){
                tRegistersAvail[j].Avail = false;
            }
        }
    showRegisters();
    return;
}

//function for binary operations
char * emitBINOP(char * op, char * id1, char * id2){
    char * results = malloc(sizeof(char)*50);
    strcpy(results, id1);
    strcat(results, " ");
    strcat(results, op);
    strcat(results, " ");
    strcat(results, id2);

    return results;
}

//function for unary operations
char * emitUNARY(char * op, char * id1){
    char * results = malloc(sizeof(char)*50);
    strcpy(results, "UNOT ");
    strcat(results, id1);
    return results;
}

//functions for if statements and if else statements
void emitStartIF(){
    fprintf(IRcode,"IF (");
}

void emitMidIFELSE(char * expr){
    char * newExpr = expr;
    fprintf(IRcode,"%s) goto <IFBLOCK>\ngoto <ELSEBLOCK>\n", newExpr);
}

void emitMidIF(char * expr){
    char * newExpr = expr;
    fprintf(IRcode,"%s) goto <IFBLOCK>\ngoto <ENDIFBLOCK>\n", newExpr);
}

void emitIFBLOCK(){
    fprintf(IRcode,"<IFBLOCK>\n");
}

void emitEndIFELSEBLOCK(){
    fprintf(IRcode,"goto <ENDELSEBLOCK>\n");
}

void emitEndIFBLOCK(){
    fprintf(IRcode,"<ENDIFBLOCK>\n");
}

void emitELSEBLOCK(){
    fprintf(IRcode,"<ELSEBLOCK>\n");
}

void emitEndELSEBLOCK(){
    fprintf(IRcode,"<ENDELSEBLOCK>\n");
}

//functions for while loops
void emitStartWHILE(){
    fprintf(IRcode,"<WHILE>\n");
}

void emitMidWHILE(char * expr){
    char * newExpr = expr;
    fprintf(IRcode,"IF (%s) goto <WHILEBLOCK>\ngoto <ENDWHILEBLOCK>\n", newExpr);
}

void emitWHILEBLOCK(){
    fprintf(IRcode,"<WHILEBOCK>\n");
}

void emitRestartWHILE(){
    fprintf(IRcode,"goto <WHILE>\n");
}

void emitEndWHILEBLOCK(){
    fprintf(IRcode,"<ENDWHILEBLOCK>\n");
}


//function for write
void emitWrite(char * str){
    freeReg(str);
    char* line = malloc(sizeof(char)*500);
    strcpy(line, "la $a0, ");
    strcat(line, str);
    strcat(line, "\n");
    fprintf(IRcode,"%s", line);
    strcpy(line, "li $v0, 4\n");
    fprintf(IRcode,"%s", line);
    strcpy(line, "syscall\n");
    fprintf(IRcode,"%s", line);
}


//function for mips generation of write int
void emitWriteForInt(char * str){
    freeReg(str);
    char * line = malloc(sizeof(char)*500);
    regex_t reg;
    const char *regex="[0-9]+";
    int ret;
    char err[1024];
    //Read data into variable filecontent
    ret = regcomp(&reg, regex, REG_EXTENDED);
    if (ret != 0) {
        regerror(ret, &reg, err, 1024);
        return;
    }
    int return_value;
    return_value = regexec(&reg, str , 0, NULL, 0);
    regfree(&reg);
    if (return_value == 0){
        strcpy(line, "li $a0, ");
        strcat(line, str);
        strcat(line, "\n");
        fprintf(IRcode,"%s", line);
        strcpy(line, "li $v0, 1\n");
        fprintf(IRcode,"%s", line);
        strcpy(line, "syscall\n");
        fprintf(IRcode,"%s", line);
    }
    else{
        // lw $a0, x
	    // li $v0, 1
	    // syscall
        strcpy(line, "lw $a0, ");
        strcat(line, str);
        strcat(line, "\n");
        fprintf(IRcode,"%s", line);
        strcpy(line, "li $v0, 1\n");
        fprintf(IRcode,"%s", line);
        strcpy(line, "syscall\n");
        fprintf(IRcode,"%s", line);
    }
}


//function for mips generation for write strings
void emitWriteLnForString(char * str){
    freeReg(str);
    char editedStr[500];
    strcpy(editedStr, str);
    editedStr[strlen(editedStr)-1] = '\0';
    char* line = malloc(sizeof(char)*500);
    strcpy(line, "la $a0, ");
    strcat(line, editedStr);
    strcat(line, "\\n\"");
    strcat(line, "\n");
    fprintf(IRcode,"%s", line);
    strcpy(line, "li $v0, 4\n");
    fprintf(IRcode,"%s", line);
    strcpy(line, "syscall\n");
    fprintf(IRcode,"%s", line);
}


//function for writeln
void emitWriteLn(char * str){
    freeReg(str);
    char* line = malloc(sizeof(char)*500);
    strcpy(line, "la $a0, ");
    strcat(line, str);
    strcat(line, "\n");
    fprintf(IRcode,"%s", line);
    strcpy(line, "li $v0, 4\n");
    fprintf(IRcode,"%s", line);
    strcpy(line, "syscall\n");
    fprintf(IRcode,"%s", line);
    emitWriteLnForString("\"\"");
}

//function for arrays
void emitArray(char * expr, char * idL , char * idR){
    if (isARegister(expr)){
        fprintf(IRcode,"%s = 4 * %s\n", expr, expr);
        fprintf(IRcode,"%s = %s[%s]\n", idL, idR, expr);
        freeReg(expr);
        showRegisters();
        return;
    }
    else{
        for(int i = 0; i < 10; i++){
            if(tRegistersAvail[i].Avail == false){
                fprintf(IRcode,"%s = 4 * %s\n", tRegistersAvail[i].Name, expr);
                fprintf(IRcode,"%s = %s[%s]\n", idL, idR, tRegistersAvail[i].Name);
                showRegisters();
                return;
            }
        }
    }
}

//function to obtain register name
char* getRegister(){
    for(int i = 0; i < 10; i++){
        if(tRegistersAvail[i].Avail == false){
            tRegistersAvail[i].Avail = true;
            return tRegistersAvail[i].Name;
        }
    }
    return "";
}

//function to pass a specific token to IR
void writeIR(char * str){
    fprintf(IRcode, "%s\n", str);
}

//function for mips for writeln int
void emitWriteLnForInt(char *str){
    char * line = malloc(sizeof(char)*500);
    regex_t reg;
    const char *regex="[0-9]+";
    int ret;
    char err[1024];
    //Read data into variable filecontent
    ret = regcomp(&reg, regex, REG_EXTENDED);
    if (ret != 0) {
        regerror(ret, &reg, err, 1024);
        return;
    }
    int return_value;
    return_value = regexec(&reg, str , 0, NULL, 0);
    regfree(&reg);
    if (return_value == 0){
        // li $a0, 12
	    // li $v0, 1
        // syscall
        strcpy(line, "li $a0, ");
        strcat(line, str);
        strcat(line, "\n");
        fprintf(IRcode,"%s", line);
        strcpy(line, "li $v0, 1\n");
        fprintf(IRcode,"%s", line);
        strcpy(line, "syscall\n");
        fprintf(IRcode,"%s", line);
        emitWriteLnForString("\"\"");
    }
    else{
        // lw $a0, x
	    // li $v0, 1
	    // syscall
        strcpy(line, "lw $a0, ");
        strcat(line, str);
        strcat(line, "\n");
        fprintf(IRcode,"%s", line);
        strcpy(line, "li $v0, 1\n");
        fprintf(IRcode,"%s", line);
        strcpy(line, "syscall\n");
        fprintf(IRcode,"%s", line);
        emitWriteLnForString("\"\"");
    }
}
