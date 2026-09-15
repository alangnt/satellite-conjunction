#include <cmath>
#include <iostream>
#include <string>

/**
 * We call Epsilon a small
 * comparison threshold to avoid using
 * a "== 0" that can be unreliable
 * for calculated floating-point values
 */
constexpr double TIME_EPSILON = 0.001;
constexpr double VELOCITY_EPSILON = 1e-12;

class Vector {
public:
  double x;
  double y;
  double z;

  Vector(double x_coord, double y_coord, double z_coord)
      : x(x_coord), y(y_coord), z(z_coord) {}

  Vector() : x(0.0), y(0.0), z(0.0) {}
};

class Satellite {
public:
  Vector position;
  Vector velocity;

  Satellite(Vector p, Vector v) : position(p), velocity(v) {}
};

/**
 * Since we assume velocity is constant and
 * there is no orbital motion,
 * closest approach can only
 * happen once
 */
std::string define_closest_approach_status(double time_to_closest_approach) {
  if (time_to_closest_approach < -TIME_EPSILON) {
    // If t(ca) is < 0, closest approach already happened
    return "Oh... you missed it!";
  } else if (std::abs(time_to_closest_approach) < TIME_EPSILON) {
    // If t(ca) = 0, closest approach is currently happening
    return "They are at their closest approach!";
  } else {
    // If t(ca) > 0, closest approach hasn't happened yet
    return "You're too early!";
  }
}

double calculate_magnitude(const Vector &relative_position) {
  double rel_position_x_squared = relative_position.x * relative_position.x;
  double rel_position_y_squared = relative_position.y * relative_position.y;
  double rel_position_z_squared = relative_position.z * relative_position.z;

  return std::sqrt(rel_position_x_squared + rel_position_y_squared +
                   rel_position_z_squared);
}

Vector calculate_relative_position_at_closest_approach(
    const Vector &relative_position, const Vector &relative_velocity,
    const double time_until_closest_approach) {
  double position_x =
      relative_position.x + (relative_velocity.x * time_until_closest_approach);
  double position_y =
      relative_position.y + (relative_velocity.y * time_until_closest_approach);
  double position_z =
      relative_position.z + (relative_velocity.z * time_until_closest_approach);

  return {position_x, position_y, position_z};
}

double calculate_dot_product(const Vector &vector_a, const Vector &vector_b) {
  return (vector_a.x * vector_b.x) + (vector_a.y * vector_b.y) +
         (vector_a.z * vector_b.z);
}

Vector calculate_relative_vector(const Vector &vector_a,
                                 const Vector &vector_b) {
  return {vector_b.x - vector_a.x, vector_b.y - vector_a.y,
          vector_b.z - vector_a.z};
}

int main() {
  Satellite s_a({7000.0, 0.0, 0.0}, {0.0, 7.5, 0.0});
  Satellite s_b({7005.0, 10.0, 1.0}, {0.0, 7.49, -0.001});

  // r = r2 - r1 (delta r)
  const Vector relative_position =
      calculate_relative_vector(s_a.position, s_b.position);

  // v = v2 - v1 (delta v)
  const Vector relative_velocity =
      calculate_relative_vector(s_a.velocity, s_b.velocity);

  /** Dot Product
   * dot product -> relative position * relative velocity
   * tells us if the velocity is pointing toward or away from
   * the current separation vector
   */
  const double dot_product =
      calculate_dot_product(relative_position, relative_velocity);

  // Will be needed to calculate the time of closest approach
  const double squared_relative_velocity =
      calculate_dot_product(relative_velocity, relative_velocity);

  /**
   * If squared_relative_velocity = 0,
   * that means their relative velocity is small
   * enough to treat as 0
   * -> we skip time to closest approach because their
   * relative position never changes anyway
   */
  if (squared_relative_velocity < VELOCITY_EPSILON) {
    // We calculate their constant separation (in km)
    const double separation = calculate_magnitude(relative_position);

    std::cout << "Conjunction Analysis\n";
    std::cout << "--------------------\n";

    std::cout << "No relative motion detected\n";
    std::cout << "Separation remains constant at " << separation << "km"
              << std::endl;
  } else {
    // Find time to closest approach (in seconds): t(ca)
    // t(ca) = - (r * v / v * v)
    double time_to_closest_approach =
        -(dot_product / squared_relative_velocity);

    /**
     * Assuming a constant velocity (acceleration = 0),
     * we can find the position at closest approach with
     * r(ca) = r + v * t(ca)
     */
    const Vector relative_position_at_closest_approach =
        calculate_relative_position_at_closest_approach(
            relative_position, relative_velocity, time_to_closest_approach);

    /**
     * Now that we have our relative position at time of closest approach,
     * we can calculate its magnitude, so we can answer:
     * "How far apart are they actually"
     * -> the magnitude d(min) is a scalar distance that gives
     * the minimum separation between the two objects (in km)
     */
    const double minimum_separation =
        calculate_magnitude(relative_position_at_closest_approach);

    /**
     * Thanks to the t(ca) (time to closest approach),
     * we can define whether the closest approach already
     * happened, is happening, or when it will happen
     */
    const std::string closest_approach_status =
        define_closest_approach_status(time_to_closest_approach);

    /**
     * Now that we have all the data we need,
     * we can output the results
     */
    std::cout << "Conjunction Analysis\n";
    std::cout << "--------------------\n";

    std::cout << "Time to closest approach: " << time_to_closest_approach
              << "s\n";
    std::cout << "Minimum separation: " << minimum_separation << "km\n";
    std::cout << "Status: " << closest_approach_status << std::endl;
  }

  return 0;
}