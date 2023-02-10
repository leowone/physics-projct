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

	LOG("Loading Map");

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

	

	return UPDATE_CONTINUE;

}

void ModuleMap::LoadMap()
{

	MergeMap();

	CreateGoal();
	CreateBall(2, (0, 5, 8), White);

}

void ModuleMap::MergeMap()
{

	Color Green(0.0, 1.0, 0.0);
	Color White(1.0, 1.0, 1.0);
	Color Red(1.0, 0.0, 0.0);
	Color Black(0.0, 0.0, 0.0);
	Color Blue(0.0, 0.0, 0.5);
	Color Yellow(1.0, 1.0, 0.0);
	Color Pink(1.0, 0.0, 1.0);
	Color Cyan(0.0, 1.0, 1.0);

	//Map base
	
	//walls
	CreateWalls(vec3(5, 60, 200), vec3 (100, 0, 0), 0, Blue);
	CreateWalls(vec3(5, 60, 200), vec3 (-100, 0, 0), 0, Blue);
	CreateWalls(vec3(200, 60, 5), vec3 (0, 0, 100), 0, Blue);
	CreateWalls(vec3(200, 60, 5), vec3 (0, 0, -100), 0, Blue);

	//gradas
	CreateWalls(vec3(7, 30, 150), vec3(94, -28, 0));
	CreateWalls(vec3(10, 22, 150), vec3(85.5, -28, 0));
	CreateWalls(vec3(12, 16, 150), vec3(74.5, -30, 0));
	CreateWalls(vec3(7, 30, 150), vec3(-94, -28, -0));
	CreateWalls(vec3(10, 22, 150), vec3(-85.5, -28, -0));
	CreateWalls(vec3(12, 16, 150), vec3(-74.5, -30, -0));

	//mini walls
	CreateWalls(vec3(1, 3, 159), vec3(62.5, -28.5, 0), 0, Yellow);
	CreateWalls(vec3(1, 3, 159), vec3(-62.5, -28.5, 0), 0, Yellow);
	CreateWalls(vec3(50, 3, 1), vec3(38, -28.5, 80), 0, Yellow);
	CreateWalls(vec3(50, 3, 1), vec3(-38, -28.5, 80), 0, Yellow);
	CreateWalls(vec3(126, 3, 1), vec3(0, -28.5, -80), 0, Yellow);

	//goal
	CreateWalls(vec3(2, 10, 10), vec3(12, -25.1, 80), 0, White);
	CreateWalls(vec3(2, 10, 10), vec3(-12, -25.1, 80), 0, White);
	CreateWalls(vec3(23, 10, 1), vec3(0, -25.1, 85), 0, White);
	CreateWalls(vec3(22, 0.5, 9), vec3(0, -19.9, 79.5), 0, White);

	//arrow
	CreateWalls(vec3(10, 20, 1), vec3(0, 10, 82), 0, Red);
	CreateWalls(vec3(25, 2, 1), vec3(0, -1, 82), 0, Red);
	CreateWalls(vec3(20, 2, 1), vec3(0, -3, 82), 0, Red);
	CreateWalls(vec3(15, 2, 1), vec3(0, -5, 82), 0, Red);
	CreateWalls(vec3(10, 2, 1), vec3(0, -7, 82), 0, Red);
	CreateWalls(vec3(5, 2, 1), vec3(0, -9, 82), 0, Red);
	CreateWalls(vec3(3, 2, 1), vec3(0, -11, 82), 0, Red);
	CreateWalls(vec3(1, 2, 1), vec3(0, -13, 82), 0, Red);

	//roof
	CreateWalls(vec3(200, 1, 200), vec3(0, 40, 0), 0, Blue);

	//floor texture
	CreateWalls(vec3(200, 1, 200), vec3(0, -40, 0), 0, Pink);
	CreateWalls(vec3(60, 40, 200), vec3(93, -49.9, 0), 0, Green);
	CreateWalls(vec3(60, 40, 200), vec3(-93, -49.9, 0), 0, Green);
	CreateWalls(vec3(126, 40, 20), vec3(0, -49.9, -90), 0, Green);
	CreateWalls(vec3(126, 40, 10), vec3(0, -49.9, 90), 0, Green);


	CreateFloor(vec3(100, 1, 100), vec3(0, 0, 0));

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
	pos.y += 1;

	btCollisionShape* colShape = new btStaticPlaneShape(btVector3(0, 1, 0), 0);
	btDefaultMotionState* myMotionState = new btDefaultMotionState();
	btRigidBody::btRigidBodyConstructionInfo rbInfo(0.0f, myMotionState, colShape);
	btRigidBody* body = new btRigidBody(rbInfo);

	App->physics->world->addRigidBody(body);

}

void ModuleMap::CreateGoal()
{

	sensor_goal = App->physics->AddBody(Cube(22, 10, 8), 0.0);
	sensor_goal->SetPos(0, 5, 80);
	sensor_goal->SetAsSensor(true);

}

void ModuleMap::CreateBall(float radius, vec3 pos, Color color)
{
	ball = App->physics->AddBody(Sphere(radius), 1.0);
	ball->SetPos(pos.x, pos.y, pos.z);
	ball->collision_listeners.add(this);

}

void ModuleMap::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	if ((body1 == ball && body2 == sensor_goal) || (body2 == ball && body1 == sensor_goal)) {

		//WIN
		//setposiiotn

		ball->SetPos(0, 5, 8);
		App->player->vehicle->SetPos(0, 5, 0);

		ball->SetVelocity(0, 0, 0);
		ball->AngularVelocity(0, 0, 0);
		App->player->vehicle->SetVelocity(0, 0, 0);

	}
}