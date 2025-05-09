#ifndef FLOWPANEL_H
#define FLOWPANEL_H

#include <X11/Xlib.h>
#include <string>
#include "defs.h"      // For the Rectangle struct
#include "RGB.h"
#include "TAArray.h"
#include "TextArea.h"

class FlowPanel {
private:
    int xgap, ygap;
    std::string id;
    Rectangle dimensions;
    TAArray taArray;     
    
    

public:
    // Constructors
    FlowPanel(int x, int y, int width, int height, const std::string& id, int xgap = 10, int ygap = 10);
    FlowPanel(const Rectangle& dimensions, const std::string& id, int xgap = 10, int ygap = 10);
    FlowPanel(const FlowPanel& other); 

    
    bool addTextArea(TextArea* ta);
    bool addTextArea(TextArea* ta, int index);

    // Functions to get TextArea
    TextArea* getTextArea(const std::string& id) const;
    TextArea* getTextArea(int index) const;
    const Rectangle& getDimensions() const;

    
    

    TextArea* removeTextArea(const std::string& id);
    TextArea* removeTextArea(int index);


    bool overlaps(const FlowPanel& panel) const;

    const std::string& getId()      const;

    // Draw function to render FlowPanel and its TextAreas in a flow layout
    void draw(Display* display, Window win, GC graphicsContext) const;

    // Print functions
    void print() const;
    void printTextAreas() const;
};
#endif