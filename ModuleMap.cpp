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

	if (App->player->vehicle->GetPos().y < -50) {

		App->player->vehicle->SetPos(0, 5, 0);

	}

	//PhysBodyA->GetTransform(cubeA->transform.M);
	//cubeA->Render();

	return UPDATE_CONTINUE;

}

void ModuleMap::LoadMap()
{

	MergeMap(); //sounds like a shitty mobile game

	CreateGoal();
	CreateBall();

}

void ModuleMap::MergeMap()
{

	Color Green(0.0, 1.0, 0.0); //bob ross said green
	Color White(1.0, 1.0, 1.0);

	//Map base
	
	//walls
	CreateWalls(vec3(5, 60, 200), vec3 (100, 0, 0));
	CreateWalls(vec3(5, 60, 200), vec3 (-100, 0, 0));
	CreateWalls(vec3(200, 60, 5), vec3 (0, 0, 100));
	CreateWalls(vec3(200, 60, 5), vec3 (0, 0, -100));

	//gradas
	CreateWalls(vec3(7, 40, 100), vec3(94, -10, 0), 0, White);
	CreateWalls(vec3(10, 32, 100), vec3(85.5, -14, 0), 0, White);
	CreateWalls(vec3(12, 26, 100), vec3(74.5, -17, 0), 0, White);

	CreateWalls(vec3(7, 40, 100), vec3(-94, -10, -0), 0, White);
	CreateWalls(vec3(10, 32, 100), vec3(-85.5, -14, -0), 0, White);
	CreateWalls(vec3(12, 26, 100), vec3(-74.5, -17, -0), 0, White);

	//mini walls
	//CreateWalls(vec3(1, 3, 150), vec3(60, -18, 0));


	CreateFloor(vec3(20, 1, 20), vec3(20, 0, 20));

}

void ModuleMap::CreateWalls(vec3 size, vec3 pos, float angle, Color color)
{

	pos.y += 30;

	btBoxShape* box = new btBoxShape(btVector3(size.x / 2, size.y / 2, size.z / 2));
	btCollisionShape* collision = box;
	btCollisionObject* collider = new btCollisionObject();
	btDefaultMotionState* motionState = new btDefaultMotionState();
	btRigidBody* body = new btRigidBody(0, motionState, collision);

	App->physics->world->addRigidBody(body);

	PhysBody3D* PhysBody = new PhysBody3D(body);
	PhysBody->SetPos(pos.x, pos.y, pos.z);

	Cube* cube = new Cube(size.x, size.y, size.z);
	cube->SetPos(pos.x, pos.y, pos.z);
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

void ModuleMap::CreateGoal()
{

	sensor_goal = App->physics->AddBody(Cube(5, 5, 5), 0.0);
	sensor_goal->SetPos(50, 5, 10);
	sensor_goal->SetAsSensor(true);

}

void ModuleMap::CreateBall()
{
	ball = App->physics->AddBody(Sphere(2), 1.0);
	ball->SetPos(7, 5, 7);
	ball->collision_listeners.add(this);
}

void ModuleMap::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	if ((body1 == ball && body2 == sensor_goal) || (body2 == ball && body1 == sensor_goal)) {

		//WIN
		//setposiiotn

		ball->SetPos(3, 5, 3);
		App->player->vehicle->SetPos(0, 5, 0);

		ball->SetVelocity(0, 0, 0);
		ball->AngularVelocity(0, 0, 0);
		App->player->vehicle->SetVelocity(0, 0, 0);

	}
}