#ifndef PANELARRAY_H
#define PANELARRAY_H

#include "FlowPanel.h"

#define MAX_PANELS 5

class PanelArray {
private:
    FlowPanel** panels;
    int panelCount;

public:
    PanelArray();
    ~PanelArray();
    
    bool add(FlowPanel* panel);
    FlowPanel* remove(int index);
    FlowPanel* get(int index) const;  
    int getSize() const;
};

#endif