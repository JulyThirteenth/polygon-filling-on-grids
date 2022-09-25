#ifndef _FILL_POLYGON_H_
#define _FILL_POLYGON_H_

#include <vector>
#include <algorithm>

namespace JulyThirteenth
{
    template <typename T>
    struct point
    {
        T x, y;
    };
    typedef struct point<double> Point;
    typedef struct point<int> intPoint;

    typedef struct edge
    {
        int ymax;
        double x;
        double dx;
        struct edge *next;
    } Edge;
    typedef Edge **EdgeTable;
    typedef Edge *ActiveEdgeTable;

    void fillPolygon(const std::vector<Point> &vertexes, double resolution, std::vector<intPoint> &polygArea);
}

#endif