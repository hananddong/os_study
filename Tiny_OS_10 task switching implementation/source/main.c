#include "tiny_os.h"


tTask * current_task;
tTask * next_task;
tTask * task_table[2];

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




void delay(int count)               // 延时函数
{
    while(--count >0);
}



tTask tTask1;
tTask tTask2;


tTaskStack task1Env[1024];
tTaskStack task2Env[1024];



void tTask_init(tTask * task, void (*entry)(void *), void *param, tTaskStack * stack)
{
    *(--stack) = (unsigned long)(1<<24);  // XPSR,
    *(--stack) = (unsigned long)entry;    // 程序的入口地址
    *(--stack) = (unsigned long)0x14;     // r14(LR),
    *(--stack) = (unsigned long)0x12;     // r12 也没有用到
    *(--stack) = (unsigned long)0x3;      // r3
    *(--stack) = (unsigned long)0x2;      // r2
    *(--stack) = (unsigned long)0x1;      // r1
    *(--stack) = (unsigned long)param;    // r0 用于保存程序的入口参数 
    
    *(--stack) = (unsigned long)0x11;      // r11,未用
    *(--stack) = (unsigned long)0x10;      // r10,未用
    *(--stack) = (unsigned long)0x9;       // r9,未用
    *(--stack) = (unsigned long)0x8;       // r8,未用
    *(--stack) = (unsigned long)0x7;       // r7,未用
    *(--stack) = (unsigned long)0x6;       // r6,未用
    *(--stack) = (unsigned long)0x5;       // r5,未用
    *(--stack) = (unsigned long)0x4;       // r4,未用
    
    task->stack = stack ;
}

/**
    调度函数
*/
void t_task_sched()
{
    if( current_task == task_table[0] )
    {
        next_task = task_table[1];
    }
    else
    {
        next_task = task_table[0];
    }
    t_task_switch();
}

int task1_flag;
void task1_entry (void * param)
{
    for(;;)
    {
        task1_flag = 0 ;
        delay(100);
        task1_flag = 1 ;
        delay(100);
    
    }
}

int task2_flag;
void task2_entry (void * param)
{
    for(;;)
    {
        task2_flag = 0 ;
        delay(100);
        task2_flag = 1 ;
        delay(100);
    
    }
}


int main()
{
    tTask_init(&tTask1,task1_entry,(void *)0x11111111,&task1Env[1024]);
    tTask_init(&tTask2,task2_entry,(void *)0x22222222,&task2Env[1024]);

    task_table[0] = &tTask1;
    task_table[1] = &tTask2;
    
    next_task = task
    
}







