//
// Created by AJYDAN on 02/05/2025.
//

#ifndef PHYSICS_COMPONENT_H
#define PHYSICS_COMPONENT_H

#include "core/vector.h"



enum Physics_Type{
    PHYSICS_NONE,
    PHYSICS_RIGID_BODY,
    PHYSICS_KINEMATIC,
    PHYSICS_PARTICLE
};

class Physics_Component{

public:
	virtual ~Physics_Component() = default;
	virtual void update(float deltaTime) = 0;
	virtual Physics_Type get_type() = 0;
	void set_velocity(Vector_2D v);
	void set_velocity_y( float y);
	void set_velocity_x( float x);
	void set_position(Vector_2D v);
	void set_position_y( float y);
	void set_position_x( float x);
	bool get_is_static();
	Vector_2D get_velocity();
	Vector_2D get_position();
	void set_is_static(bool val);

private:
	Vector_2D position = {0,0};
	Vector_2D velocity = {0,0};
	bool is_static = false;

};

// extern Physics_Component create_physics_component(Physics_Type type, Vector_2D velocity , Vector_2D acceleration , float mass);




#endif //PHYSICS_COMPONENT_H
