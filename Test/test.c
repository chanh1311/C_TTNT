#include<stdio.h>

typedef struct{
	int a ;
	int b ;
}test;

int main(){
	test t;
	t.a = 5;
	t.b = 10;
	printf("%d",t.a);
	printf("\n%d",t.b);
	
	return 0;
}	
