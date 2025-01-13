#ifndef EX23_H
#define EX23_H

#include <string>

// Point class
class Point
{
public:
    double x, y;

    Point(double x = 0, double y = 0);
    bool operator==(const Point &other) const;
};

// Shape class (abstract base class)
class Shape
{
public:
    std::string name;
    Shape(const std::string &name);
    virtual double getArea() const = 0; // Pure virtual function
    virtual ~Shape() = default;
};

// Circle class
class Circle : public Shape
{
public:
    Point center;
    double radius;

    Circle(const std::string &name, const Point &center, double radius);
    double getArea() const override;
    bool operator==(const Circle &other) const;
};

// Square class
class Square : public Shape
{
public:
    double sideLength;

    Square(const std::string &name, double sideLength);
    double getArea() const override;
};

// Function to print the area of a shape
void printArea(const Shape &shape);

#endif // EX23_H

