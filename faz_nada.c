#include <stdio.h>
#include <stdlib.h>

int main(){
    int *A;
    A = (int*)malloc(sizeof(int));
    if(*A == 1){
	*A = 1;
	printf("%d\n",*A);
    } else{
	*A = 0;
	printf("%d\n",*A);
    }
    return 0;
}

