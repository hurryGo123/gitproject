#include "mm.h"

int mm_init(){
    l_init();
    char* bp = heap_listp; 
    if((heap_listp = (char*)m_sbrk(4)) == (void*)-1){
        heap_listp = bp;
        return 0;
    }
    PUSH(heap_listp);           MODIFY(heap_listp,0);
    PUSH(heap_listp + WSIZE);   MODIFY(heap_listp + WSIZE, 2*WSIZE);
    PUSH(heap_listp + 2*WSIZE); MODIFY(heap_listp + 2*WSIZE,2*WSIZE);
    PUSH(heap_listp + 3*WSIZE); MODIFY(heap_listp + 3*WSIZE,0);
    heap_listp += 3*WSIZE;

    mm_sbrk(defspa);
    return 1;
}

static void* mm_sbrk(int bytes){
    char* bp;

    bytes = (bytes+DSIZE-1)/DSIZE * DSIZE;

    if((bp = (char*)m_sbrk(bytes/WSIZE)) == (void*)-1){
        return 0;
    }
    POP(bp-WSIZE);             MODIFY(bp-WSIZE,bytes);          MODIFY(LOCTAIL(bp-WSIZE),bytes);
    PUSH(bp+bytes-WSIZE);      MODIFY(bp+bytes-WSIZE,0);
    
    bp = (char*)mm_checkpre(bp-WSIZE);

    return (void*)bp;
}

void* mm_malloc(int len){
    int tar = (len+DSIZE-1+DSIZE)/DSIZE*DSIZE;
    int tmp = SIZE(heap_listp);
    char* dp = heap_listp;

    while(tmp != 0 ){
        if(tmp >= tar && ISFULL(dp) == 0)
            break;
        dp = LOCSUC(dp);
        tmp = SIZE(dp);
    }
    if(tmp == 0){
        
        dp = (char*)mm_sbrk(tar);
    }

    dp = (char*)mm_division(dp,tar);
    return (void*)(dp+WSIZE);
}

void mm_free(void* ptr){
    char* head = (char*)((char*)(ptr)-WSIZE);
    char* tail =  (char*)LOCTAIL(head);
    POP(head);             POP(tail);
    mm_merge(head);
}

static void* mm_merge(void* ptr){
    char* tmp = (char*)ptr;
    tmp = (char*)mm_checkpre(tmp);
    if(SIZE(LOCSUC(tmp)) != 0)
        tmp = (char*)mm_checkpre(tmp);
    
    return tmp;
}

static void* mm_checkpre(void* ptr){
    char* head = (char*) ptr;
    char* newhead = (char*)LOCPRE(head);
    if(ISFULL(LOCPRE(head)) == 0){
        int newsize = SIZE(head) + SIZE(newhead);
        MODIFY(head,0);
        MODIFY(head-WSIZE,0);
        MODIFY(newhead,newsize);
        MODIFY(LOCTAIL(newhead),newsize);
        head = newhead;
    }
    return head;
}
static void* mm_division(void* ptr,int bytes){
    int sizes = SIZE(ptr);
    char* head = (char*)ptr,*newhead;
    PUSH(head);         MODIFY(head,bytes);
    PUSH(LOCTAIL(head));MODIFY(LOCTAIL(head),bytes);
    sizes -= bytes;
    newhead = (char*)LOCSUC(head);
    POP(newhead);       MODIFY(newhead,sizes);
    POP(LOCTAIL(newhead));  MODIFY(LOCTAIL(newhead),sizes);

    return head;
}

void mm_show(){
    int* begin = (int*)(heap_listp - 3*WSIZE);
    //cout<<"begin: "<<*begin<<endl;
    //cout<<"head: "<<*(begin+1)<<endl;
    
    begin = (int*)heap_listp;
    int tmp = SIZE(begin);
    while(tmp != 0){
        //cout<<SIZE(begin)<<':';
        mm_show_context(begin,tmp-2*WSIZE);
        begin = (int*)LOCSUC(begin);
        tmp = SIZE(begin);
        
    }
    
    //cout<<"tail: "<<*(begin)<<endl;
}
static void mm_show_context(void* ptr,int len){
    char* head = (char*)ptr;
    head++;
    while(len--){
        //cout<<(int)(*head)<<' ';
        ++head;
    }
    //cout<<endl;
}