
#include <stdio.h>
struct person
{
   int age;
   float weight;
};
int main()
{
    struct person person1, *personPtr;
	personPtr = &person1;   
    printf("Enter age: ");
    scanf("%d", &personPtr->age);
    printf("Enter weight: ");
    scanf("%f", &person1.weight);
    printf("Displaying:\n");
    
    printf("Age: %d\n", personPtr->age);
    printf("weight: %f\n", personPtr->weight);
    
    printf("Age: %d\n", person1.age);
    printf("weight: %f\n", person1.weight);
    return 0;
}
