#define NVIC_INT_CTRL           0xE000ED04  // 寄存器的地址
#define NVIC_PENDSVSET          0x10000000	// 需要向寄存器中写入的值
#define NVIC_SYSPRI2            0xE000ED22	// 寄存器的地址
#define NVIC_PENDSV_PRI         0x000000FF	// 需要向寄存器中写入的值

#define MEM32(addr)				*(volatile unsigned long *)(addr)
#define MEM8(addr)				*(volatile unsigned char *)(addr)
	
void triggPendSVC(void) // PendSVC异常触发函数
{
	MEM8(NVIC_SYSPRI2) = NVIC_PENDSV_PRI;
	MEM32(NVIC_INT_CTRL) = NVIC_PENDSVSET;
}

typedef struct 
{
    unsigned long *stack_ptr;
}_Bolck_tpye_t;


_Bolck_tpye_t  *_block_ptr;
_Bolck_tpye_t  block;				// 

void delay(int count)               // 延时函数
{
    while(--count >0);
}


int flag;
unsigned long stack_buffer[1024];   // 缓冲区 用于保存 R4到R11寄存器的值


int main()
{
    block.stack_ptr = &stack_buffer[1024];    // 改地址为stack_buffer[]数组越界处的地址  
    _block_ptr = &block;            // 对结构进行初始化
    for(;;)
    {
        flag = 0;
        delay(100);
        flag = 1;
        delay(100);        
		triggPendSVC();
    }
}







