# Satellite Conjunction Analyzer

A small C++ project built for the Codédex C++ Final Project.

The program estimates the closest approach between two satellites using their current 3D position and velocity.

## Features

- Custom satellite input
- Example simulation
- 3D position and velocity vectors
- Closest-approach time calculation
- Minimum separation calculation
- Input validation
- Handling of near-zero relative velocity
- Simple status interpretation

## How it works

The program first calculates the relative position and relative velocity between two satellites.

It then uses the closest-approach equation:

$$
t_{CA} = -\frac{\mathbf r \cdot \mathbf v}{\mathbf v \cdot \mathbf v}
$$

where:

- `r` is the relative position vector
- `v` is the relative velocity vector
- `t_CA` is the time of closest approach

The relative position at closest approach is then calculated with:

$$
\mathbf r_{CA} = \mathbf r + \mathbf v t_{CA}
$$

The minimum separation is the magnitude of that vector:

$$
d_{min} = \|\mathbf r_{CA}\|
$$

## Assumptions

This is a simplified model.

It assumes:

- Constant velocity
- Zero acceleration
- Straight-line motion
- No gravity
- No orbital propagation

Because of this, the program models only a single closest approach and should not be used for real satellite collision prediction.

## Units

- Position: kilometers
- Velocity: kilometers per second
- Time: seconds
- Separation: kilometers

## Example

The included example simulation uses two synthetic satellites and produces approximately:

```text
Time to closest approach: 1000 s
Minimum separation: 5 km
Status: You're too early!
```

## Built with

C++ and the standard library.