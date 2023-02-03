#pragma once
#include "Module.h"
#include "Globals.h"
#include "PhysBody3D.h"

struct Cube;

class ModuleMap : public Module
{

public:

	ModuleMap(Application* app, bool start_enabled = true);
	virtual ~ModuleMap();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void CreateMap(vec3 size, vec3 pos, float angle = 0.0, Color color = Color(0, 1, 0, 0));
	void MergeMap();

	void LoadMap();

	p2List<Cube*> Cubes;
	p2List_item<Cube*>* CubesItem;

	PhysBody3D* PhysBodyA;
	PhysBody3D* PhysBodyB;

	Cube* cubeA;
	Cube* cubeB;
	
};
