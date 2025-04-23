#include <stdio.h>
#include <math.h>

#define SETS_K_BIT(n,k)  ((n) | ((1<<(k))))
#define CLEARS_K_BIT(n,k) ((n) & (~(1<<(k))))
#define IS_SET_K_BIT(n,k) (((n)&(1<<(k))) != 0)


int subfield(int x, int y, unsigned k){
    int num_bits = (k-1)-(int)log2(y);
    printf("num_bits: %d\n",num_bits);
    for (int i = 0; i < num_bits; i++)
    {
        if(IS_SET_K_BIT(y,i)){
            x = SETS_K_BIT(x,i+num_bits);
        }
        else{
            x = CLEARS_K_BIT(x,i+num_bits);
        }
    }
    return x;
}

int main(){
    int x = 0;
    int y = 0;
    int num = 0;

    scanf("%d %d %d",&x,&y,&num);

    printf("subfield: %d\n", subfield(x,y,num));
    return 0;
}