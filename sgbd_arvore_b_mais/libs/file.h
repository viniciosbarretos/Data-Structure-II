#ifndef SGBD_FILE_H
#define SGBD_FILE_H
#include "bplustree.h"

int saveStudent(Student student);
int removeStudent(int line);
Student readStudent(int line);
void showStudentList();
void destroyFile();

#endif //SGBD_FILE_H
