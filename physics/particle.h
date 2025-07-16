//
// Created by AJYDAN on 01/07/2025.
//

#ifndef PARTICLE_H
#define PARTICLE_H
#include "physics_component.h"
#include "core/vector.h"

class Particle : public  Physics_Component{

private:
    float lifetime;
    float mass;
		bool affected_by_gravity;
public:
	Particle();
	Particle(float m, Vector_2D v, float lifetime, bool isStat);
	float get_mass();
	bool is_affected_by_gravity();
	void set_affected_by_gravity(bool val);
	void set_mass(float m);
	Physics_Type get_type() override;

} ;


#endif //PARTICLE_H
