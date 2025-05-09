#include "FlowPanel.h"
#include <iostream>

// Constructor 1: Initialize with  x, y, width, height
FlowPanel::FlowPanel(int x, int y, int width, int height,
                     const std::string &id,
                     int xgap, int ygap)
    : id(id),
      dimensions{x, y, width, height},
      xgap(xgap),
      ygap(ygap),
      taArray(10) 
{
}

// Constructor 2: Initialize with a Rectangle 
FlowPanel::FlowPanel(const Rectangle &rect,
                     const std::string &id,
                     int xgap, int ygap)
    : id(id),
      dimensions(rect),
      xgap(xgap),
      ygap(ygap),
      taArray(10)
{
}

// Deep Copy Constructor: this copies existing FlowPanel (TextAreas deep copied)
FlowPanel::FlowPanel(const FlowPanel &other)
    : id(other.id),
      dimensions(other.dimensions),
      xgap(other.xgap),
      ygap(other.ygap),
      taArray(other.taArray.getSize()) 
{
    // Copy each TextArea
    for (int i = 0; i < other.taArray.getSize(); ++i) {
        TextArea *orig = other.taArray.get(i);
        if (orig) {
            TextArea *copy = new TextArea(*orig);
            taArray.add(copy);
        }
    }
}



// Getters
const std::string& FlowPanel::getId() const {
    return id;
}
const Rectangle& FlowPanel::getDimensions() const{
    return dimensions;
}

bool FlowPanel::addTextArea(TextArea *ta) {
    return taArray.add(ta);
}

bool FlowPanel::addTextArea(TextArea *ta, int index) {
    return taArray.add(ta, index);
}

// Remove TextArea (this returns pointer to removed TextArea) --commenting this to understand
TextArea* FlowPanel::removeTextArea(const std::string &id) {
    return taArray.remove(id); 
}

TextArea* FlowPanel::removeTextArea(int index) {
    return taArray.remove(index); 
}


TextArea* FlowPanel::getTextArea(const std::string &id) const {
    return taArray.get(id);
}

TextArea* FlowPanel::getTextArea(int index) const {
    return taArray.get(index);
}


bool FlowPanel::overlaps(const FlowPanel &panel) const {
    return dimensions.overlaps(panel.dimensions);
}

// to Draw the FlowPanel and its TextAreas in a flow layout
void FlowPanel::draw(Display *display, Window window, GC gc) const {
    std::cout << "Drawing FlowPanel \"" << id << "\" at ("
              << dimensions.x << ", " << dimensions.y << ") size("
              << dimensions.width << ", " << dimensions.height << ")\n";

    int currentX = dimensions.x + xgap;
    int currentY = dimensions.y + ygap;
    int maxHeightInRow = 0;

    for (int i = 0; i < taArray.getSize(); ++i) {
        TextArea *ta = taArray.get(i);
        if (!ta) continue;


        ta->draw(display, window, gc, -1000, -1000);
        Rectangle tRect = ta->getDimensions();

        // If next TextArea doesn't fit in the current row, move to the next row
        if (currentX + tRect.width + xgap > dimensions.x + dimensions.width) {
            currentX = dimensions.x + xgap;
            currentY += maxHeightInRow + ygap;
            maxHeightInRow = 0;
        }

        // Stop drawing if TextArea would be outside FlowPanel
        if (currentY + tRect.height + ygap > dimensions.y + dimensions.height) {
            break;
        }

        // "Draw" the TextArea at (currentX, currentY)
        ta->draw(display, window, gc, currentX, currentY);

        currentX += tRect.width + xgap;
        if (tRect.height > maxHeightInRow) {
            maxHeightInRow = tRect.height;
        }
    }
}


void FlowPanel::print() const {
    std::cout << "FlowPanel: " << id << "\n"
              << "Position: " << dimensions.x << ", " << dimensions.y << "\n"
              << "Size: " << dimensions.width << ", " << dimensions.height << "\n"
              << "Num TextAreas: " << taArray.getSize() << "\n";
}


