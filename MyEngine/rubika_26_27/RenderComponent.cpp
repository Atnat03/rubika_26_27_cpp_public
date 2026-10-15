#include "RenderComponent.h"

#include <Entity.h>

RenderComponent::RenderComponent(Entity& entity) : IComponent(entity)
{}

RenderComponent::~RenderComponent(){}

void RenderComponent::Start(){}
void RenderComponent::Update(float dt){}
void RenderComponent::Destroy(){}