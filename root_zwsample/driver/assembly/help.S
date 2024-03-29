.global _start

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ 数据转移类
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ 数据转移指令
mov r0, r1              @ 将r1数据保存到r0中
mov r0, #0x21           @ 将立即数0x21保存到r0中

@ 特殊功能寄存器存储
mrs r0, cpsr            @ 将特殊寄存器保存到r0
msr cpsr, r0            @ 将r0复制到cpsr中

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ 存储器类
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ 从存储器读取数据
ldr r0, =0x0209C004     @ 保存地址到r0
ldr r1, [r0]            @ 读取地址中的值到r1

# 将数据写入存储器
ldr r0, =0x0209C004     @ 保存地址到r0, 既r0 = 0x0209C004
ldr r1, =0x20000002     @ 保存地址到r1, 既r1 = 0x20000002 
str r1, [r0]            @ 将r1中的值写入到r0所保存的地址中

# 设置sp
ldr sp, =0x80200000     @ 设置sp指针

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ 压栈出栈类
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ 压栈操作
push {r0~r3,r12}        @ 将r0~r3和r12压栈
push {lr}               @ 将lr进行压栈

@ 出栈操作
pop {lr}                @ 将lr出栈
pop {r0~r3,r12}         @ 恢复r0~r3和r12

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ 跳转指令
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
b main                  @ 跳转到main
bl _label               @ 带链接跳转(跳转前将pc保存到lr)

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ 算术运算
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ 加减乘除
add r1, r2, r3          @ r1 = r2 + r3
sub r1, r2, r3          @ r1 = r2 - r3
mul r1, r2, r3          @ r1 = r2 * r3
udiv r1, r2, r3         @ r1 = r2 / r3

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ 逻辑运算
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ 与操作
and r1, r2              @ r1 = r1 & r2
and r1, r2, #immed      @ r1 = r2 & #immed
and r1, r2, r3          @ r1 = r2 & r3

@ 或操作
orr r1, r2              @ r1 = r1 | r2
orr r1, r2, #immed      @ r1 = r2 | #immed
orr r1, r2, r3          @ r1 = r2 | r3    

@ 位清除
bic r1, r2              @ r1 = r1 & (~r2)
bic r1, r2, #immed      @ r1 = r2 & (~#immed)
bic r1, r2, r3          @ r1 = r2 & (~r3)

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ CP15相关
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ 从cp15的c0寄存器的值读取到r1中
mrc p15, 4, r1, c15, c0, 0
