#include <stdio.h>
#define MAX_SIZE 100

void read_file(){
    char txt[MAX_SIZE];
    int i = 0;
    while (txt[i] != EOF && i<MAX_SIZE){
        scanf(" %c", &txt[i]);
        printf("dado lido: %c\n",txt[i]);
        i++;
    }
}

int main(){
    read_file();
    return 0;
}