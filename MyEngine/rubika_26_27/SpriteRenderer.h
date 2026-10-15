#pragma once

#include <SFML/Graphics.hpp>
#include <IDrawable.h>
#include <AnimationControllerComponent.h>

class TransformComponent;
struct TextureData;

class SpriteRenderer : public IDrawable
{
public:
	SpriteRenderer(const TextureData& data, Entity* entity, TransformComponent& transform);
	~SpriteRenderer() override;

	void Start() override;
	void Update(float dt) override;
	void Destroy() override;

	void SetAnimation(const std::string&);
	void SetFrameAnimation(int newFrame);

private:
	const TextureData* DataTexture;
	TransformComponent* Transform = nullptr;
	
	sf::Sprite* Sprite = nullptr;

	AnimationControllerComponent Animator;

	void UpdateTextureRect();
};

