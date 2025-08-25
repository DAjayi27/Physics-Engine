//
// Created by AJYDAN on 02/05/2025.
//

#pragma once

#include "collision/collision_types.h"

/**
 * @brief Enumeration of shape types
 */
enum class ShapeType {
    NONE,
    CIRCLE,
    RECTANGLE,
    POLYGON,
    TRIANGLE
};

// Legacy compatibility
using Shape_Type = ShapeType;

/**
 * @brief Abstract base class for all shapes
 * 
 * Provides common interface for different geometric shapes
 * including collision type, area calculation, and type identification.
 */
class Shape {
public:
    virtual ~Shape() = default;
    
    // Core shape methods
    virtual ShapeType get_type() const = 0;
    virtual Collision_Type get_collision_type() const = 0;
    virtual float get_area() const = 0;
		virtual float get_area_normalised(int PPM) const  = 0 ;
    // Collision detection
    bool has_collider() const;

protected:
    bool has_collision = false;
};


