#include <Player.h>

#include <Globals.h>
#include <Logger.h>
#include <TransformComponent.h>
#include <RenderComponent.h>
#include <SpriteRenderer.h>

Player::Player(std::string name) : Entity(name)
{
	SetPosition({ 400.f, 300.f });

	gData.TextureMgr->LoadTexture("D:\\C++\\rubika_26_27_cpp_public\\MyEngine\\Ressources\\IsaacSprite.png");

	Start();
}

Player::~Player()
{}

void Player::Update(float fDeltaTime)
{
	isMoving = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		Move(fDeltaTime * sf::Vector2f(-1.f, 0.f) * speed);
		currentAnimationHead = "Head_Left";
		currentAnimationBody = "Body_Left";

		isMoving = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		Move(fDeltaTime * sf::Vector2f(1.f, 0.f) * speed);
		currentAnimationHead = "Head_Right";
		currentAnimationBody = "Body_Right";

		isMoving = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		Move(fDeltaTime * sf::Vector2f(0.f, -1.f) * speed);
		currentAnimationHead = "Head_Up";
		currentAnimationBody = "Body_Vertical";

		isMoving = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		Move(fDeltaTime * sf::Vector2f(0.f, 1.f) * speed);
		currentAnimationHead = "Head_Down";
		currentAnimationBody = "Body_Vertical";

		isMoving = true;
	}

	if (isMoving)
	{
		elapsedTime += fDeltaTime;

		if (elapsedTime >= frameIntervale)
		{
			if (bodyData.AnimationSpriteCount > 0)
			{
				currentFrameAnimation =	(currentFrameAnimation + 1) % bodyData.AnimationSpriteCount;
			}

			elapsedTime -= frameIntervale;
		}
	}
	else
	{
		currentFrameAnimation = 0;
		elapsedTime = 0.f;
	}

	UpdateAnimation();
}

void Player::Start()
{
	currentAnimationHead = "Head_Down";
	currentAnimationBody = "Body_Vertical";

	const TextureData& text = gData.TextureMgr->GetTextureData("IsaacSprite");

	GetComponent<RenderComponent>()->AddDrawable<SpriteRenderer>(text.Texture);

	Entity::Start();

	UpdateAnimation();
}

void Player::SetPosition(sf::Vector2f newPosition)
{
	GetComponent<TransformComponent>()->SetWorldPosition(newPosition);
	sf::Vector2 pos = GetComponent<TransformComponent>()->GetWorldPosition();

	headSprite.setPosition({ pos.x, pos.y });
	bodySprite.setPosition(
		{ pos.x + (headData.SizeX / 2 - bodyData.SizeX / 2),
		pos.y + (headData.SizeY / 2 + bodyData.SizeY / 2) });
}

void Player::Move(sf::Vector2f velocity)
{
	SetPosition(GetComponent<TransformComponent>()->GetWorldPosition() + velocity);
}