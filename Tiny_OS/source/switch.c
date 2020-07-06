__asm void PendSV_Handler(void)
{
	IMPORT _block_ptr      // IMPORT： 定义表明这是一个外部变量的标号，不是在本程序定义的 
                           // EXPORT： 翻译为出口或输出，表明该符号可以被外部模块使用，类似于C中的extern功能
	
	LDR R0, =_block_ptr    // LDR伪指令：将指定标号的值赋给r0
	LDR R0, [R0]           // LDR指令：将存储器地址为R0的字数据读入寄存器R0. (通俗解释：从R0寄存器指向的地址中取出一个字的数据，存储到R1寄存器中)
	LDR R0, [R0]

	STMDB	R0!, {R4-R11}  // 将寄存器压栈（保存寄存器的值）
	
	LDR R1, =_block_ptr
	LDR R1, [R1]
	STR R0, [R1]           // 
	
	ADD R4, R4, #1
	ADD R5, R5, #1
	
	LDMIA   R0!, {R4-R11}  // 寄存器弹出栈（恢复寄存器的值）
	
	BX LR
}


