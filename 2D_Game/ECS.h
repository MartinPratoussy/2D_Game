#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;
class Manager;

using ComponentID = std::size_t;
using Group = std::size_t;

inline ComponentID getNewComponentTypeID()
{
	static ComponentID last_id = 0u;
	return last_id++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
	static_assert (std::is_base_of<Component, T>::value, "");
	static ComponentID type_id = getNewComponentTypeID();
	return type_id;
}

constexpr  std::size_t max_components = 32;
constexpr std::size_t max_groups = 32;

using ComponentBitSet = std::bitset<max_components>;
using GroupBitSet = std::bitset<max_groups>;
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
	Manager& manager_;
	bool active = true;
	std::vector<std::unique_ptr<Component>> components_;

	ComponentArray component_array_;
	ComponentBitSet component_bit_set_;
	GroupBitSet group_bit_set;

public:
	Entity(Manager& mManager) : manager_(mManager) {}

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

	bool hasGroup(Group mGroup)
	{
		return group_bit_set[mGroup];
	}

	void addGroup(Group m_group);
	void deleteGroup(Group m_group)
	{
		group_bit_set[m_group] = false;
	}

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
	std::array<std::vector<Entity*>, max_groups> grouped_Entities_;

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
		for (auto i(0u); i < max_groups; i++)
		{
			auto& v(grouped_Entities_[i]);
			v.erase(
				std::remove_if(std::begin(v), std::end(v), [i](Entity* m_entity)
					{
						return !m_entity->isActive() || !m_entity->hasGroup(i);
					}),
				std::end(v));
		}

		entities_.erase(
			std::remove_if(std::begin(entities_), std::end(entities_), [](const std::unique_ptr<Entity>& m_entity)
				{
					return !m_entity->isActive();
				}),
			std::end(entities_));
	}

	void AddToGroup(Entity* m_entity, Group m_group)
	{
		grouped_Entities_[m_group].emplace_back(m_entity);
	}

	std::vector<Entity*>& GetGroup(Group m_group)
	{
		return grouped_Entities_[m_group];
	}

	Entity& addEntity()
	{
		Entity* e = new Entity(*this);
		std::unique_ptr<Entity> unique_ptr{ e };
		entities_.emplace_back(std::move(unique_ptr));
		return *e;
	}
};