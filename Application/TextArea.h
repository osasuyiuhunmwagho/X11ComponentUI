#ifndef TEXTAREA_H
#define TEXTAREA_H

#include "defs.h"
#include <X11/Xlib.h>
#include "RGB.h"
#include <string>

class TextArea {
    private:
        Rectangle dimensions;
        std::string text;
        std::string id;
        RGB fill;
        RGB border;

    public:
        // Constructor using individual dimensions
        TextArea(int x, int y, int width, int height, 
                const std::string& id, const std::string& label,
                const RGB& fill = RGB(255, 255, 255), 
                const RGB& border = RGB(0, 0, 0));

        // Constructor using Rectangle object
        TextArea(const Rectangle& rect, const std::string& id, 
                const std::string& label,
                const RGB& fill = RGB(255, 255, 255), 
                const RGB& border = RGB(0, 0, 0));

        // Member functions
        void draw(Display* display, Window win, GC gc, int x, int y);
        bool overlaps(TextArea& ta);

        // Getters
        int getX() const { return dimensions.x; }
        int getY() const { return dimensions.y; }
        int getWidth() const { return dimensions.width; }
        int getHeight() const { return dimensions.height; }
        const Rectangle&   getDimensions() const;


        std::string getId() const;
        const RGB& getFill() const { return fill; }
        const RGB& getBorder() const { return border; }

        // Setters
        void setX(int x) { dimensions.x = x; }
        void setY(int y) { dimensions.y = y; }
        void setWidth(int w) { dimensions.width = w; }
        void setHeight(int h);
        void setId(const std::string& newId) { id = newId; }
        void setFill(const RGB& newFill) { fill = newFill; }
        void setBorder(const RGB& newBorder) { border = newBorder; }
        void setText(const std::string& newText) ;

        void print() const;
};

#endif