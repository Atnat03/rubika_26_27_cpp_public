#include "SpriteRenderer.h"

#include <SFML/Graphics.hpp>

SpriteRenderer::SpriteRenderer(const sf::Texture& texture) : IDrawable()
{
	sf::Sprite* s = new sf::Sprite(texture);
	s->setPosition({ 200.f, 200.f });

	Drawable = s;
}

SpriteRenderer::~SpriteRenderer(){}
void SpriteRenderer::Start(){}
void SpriteRenderer::Update(float dt){}
void SpriteRenderer::Destroy(){}