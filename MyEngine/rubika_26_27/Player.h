#pragma once

#include <Entity.h>
#include <string.h>

class Player : public Entity
{
public :
	Player(std::string name);
	~Player();

	void Update(float fDeltaTime) override;
	void Start() override;

	void SetPosition(sf::Vector2f newPosition);
	void Move(sf::Vector2f velocity);

private :
	float speed = 200.f;
};

