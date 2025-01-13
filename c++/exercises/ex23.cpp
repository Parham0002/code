/*
A circle is a shape which has a center point and a radius.
A square is a shape which has a length(four equal sides).
Every shape has a name and an area. Every point has x and y on the 2d cartesian coordinate system.
Make a Shape class and a Point class.
Make a Circle class based on Shape.
The class shall have a function to get area of a circle.
It shall be possible to  check if two circles are equal or not by overloading the == operator.
Make a Square class based on Shape. The class shall have a function to get area of a square.
Make a function to print area of any shape.*/

#include "ex23.h"
#include <iostream>
#include <cmath>

// Point class implementation
Point::Point(double x, double y) : x(x), y(y) {}

bool Point::operator==(const Point &other) const
{
    return x == other.x && y == other.y;
}

// Shape class implementation
Shape::Shape(const std::string &name) : name(name) {}

// Circle class implementation
Circle::Circle(const std::string &name, const Point &center, double radius)
    : Shape(name), center(center), radius(radius) {}

double Circle::getArea() const
{
    return M_PI * radius * radius;
}

bool Circle::operator==(const Circle &other) const
{
    return center == other.center && radius == other.radius;
}

// Square class implementation
Square::Square(const std::string &name, double sideLength)
    : Shape(name), sideLength(sideLength) {}

double Square::getArea() const
{
    return sideLength * sideLength;
}

// Function to print the area of a shape
void printArea(const Shape &shape)
{
    std::cout << "Area of " << shape.name << ": " << shape.getArea() << std::endl;
}
