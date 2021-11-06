#include "ECS.h"

void Entity::addGroup(Group m_group)
{
	group_bit_set[m_group] = true;
	manager_.AddToGroup(this, m_group);
}
