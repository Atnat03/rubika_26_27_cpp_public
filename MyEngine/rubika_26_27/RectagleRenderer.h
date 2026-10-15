#pragma once

#include <IDrawable.h>

class RectangleRenderer : public IDrawable
{
public :
	RectangleRenderer();
	~RectangleRenderer() override;

	void Start() override;
	void Update(float dt) override;
	void Destroy() override;
};