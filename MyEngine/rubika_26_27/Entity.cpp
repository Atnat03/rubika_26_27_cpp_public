#include <Entity.h>
#include <Logger.h>
#include <Globals.h>

#include <string.h>
#include <utility>

Entity::Entity(std::string name) : 
	name(std::move(name)),
	headSprite(gData.TextureMgr->DefaultTextureData.Texture), 
	bodySprite(gData.TextureMgr->DefaultTextureData.Texture),
	textureData(gData.TextureMgr->DefaultTextureData)
{}

Entity::~Entity()
{
}

void Entity::Start()
{
	bool b = gData.TextureMgr->LoadTexture("D:\\C++\\rubika_26_27_cpp_public\\MyEngine\\Ressources\\IsaacSprite.png");

	if (b)
	{
		const TextureData& text = gData.TextureMgr->GetTextureData("IsaacSprite");

		texture = text.Texture;
		textureData = text;

		headSprite = sf::Sprite(texture);
		bodySprite = sf::Sprite(texture);

		Transform.SetWorldPosition({ 400.f, 300.f });
		sf::Vector2 pos = Transform.GetWorldPosition();
	
		UpdateAnimation();
	}
}

void Entity::Draw(sf::RenderWindow& window) const
{
	window.draw(bodySprite);
	window.draw(headSprite);
}

void Entity::UpdateAnimation()
{
    sf::Vector2f pos = Transform.GetWorldPosition();

	if (!textureData.AnimationsData.contains(currentAnimationHead))	return;
	if (!textureData.AnimationsData.contains(currentAnimationBody))	return;

    headData = textureData.AnimationsData.at(currentAnimationHead);
    bodyData = textureData.AnimationsData.at(currentAnimationBody);

    headSprite.setTextureRect({
        {headData.StartX, headData.StartY},
        {headData.SizeX, headData.SizeY}
    });

	headSprite.setPosition(pos);

	int frame = currentFrameAnimation;

	int column = frame % bodyData.SpriteOnLine;
	int row = frame / bodyData.SpriteOnLine;

	int frameX = bodyData.StartX + column * (bodyData.SizeX + bodyData.OffsetX);
	int frameY = bodyData.StartY + row * (bodyData.SizeY + bodyData.OffsetY);

	bodySprite.setTextureRect({
		{ frameX, frameY },
		{ bodyData.SizeX, bodyData.SizeY }
	});

	bodySprite.setOrigin({bodyData.SizeX / 2.f,	0.f});

	bodySprite.setScale({bodyData.IsReverted ? -1.f : 1.f, 1.f });

	bodySprite.setPosition({
		pos.x + headData.SizeX / 2.f,
		pos.y + headData.SizeY - 5.f
	});
}

void Entity::Update(float fDeltaTime)
{}

void Entity::Destroy()
{

}

std::string Entity::GetName() const
{
	return name;
}