#include <Entity.h>
#include <Logger.h>
#include <string.h>
#include <Globals.h>
#include <TextureMgr.h>

Entity::Entity(std::string friendlyName)
{
	name = friendlyName;
	Start();
}

Entity::~Entity()
{
}

void Entity::Start()
{
	sprite = sf::CircleShape(20);

	bool b = gData.TextureMgr->LoadTexture("D:\\C++\\rubika_26_27_cpp_public\\MyEngine\\Ressources\\IsaacSprite.png");

	if (b)
	{
		const TextureData& texture = gData.TextureMgr->GetTextureData("IsaacSprite");

		if (texture.Name.empty())
		{
			Logger::Info("Texture not found!");
			return;
		}
		sprite.setTexture(&texture.Texture);
	}

	sprite.setOrigin({ 200.f, 200.f });
	sprite.setPosition({ 400.f, 300.f });
}

void Entity::Draw(sf::RenderWindow& window) const
{
	window.draw(sprite);
}

void Entity::Update(float fDeltaTime)
{
}

void Entity::Destroy()
{
}

std::string Entity::GetName() const
{
	return name;
}