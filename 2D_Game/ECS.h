#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;

class Entity;

using ComponentID = std::size_t;

inline ComponentID getComponentID()
{
	static ComponentID last_id = 0;
	return last_id++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
	static ComponentID type_id = getComponentID();
	return type_id;
}

constexpr  std::size_t max_components = 32;

using ComponentBitSet = std::bitset<max_components>;
using ComponentArray = std::array<Component*, max_components>;

class Component
{
public:
	Entity* entity;

	virtual void init() {}
	virtual void update() {}
	virtual void draw() {}

	virtual ~Component() {}
};

class Entity
{
private:
	bool active = true;
	std::vector<std::unique_ptr<Component>> components_;

	ComponentArray component_array_;
	ComponentBitSet component_bit_set_;

public:
	void udpate()
	{
		for (auto& c : components_) c->update();
	}

	void draw()
	{
		for (auto& c : components_) c->draw();
	}

	bool isActive() { return active; }
	void destroy() { active = false; }

	template <typename T> bool hasComponents() const
	{
		return component_bit_set_[getComponentTypeID<T>()];
	}

	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... m_args)
	{
		T* c(new T(std::forward<TArgs>(m_args)...));
		c->entity = this;
		std::unique_ptr<Component> unique_ptr{ c };
		components_.emplace_back(std::move(unique_ptr));

		component_array_[getComponentTypeID<T>()] = c;
		component_bit_set_[getComponentTypeID<T>()] = true;

		c->init();
		return *c;
	}

	template<typename T> T& getComponent() const
	{
		auto ptr(component_array_[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}
};

class Manager
{
private:
	std::vector<std::unique_ptr<Entity>> entities_;

public:
	void update()
	{
		for (auto& e : entities_) e->udpate();
	}

	void draw()
	{
		for (auto& e : entities_) e->draw();
	}

	void refresh()
	{
		entities_.erase(std::remove_if(std::begin(entities_), std::end(entities_), [](const std::unique_ptr<Entity> &m_entity)
		{
			return !m_entity->isActive();
		}),
			std::end(entities_));
	}

	Entity& addEntity()
	{
		Entity* e = new Entity();
		std::unique_ptr<Entity> unique_ptr{ e };
		entities_.emplace_back(std::move(unique_ptr));
		return *e;
	}
};