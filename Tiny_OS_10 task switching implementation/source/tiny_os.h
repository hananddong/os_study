#ifndef TINYOS_H_
#define TINYOS_H_
#include <stdint.h>


typedef uint32_t tTaskStack;

typedef struct _tTask
{
    tTaskStack *stack;
}tTask;







#endif

