#ifndef LIST_H
#define LIST_H

#define MAX_ARR 64

#include "Student.h"

class StudentArray
{
  public:
    StudentArray();
    ~StudentArray();

    bool add(Student*);
    
    Student* get(string name);
    Student* get(int index);

    Student* remove(string name);
    Student* remove(int index);


    bool isFull(){return size == MAX_ARR;}
    int getSize(){return size;}
    void print();
    

  private:
    Student** elements;
    int size;
   
};

#endif

