#include "memlib.h"

void l_init(){
    mem_heap = new char[max_size];
    mem_brk = mem_heap;
    mem_max_addr = mem_heap + max_size;
}

void* m_sbrk(int Wlen){
    char* oldbrk = mem_brk;
    if(Wlen == 0)
        return (void*)-1;
    int len = Wlen % 2 == 1 ? (Wlen+1)*4 : Wlen*4;              //双字对齐,一字四字节,转字节
    if(len + mem_brk > mem_max_addr)
        return (void*)-1;
    mem_brk = mem_brk + len;
    return (void*)oldbrk;
}