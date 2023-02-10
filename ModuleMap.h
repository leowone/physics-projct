#pragma once
#include "Module.h"
#include "Globals.h"
#include "PhysBody3D.h"
#include "Color.h"

struct Cube;

class ModuleMap : public Module
{

public:

	ModuleMap(Application* app, bool start_enabled = true);
	virtual ~ModuleMap();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void CreateWalls(vec3 size, vec3 pos, float angle = 0.0, Color color = Color (1, 1, 1, 1));
	void CreateFloor(vec3 size, vec3 pos, Color color = Color(1, 1, 1, 1));

	void CreateGoal();
	void CreateBall(float radius, vec3 pos, Color color);

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

	void MergeMap();

	void LoadMap();

	p2List<Cube*> Cubes;
	p2List_item<Cube*>* CubesItem;

	//p2List<Sphere*> Spheres;
	//p2List_item<Sphere*>* SpheresItem;

	PhysBody3D* PhysBodyA;
	PhysBody3D* PhysBodyB;
	PhysBody3D* sensor_goal;
	PhysBody3D* ball;

	Cube* cubeA;
	Cube* cubeB;
	
};
