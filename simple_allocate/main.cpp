#include<iostream>
#include"mm.h"
using namespace std;

int main(){
    int tmp = mm_init();
    int *sz = (int*)mm_malloc(14*sizeof(int));
    for(int i = 0;i<14;++i){
        *(sz+i) = i;
    }
    mm_show();
    //cout<<*(sz)<<endl;
    return 0;
}
