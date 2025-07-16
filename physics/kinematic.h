//
// Created by AJYDAN on 01/07/2025.
//

#ifndef KINEMATIC_H
#define KINEMATIC_H
#include "physics_component.h"
#include "core/vector.h"

class Kinematic : public Physics_Component{
private:
	bool affected_by_gravity;
	Vector_2D acceleration{};
	float mass;

public:
	Kinematic();
	Kinematic(float mass,Vector_2D velocity,  Vector_2D a, bool isStat, bool affectedGravity);
	const Vector_2D get_acceleration();
	float get_mass();
	bool is_affected_by_gravity();
	Physics_Type get_type() override;

	void set_acceleration(Vector_2D a);
	void set_mass(float m);
	void set_affected_by_gravity(bool val);

};


#endif //KINEMATIC_H
