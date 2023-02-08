#include "Globals.h"
#include "Application.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "ModulePhysics3D.h"
#include "ModuleMap.h"

ModuleMap::ModuleMap(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

ModuleMap::~ModuleMap()
{}

bool ModuleMap::Start()
{

	LOG("Loading Map"); //thanks moduleplayer.ccp!

	LoadMap();

	return true;

}

bool ModuleMap::CleanUp()
{

	LOG("Unloading Circuit");

	return true;

}

update_status ModuleMap::Update(float dt)
{

	CubesItem = Cubes.getFirst();

	while (CubesItem != NULL) {

		CubesItem->data->Render();
		CubesItem = CubesItem->next;

	}

	//PhysBodyA->GetTransform(cubeA->transform.M);
	//cubeA->Render();

	return UPDATE_CONTINUE;

}

void ModuleMap::LoadMap()
{

	MergeMap(); //sounds like a shitty mobile game

}

void ModuleMap::MergeMap()
{

	Color Green(0.0, 1.0, 0.0); //bob ross said green

	//Map base

	CreateWalls(vec3(20, 1, 20), vec3(0, 0, 0));
	CreateFloor(vec3(20, 1, 20), vec3(0, 0, 0));

}

void ModuleMap::CreateWalls(vec3 size, vec3 pos, float angle, Color color)
{

	pos.y += 1;

	btBoxShape* box = new btBoxShape(btVector3(size.x / 2, size.y / 2, size.z / 2));
	btCollisionShape* collision = box;
	btCollisionObject* collider = new btCollisionObject();
	btDefaultMotionState* motionState = new btDefaultMotionState();
	btRigidBody* body = new btRigidBody(0, motionState, collision);

	App->physics->world->addRigidBody(body);

	PhysBody3D* PhysBody = new PhysBody3D(body);
	PhysBody->SetPos(pos.x, pos.y, pos.z);

	Cube* cube = new Cube(size.x, size.y, size.z);
	cube->SetPos(size.x, size.y, size.z);
	cube->SetRotation(angle, vec3(0, 1, 0));

	PhysBody->SetTransform(cube->transform.M);

	cube->color.Set(color.r, color.g, color.b, color.a);

	Cubes.add(cube);

}

void ModuleMap::CreateFloor(vec3 size, vec3 pos, Color color)
{
	pos.y += 0;

	btCollisionShape* colShape = new btStaticPlaneShape(btVector3(0, 1, 0), 0);
	btDefaultMotionState* myMotionState = new btDefaultMotionState();
	btRigidBody::btRigidBodyConstructionInfo rbInfo(0.0f, myMotionState, colShape);
	btRigidBody* body = new btRigidBody(rbInfo);

	App->physics->world->addRigidBody(body);

}
