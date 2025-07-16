//
// Created by AJYDAN on 02/05/2025.
//

#pragma once

#include "shape.h"

/**
 * @brief Circle shape with radius-based geometry
 * 
 * Implements circular collision detection and area calculation
 * using the mathematical properties of circles.
 */
class Circle : public Shape {
private:
    float radius = 1.0f;

public:
    explicit Circle(float radius);
    
    // Core shape methods
    ShapeType get_type() const override;
    Collision_Type get_collision_type() const override;
    float get_area() const override;
    
    // Circle-specific methods
    float get_radius() const;
    void set_radius(float radius);
};
