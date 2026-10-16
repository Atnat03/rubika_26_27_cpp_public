#include <Player.h>

#include <Globals.h>
#include <Logger.h>
#include <TransformComponent.h>
#include <RenderComponent.h>
#include <SpriteRenderer.h>
#include <string.h>

Player::Player(std::string name) : Entity(name)
{
    transform = GetComponent<TransformComponent>();
    transform->SetWorldPosition({ 400.f, 300.f });

	Start();
}

Player::~Player()
{}


void Player::Start()
{
    Entity::Start();

    currentAnimationHead = "Head_Down";
    currentAnimationBody = "Body_Vertical";

    const TextureData& texture = gData.TextureMgr->GetTextureData("IsaacSprite");

    headSprite = GetComponent<RenderComponent>()->AddDrawable<SpriteRenderer>(texture, this, *transform);
    bodySprite = GetComponent<RenderComponent>()->AddDrawable<SpriteRenderer>(texture, this, *transform);

    bodySprite->Animator.SetAnimation("Body_Vertical");
    Logger::Warning("Animation : " + std::to_string(bodySprite->Animator.GetCurrentAnimation()->TimeBetweenAnimationInS));
    
    Entity::Start();

    headSprite->SetAnimation(currentAnimationHead);
    bodySprite->SetAnimation(currentAnimationBody);
}

void Player::Update(float dt)
{
    Entity::Update(dt);

    std::string animationHead = currentAnimationHead;
    std::string animationBody = currentAnimationBody;

    sf::Vector2f direction{ 0.f, 0.f };

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        direction.x -= 1.f;
        animationHead = "Head_Left";
        animationBody = "Body_Left";
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        direction.x += 1.f;
        animationHead = "Head_Right";
        animationBody = "Body_Right";
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        direction.y -= 1.f;
        animationHead = "Head_Up";
        animationBody = "Body_Vertical";
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        direction.y += 1.f;
        animationHead = "Head_Down";
        animationBody = "Body_Vertical";
    }

    if (direction.x != 0.f || direction.y != 0.f)
    {
        const float length = std::sqrt(
            direction.x * direction.x +
            direction.y * direction.y
        );

        direction /= length;

        Move(direction * speed * dt);
    }
    
    currentAnimationHead = animationHead;
    currentAnimationBody = animationBody;

    headSprite->SetAnimation(currentAnimationHead);
    bodySprite->SetAnimation(currentAnimationBody);
}

void Player::Move(sf::Vector2f velocity)
{
	sf::Vector2f newPosition = transform->GetWorldPosition() + velocity;

	transform->SetWorldPosition(newPosition);

	if (headSprite)
        headSprite->SetWorldPosition(newPosition);

    if (bodySprite)
        bodySprite->SetWorldPosition({newPosition.x + 10, newPosition.y + 10});
}