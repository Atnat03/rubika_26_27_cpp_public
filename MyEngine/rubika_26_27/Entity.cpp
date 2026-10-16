#include <Entity.h>
#include <Logger.h>
#include <Globals.h>

#include <string.h>
#include <utility>

#include <TransformComponent.h>
#include <RenderComponent.h>

Entity::Entity(std::string name) : 
	name(std::move(name)),
	textureData(gData.TextureMgr->DefaultTextureData)
{

	AddComponent<TransformComponent>();
	AddComponent<RenderComponent>();
}

Entity::~Entity()
{
}

void Entity::Start()
{
	GetComponent<TransformComponent>()->SetWorldPosition({400.f, 300.f});
	sf::Vector2 pos = GetComponent<TransformComponent>()->GetWorldPosition();
}

void Entity::Draw(sf::RenderWindow& window) const
{
	for (auto d : GetComponent<RenderComponent>()->DrawableList)
	{
		d->Draw(window);
	}
}

void Entity::Update(float fDeltaTime)
{
	for (auto c : Components)
	{
		c->Update(fDeltaTime);
	}
}

void Entity::Destroy()
{

}

std::string Entity::GetName() const
{
	return name;
}