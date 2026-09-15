#include <iostream>
#include <cmath>

class Vector {
public:
  double x;
  double y;
  double z;

  Vector(double x_coord, double y_coord, double z_coord) {
    x = x_coord;
    y = y_coord;
    z = z_coord;
  }

  Vector() : x(0.0), y(0.0), z(0.0) {};
};

class Satellite {
public:
  Vector position;
  Vector velocity;

  Satellite(Vector p, Vector v) {
    position = p;
    velocity = v;
  }
};

double calculate_magnitude(Vector *relative_position) {
    Vector rel_position = *relative_position;

    double rel_position_x_squared = rel_position.x * rel_position.x;
    double rel_position_y_squared = rel_position.y * rel_position.y;
    double rel_position_z_squared = rel_position.z * rel_position.z;

    return std::sqrt(rel_position_x_squared + rel_position_y_squared + rel_position_z_squared);
}

Vector calculate_relative_position_at_closest_approach(Vector *relative_position,
                                    Vector *relative_velocity,
                                    double time_until_closest_approach) {
  Vector rel_position = *relative_position;
  Vector rel_velocity = *relative_velocity;

  double position_x =
      rel_position.x + (rel_velocity.x * time_until_closest_approach);
  double position_y =
      rel_position.y + (rel_velocity.y * time_until_closest_approach);
  double position_z =
      rel_position.z + (rel_velocity.z * time_until_closest_approach);

  return {position_x, position_y, position_z};
}

double calculate_dot_product(Vector *relative_position,
                             Vector *relative_velocity) {
  Vector rel_position = *relative_position;
  Vector rel_velocity = *relative_velocity;

  return (rel_position.x * rel_velocity.x) + (rel_position.y * rel_velocity.y) +
         (rel_position.z * rel_velocity.z);
}

Vector compute_relative_vector(Vector *a, Vector *b) {
  Vector vector_a = *a;
  Vector vector_b = *b;

  return {vector_b.x - vector_a.x, vector_b.y - vector_a.y,
          vector_b.z - vector_a.z};
}

int main() {
  Satellite s_a({0.0, 0.0, 0.0}, {0.0, 0.0, 0.0});
  Satellite s_b({1.0, 1.0, 1.0}, {1.0, 1.0, 1.0});

  // r = r2 - r1 (delta r)
  Vector relative_position =
      compute_relative_vector(&s_a.position, &s_b.position);

  // v = v2 - v1 (delta v)
  Vector relative_velocity =
      compute_relative_vector(&s_a.velocity, &s_b.velocity);

  /** Dot Product
   * dot product -> relative position * relative velocity
   * tells us if the velocity is pointing toward or away from
   * the current separation vector
   */
  double dot_product =
      calculate_dot_product(&relative_position, &relative_velocity);

  // Will be needed to calculate the time of closest approach
  double squared_relative_velocity =
      calculate_dot_product(&relative_velocity, &relative_velocity);

  // Find time until closest approach (in seconds)
  double time_until_closest_approach = dot_product / squared_relative_velocity;

  // Assuming a constant velocity (acceleration = 0),
  // we calculate the evolution of the position as is
  Vector relative_position_at_closest_approach = calculate_relative_position_at_closest_approach(
      &relative_position, &relative_velocity, time_until_closest_approach);

  /**
   * Now that we have our relative position at time of closest approach,
   * we can calculate its magnitude, so we can answer:
   * "How far apart are they actually"
   * -> the magnitude d(min) is a scalar distance that gives
   * the minimum separation between the two objects
   */
   double magnitude = calculate_magnitude(&relative_position_at_closest_approach);

  return 0;
}