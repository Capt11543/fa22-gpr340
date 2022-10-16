#ifndef POINT2D_H
#define POINT2D_H

struct Point2D {
public:
    bool operator== (const Point2D& rhs) const;
    bool operator!= (const Point2D& rhs) const;
    Point2D& operator= (const Point2D& rhs);
    Point2D(int x, int y) : x(x), y(y){};
    Point2D() = default;
    
    int x, y;
};

#endif //POINT2D_H
