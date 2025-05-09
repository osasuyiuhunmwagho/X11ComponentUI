#ifndef CUWINDOW_H
#define CUWINDOW_H

#include "PanelArray.h"
#include "FlowPanel.h"
#include <X11/Xlib.h>
#include <unistd.h>
using namespace std;

#define MAX_PANELS 5

class CuWindow {

    private:

        int width;
        int height;
        string name; 
        RGB background;
        Display* display;
        Window window;
        GC graphicsContext;
        //additional member variables
        PanelArray panels;
        int panelCount;
      

        
        
        
    public:
       


        CuWindow(string name, int width, int height, RGB background);

        // Destructorrrr
        ~CuWindow();

    
        bool addPanel(FlowPanel* panel);
        FlowPanel* removePanel(const std::string& id);
        FlowPanel* getPanel(const std::string& id) const;
        //get
        void getPanel(string id);
        //set
        void setBackground(const RGB& color);

        // the draw Function
        void draw();
        void print()const;
        void printPanels() const;        
        void printPanelTextAreas() const;
};

#endif