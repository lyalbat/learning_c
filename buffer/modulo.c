
#include <stdio.h>
#include <math.h>
#include <string.h>

int modulo(int a, int d)
{
    int q = floor((double)a / d);
    int res = a - (q * d);
    printf("%d %% %d = %d and q: %d\n", a, d, res,q);
    
    return 1;
}

int main()
{

    char *message = "Hello Embraer (PES)!\n";
    char buffer[6];
    int done = 0;
    int part = 1;

    modulo(strlen(message),6);
    modulo(7,3);
    modulo(13,6);
    // while (!done)
    // {
    //     for (int i = 0; i < count; i++)
    //     {
    //        buffer[i]
    //     }
    // }

    return 0;
}