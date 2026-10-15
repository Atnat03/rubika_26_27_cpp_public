
#include "SpriteRenderer.h"

#include <TextureMgr.h>
#include <Entity.h>

SpriteRenderer::SpriteRenderer(const TextureData& data, Entity* entity, TransformComponent& transform)
    : IDrawable(),
    DataTexture(&data),
    Animator(*entity, &data),
    Transform(&transform)
{
    Sprite = new sf::Sprite(data.Texture);
    Drawable = Sprite;
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::Start()
{
}

void SpriteRenderer::Update(float dt)
{
    Animator.Update(dt);
    UpdateTextureRect();
}

void SpriteRenderer::Destroy()
{
}

void SpriteRenderer::SetAnimation(const std::string& name)
{
    Animator.SetAnimation(name);
    UpdateTextureRect();
}

void SpriteRenderer::SetFrameAnimation(int frame)
{}

void SpriteRenderer::UpdateTextureRect()
{
    const AnimationData* animation =
        Animator.GetCurrentAnimation();

    if (!Sprite || !animation)
        return;

    if (animation->SpriteOnLine <= 0 ||
        animation->SizeX <= 0 ||
        animation->SizeY <= 0)
        return;

    const int frame = Animator.GetCurrentFrame();

    const int column = frame % animation->SpriteOnLine;
    const int row = frame / animation->SpriteOnLine;

    const int frameX = animation->StartX +
        column * (animation->SizeX + animation->OffsetX);

    const int frameY = animation->StartY +
        row * (animation->SizeY + animation->OffsetY);

    Sprite->setTextureRect({
        {frameX, frameY},
        {animation->SizeX, animation->SizeY}
        });

    Sprite->setScale({
        animation->IsReverted ? -1.f : 1.f,
        1.f
        });
}
