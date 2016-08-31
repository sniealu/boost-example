#ifndef _BOOSTPOLY_
#define _BOOSTPOLY_
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

struct point 
{
    point(int p_x, int p_y) : x(p_x), y(p_y) {}
    int x;
    int y;
};


class boostPoly_C
{
    public:
    //Constructor
    double calcArea();
    
        
    private:
};

#endif
