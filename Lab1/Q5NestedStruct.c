// Wap to implememnt the nested struct with a suitable example

#include <stdio.h>
#include <stdlib.h>

struct student
{
    char name[20];
    int roll;
    float marks;
};

struct class
{
    char name[20];
    int n;
    struct student s[100];
};

void display(struct class c)
{
    int i;
    printf("\n\nName\t\tRoll\t\tMarks\n");
    for (i = 0; i < c.n; i++)
    {
        printf("%s\t\t%d\t\t%.2f\n", c.s[i].name, c.s[i].roll, c.s[i].marks);
    }
}

int main()
{
    int i;
    struct class c;
    printf("Enter the name of the class: ");
    scanf("%s", c.name);
    printf("Enter the number of students: ");
    scanf("%d", &c.n);
    for (i = 0; i < c.n; i++)
    {
        printf("\nEnter the name of student %d: ", i + 1);
        scanf("%s", c.s[i].name);
        printf("Enter the roll number of student %d: ", i + 1);
        scanf("%d", &c.s[i].roll);
        printf("Enter the marks of student %d: ", i + 1);
        scanf("%f", &c.s[i].marks);
    }
    display(c);
    return 0;
}