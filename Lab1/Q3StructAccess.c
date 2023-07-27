// Wap to use struc and access struct member through a struct pointer and display it
// struct of chef

#include <stdio.h>
#include <string.h>

struct Chef
{
    char name[50];
    int age;
    char specialty[100];
};

int main()
{
    struct Chef myChef = {"Ratatouille", 19, "Italian Cuisine"};

    struct Chef *ptrChef;

    ptrChef = &myChef;

    printf("Chef Name: %s\n", ptrChef->name);
    printf("Chef Age: %d\n", ptrChef->age);
    printf("Chef Specialty: %s\n", ptrChef->specialty);

    return 0;
}
