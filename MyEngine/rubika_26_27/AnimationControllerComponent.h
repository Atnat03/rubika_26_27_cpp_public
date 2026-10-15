#pragma once

#include <IComponent.h>
#include <string>
#include <TextureMgr.h>

class AnimationControllerComponent : public IComponent
{
public:
	AnimationControllerComponent(Entity& entity, const TextureData* data);
	~AnimationControllerComponent();

	void Start() override;
	void Update(float dt) override;
	void Destroy() override;

	void SetAnimation(const std::string& name);

	const AnimationData* GetCurrentAnimation() const;
	int GetCurrentFrame() const;

private:
	const TextureData* DataTexture = nullptr;

	std::string AnimationName;
	int CurrentFrame = 0;
	float ElapsedTime = 0.f;
};

