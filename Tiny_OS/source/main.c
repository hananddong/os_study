#define NVIC_INT_CTRL           0xE000ED04  // �Ĵ����ĵ�ַ
#define NVIC_PENDSVSET          0x10000000	// ��Ҫ��Ĵ�����д���ֵ
#define NVIC_SYSPRI2            0xE000ED22	// �Ĵ����ĵ�ַ
#define NVIC_PENDSV_PRI         0x000000FF	// ��Ҫ��Ĵ�����д���ֵ

#define MEM32(addr)				*(volatile unsigned long *)(addr)
#define MEM8(addr)				*(volatile unsigned char *)(addr)
	
void triggPendSVC(void) // PendSVC�쳣��������
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

void delay(int count)               // ��ʱ����
{
    while(--count >0);
}


int flag;
unsigned long stack_buffer[1024];   // ������ ���ڱ��� R4��R11�Ĵ�����ֵ


int main()
{
    block.stack_ptr = &stack_buffer[1024];    // �ĵ�ַΪstack_buffer[]����Խ�紦�ĵ�ַ  
    _block_ptr = &block;            // �Խṹ���г�ʼ��
    for(;;)
    {
        flag = 0;
        delay(100);
        flag = 1;
        delay(100);        
		triggPendSVC();
    }
}







