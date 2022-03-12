#include <stdio.h>


typedef struct
{
   int age;
   int weight;
}person;
int main(){
	
	
	
person a;
// tao bien a kieu person //
person *p;
// tao bien con tro p kieu person(Luu dia chi cua bien khac) //
p = &a;

&p->age = 10;
&p->weight = 10;





return 0;




}

