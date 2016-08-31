#include "boost_poly.h"



int main()
{
    vector<point> boundary;
    point test(1,1);
    printf("%d\n",test.x);
    boundary.push_back(test);

    boostPoly_C boostPoly;
    boostPoly.calcArea();
    
}
