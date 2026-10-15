#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <IDrawable.h>

class SpriteRenderer : public IDrawable
{
public:
	SpriteRenderer(const sf::Texture& texture);
	~SpriteRenderer() override;

	void Start() override;
	void Update(float dt) override;
	void Destroy() override;
};

