#ifndef MEMLIB_H_INCLUDE
#define MEMLIB_H_INCLUDE

static char* mem_heap;
static char* mem_brk;
static char* mem_max_addr;
static int max_size = 1 << 10;

void l_init();
void* m_sbrk(int);

#endif