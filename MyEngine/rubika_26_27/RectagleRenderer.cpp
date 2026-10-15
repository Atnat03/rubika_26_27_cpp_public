#include "RectagleRenderer.h"

#include <SFML/Graphics.hpp>

RectangleRenderer::RectangleRenderer() : IDrawable()
{

	sf::RectangleShape *rect = new sf::RectangleShape();
	rect->setFillColor(sf::Color::Red);
	rect->setSize({100.f, 50.f});
	rect->setPosition({ 200.f, 200.f });

	Drawable = rect;
}

RectangleRenderer::~RectangleRenderer(){}

void RectangleRenderer::Start()
{
}

void RectangleRenderer::Update(float dt)
{
}

void RectangleRenderer::Destroy()
{
}
