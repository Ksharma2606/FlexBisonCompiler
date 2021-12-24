//Made By: Karan Sharma
//Refrence: Help from Adam Harris
//Date: 22/12/2021
//initialize the output file
void  initMIPScodeFile(){
    MIPS = fopen("MIPS.asm", "w+");
}

void emitStartTimer(){


  // la $a0, newline
  // li $v0, 4
  // syscall
  fprintf(MIPS, "la $a0, newline\n");
  fprintf(MIPS, "li $v0, 4\n");
  fprintf(MIPS, "syscall\n");

  //   li $v0, 30
  // syscall
  //   li $v0, 1                        
  // syscall
  
  fprintf(MIPS, "li $v0, 30\n");
  fprintf(MIPS, "syscall\n");
  fprintf(MIPS, "li $v0, 1\n");
  fprintf(MIPS, "syscall\n");
  // la $a0, newline
  // li $v0, 4
  // syscall
  fprintf(MIPS, "la $a0, newline\n");
  fprintf(MIPS, "li $v0, 4\n");
  fprintf(MIPS, "syscall\n");
}

void emitEndTimer(){
  // la $a0, newline
  // li $v0, 4
  // syscall
  fprintf(MIPS, "la $a0, newline\n");
  fprintf(MIPS, "li $v0, 4\n");
  fprintf(MIPS, "syscall\n");

  //   li $v0, 30
  // syscall
//   li $v0, 1                        
  // syscall
  fprintf(MIPS, "li $v0, 30\n");
  fprintf(MIPS, "syscall\n");
  fprintf(MIPS, "li $v0, 1\n");
  fprintf(MIPS, "syscall\n");
  // lw $t0, end_time
  // lw $t1, start_time
  fprintf(MIPS, "lw $t0, end_time\n");
  fprintf(MIPS, "lw $t1, start_time\n");

  // sub $t0, $t1, $t0
  // la $a0, duration
  // sw $t0, 0($a0)
  fprintf(MIPS, "sub $t0, $t0, $t1\n");
  fprintf(MIPS, "la $a0, duration\n");
  fprintf(MIPS, "sw $t0, 0($a0)\n");

  // la $a0, TIMER_MSG_SRT 
  // li $v0, 4
  // syscall
  fprintf(MIPS, "la $a0, TIMER_MSG_SRT\n");
  fprintf(MIPS, "li $v0, 4\n");
  fprintf(MIPS, "syscall\n");

  // la $a0, duration
  // li $v0, 1
  // syscall
  fprintf(MIPS, "lw $a0, duration\n");
  fprintf(MIPS, "li $v0, 1\n");
  fprintf(MIPS, "syscall\n");

  // la $a0, TIMER_MSG_END 
  // li $v0, 4
  // syscall
  fprintf(MIPS, "la $a0, TIMER_MSG_END\n");
  fprintf(MIPS, "li $v0, 4\n");
  fprintf(MIPS, "syscall\n");
}

//function to print the MIPS code
void writeMIPS(char * str){
  fprintf(MIPS, "%s\n", str);
}

// function add $t0 = i + 1;
// lw $t0, dfs_if1_i                           #access main_while1_i for editing
// addiu $t1, $t0, 1                           #perform math
// move $t0, $zero                             #release register  
void emitAddIDNum(char * left, char * right, char * scope, char * t){
  char *reg = getRegister();
  fprintf(MIPS, "lw %s, %s_%s\naddiu %s, %s, %s\nmove %s, $zero\n", reg, scope, left, t, reg, right, reg);
  freeReg(reg); 
}

// exit the main function
// end_main:
// j endpro    #return;
//             #}
// .end end_main
            
// endpro:
// li $v0,10               
// syscall
// .end endpro
void exitMain(){
  char *line = "end_main: \nj endpro \n.end end_main\n \nendpro: \nli $v0,10 \nsyscall \n";
  writeMIPS(line);
}

// function add t = i + a;
// lw $t0, global_i
// lw $t1, global_a
// add $t3, $t0, $t1
// move $t0, $zero
// move $t1, $zero
void emitAddIDOnBoth(char * left, char * right, char * scopeL, char * scopeR, char * t){
  char *reg = getRegister();
  char * reg2 = getRegister();
  fprintf(MIPS, "lw %s, %s_%s\nlw %s, %s_%s\nadd %s, %s, %s\nmove %s, $zero\nmove %s, $zero\n", reg, scopeL, left, reg2, scopeR, right, t, reg, reg2, reg, reg2);
  freeReg(reg);
  freeReg(reg2);
}

