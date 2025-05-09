#include "CuWindow.h"
#include <iostream>

using namespace std;

// Constructor
CuWindow::CuWindow(std::string name, int width, int height, RGB background) 
    : width(width), height(height), name(name), background(background), panelCount(0) {

    display = XOpenDisplay(NULL);
    if (!display) {
        cerr << "Error: Unable to open X display" << endl;
        exit(1);
    }

    // Create X11 window
    window = XCreateSimpleWindow(display, RootWindow(display, 0), 0, 0, width, height, 1,
                                 BlackPixel(display, 0), WhitePixel(display, 0));

    // Create graphics context
    graphicsContext = XCreateGC(display, window, 0, 0);

    // Set background color
    XSetWindowBackground(display, window, (background.getR() << 16) | 
                                            (background.getG() << 8) | background.getB());

    XMapWindow(display, window);
    XFlush(display);
    usleep(100000);
}

// Destructor
CuWindow::~CuWindow() {
    XFreeGC(display, graphicsContext);
    XDestroyWindow(display, window);
    XCloseDisplay(display);
}

// Set background color
void CuWindow::setBackground(const RGB& color) {
    background = color;
}

// Add a FlowPanel to the PanelArray
bool CuWindow::addPanel(FlowPanel* panel) {
    if (!panel || panels.getSize() >= MAX_PANELS) return false;

    // Check if panel overlaps existing panels
    for (int i = 0; i < panels.getSize(); i++) {
        if (panels.get(i)->overlaps(*panel)) {
            return false;  // Overlap detected, reject panel
        }
    }

    // Ensure panel fits inside the window boundaries
    Rectangle rect = panel->getDimensions();
    if (rect.x + rect.width > width || rect.y + rect.height > height) {
        return false;  // Panel is out of bounds
    }

    return panels.add(panel);
}

// Remove a FlowPanel from the PanelArray and return it to the user
FlowPanel* CuWindow::removePanel(const std::string& id) {
    for (int i = 0; i < panels.getSize(); i++) {
        if (panels.get(i)->getId() == id) { // <-- FIXED: Use getId()
            return panels.remove(i);
        }
    }
    return nullptr;
}

// Retrieve a FlowPanel by ID (without removing it)
FlowPanel* CuWindow::getPanel(const std::string& id) const {
    for (int i = 0; i < panels.getSize(); i++) {

        if (panels.get(i)->getId() == id) { 
            return panels.get(i);
        }
    }
    return nullptr;
}

// Draw function
void CuWindow::draw() {
    usleep(100000); // Prevent rendering issues

    // Fill window with background color
    XSetForeground(display, graphicsContext, (background.getR() << 16) | 
                                           (background.getG() << 8) | background.getB());
    XFillRectangle(display, window, graphicsContext, 0, 0, width, height);

    // Draw all panels
    for (int i = 0; i < panels.getSize(); i++) {
        panels.get(i)->draw(display, window, graphicsContext);
    }

    XFlush(display); // Force rendering
}

// Print basic CuWindow info
void CuWindow::print() const {
    std::cout << "Window: " << name << " (" << width << "x" << height << ")" << std::endl;
    std::cout << "Number of Panels: " << panels.getSize() << std::endl;
}

// Print all panels in the window
void CuWindow::printPanels() const {
    std::cout << "Panels in " << name << ":" << std::endl;
    for (int i = 0; i < panels.getSize(); i++) {
        panels.get(i)->print();
    }
}

// Print all TextAreas from all FlowPanels
void CuWindow::printPanelTextAreas() const {
    std::cout << "TextAreas in " << name << ":" << std::endl;
    for (int i = 0; i < panels.getSize(); i++) {
        panels.get(i)->printTextAreas();
    }
}