#include <iostream>

class Vector
{
public:
    double x;
    double y;
    double z;

    Vector(double x_coord, double y_coord, double z_coord)
    {
        x = x_coord;
        y = y_coord;
        z = z_coord;
    }

    Vector() : x(0.0), y(0.0), z(0.0) {};
};

class Satellite
{
public:
    Vector position;
    Vector velocity;

    Satellite(Vector p, Vector v)
    {
        position = p;
        velocity = v;
    }
};

int main()
{
    Satellite s_a({0.0, 0.0, 0.0}, {0.0, 0.0, 0.0});
    Satellite s_b({1.0, 1.0, 1.0}, {1.0, 1.0, 1.0});

    return 0;
}