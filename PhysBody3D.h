#ifndef __PhysBody3D_H__
#define __PhysBody3D_H__

#include "p2List.h"
#include "glmath.h"

class btRigidBody;
class Module;

// =================================================
struct PhysBody3D
{
	friend class ModulePhysics3D;
public:
	PhysBody3D(btRigidBody* body);
	~PhysBody3D();

	//void SetBody(Sphere* primitive, float mass);
	//bool HasBody() const;
	//btRigidBody* GetBody() const;

	void Push(float x, float y, float z);
	void GetTransform(float* matrix) const;
	void SetTransform(const float* matrix) const;
	void SetPos(float x, float y, float z);
	void AngularVelocity(float x, float y, float z);
	void SetVelocity(float x, float y, float z);
	void SetGrav(vec3 g);

	vec3 GetPos();

	void SetAsSensor(bool is_sensor);

private:

	btRigidBody* body = nullptr;
	bool is_sensor;

public:
	p2List<Module*> collision_listeners;

};

#endif // __PhysBody3D_H__