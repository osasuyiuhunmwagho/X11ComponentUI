
#include "TestControl.h"


    // int testPrintTextAreas();
    // int testPrintFlowPanels();
    // int testTextAreasinFlowPanel();

    // // Integration tests for CuWindow
    // int mwTestFlowPanels();
    // int mwTestTextAreas();

    // void testRenderWindow();

    // void studentTests();

vector<string> TestControl::menu ={
    "Student tests\n",
    "TextArea test",
    "FlowPanel test",
    "TextArea in FlowPanel test",
    "FlowPanel in CuWindow test\n",
    
    "Test all and get mark\n",
    "Flowlayout Render test\n\nMemory tests - use valgrind:\n",
    "FlowPanel Memory tests",
    "CuWindow Memory tests\n"
    
    
};


void TestControl::launch(){
    //get input, launch the appropriate test
    int choice = -1;

    while (choice!= 0){
        view.menu(menu, choice);
        switch(choice){
            case 1: studentTests(); break;
            case 2: testTextAreas(); break;
            case 3: testFlowPanels(); break;
            case 4: testTextAreasinFlowPanel(); break;
            case 5: testFlowPanelsinWindow(); break;
            case 6: cout<<"Total score: "<<testTextAreas() + testFlowPanels() + testTextAreasinFlowPanel() + testFlowPanelsinWindow()<<"/18"<<endl; break;
            case 7: testRenderWindow(); break;
            case 8: testFlowPanelMemory(); break;
            case 9: testWindowMemory(); break;
        }
    }
}

void TestControl::studentTests(){
    cout<<"Student tests"<<endl;
    cout<<"No tests found"<<endl;
    // Make a window, try stuff out
    // RGB colour(0, 255, 0);  // change this to your favourite colour
    // CuWindow window("Test", 600, 600, colour);

    // make and add panels, add textAreas to panels, etc
    // You should test, at least, different TextArea colours, different Window colours, 
    // and different placements of FlowPanels and TextAreas. There should be at least 
    // 4 different configurations of FlowPanels and TextAreas in your test. Each configuration must have
    // at least 2 FlowPanels and 2 TextAreas.

    // You can use tester.pressEnterToContinue() to pause the program between configurations
}


/*
* Panel tests:
    Add to panel (at back), print, ensure order
    Add to panel at index, print, ensure order
    Remove from panel at index, print, ensure order
CuWindow tests:
    These are currently unchanged I beleive. 
* Panel Memory tests:
    Add to Panel, remove from Panel, printTAs, delete TA, print TAs
    Add to Panel, remove from Panel, change, add again, print
    Add to Panel, change TA, ensure it is changed (Should we test this?)
    Make sure things are in the Panel and use Valgrind
    Make a deep copy of the Panel, delete one and print the other
  CuWindow Memory tests
    Add to window, remove from window, print Panels, delete print Panels
    Add to Window, remove from Window, change, add again, print
    Add to Window, change TA, ensure it is changed (Should we test this?)
    Make sure things are in the Window and use Valgrind

*/


int TestControl::testTextAreas(){
    string labels[5] = {"TextArea 1", "TextArea 2", "TextArea 3", "TextArea 4", "TextArea 5"};
    string ids[5] = {"ta1", "ta2", "ta3", "ta4", "ta5"};
    TextArea* textAreas[5];
    string ycoords[5] = {"10", "70", "130", "190", "250"};
    string widths[5] = {"20", "31", "42", "53", "64"};
    for (int i = 0; i < 5; i++){
        textAreas[i] = new TextArea(10 + 10*i, 10 + 60*i, 20+11*i, 50, ids[5], labels[i]);
    }

    cout<<"TextArea print test"<<endl<<endl;

    tester.initCapture();
    for (int i = 0; i < 5; i++){
        textAreas[i]->print();
    }
    tester.endCapture();

    int score = 0;
    int error = 0;
    tester.findInOrder({0,1,2,3,4}, labels, error);

    if (error == 0){
        cout<<"Label printing test passed, 1 mark"<<endl;
        score += 1;
    } else {
        cout<<"Label printing test failed"<<endl;
    }


    error = 0;

    tester.findInOrder({0,1,2,3,4}, widths, error);

    if (error == 0){
        cout<<"Width printing test passed, 1 mark"<<endl;
        score += 1;
    } else {
        cout<<"Width printing test failed"<<endl;
    }

    cout<<"TextArea print test score: "<<score<<"/2"<<endl<<endl;

    cout<<"Deleting textAreas"<<endl;

    for (int i = 0; i < 5; i++){
        delete textAreas[i];
    }

    return score;
}

