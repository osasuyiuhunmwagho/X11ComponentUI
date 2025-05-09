objects = main.o CuWindow.o FlowPanel.o TextArea.o Tester.o RGB.o TAArray.o PanelArray.o TestControl.o View.o
libs = -std=c++11 -lX11

a2: $(objects)
	g++ -o a2 $(objects) $(libs) -I /opt/X11/include -L /opt/X11/lib

main.o: main.cc defs.h
	g++ -c main.cc -I /opt/X11/include

RGB.o: RGB.h RGB.cc defs.h
	g++ -c RGB.cc -I /opt/X11/include

FlowPanel.o: FlowPanel.h FlowPanel.cc defs.h
	g++ -c FlowPanel.cc -I /opt/X11/include

TextArea.o: TextArea.h TextArea.cc defs.h
	g++ -c TextArea.cc -I /opt/X11/include

CuWindow.o: CuWindow.h CuWindow.cc defs.h
	g++ -c CuWindow.cc -I /opt/X11/include

Tester.o: Tester.h Tester.cc defs.h
	g++ -c Tester.cc -I /opt/X11/include

TAArray.o: TAArray.h TAArray.cc defs.h
	g++ -c TAArray.cc -I /opt/X11/include

PanelArray.o: PanelArray.h PanelArray.cc defs.h
	g++ -c PanelArray.cc -I /opt/X11/include

TestControl.o: TestControl.h TestControl.cc defs.h
	g++ -c TestControl.cc -I /opt/X11/include

View.o: View.h View.cc defs.h
	g++ -c View.cc -I /opt/X11/include

clean:
	rm a2 *.o