// li $t0,100
// addiu $t0, $t0, 5
void emitAddNoID(char * t, char * left, char * right){
  fprintf(MIPS, "li %s,%s\naddiu %s, %s, %s\n", t, left, t, t, right);
}

// function add t = i - a;
// lw $t0, global_i
// lw $t1, global_a
// sub $t3, $t0, $t1
// move $t0, $zero
// move $t1, $zero
void emitSubtIDOnBoth(char * left, char * right, char * scopeL, char * scopeR, char * t){
  char *reg = getRegister();
  char * reg2 = getRegister();
  fprintf(MIPS, "lw %s, %s_%s\nlw %s, %s_%s\nsub %s, %s, %s\nmove %s, $zero\nmove %s, $zero\n", reg, scopeL, left, reg2, scopeR, right, t, reg, reg2, reg, reg2);
  freeReg(reg);
  freeReg(reg2);
}

void emitSubtRegNum(char * left, char * right, char * IDside){
  if (strcmp(IDside, "left") == 0){
    char *reg = getRegister();
    fprintf(MIPS,"li %s, %s\nsub %s, %s, %s\n", reg, right, left, left, reg);
    freeReg(reg);
  }
  else{
    char *reg = getRegister();
    fprintf(MIPS,"li %s, %s\nsub %s, %s, %s\n", reg, left, right, reg, right);
    freeReg(reg);
  }
}

void emitSubtBothReg(char * left, char * right){
  fprintf(MIPS, "sub %s, %s, %s\n", left, left, right);
}


void emitSubtNoID(char * t, char * left, char * right){
  fprintf(MIPS, "li %s,%s\naddiu %s, %s, -%s\n", t, left, t, t, right);
}

void emitSubtIDReg(char * left, char * right, char * scopeL, char * scopeR){
  if (strcmp(scopeL, "") != 0){
    char *reg = getRegister();
    fprintf(MIPS, "lw %s, %s_%s\nsub %s, %s, %s\nmove %s, $zero\n\n", reg, scopeL, left, right, reg, right, reg);
    freeReg(reg);
  }
  else{
    char *reg = getRegister();
    fprintf(MIPS, "lw %s, %s_%s\nsub %s, %s, %s\nmove %s, $zero\n\n", reg, scopeR, right, left, left, reg, reg);
    freeReg(reg);
  }
}

void emitSubtIDNum(char * left, char * right, char * scope, char * t, char * IDSide){
  if (strcmp(IDSide, "left") == 0){
    char *reg = getRegister();
    fprintf(MIPS, "lw %s, %s_%s\naddiu %s, %s, -%s\nmove %s, $zero\n", reg, scope, left, t, reg, right, reg);
    freeReg(reg); 
  }
  else{
    char *reg = getRegister();
    char *regForNum = getRegister();
    fprintf(MIPS, "lw %s, %s_%s\nli %s, %s\nsub %s, %s, %s\nmove %s, $zero\nmove %s, $zero\n", reg, scope, right, regForNum, left, t, regForNum, reg, regForNum, reg);
    freeReg(reg); 
    freeReg(regForNum);
  }
}


// li $t0, 3 
// la $a0, dfs_if1_i                           #access address
// move $a1, $t0                               #set new value
// sw $a1, 0($a0)      
void assignNumber (char * ID, char * num, char * scope){
  char *reg = getRegister();
  fprintf(MIPS, "li %s, %s\nla $a0, %s_%s\nmove $a1, %s\nsw $a1, 0($a0)\n", reg, num, scope, ID, reg);
  freeReg(reg);
}

// li $t0, 5                       #access main_while1_i
// li $t1, 4                                   #4 bits per index
// mult $t0, $t1                               #multiply to obtain bit-index
// mflo $t0                                    #obtain result
void assignArrayWithNumInBrackets (char * num, char * reg){
  char *reg2 = getRegister();
  fprintf(MIPS, "li %s, %s\nli %s, 4\nmult %s, %s\nmflo %s\n", reg, num, reg2, reg, reg2, reg);
  freeReg(reg2);
}

