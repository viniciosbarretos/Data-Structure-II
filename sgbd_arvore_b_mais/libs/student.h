#ifndef DATA_STRUCTURE_STUDENT_H
#define DATA_STRUCTURE_STUDENT_H

typedef struct Student {
    int id;
    char name[20];
    char email[40];
    int age;
    char status;
} Student;

Student getStudent(int defaultID);

#endif //DATA_STRUCTURE_STUDENT_H
