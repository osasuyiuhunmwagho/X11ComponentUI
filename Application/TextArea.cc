#include "TextArea.h"
#include <iostream>
#include <iomanip>

// Constructor with individual dimensions
TextArea::TextArea(int x, int y, int width, int height, 
                   const std::string& id, const std::string& label,
                   const RGB& fill, const RGB& border)
    : dimensions{x, y, width, height}, 
      id(id), 
      text(label), 
      fill(fill), 
      border(border) {}

// Constructor with Rectangle
TextArea::TextArea(const Rectangle& rect, const std::string& id, 
                   const std::string& label,
                   const RGB& fill, const RGB& border)
    : dimensions(rect), 
      id(id), 
      text(label), 
      fill(fill), 
      border(border) {}

void TextArea::print() const {
    std::cout << "TextArea id: " << id << std::endl
              << "Preferred location: " << dimensions.x << ", " << dimensions.y << std::endl
              << "Size: " << dimensions.width << "x" << dimensions.height << std::endl
              << "Text: " << text << std::endl;
}

bool TextArea::overlaps(TextArea& ta) {
    return dimensions.overlaps(ta.dimensions);
}

void TextArea::draw(Display* display, Window win, GC gc, int parentX, int parentY) {
    // --- Start: Height calculation logic ---
    XFontStruct* font_info = XLoadQueryFont(display, "fixed");
    if (!font_info) return;

    int charHeight = font_info->ascent + font_info->descent;
    int maxWidth = dimensions.width - 10;
    int lineCount = 0;
    std::string currentLine, currentWord;

    // Manual text wrapping to calculate required height
    for (char c : text) {
        if (c == ' ' || c == '\n') {
            std::string testLine = currentLine.empty() ? currentWord : currentLine + " " + currentWord;
            int textWidth = XTextWidth(font_info, testLine.c_str(), testLine.length());
            if (textWidth > maxWidth) {
                lineCount++;
                currentLine = currentWord;
            } else {
                currentLine = testLine;
            }
            currentWord.clear();
            if (c == '\n') lineCount++;
        } else {
            currentWord += c;
        }
    }
    if (!currentWord.empty()) lineCount++;

    // Update TextArea height based on wrapped text
    int requiredHeight = lineCount * charHeight + 10;
    if (requiredHeight > dimensions.height) {
        dimensions.height = requiredHeight; // Update height BEFORE drawing
    }
    XFreeFont(display, font_info);
    //trying to calculate height
    int x = parentX + dimensions.x;
    int y = parentY + dimensions.y;

    XSetForeground(display, gc, fill.getColour());
    XFillRectangle(display, win, gc, x, y, dimensions.width, dimensions.height);

    XSetForeground(display, gc, border.getColour());
    XDrawRectangle(display, win, gc, x, y, dimensions.width, dimensions.height);

    // Load font for text rendering
    font_info = XLoadQueryFont(display, "fixed");
    if (!font_info) {
        std::cerr << "Error: Failed to load font!" << std::endl;
        return;
    }

    // trying to draw text centered in the rectangle
    XSetFont(display, gc, font_info->fid);

    int totalTextHeight = lineCount * charHeight;
    int textY = y + (dimensions.height - totalTextHeight) / 2 + font_info->ascent;

    // Buffer for manually storing wrapped text lines
    const int MAX_LINES = 20;  
    std::string lines[MAX_LINES];
    int actualLineCount = 0;

    currentLine.clear();
    currentWord.clear();

    for (size_t i = 0; i < text.size(); ++i) {
        char c = text[i];

        if (c == ' ' || c == '\n' || i == text.size() - 1) {
            // Add last character if it's the end of the string
            if (i == text.size() - 1 && c != ' ' && c != '\n') {
                currentWord += c;
            }

            // this is to Check if adding this word would overflow the width
            std::string testLine = (currentLine.empty()) ? currentWord : currentLine + " " + currentWord;
            int textWidth = XTextWidth(font_info, testLine.c_str(), testLine.length());

            if (textWidth > maxWidth) {
                // Store the current line in the array and move to next
                if (actualLineCount < MAX_LINES) {
                    lines[actualLineCount++] = currentLine;
                }
                currentLine = currentWord;
            } else {
                currentLine = testLine;
            }

            //to Reset current word
            currentWord.clear();

            // If the character is a newline, force a new line
            if (c == '\n') {
                if (actualLineCount < MAX_LINES) {
                    lines[actualLineCount++] = currentLine;
                }
                currentLine.clear();
            }
        } else {
            currentWord += c;
        }
    }

    // Store last line if any text remains
    if (!currentLine.empty() && actualLineCount < MAX_LINES) {
        lines[actualLineCount++] = currentLine;
    }

    // Draw text line by line
    XSetForeground(display, gc, 0x000000); 
    for (int i = 0; i < actualLineCount; i++) {
        int textWidth = XTextWidth(font_info, lines[i].c_str(), lines[i].length());
        int textX = x + (dimensions.width - textWidth) / 2; // Centered horizontally
        XDrawString(display, win, gc, textX, textY, lines[i].c_str(), lines[i].length());
        textY += charHeight; 
    }

    XFreeFont(display, font_info);
}

std::string TextArea::getId() const {
    return id;
}

void TextArea::setText(const std::string& newText) {
    text = newText;
}

void TextArea::setHeight(int newHeight) {
    dimensions.height = newHeight;
}

const Rectangle& TextArea::getDimensions() const {
    return dimensions;
}