// lw $t0, dfs_if1_a                           #access main_while1_i for editing
// li $t1, 4                                   #4 bits per index
// mult $t0, $t1                               #multiply to obtain bit-index
// mflo $t0  
void assignArrayWithIdInBrackets (char * id, char * scope, char * reg){
  char *reg2 = getRegister();
  fprintf(MIPS, "lw %s, %s_%s\nli %s, 4\nmult %s, %s\nmflo %s\n", reg, scope, id, reg2, reg, reg2, reg);
  freeReg(reg2);
}
                  
// li $t1, 4                                   #4 bits per index
// mult $t0, $t1                               #multiply to obtain bit-index
// mflo $t0  
void assignArrayWithRegInBrackets (char * regInBracket, char * reg){
  fprintf(MIPS, "li %s, 4\nmult %s, %s\nmflo %s\n", reg, reg, regInBracket, reg);
}

// sw $t1, glob_X($t0)                              #save new value
// move $t0, $zero                             #release register
// move $t1, $zero                             #release register
void assignArrayToExpr(char * id , char * scope, char * reg, char * reg2){
  fprintf(MIPS, "sw %s, %s_%s(%s)\nmove %s, $zero\nmove %s, $zero\n", reg2, scope, id, reg, reg, reg2);
}

// li $t0, 5                    
void assignArrayToInt(char * num, char * reg){
  fprintf(MIPS, "li %s, %s\n", reg, num);
}

// lw $t0, dfs_if1_a                           #access main_while1_i for editing                                 #4 bits per index
void assignArrayToId (char * id, char * scope, char * reg){
  fprintf(MIPS, "lw %s, %s_%s\n", reg, scope, id);
}

// move $t1, $t0                             
// move $t0, $zero                             #release register
void assignArrayToReg (char * oldReg, char * reg){
  fprintf(MIPS, "move %s, %s\nmove %s, $zero\n", reg, oldReg, oldReg);
}





// la $a0, dfs_if1_i                           #access address
// move $a1, $t0                               #set new value
// sw $a1, 0($a0)      
void assignReg (char * ID, char * reg, char * scope){
  fprintf(MIPS, "la $a0, %s_%s\nmove $a1, %s\nsw $a1, 0($a0)\n", scope, ID, reg);
}

// add $t0, $t0, $t1
void emitAddBothReg(char * left, char * right){
  fprintf(MIPS, "add %s, %s, %s\n", left, left, right);
}




// lw $t1, global_i
// add $t0, $t1, $t0
// move $t1, $zero
void emitAddIDReg(char * left, char * right, char * scopeL, char * scopeR){
  if (strcmp(scopeL, "") != 0){
    char *reg = getRegister();
    fprintf(MIPS, "lw %s, %s_%s\nadd %s, %s, %s\nmove %s, $zero\n\n", reg, scopeL, left, right, reg, right, reg);
    freeReg(reg);
  }
  else{
    emitAddIDReg(right, left, scopeR, scopeL);
  }
}

// $t0 = $t0 + 4
// addiu $t0, $t0, 4
void emitAddRegNum(char * left, char * right, char * side){
  if (strcmp(side, "left") == 0){
    fprintf(MIPS,"addiu %s, %s, %s\n", left, left, right);
  }
  else{
    fprintf(MIPS,"addiu %s, %s, %s\n", right, right, left);
  }
}

// lw $t0, dfs_if1_a                           #access main_while1_i for editing
// la $a0, dfs_if1_i                           #access address
// move $a1, $t0                               #set new value
// sw $a1, 0($a0) 
void assignID (char * IDL, char * IDR, char * scopeL, char * scopeR){
  char *reg = getRegister();
  fprintf(MIPS, "lw %s, %s_%s\nla $a0, %s_%s\nmove $a1, %s\nsw $a1, 0($a0)\n", reg, scopeR, IDR, scopeL, IDL, reg);
  freeReg(reg);
}






char * getExprType(char expr[50]){
  regex_t reg;
  const char *regex="^-?[0-9]+";
  int ret;
  char err[1024];
  //Read data into variable filecontent
  ret = regcomp(&reg, regex, REG_EXTENDED);
  if (ret != 0) {
    regerror(ret, &reg, err, 1024);
    return "";
  }
  int return_value;
  return_value = regexec(&reg, expr , 0, NULL, 0);
  regfree(&reg);
  if (return_value == 0){
    return "int";
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
      return "";
    }
    int return_value;
    return_value = regexec(&reg, expr , 0, NULL, 0);
    regfree(&reg);
    if (return_value == 0){
      return "id";
    }
    else{
      return "reg";
    }
  }
}

