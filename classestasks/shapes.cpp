#include <iostream>
#include <numbers>
class Shape{
public:
    Shape(){std::cout<<"Pure shape called\n";};
    int x=4;
    virtual double area()=0;

};
class triangle: virtual public Shape
{
    public:
    int y=7;
    virtual double area() override
    {
        double area = x*y/2;
        std::cout<<"Area of triangle: "<<area<<"\n";
        return area;
    }
};
class rectangle: virtual public Shape
{
    public:
    int y=4;
    virtual double area() override
    {

        double area = x*y;
        std::cout << "Area of rectangle: " << area <<"\n";
        return area;
    }
};
class circle : virtual public Shape
{
public:
    double r = x/2;
    virtual double area() override
    {
        double area=std::numbers::pi*r*r;
        std::cout<<"Area of circle: "<<area<<"\n";
        return area;
    }
};
class cilinder: virtual public circle, virtual public rectangle
{
    public:
    virtual double area() override
    {
        double base = circle::area();
        double wall = rectangle::area();
        double area = (2*base)+(std::numbers::pi*wall);
        std::cout<<"Area of cylinder: "<<area<<"\n";
        return area;
    }
};
class triangularprism: virtual public triangle, virtual public rectangle
{
    public:
    virtual double area() override
    {
        double base = triangle::area();
        double wall = rectangle::area();
        double area = (2*base)+(3*wall);
        std::cout<<"Area of triangular prism: "<<area<<"\n";

        return area;
    }
};
int main()
{
    cilinder c;
    c.area();

    triangularprism t;
    t.area();
    return 0;
}