#ifndef MM_H_INCLUDE
#define MM_H_INCLUDE

#include "memlib.h"


#define defspa (1<<4)

#define WSIZE 4
#define DSIZE 8

#define GET(x) ((*(unsigned int*)(x)))
#define PUSH(x) (GET(x) = GET(x) | 1 )
#define POP(x)  (GET(x) = GET(x) & ~1)
#define ISFULL(x) (GET(x) & 1)
#define SIZE(x) (GET(x) & ~7)

#define LOCTAIL(x) ((char*)(x) + SIZE(x) - WSIZE)
#define LOCPRE(x) ((char*)(x) - SIZE(x-WSIZE))
#define LOCSUC(x) ((char*)(x) + SIZE(x))

#define MODIFY(x,s) (GET(x) = s | ISFULL(x))

static char* heap_listp;                            

int mm_init(); 
void* mm_malloc(int); 
void mm_free(void*);    

static void* mm_division(void*,int);  
static void* mm_merge(void*);   
static void* mm_checkpre(void*);    
static void* mm_sbrk(int);      

void mm_show();
static void mm_show_context(void*,int);

#endif