.text
.globl main
.ent main

return_func:
lw $ra, 0($sp)
addiu $sp, $sp, 4
jr $ra
.end return_func

li $t0, 2
la $a0, global_num1
move $a1, $t0
sw $a1, 0($a0)
li $t0, 3
la $a0, global_num2
move $a1, $t0
sw $a1, 0($a0)
lw $t0, global_num1
lw $t1, global_num2
mul $t0, $t0, $t1
la $a0, global_num1
move $a1, $t0
sw $a1, 0($a0)
lw $a0, global_num1
li $v0, 1
syscall
end_main: 
j endpro 
.end end_main
 
endpro: 
li $v0,10 
syscall 

.data
global_num1: .word 0
.data
global_num2: .word 0
.data
newline: .asciiz "\n"
.data
start_time: .word 0
end_time: .word 0
duration: .word 0
TIMER_MSG_SRT: .asciiz "\n\nExecuted in: "
TIMER_MSG_END: .asciiz " milliseconds"
