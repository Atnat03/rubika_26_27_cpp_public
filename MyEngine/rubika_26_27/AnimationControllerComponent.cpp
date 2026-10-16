#include "AnimationControllerComponent.h"

#include <Logger.h>

AnimationControllerComponent::AnimationControllerComponent(Entity& entity, const TextureData* data)
	: IComponent(entity),
	DataTexture(data)
{

}

AnimationControllerComponent::~AnimationControllerComponent(){}
void AnimationControllerComponent::Start()
{}

void AnimationControllerComponent::Destroy(){}

void AnimationControllerComponent::SetAnimation(const std::string& name)
{
	if (!DataTexture->AnimationsData.contains(name))
		return;

	if (AnimationName == name)
		return;

	AnimationName = name;
	CurrentFrame = 0;
	ElapsedTime = 0.f;
}

void AnimationControllerComponent::Update(float dt)
{
	const AnimationData* animation = GetCurrentAnimation();

	if (!animation)
		return;

	const int frameCount = animation->AnimationSpriteCount;
	const int interval = animation->TimeBetweenAnimationInS;

	if (frameCount <= 1 || interval <= 0.f)
	{
		CurrentFrame = 0;
		return;
	}

	ElapsedTime += dt;

	while (ElapsedTime >= interval)
	{
		ElapsedTime -= interval;
		CurrentFrame = (CurrentFrame + 1) % frameCount;
	}
}

const AnimationData* AnimationControllerComponent::GetCurrentAnimation() const
{
	if (!DataTexture || AnimationName.empty())
		return nullptr;

	auto it = DataTexture->AnimationsData.find(AnimationName);

	if (it == DataTexture->AnimationsData.end())
		return nullptr;

	return &it->second;
}

int AnimationControllerComponent::GetCurrentFrame() const
{
	return CurrentFrame;
}