int TestControl::testFlowPanels(){
    string ids[5] = {"FlowPanel 1", "FlowPanel 2", "FlowPanel 3", "FlowPanel 4", "FlowPanel 5"};
    FlowPanel* panels[5];
    string ycoords[5] = {"10", "70", "130", "190", "250"};
    string widths[5] = {"20", "31", "42", "53", "64"};
    for (int i = 0; i < 5; i++){
        panels[i] = new FlowPanel(10 + 10*i, 10 + 60*i, 20+11*i, 50, ids[i]);
    }

    cout<<"FlowPanel print test"<<endl<<endl;

    tester.initCapture();
    for (int i = 0; i < 5; i++){
        panels[i]->print();
    }
    tester.endCapture();

    int score = 0;
    int error = 0;
    tester.findInOrder({0,1,2,3,4}, ids, error);

    if (error == 0){
        cout<<"ID printing test passed, 1 mark"<<endl;
        score += 1;
    } else {
        cout<<"ID printing test failed"<<endl;
    }

    error = 0;
    tester.findInOrder({0,1,2,3,4}, ycoords, error);

    if (error == 0){
        cout<<"Y coordinate printing test passed, 1 mark"<<endl;
        score += 1;
    } else {
        cout<<"Y coordinate printing test failed"<<endl;
    }

    error = 0;

    tester.findInOrder({0,1,2,3,4}, widths, error);

    if (error == 0){
        cout<<"Width printing test passed, 1 mark"<<endl;
        score += 1;
    } else {
        cout<<"Width printing test failed"<<endl;
    }

    cout<<"FlowPanel print test score: "<<score<<"/3"<<endl<<endl;

    cout<<"Deleting FlowPanels"<<endl;

    for (int i = 0; i < 5; i++){
        delete panels[i];
    }

    return score;
}

