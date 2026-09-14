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

Vector squared_vector(Vector* vector_to_square) {
    Vector vector = *vector_to_square;

    return {vector.x * vector.x, vector.y * vector.y, vector.z * vector.z};
}

Vector calculate_dot_product(Vector* relative_position, Vector* relative_velocity)
{
    Vector rel_position = *relative_position;
    Vector rel_velocity = *relative_velocity;

    return {rel_position.x * rel_velocity.x, rel_position.y * rel_velocity.y, rel_position.z * rel_velocity.z};
}

Vector compute_relative_vector(Vector* a, Vector* b)
{
    Vector vector_a = *a;
    Vector vector_b = *b;

    return {vector_b.x - vector_a.x, vector_b.y - vector_a.y, vector_b.z - vector_a.z};
}

int main()
{
    Satellite s_a({0.0, 0.0, 0.0}, {0.0, 0.0, 0.0});
    Satellite s_b({1.0, 1.0, 1.0}, {1.0, 1.0, 1.0});

    // r = r2 - r1 (delta r)
    Vector relative_position = compute_relative_vector(&s_a.position, &s_b.position);

    // v = v2 - v1 (delta v)
    Vector relative_velocity = compute_relative_vector(&s_a.velocity, &s_b.velocity);
   
    /** Dot Product
     * dot product -> relative position * relative velocity
     * tells us if the velocity is pointing toward or away from
     * the current separation vector
     */
    Vector dot_product = calculate_dot_product(&relative_position, &relative_velocity);

    return 0;
}