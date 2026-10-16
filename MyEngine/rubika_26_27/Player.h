#pragma once

#include <Entity.h>
#include <string.h>

class SpriteRenderer;
class TransformComponent;
struct AnimationData;

class Player : public Entity
{
public :
	Player(std::string name);
	~Player();

	void Update(float fDeltaTime) override;
	void Start() override;

	void Move(sf::Vector2f velocity);

private :
	float speed = 200.f;

	SpriteRenderer* headSprite;
	SpriteRenderer* bodySprite;

	TransformComponent* transform;

	AnimationData headData;
	AnimationData bodyData;

	std::string currentAnimationHead = "";
	std::string currentAnimationBody = "";
};

