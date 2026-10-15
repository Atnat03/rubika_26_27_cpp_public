#include "RenderComponent.h"

#include <Entity.h>
#include <Logger.h>

RenderComponent::RenderComponent(Entity& entity) : IComponent(entity)
{}

RenderComponent::~RenderComponent(){}

void RenderComponent::Start(){}

void RenderComponent::Update(float dt)
{
	for (auto d : DrawableList)
	{
		d->Update(dt);
	}
}

void RenderComponent::Destroy(){}