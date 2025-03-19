#include <stdio.h>

int main(int cmdC, char* cmdV[]) {
    printf("Given args: ");
    for (int i = 0; i < cmdC; i++)
    {
        printf("%s ", cmdV[i]);
    }
    printf("\n");
    return 0;
}