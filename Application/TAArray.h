#ifndef TAARRAY_H
#define TAARRAY_H

#include <string>

// Forward declaration 
class TextArea;



class TAArray {
    private:
        TextArea** elements;  // an Array of TextArea pointers
        int capacity;
        int size;

    public:
        TAArray(int capacity = 10);
        ~TAArray();
        
        bool add(TextArea* ta);
        bool add(TextArea* ta, int index);
        TextArea* get(int index) const;
        TextArea* get(const std::string& id) const;
        TextArea* remove(int index);
        TextArea* remove(const std::string& id);
        
        int getSize() const;
};

#endif