int TestControl::testTextAreasinFlowPanel(){
    FlowPanel panel(10, 10, 200, 200, "FlowPanel 1");
    vector<string> ids = {"ta1", "ta2", "ta3", "ta4", "ta5","ta6"};
    vector<string> text = {"TextArea 1", "TextArea 2", "TextArea 3", "TextArea 4", "TextArea 5", "TextArea 6"};
    Rectangle rects[6] = {{10, 10, 80, 50}, {10, 50, 80, 50}, {10, 130, 80, 50}, {80, 130, 80, 50}, {100, 130, 80, 50}, {100, 180, 80, 50}};
    TextArea* textAreas[6];

    for (int i = 0; i < 6; i++){
        textAreas[i] = new TextArea(rects[i], ids[i], text[i]);
        panel.addTextArea(textAreas[i]);
    }


    cout<<"FlowPanel textAreas test"<<endl<<endl;

    tester.initCapture();
    panel.printTextAreas();
    tester.endCapture();

    int score = 0;
    int error = 0;
    tester.findInOrder(text, error);

    if (error == 0){
        cout<<"Correct text found in order, test passed, 1 mark"<<endl;
        score += 1;
    } else {
        cout<<"Not all text found, or not in order, test failed"<<endl;
    }

    cout<<"Removing textArea 3"<<endl<<endl;
    TextArea* removed = panel.removeTextArea("ta3");

    error = 0;
    tester.initCapture();
    panel.printTextAreas();
    tester.endCapture();

    error = 0;

    tester.findInOrder({0,1,3,4,5}, text, error);

    if (error == 0){
        cout<<"Correct textAreas found after removal, test passed, 1 mark"<<endl;
        score += 1;
    } else {
        cout<<"Not all TextAreas found after removal, test failed"<<endl;
    }

    error = 0;
    tester.confirmAbsent({"TextArea 3"}, error);

    if (error == 0){
        cout<<"TextArea 3 not found after removal, test passed, 1 mark"<<endl;
        score += 1;
    } else {
        cout<<"TextArea 3 was not removed, test failed"<<endl;
    }

    if (removed != textAreas[2]){
        cout<<"Incorrect TextArea returned (or maybe nullptr), test failed"<<endl;
    } else {
        cout<<"Correct TextArea returned, test passed, 1 mark"<<endl;
        score += 1;
    }

    cout<<"Removing textAreas 1 and 6 by *index*"<<endl<<endl;

    if (panel.removeTextArea(0)!=textAreas[0]){
        cout<<"Incorrect TextArea removed, test failed"<<endl;
    } else {
        cout<<"Correct TextArea returned, test passed, 1 mark"<<endl;
        score += 1;
    }

    if (panel.removeTextArea(3)!=textAreas[5]){
        cout<<"Incorrect TextArea removed, test failed"<<endl;
    } else {
        cout<<"Correct TextArea returned, test passed, 1 mark"<<endl;
        score += 1;
    }

    error = 0;
    tester.initCapture();
    panel.printTextAreas();
    tester.endCapture();

    error = 0;
    tester.findInOrder({"TextArea 2", "TextArea 4"}, error);

    if (error == 0){
        cout<<"TextArea 2 and 4 found after removal, test passed, 1 mark"<<endl;
        score += 1;
    } else {
        cout<<"TextArea 2 or 4 was removed/not found, test failed"<<endl;
    }

    error = 0;

    tester.confirmAbsent({"TextArea 1", "TextArea 6"}, error);

    if (error == 0){
        cout<<"TextArea 1 and 6 not found after removal, test passed, 1 mark"<<endl;
        score += 1;
    } else {
        cout<<"TextArea 1 or 6 was not removed, test failed"<<endl;
    }

    cout<<"FlowPanel textAreas test score: "<<score<<"/8"<<endl<<endl;

    // cout<<endl<<"Deleting removed textAreas, test with valgrind and watch for memory errors on exit"<<endl;

    // delete textAreas[2];
    // delete textAreas[0];
    // delete textAreas[5];

    return score;
}

int TestControl::testFlowPanelMemory(){
    FlowPanel panel(10, 10, 200, 200, "FlowPanel 1");
    vector<string> ids = {"ta1", "ta2", "ta3", "ta4", "ta5","ta6"};
    vector<string> text = {"TextArea 1", "TextArea 2", "TextArea 3", "TextArea 4", "TextArea 5", "TextArea 6"};
    Rectangle rects[6] = {{10, 10, 80, 50}, {10, 50, 80, 50}, {10, 130, 80, 50}, {80, 130, 80, 50}, {100, 130, 80, 50}, {100, 180, 80, 50}};
    TextArea* textAreas[6];

    cout<<"Adding 6 textAreas to FlowPanel"<<endl<<endl;

    for (int i = 0; i < 6; i++){
        textAreas[i] = new TextArea(rects[i], ids[i], text[i]);
        panel.addTextArea(textAreas[i]);
    }


    cout<<"Removing textArea 3"<<endl<<endl;
    panel.removeTextArea("ta3");

    cout<<"Removing textAreas 1 and 6 by *index*"<<endl<<endl;

    panel.removeTextArea(0);

    panel.removeTextArea(3);



    cout<<endl<<"Deleting removed textAreas, test with valgrind and watch for memory errors on exit"<<endl;

    tester.pressEnterToContinue();
    tester.pressEnterToContinue();

    delete textAreas[2];
    delete textAreas[0];
    delete textAreas[5];

    return 0;
 
}


