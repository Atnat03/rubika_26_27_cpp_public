#pragma once

#include <IDrawable.h>
#include <IComponent.h>
#include <vector>

class Entity;

class RenderComponent : public IComponent
{
public:
	RenderComponent(Entity& entity);
	~RenderComponent();

	void Start() override;
	void Update(float dt) override;
	void Destroy() override;

	template <typename D, typename... Arg>
	D* AddDrawable(Arg&&... arg);

	template <typename D>
	D* GetDrawable() const;

	std::vector<IDrawable*> DrawableList;

private :
};


template<typename D, typename... Arg>
D* RenderComponent::AddDrawable(Arg&&... args)
{
    static_assert(std::is_base_of_v<IDrawable, D>, "D must inherit from IDrawable");

    D* drawable = new D(std::forward<Arg>(args)...);
    DrawableList.push_back(drawable);

    return drawable; 
}


template<typename D>
D* RenderComponent::GetDrawable() const
{
    for (auto* d : DrawableList)
    {
        if (auto* drawable = dynamic_cast<D*>(d))
        {
            return drawable;
        }
    }

    return nullptr;
}


