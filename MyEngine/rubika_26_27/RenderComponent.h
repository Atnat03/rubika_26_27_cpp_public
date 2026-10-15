#pragma once

#include <IDrawable.h>

#include <vector>

class Entity;

class RenderComponent
{
public:
	RenderComponent(Entity& entity);
	~RenderComponent();

	void Start();
	void Update(float dt);
	void Destroy(float dt);

	std::vector<IDrawable> DrawableList;
};

