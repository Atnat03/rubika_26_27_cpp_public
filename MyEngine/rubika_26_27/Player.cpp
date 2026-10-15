#include <Player.h>

#include <Globals.h>
#include <Logger.h>
#include <TransformComponent.h>
#include <RenderComponent.h>
#include <SpriteRenderer.h>
#include <string.h>

Player::Player(std::string name) : Entity(name)
{
	GetComponent<TransformComponent>()->SetWorldPosition({ 400.f, 300.f });

	Start();
}

Player::~Player()
{}


void Player::Update(float dt)
{
    Entity::Update(dt);

    auto* renderer =
        GetComponent<RenderComponent>()
        ->GetDrawable<SpriteRenderer>();

    if (!renderer)
        return;

    std::string animation = currentAnimationHead;
    sf::Vector2f direction{ 0.f, 0.f };

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        direction.x -= 1.f;
        animation = "Head_Left";
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        direction.x += 1.f;
        animation = "Head_Right";
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        direction.y -= 1.f;
        animation = "Head_Up";
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        direction.y += 1.f;
        animation = "Head_Down";
    }

    if (direction.x != 0.f || direction.y != 0.f)
    {
        const float length = std::sqrt(
            direction.x * direction.x +
            direction.y * direction.y
        );

        direction /= length;

        Move(direction * speed * dt);
        currentAnimationHead = animation;
    }

    renderer->SetAnimation(currentAnimationHead);
}


void Player::Start()
{
    currentAnimationHead = "Head_Down";
    currentAnimationBody = "Body_Vertical";

    const TextureData& texture =
        gData.TextureMgr->GetTextureData("IsaacSprite");

    auto* transform = GetComponent<TransformComponent>();

    GetComponent<RenderComponent>()->AddDrawable<SpriteRenderer>(texture, this, *transform);

    Entity::Start();

    GetComponent<RenderComponent>()->GetDrawable<SpriteRenderer>()->SetAnimation(currentAnimationHead);
}

void Player::Move(sf::Vector2f velocity)
{
	auto* transform = GetComponent<TransformComponent>();

	sf::Vector2f newPosition = transform->GetWorldPosition() + velocity;

	transform->SetWorldPosition(newPosition);

	auto* renderer = GetComponent<RenderComponent>()->GetDrawable<SpriteRenderer>();

	if (renderer)
		renderer->SetWorldPosition(newPosition);
}