#include "TAArray.h"
#include "TextArea.h"
#include <iostream>


TAArray::TAArray(int capacity) : capacity(capacity), size(0) {
    elements = new TextArea*[capacity];
}

TAArray::~TAArray() {
    for (int i = 0; i < size; ++i) {
        delete elements[i]; 
    }
    delete[] elements; 
}

bool TAArray::add(TextArea* ta) {
    if (size >= capacity) return false;  

    elements[size++] = ta;  
    
    return true;
}

bool TAArray::add(TextArea* ta, int index) {
    if (size >= capacity || index < 0 || index > size){
            return false; 
    }

    // Shift elements right
    for (int i = size; i > index; i--) {
        elements[i] = elements[i - 1];
    }

   
    elements[index] = ta;
    size++;
    return true;
}
TextArea* TAArray::get(int index) const {
    if (index < 0 || index >= size) return nullptr;
    return elements[index];
}

TextArea* TAArray::get(const std::string& id) const {
    for (int i = 0; i < size; ++i) {
        if (elements[i]->getId() == id) {
            return elements[i];
        }
    }
    return nullptr;
}

TextArea* TAArray::remove(const std::string &id) {

    for (int i = 0; i < size; ++i)
        if (elements[i]->getId() == id)
            return remove(i);

    return nullptr;

}

TextArea* TAArray::remove(int index) {
    if (index < 0 || index >= size) {
        return nullptr; // Invalid index
    }
    TextArea* removed = elements[index];

    //shift the elements to keep the  order
    for (int i = index; i < size - 1; i++) {
        elements[i] = elements[i + 1];
    }
    elements[size - 1] = nullptr; 
    size--;

    return removed;
}
int TAArray::getSize() const {
    return size;
}