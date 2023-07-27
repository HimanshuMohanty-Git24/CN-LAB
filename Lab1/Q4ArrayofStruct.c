// Wap to give an exapmle of using an array of struct passing to a function & display it

#include <stdio.h>
#include <stdlib.h>

struct student
{
    char name[20];
    int roll;
    float marks;
};

void display(struct student s[], int n)
{
    int i;
    printf("\n\nName\t\tRoll\t\tMarks\n");
    for (i = 0; i < n; i++)
    {
        printf("%s\t\t%d\t\t%.2f\n", s[i].name, s[i].roll, s[i].marks);
    }
}

int main()
{
    int i, n;
    printf("Enter the number of students: ");
    scanf("%d", &n);
    struct student s[n];
    for (i = 0; i < n; i++)
    {
        printf("\nEnter the name of student %d: ", i + 1);
        scanf("%s", s[i].name);
        printf("Enter the roll number of student %d: ", i + 1);
        scanf("%d", &s[i].roll);
        printf("Enter the marks of student %d: ", i + 1);
        scanf("%f", &s[i].marks);
    }
    display(s, n);
    return 0;
}