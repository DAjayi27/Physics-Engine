//
// Created by AJYDAN on 02/05/2025.
//

#ifndef RIGID_BODY_H
#define RIGID_BODY_H


#include <stdbool.h>
#include "core/vector.h"
#include "physics_component.h"


class Rigid_Body: public Physics_Component{


private:
	Vector_2D acceleration{};
	float mass;
	float restitution;
	bool affected_by_gravity;
	float friction;

public:
	Rigid_Body();
	Rigid_Body(float m, float f, float r,  Vector_2D v,  Vector_2D a, bool isStat, bool affectedGravity);
	const Vector_2D get_acceleration();
	float get_mass();
	float get_restitution();
	bool is_affected_by_gravity();
	float get_friction();
	Physics_Type get_type() override;

	void set_acceleration(Vector_2D a);
	void set_mass(float m);
	void set_restitution(float r);
	void set_affected_by_gravity(bool val);
	void set_friction(float f);


};


#endif //RIGID_BODY_H
