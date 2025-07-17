//
// Created by AJYDAN on 01/05/2025.
//

#pragma once

#include "shape.h"

/**
 * @brief Rectangle shape with width and height dimensions
 * 
 * Implements axis-aligned bounding box (AABB) collision detection
 * and rectangular area calculation.
 */
class Rectangle : public Shape {
private:
    float width = 1.0f;
    float height = 1.0f;

public:
    Rectangle(float width, float height);
    Rectangle(float width, float height, bool has_collision);
    
    // Core shape methods
    ShapeType get_type() const override;
    Collision_Type get_collision_type() const override;
    float get_area() const override;
    
    // Rectangle-specific methods
    float get_width() const;
    float get_height() const;
    void set_width(float width);
    void set_height(float height);
};






