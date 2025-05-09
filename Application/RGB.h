using namespace std;

#include "defs.h"
#ifndef RGB_H
#define RGB_H

class RGB{
    private:
        int r;
        int g;
        int b;
    public: 
   
    //2b
        RGB(int red, int green, int blue);
    //2b
        RGB(CuColour colour);

    //2c
       
        RGB ();

        static RGB WHITE() ;
        static RGB BLACK() ;
        static RGB RED() ;
        static RGB GREEN() ;
        static RGB BLUE() ;


        CuColour getColour() const;

        
        int getR() const;
        int getB() const;
        int getG() const;
        
        void setColour(CuColour colour);
        void setR(int r);
        void setB(int b);
        void setG(int g);




};

#endif

