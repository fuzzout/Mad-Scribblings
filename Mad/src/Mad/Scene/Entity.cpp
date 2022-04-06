#include "madpch.h"
#include "Entity.h"
namespace Mad {

	Entity::Entity(entt::entity handle, Scene* scene) 
		: m_EntityHandle(handle), m_Scene(scene)
	{
	}

}