int TestControl::testFlowPanelsinWindow(){
    RGB colour(0, 255, 0);
    CuWindow window("Test", 600, 600, colour);

    FlowPanel* panel1  = new FlowPanel(10, 10, 80, 50, "FlowPanel 1");
    FlowPanel* panel2  = new FlowPanel(10, 50, 80, 50, "FlowPanel 2");
    FlowPanel* panel3  = new FlowPanel(10, 60, 80, 50, "FlowPanel 3");
    FlowPanel* panel4  = new FlowPanel(80, 60, 80, 50, "FlowPanel 4");
    FlowPanel* panel5  = new FlowPanel(100, 60, 80, 50, "FlowPanel 5");
    FlowPanel* panel6  = new FlowPanel(100, 180, 550, 50, "FlowPanel 6");

    TextArea* textArea1 = new TextArea(10, 10, 50, 30,"ta1", "panel 1");
    TextArea* textArea2 = new TextArea(10, 50, 50, 30, "ta2", "panel 2");
    TextArea* textArea3 = new TextArea(10, 60, 50, 30, "ta3", "panel 3");
    TextArea* textArea4 = new TextArea(80, 60, 50, 30, "ta4", "panel 4");
    TextArea* textArea5 = new TextArea(100, 60, 50, 30, "ta5", "panel 5");
    TextArea* textArea6 = new TextArea(100, 180, 50, 30, "ta6", "panel 6");

    panel1->addTextArea(textArea1);
    panel2->addTextArea(textArea2);
    panel3->addTextArea(textArea3);
    panel4->addTextArea(textArea4);
    panel5->addTextArea(textArea5);
    panel6->addTextArea(textArea6);

    window.addPanel(panel1);
    window.addPanel(panel2);
    window.addPanel(panel3);
    window.addPanel(panel4);
    window.addPanel(panel5);
    window.addPanel(panel6);

    cout<<"CuWindow panels test"<<endl<<endl;
   
    window.draw();
    tester.pressEnterToContinue();
    tester.pressEnterToContinue();
    tester.initCapture();
    window.printPanels();
    tester.endCapture();

    int score = 0;
    int error = 0;
    tester.find({"FlowPanel 1", "FlowPanel 3",  "FlowPanel 5"}, error);

    if (error == 0){
        cout<<"Correct panels found, test passed, 1 mark"<<endl;
        score += 1;
    } else {
        cout<<"Not all FlowPanels found, test failed"<<endl;
    }

    error = 0;

    tester.confirmAbsent({"FlowPanel 2", "FlowPanel 4", "FlowPanel 6"}, error);

    if (error == 0){
        cout<<"FlowPanel 2, 4 and 6 not found, test passed, 1 mark"<<endl;
        score += 1;
    } else {
        cout<<"FlowPanel 2, 4 or 6 was added but should not be, test failed"<<endl;
    }

    cout<<"Removing FlowPanel 3"<<endl<<endl;
    if (panel3!= window.removePanel("FlowPanel 3")){
        cout<<"Incorrect FlowPanel removed, test failed"<<endl;
    } else {
        cout<<"Correct FlowPanel removed, test passed, 1 mark"<<endl;
        score += 1;
    }


    error = 0;
    tester.initCapture();
    window.printPanels();
    tester.endCapture();

    error = 0;

    tester.find({"FlowPanel 1", "FlowPanel 5"}, error);

    if (error == 0){
        cout<<"Correct panels found after removal, test passed, 1 mark"<<endl;
        score += 1;
    } else {
        cout<<"Not all FlowPanels found after removal, test failed"<<endl;
    }

    error = 0;
    tester.confirmAbsent({"FlowPanel 3"}, error);

    if (error == 0){
        cout<<"FlowPanel 3 not found after removal, test passed, 1 mark"<<endl;
        score += 1;
    } else {
        cout<<"FlowPanel 3 was not removed, test failed"<<endl;
    }

    window.draw();
    tester.pressEnterToContinue();

    cout<<"CuWindow panels test score: "<<score<<"/5"<<endl<<endl;

    return score;
}

