#include<stdio.h>
void ordenarPar(int *a, int *b){
	if(*a > *b){
		int temp = *a;
		*a = *b;
		*b = temp;
	}
}
int main(void){
	int a, b;
	scanf("%d %d", &a, &b);
	ordenarPar(&a, &b);

	printf("%d %d", a, b);
	return 0;
}
