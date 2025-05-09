#include "RGB.h"



// RGB::RGB(int red, int green, int blue){
//             //initialization of memeber vairables to constructor variables
//             r = red;
//             g = green;
//             b = blue;

// }
RGB::RGB(int red, int green, int blue) : r(red), g(green), b(blue) {}  

RGB::RGB(CuColour colour){
            r =  (colour >> 16) & 0xFF;
            g = (colour >> 8) & 0xFF ;
            b = colour & 0xFF;

    //2c
}
RGB::RGB (){
            r = 0;
            g = 0;
            b = 0;
        }

static RGB WHITE() {
    return RGB(255, 255, 255);
}
static RGB BLACK() {
    return RGB(0, 0, 0);
}
static RGB RED() {
    return RGB(255, 0, 0);
}
static RGB GREEN(){
    return RGB(0, 255, 0);
}
static RGB BLUE(){
    return RGB(0, 0, 255);
}
        
// MASTER GETTERS
//  MASTER SETTERS
CuColour RGB::getColour() const {
            return (r << 16) | (g << 8) | b;
}
void RGB:: setColour(CuColour colour){
            r  = (colour >> 16)&0xFF;
            g = (colour >> 8)&0xFF ;
            b = colour&0xFF;


        }

//GETTERS
int RGB:: getR() const{
            return r;
}
int RGB::  getB() const{
            return b;
}
int RGB:: getG() const{
            return g;
}

//SETTERS
            
void RGB :: setR(int red) {
            r = red;
    
}
void RGB :: setB(int blue){
            b = blue;

            
}
void RGB :: setG(int green){
            g = green;
}