int TestControl::testWindowMemory(){
    RGB colour(0, 255, 0);
    CuWindow window("Test", 600, 600, colour);

    FlowPanel* panel1  = new FlowPanel(10, 10, 80, 50, "FlowPanel 1");
    FlowPanel* panel2  = new FlowPanel(10, 50, 80, 50, "FlowPanel 2");
    FlowPanel* panel3  = new FlowPanel(10, 60, 80, 50, "FlowPanel 3");
    FlowPanel* panel4  = new FlowPanel(80, 60, 80, 50, "FlowPanel 4");
    FlowPanel* panel5  = new FlowPanel(100, 60, 80, 50, "FlowPanel 5");
    FlowPanel* panel6  = new FlowPanel(100, 180, 350, 50, "FlowPanel 6");

    TextArea* textArea1 = new TextArea(10, 10, 50, 30,"ta1", "panel 1");
    TextArea* textArea2 = new TextArea(10, 50, 50, 30, "ta2", "panel 2");
    TextArea* textArea3 = new TextArea(10, 60, 50, 30, "ta3", "panel 3");
    TextArea* textArea4 = new TextArea(80, 60, 50, 30, "ta4", "panel 4");
    TextArea* textArea5 = new TextArea(100, 60, 50, 30, "ta5", "panel 5");
    TextArea* textArea6 = new TextArea(100, 180, 50, 30, "ta6", "panel 6");

    panel1->addTextArea(textArea1);
    panel2->addTextArea(textArea2);
    panel3->addTextArea(textArea3);
    panel4->addTextArea(textArea4);
    panel5->addTextArea(textArea5);
    panel6->addTextArea(textArea6);

    window.addPanel(panel1);
    window.addPanel(panel2);
    window.addPanel(panel3);
    window.addPanel(panel4);
    window.addPanel(panel5);
    window.addPanel(panel6);

    cout<<"CuWindow panels test"<<endl<<endl;
   
    window.draw();
    tester.pressEnterToContinue();
    tester.pressEnterToContinue();
    

    cout<<"Removing FlowPanel 3"<<endl<<endl;
    window.removePanel("FlowPanel 3");

    cout<<"Removing FlowPanel 6"<<endl<<endl;
    window.removePanel("FlowPanel 6");


    window.draw();
    tester.pressEnterToContinue();

    cout<<"Making a DEEP COPY of panel 6 and adding it back to the window"<<endl<<endl;

    FlowPanel* panel6copy = new FlowPanel(*panel6);
    window.addPanel(panel6copy);

    cout<<"Deleting original panel 6 and printing / rendering CuWindow"<<endl<<endl;

    delete panel6;

    window.printPanels();
    window.draw();
    tester.pressEnterToContinue();

    cout<<"Deleting removed FlowPanels, test with valgrind and watch for memory errors on exit"<<endl;

    delete panel3;
    delete panel2;
    delete panel4;


    return 0;
}



