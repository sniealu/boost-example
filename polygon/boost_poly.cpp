#include <vector>
#include <iostream>
#include <boost/polygon/polygon.hpp>
#include "boost_poly.h"

using std::vector;
using namespace boost::polygon;
using namespace boost::polygon::operators;
namespace gtl = boost::polygon;

typedef boost::polygon::rectangle_data<int> Rect;
typedef std::vector<Rect> RectSet;
typedef boost::polygon::polygon_90_data<int> Polygon;
typedef std::vector<Polygon> PolygonSet;
typedef boost::polygon::polygon_traits_90<Polygon>::point_type Point;


double boostPoly_C::calcArea() 
{
    //Outer Boundary
    vector<Point> boundary_points;
    boundary_points.push_back(boost::polygon::construct<Point>(1,1));
    boundary_points.push_back(boost::polygon::construct<Point>(6,1));
    boundary_points.push_back(boost::polygon::construct<Point>(6,6));
    boundary_points.push_back(boost::polygon::construct<Point>(1,6));
    //Inner Blockage
    vector<Point> blockage_points;
    blockage_points.push_back(boost::polygon::construct<Point>(3,3));
    blockage_points.push_back(boost::polygon::construct<Point>(4,3));
    blockage_points.push_back(boost::polygon::construct<Point>(4,4));
    blockage_points.push_back(boost::polygon::construct<Point>(3,4));
    //Chip Boundary Points to Polygon
    Polygon body_polygon;
    boost::polygon::set_points(body_polygon,boundary_points.begin(),boundary_points.end());
    
    Polygon blockage_polygon;
    boost::polygon::set_points(blockage_polygon, blockage_points.begin(),blockage_points.end());

    //Polygon Set
    PolygonSet body_polygon_set;
    body_polygon_set += body_polygon;

    PolygonSet blockage_polygon_set;
    blockage_polygon_set += blockage_polygon;

    PolygonSet core_polygon_set;
    core_polygon_set += body_polygon_set - blockage_polygon_set;

    double core_ps_area = gtl::area(core_polygon_set);
    printf("core_ps_area:%f\n",core_ps_area);

    //Shrinking
    PolygonSet shrunk_polygon_set;
    shrunk_polygon_set += core_polygon_set;
    shrunk_polygon_set = gtl::shrink(shrunk_polygon_set, 1.0);
    
    //Final
    PolygonSet final_polygon_set;
    final_polygon_set += core_polygon_set - shrunk_polygon_set;

    RectSet blockage_set;
    get_max_rectangles(blockage_set, final_polygon_set);

    //Print rectangles
    for(size_t i=0; i < blockage_set.size(); ++i)
    {
        printf("%d %d - %d %d\n",
            boost::polygon::xl(blockage_set[i]),
            boost::polygon::yl(blockage_set[i]),
            boost::polygon::xh(blockage_set[i]),
            boost::polygon::yh(blockage_set[i]));
    }





}

