#include "PhysVehicle3D.h"
#include "Primitive.h"
#include "Bullet/include/btBulletDynamicsCommon.h"

// ----------------------------------------------------------------------------
VehicleInfo::~VehicleInfo()
{

}

// ----------------------------------------------------------------------------
PhysVehicle3D::PhysVehicle3D(btRigidBody* body, btRaycastVehicle* vehicle, const VehicleInfo& info) : PhysBody3D(body), vehicle(vehicle), info(info)
{
}

// ----------------------------------------------------------------------------
PhysVehicle3D::~PhysVehicle3D()
{
	delete vehicle;
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Render()
{
	Cylinder wheel;

	wheel.color = Black;

	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		wheel.radius = info.wheels[0].radius;
		wheel.height = info.wheels[0].width;

		vehicle->updateWheelTransform(i);
		vehicle->getWheelInfo(i).m_worldTransform.getOpenGLMatrix(&wheel.transform);

		wheel.Render();
	}

	//x y z, distance, height

	//hitbox : car.chassis_size.Set(2, 1.5, 4);

	//main body of the car
	RenderChassisElement(2, 1.5, 1.75, 0.5, 0);
	RenderChassisElement(2, 0.75, 4, 0, -0.37);
	RenderChassisElement(1.20, 0.75, 3.75, -0, -0.20);

	//aleron
	RenderChassisElement(5, 0.1, 0.4, 2, 0.8);
	RenderChassisElement(5, 0.1, 0.1, 1.86, 0.7);
	RenderChassisElement(0.1, 0.4, 0.4, 1.86, 0.7);
	RenderChassisElement(0.1, 0.4, 0.4, 1.74, 0.4);
	RenderChassisElement(0.1, 0.4, 0.4, 1.60, 0.1);

	//rueda cosa
	RenderChassisElement(3.3, 0.25, 1, 1.5, -0.1);

}

void PhysVehicle3D::RenderChassisElement(float x, float y, float z, float offsetBehind, float offsetVertical)
{
	Cube chassis_element(x, y, z); //TAMAÑO DEL OBJETO

	chassis_element.color = Red;

	vehicle->getChassisWorldTransform().getOpenGLMatrix(&chassis_element.transform);
	btQuaternion q = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offset(info.chassis_offset.x, info.chassis_offset.y, info.chassis_offset.z);
	offset = offset.rotate(q.getAxis(), q.getAngle());
	auto elementOffsetBehind = -offsetBehind * vehicle->getForwardVector();
	chassis_element.transform.M[12] += offset.getX() + elementOffsetBehind.getX();
	chassis_element.transform.M[13] += offset.getY() + elementOffsetBehind.getY() + offsetVertical;
	chassis_element.transform.M[14] += offset.getZ() + elementOffsetBehind.getZ();
	chassis_element.Render();


}

// ----------------------------------------------------------------------------
void PhysVehicle3D::ApplyEngineForce(float force)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].drive == true)
		{
			vehicle->applyEngineForce(force, i);
		}
	}
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Brake(float force)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].brake == true)
		{
			vehicle->setBrake(force, i);
		}
	}
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Turn(float degrees)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].steering == true)
		{
			vehicle->setSteeringValue(degrees, i);
		}
	}
}

// ----------------------------------------------------------------------------
float PhysVehicle3D::GetKmh() const
{
	return vehicle->getCurrentSpeedKmHour();
}
