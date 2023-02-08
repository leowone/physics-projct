#include "PhysBody3D.h"
#include "glmath.h"
#include "Globals.h"
#include "Application.h"
#include "Primitive.h"
#include "Bullet/include/btBulletDynamicsCommon.h"

// =================================================
PhysBody3D::PhysBody3D(btRigidBody* body) : body(body)

/*: body(nullptr)
	, colShape(nullptr)
	, motionState(nullptr)
	, parentPrimitive(nullptr)
	, collision_listeners()*/

{}

// ---------------------------------------------------------
PhysBody3D::~PhysBody3D()
{
	/*if (HasBody() == true)
	{
		App->physics->RemoveBodyFromWorld(body);
		delete body;
		delete colShape;
		delete motionState;
	}*/

	delete body;
}

/*void PhysBody3D::SetBody(Sphere* primitive, float mass)
{
	SetBody(new btSphereShape(primitive->GetRadius()),
		primitive, mass);
}

bool PhysBody3D::HasBody() const
{
	return body != nullptr;
}

btRigidBody* PhysBody3D::GetBody() const
{
	return body;
}*/

// ---------------------------------------------------------
void PhysBody3D::Push(float x, float y, float z)
{
	body->applyCentralImpulse(btVector3(x, y, z));
}

// ---------------------------------------------------------
void PhysBody3D::GetTransform(float* matrix) const
{
	if(body != NULL && matrix != NULL)
	{
		body->getWorldTransform().getOpenGLMatrix(matrix);
	}
}

// ---------------------------------------------------------
void PhysBody3D::SetTransform(const float* matrix) const
{
	if(body != NULL && matrix != NULL)
	{
		btTransform t;
		t.setFromOpenGLMatrix(matrix);
		body->setWorldTransform(t);
	}
}

// ---------------------------------------------------------
void PhysBody3D::SetPos(float x, float y, float z)
{
	btTransform t = body->getWorldTransform();
	t.setOrigin(btVector3(x, y, z));
	body->setWorldTransform(t);
}

vec3 PhysBody3D::GetPos()
{
	btVector3 getP = body->getWorldTransform().getOrigin();

	vec3 pos;
	pos.x = getP.x();
	pos.y = getP.y();
	pos.z = getP.z();

	return pos;
}

void PhysBody3D::AngularVelocity(float x, float y, float z)
{

	body->setAngularVelocity({ x, y, z });

}

void PhysBody3D::SetVelocity(float x, float y, float z)
{
	body->setLinearVelocity({ x, y, z });
}

void PhysBody3D::SetGrav(vec3 g)
{

	body->setGravity({ g.x, g.y, g.z });

}

void PhysBody3D::SetAsSensor(bool is_sensor)
{
	if (this->is_sensor != is_sensor)
	{
		this->is_sensor = is_sensor;
		if (is_sensor == true)
			body->setCollisionFlags(body->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
		else
			body->setCollisionFlags(body->getCollisionFlags() & ~btCollisionObject::CF_NO_CONTACT_RESPONSE);
	}
}

/*void PhysBody3D::SetBody(btCollisionShape* shape, Primitive* parent, float mass)
{
	assert(HasBody() == false);

	parentPrimitive = parent;

	colShape = shape;

	btTransform startTransform;
	startTransform.setFromOpenGLMatrix(&parent->transform);

	btVector3 localInertia(0, 0, 0);
	if (mass != 0.f)
		colShape->calculateLocalInertia(mass, localInertia);

	motionState = new btDefaultMotionState(startTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, colShape, localInertia);

	body = new btRigidBody(rbInfo);

	body->setUserPointer(this);

	App->physics->AddBodyToWorld(body); 
}*/