// deprecated
int TestControl::mwTestTextAreas(){

    RGB red(255, 0, 0);
    CuWindow window("Test", 600, 600, red);
    FlowPanel* panel1 = new FlowPanel(0, 0, 600, 300, "FlowPanel 1");
    FlowPanel* panel2 = new FlowPanel(0, 300, 600, 300, "FlowPanel 2");

    TextArea* textArea1 = new TextArea(10, 10, 80, 50,"ta1", "TextArea 1");
    TextArea* textArea2 = new TextArea(10, 70, 80, 50, "ta2","TextArea 2");
    TextArea* textArea3 = new TextArea(10, 130, 80, 50, "ta3","TextArea 3");
    TextArea* textArea4 = new TextArea(80, 130, 80, 50, "ta4","TextArea 4");

    panel1->addTextArea(textArea1);
    panel1->addTextArea(textArea2);
    panel1->addTextArea(textArea3);
    // panel1.addTextArea(textArea4);

    panel2->addTextArea(textArea1);
    panel2->addTextArea(textArea2);
    // panel2->addTextArea(textArea3);
    panel2->addTextArea(textArea4);

    window.addPanel(panel1);
    window.addPanel(panel2);

    cout<<"CuWindow textAreas test"<<endl<<endl;

    tester.initCapture();
    window.printPanelTextAreas();
    tester.endCapture();

    int error = 0;
    
    int score = 0;

    tester.findInOrder({"TextArea 1", "TextArea 2", "TextArea 3", "TextArea 1", "TextArea 2", "TextArea 4"}, error);

    if (error == 0){
        cout<<"Correct textAreas found in correct order, test passed, 1 mark"<<endl;
        score += 1;
    } else {
        cout<<"Not all TextAreas found or found out of order, test failed"<<endl;
    }

    panel1->removeTextArea("TextArea 3");
    panel2->removeTextArea("TextArea 4");

    tester.initCapture();
    window.printPanelTextAreas();
    tester.endCapture();

    error = 0;
    tester.findInOrder({"TextArea 1", "TextArea 2", "TextArea 3", "TextArea 1", "TextArea 2", "TextArea 4"}, error);

    if (error == 0){
        cout<<"Copy of FlowPanels were made correctly, 1 mark"<<endl;
        score += 1;
    } else {
        cout<<"FlowPanels not copied into CuWindow correctly, test failed"<<endl;
    }

    cout<<"CuWindow textAreas test score: "<<score<<"/2"<<endl<<endl;

    return score;
}

void TestControl::testRenderWindow(){

    RGB colour(0, 255, 0);

    CuWindow window("Test", 600, 600, colour);
    FlowPanel *panel1 = new FlowPanel(0, 0, 600, 300, "FlowPanel 1");
    FlowPanel *panel2 = new FlowPanel(0, 300, 600, 300, "FlowPanel 2");

    TextArea* textArea1 = new TextArea({10, 10, 80, 50}, "ta1","TextArea*1hereisalongstring");
    TextArea* textArea2 = new TextArea({10, 70, 280, 150}, "ta2","TextArea* 2");
    TextArea* textArea3 = new TextArea({10, 130, 280, 70}, "ta3","TextArea* 3");
    TextArea* textArea4 = new TextArea({80, 210, 180, 90}, "ta4","TextArea* 4 here is a long string, in fact this is a very long string, let's see what happens");
    TextArea* textArea5 = new TextArea({80, 210, 180, 90}, "ta5","TextArea* 5 here is a long string, in fact this is a very long string, let's see what happens");

    panel1->addTextArea(textArea1);
    panel1->addTextArea(textArea2);
    panel1->addTextArea(textArea3);
    panel1->addTextArea(textArea4);

    panel2->addTextArea(new TextArea(*textArea1 ));
    panel2->addTextArea(new TextArea(*textArea2 ));
    // panel2->addTextArea(textArea3);
    panel2->addTextArea(textArea5);

    window.addPanel(panel1);
    window.addPanel(panel2);

    cout<<"CuWindow render test"<<endl<<endl;

    
    window.draw();

    cout<<"Window rendered, please check if it looks correct (see specification for details)"<<endl;
    tester.pressEnterToContinue();
    tester.pressEnterToContinue(); // sigh, input buffers

    cout<<"Changing textArea 2, making textArea 3 too high to fit"<<endl;
    textArea2->setText("This is a new string for textArea 2. Let's make it extra long so we can see the wrapping feature");
    textArea3->setHeight(400);

    window.draw();

    cout<<"Window rendered, please check if it looks correct (see specification for details)"<<endl;
    tester.pressEnterToContinue();
    
}

