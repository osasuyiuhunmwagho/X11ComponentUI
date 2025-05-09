#include "PanelArray.h"
#include <iostream>

PanelArray::PanelArray() {
    panelCount = 0;
    panels = new FlowPanel*[MAX_PANELS];
}

PanelArray::~PanelArray() {
    for (int i = 0; i < panelCount; i++) {
        delete panels[i];
    }
    delete[] panels;
}

bool PanelArray::add(FlowPanel* panel) {
    if (panelCount >= MAX_PANELS) return false;
    panels[panelCount++] = panel;
    return true;
}

FlowPanel* PanelArray::remove(int index) {
    if (index < 0 || index >= panelCount) return nullptr;
    FlowPanel* removed = panels[index];

    for (int i = index; i < panelCount - 1; i++) {
        panels[i] = panels[i + 1];
    }

    panels[panelCount - 1] = nullptr;

    panelCount--;

    return removed;
}


FlowPanel* PanelArray::get(int index) const {
    if (index < 0 || index >= panelCount) return nullptr;
    return panels[index];
}

int PanelArray::getSize() const {
    return panelCount;
}