int whileLabelCounter = -1;
int currentWhileCounter;




//mips for WRITELN SEMICOLON
void emitWriteNewLine(){
    freeReg(str); //release register of str
    fprintf(MIPS,"la $a0, newline\n"); //print line to load address of newline
    fprintf(MIPS,"li $v0, 4\n"); //print line to tell MIPS to prepare to print string
    fprintf(MIPS,"syscall\n"); //print string
}

//mips for WRITELN Expr SEMICOLON
//Expr = string
int emitWriteNewLineForString(char * str, struct stack_t *userout, int useroutnumber){
    freeReg(str); //release register of str
    char* useroutlabel = malloc(sizeof(char)*25); //create label for data section
    strcpy(useroutlabel, "user_out_");
    char useroutnum_str[10];
    sprintf(useroutnum_str, "%d", useroutnumber); //obtain current number for label number
    strcat(useroutlabel, useroutnum_str);
    push(userout, str); //push values to stack for use later when data section is created.
    push(userout, useroutlabel);
    useroutnumber++; //increment label nuber
    char* line = malloc(sizeof(char)*500); //create MIPS line
    fprintf(MIPS,"la $a0, %s\n", useroutlabel); //load address of Expr
    fprintf(MIPS,"li $v0, 4\n"); //tell MIPS to prepare to print string
    fprintf(MIPS,"syscall\n"); //print string
    emitWriteNewLine(); //emit new line
    return useroutnumber; //pass label value back to parser.y for use elsewhere
}

//Expr = int
void emitWriteNewLineForInt(char *str, struct stack_t *theStack, char * scope){
    freeReg(str); //release register of str
    regex_t reg;                //determine if register or value
    const char *regex="^-?[0-9]+";
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
      if(strcmp(getExprType(str), "reg") == 0){ //scenario: writeln ID OP NUMBER || writeln ID OP ID
        fprintf(MIPS, "move $a0, %s\n", str); //move calculation to print register
        fprintf(MIPS, "li $v0, 1\n"); //tell MIPS to prepare to print int
        fprintf(MIPS, "syscall\n"); //print int
        emitWriteNewLine(); //emit newline
      }else{                                //scenario: writeln NUMBER
        fprintf(MIPS, "li $a0, %s\n", str); //load number to print register
        fprintf(MIPS, "li $v0, 1\n"); //tell MIPS to prepare to print int
        fprintf(MIPS, "syscall\n"); //print int
        emitWriteNewLine(); //emit newline
      }
    } else if (strcmp(scope, "main") == 0){   //scenario: scope is main when writing an ID
          // lw $a0, x
        // li $v0, 1
        // syscall
          fprintf(MIPS, "li $a0, %s\n", getValue(str, theStack)); //obtain current value of ID (optimized - constant propogation), load into print register
          fprintf(MIPS, "li $v0, 1\n"); //tell MIPS to prepare to print int
          fprintf(MIPS, "syscall\n"); //print int
          emitWriteNewLine(); //emit newline
      } else{
          fprintf(MIPS, "lw $a0, %s_%s\n", scope, str); //load id name (and thus value) int to print register
          fprintf(MIPS, "li $v0, 1\n"); //tell MIPS to prepare to print int
          fprintf(MIPS, "syscall\n"); //print int
          emitWriteNewLine(); //emit newline
      }
}

int emitMIPSWriteForString(char * str, struct stack_t *userout, int useroutnumber){
    freeReg(str); //release register of str
    char* useroutlabel = malloc(sizeof(char)*25); //create label for data section
    strcpy(useroutlabel, "user_out_");
    char useroutnum_str[10];
    sprintf(useroutnum_str, "%d", useroutnumber); //obtain current number for label number
    strcat(useroutlabel, useroutnum_str);
    push(userout, str); //push values to stack for use later when data section is created.
    push(userout, useroutlabel);
    useroutnumber++; //increment label nuber
    fprintf(MIPS,"la $a0, %s\n", useroutlabel); //load address of Expr
    fprintf(MIPS,"li $v0, 4\n"); //tell MIPS to prepare to print string
    fprintf(MIPS,"syscall\n"); //print string
    return useroutnumber; //pass label value back to parser.y for use elsewhere
}

