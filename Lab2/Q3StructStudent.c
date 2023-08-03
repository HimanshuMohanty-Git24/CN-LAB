// Q3.wap in c to assign values to each member of a following structure ,
// pass the structure to a function using call by value, another function through
// call by reference display value of each member

#include <stdio.h>
#include <string.h>

struct dob
{
    int day;
    int month;
    int year;
};

struct student_info
{
    int roll_no;
    float cgpa;
    char name[20];
    struct dob age;
};

void display2(struct student_info s) // call by value
{
    printf("Name: %s\n", s.name);
    printf("Roll No: %d\n", s.roll_no);
    printf("CGPA: %f\n", s.cgpa);
    printf("DOB: %d/%d/%d\n", s.age.day, s.age.month, s.age.year);
}

void display(struct student_info *s) // call by reference
{
    printf("Name: %s\n", s->name);
    printf("Roll No: %d\n", s->roll_no);
    printf("CGPA: %f\n", s->cgpa);
    printf("DOB: %d/%d/%d\n", s->age.day, s->age.month, s->age.year);
}

int main()
{
    struct student_info s1;
    printf("Enter Name: ");
    scanf("%s", s1.name);
    printf("Enter Roll No: ");
    scanf("%d", &s1.roll_no);
    printf("Enter CGPA: ");
    scanf("%f", &s1.cgpa);
    printf("Enter DOB: ");
    scanf("%d %d %d", &s1.age.day, &s1.age.month, &s1.age.year);
    printf("\nDisplaying using call by reference\n");
    display(&s1);
    printf("\nDisplaying using call by value\n");
    display2(s1);
    return 0;
}