void FlowPanel::printTextAreas() const {
    for (int i = 0; i < taArray.getSize(); ++i) {
        TextArea *ta = taArray.get(i);
        if (ta) {
            ta->print();
        }
    }
}

// FlowPanel::FlowPanel(int x, int y, int width, int height, const std::string& id, int xgap, int ygap)
//     : dimensions{x, y, width, height}, id(id), xgap(xgap), ygap(ygap), textAreaCount(0) {
// }

// FlowPanel::FlowPanel(const Rectangle& dimensions, const std::string& id, int xgap, int ygap)
//     : dimensions(dimensions), id(id), xgap(xgap), ygap(ygap), textAreaCount(0) {
// }



// FlowPanel::FlowPanel(const FlowPanel& other)
//     : dimensions(other.dimensions), id(other.id), xgap(other.xgap), ygap(other.ygap), textAreaCount(other.textAreaCount) {
//     for (int i = 0; i < other.textAreaCount; i++) {
//         array.add(other.array.get(i));
//     }
// }
// void FlowPanel::draw(Display* display, Window win, GC gc) const {
//     // Example: Draw panel background (assuming RGB is handled)
//     XSetForeground(display, gc, 0xFFFFFF); // White background for demonstration
//     XFillRectangle(display, win, gc, dimensions.x, dimensions.y, dimensions.width, dimensions.height);
//     // Draw each TextArea
//     for (int i = 0; i < textAreaCount; ++i) {
//         TextArea* ta = array.get(i);
//         ta->draw(display, win, gc, dimensions.x, dimensions.y); // Ensure TextArea has a draw method
//     }
// }
// bool FlowPanel::addTextArea(TextArea* ta) {
//     if (textAreaCount >= 100) return false;
//     array.add(ta);
//     textAreaCount++;
//     return true;
// }

// // Adds a TextArea at a specific index
// bool FlowPanel::addTextArea(TextArea* ta, int index) {
//     if (textAreaCount >= 100 || index < 0 || index > textAreaCount) return false;
//     array.add(ta, index);
//     textAreaCount++;
//     return true;
// }


// TextArea* FlowPanel::getTextArea(const std::string& id) const {
//     for (int i = 0; i < textAreaCount; i++) {
//         if (array.get(i)->getId() == id) {
//             return array.get(i);
//         }
//     }
//     return nullptr;
// }

// TextArea* FlowPanel::getTextArea(int index) const {
//     if (index < 0 || index >= textAreaCount) return nullptr;
//     return array.get(index);
// }

// TextArea* FlowPanel::removeTextArea(const std::string& id) {
//     for (int i = 0; i < textAreaCount; i++) {
//         if (array.get(i)->getId() == id) {
//             TextArea* removed = array.remove(i);
//             if (removed) {
//                 textAreaCount--;
//             }

//             return removed;
//         }
    
//     }
//     return nullptr;
// }

// TextArea* FlowPanel::removeTextArea(int index) {
//     if (index < 0 || index >= textAreaCount) return nullptr;
//     TextArea* removed = array.remove(index);

//     if (removed) {
//         textAreaCount--;  // debugging
//     }
    
//     return removed;
// }



// bool FlowPanel::overlaps(const FlowPanel& panel) const {
//     return dimensions.overlaps(panel.dimensions);
// }

// std::string FlowPanel::getId() const {
//     return id;
// }

// Rectangle FlowPanel::getDimensions() const {
//     return dimensions;
// }
// void FlowPanel::print() const {
//     std::cout << "FlowPanel ID: " << id 
//               << " Position: (" << dimensions.x << ", " << dimensions.y << ")"
//               << " Size: " << dimensions.width << "x" << dimensions.height << std::endl;
// }
// void FlowPanel::printTextAreas() const {
//     for (int i = 0; i < textAreaCount; i++) {
//         std::cout << "- " << array.get(i)->getId() << std::endl;
//     }
// }