//function for mips generation of write int
void emitMIPSWriteForInt(char * str, struct stack_t *theStack, char * scope){
    freeReg(str); //release register of str
    //perform regular expression to ensure correct formatting
    regex_t reg;
    const char *regex="^-?[0-9]+";
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
      if(strcmp(getExprType(str), "reg") == 0){ //scenario: writeln ID OP NUMBER || writeln ID OP ID
        fprintf(MIPS, "move $a0, %s\n", str); //move calculation to print register
        fprintf(MIPS, "li $v0, 1\n"); //tell MIPS to prepare to print int
        fprintf(MIPS, "syscall\n"); //print int
      }else{                                //scenario: writeln NUMBER
        fprintf(MIPS, "li $a0, %s\n", str); //load number to print register
        fprintf(MIPS, "li $v0, 1\n"); //tell MIPS to prepare to print int
        fprintf(MIPS, "syscall\n"); //print int
      }
    } else if (strcmp(scope, "main") == 0){   //scenario: scope is main when writing an ID
          // lw $a0, x
        // li $v0, 1
        // syscall
          fprintf(MIPS, "li $a0, %s\n", getValue(str, theStack)); //obtain current value of ID (optimized - constant propogation), load into print register
          fprintf(MIPS, "li $v0, 1\n"); //tell MIPS to prepare to print int
          fprintf(MIPS, "syscall\n"); //print int
      } else{
          fprintf(MIPS, "lw $a0, %s_%s\n", scope, str); //load id name (and thus value) int to print register
          fprintf(MIPS, "li $v0, 1\n"); //tell MIPS to prepare to print int
          fprintf(MIPS, "syscall\n"); //print int
      }
}

void emitReadForInt(char * str, char * scope){
  //li $v0, 5                               #prepare for input, saved to v0
  // syscall                                 #accept input
  // move $t0, $v0                           #move to $t0
  //                                     #Prepare to edit main_T
  // lw $a0, main_T                          #access variable
  // la $a0, main_T                          #access address
  //                                     #Save main_T
  // move $a1, $t0                           #set new value
  // sw $a1, 0($a0)                          #save new value
  // move $t0, $zero                         #release $t0
  char *reg = getRegister();  //obtain register for use (store input in prior to storage in variable)
  fprintf(MIPS, "li $v0, 5\n"); //prepare for int input
  fprintf(MIPS, "syscall\n"); //accept input
  fprintf(MIPS, "move %s, $v0\n", reg); //store input in register
  fprintf(MIPS, "la $a0, %s_%s\n", scope, str); //load address of variable
  fprintf(MIPS, "move $a1, %s\n", reg); //move input to saving register
  fprintf(MIPS, "sw $a1, 0($a0)\n"); //save into variable
  freeReg(reg); //free used register
}

void emitReadForChar(char * str, char * scope){
  // ------> NOTICE: THIS FUNCTION DOES NOT WORK YET SINCE MANIPULATION OF CHARS HAS NOT YET BEEN IMPLEMENTED <-----
  //
  //li $v0, 5                               #prepare for input, saved to v0
  // syscall                                 #accept input
  // move $t0, $v0                           #move to $t0
  //                                     #Prepare to edit main_T
  // lw $a0, main_T                          #access variable
  // la $a0, main_T                          #access address
  //                                     #Save main_T
  // move $a1, $t0                           #set new value
  // sw $a1, 0($a0)                          #save new value
  // move $t0, $zero                         #release $t0
  char *reg = getRegister(); //obtain register for use (store user input temporarily)
  fprintf(MIPS, "li $v0, 8\n"); //prepare MIPS to receive char input
  fprintf(MIPS, "syscall\n"); //receive char input
  fprintf(MIPS, "move %s, $v0\n", reg); //move value to temp register
  fprintf(MIPS, "la $a0, %s_%s\n", scope, str); //load address of variable
  fprintf(MIPS, "move $a1, %s\n", reg); //move value to saving register
  fprintf(MIPS, "sw $a1, 0($a0)\n"); //save value
  freeReg(reg); //free used register
}
