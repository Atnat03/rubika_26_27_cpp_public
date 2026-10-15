template<typename C>
C* Entity::AddComponent()
{
    static_assert(std::is_base_of_v<IComponent, C>, "C must inherit from IComponent");

    for (auto* c : Components)
    {
        if (dynamic_cast<C*>(c) != nullptr)
        {
            return nullptr;
        }
    }

    C* component = new C(*this);
    Components.push_back(component);

    return component;
}


template<typename C>
C* Entity::GetComponent() const
{
    for (auto* c : Components)
    {
        if (auto* component = dynamic_cast<C*>(c))
        {
            return component;
        }
    }

    return nullptr;
}

