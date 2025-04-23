#include <stdio.h>

#define ISOLATE_MASK(num_bits, start_bit) (((1<<(num_bits))-1)<<(start_bit))

int isolate_k_bits(int n, unsigned int num_bits,unsigned int start_bit){
    return n & ISOLATE_MASK(num_bits, start_bit);
}

int main(){
    int n = 44;
    /*scanf("%d",&n);*/
    int num = 3;
    int start = 3;
    printf("bits isolados: %d\n", isolate_k_bits(n,num,start));
    return 0;
}