#include <stdio.h>
// Não resolveria pois só passaria uma cópia do valor
// oq nesse caso seria inútil
void dobrar(int* n){
	*n = (*n)*2;
}

int main(void) {
	int n = 21;
	dobrar(&n);
	printf("%d \n", n); /* precisa imprimir 42 */
return 0;
}
