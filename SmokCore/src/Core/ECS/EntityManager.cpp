#include <smpch.h>
#include "EntityManager.h"

using namespace std; using namespace entt;

vector<Entity> EntityManager::entities;
registry EntityManager::entityRegistry;
vector<string> EntityManager::layers;

//create entity
Entity* EntityManager::Create(const char* name)
{
	if (IsEntity(name))
	{
		printf("%s is already a name of a entity\n", name);
		//entity e;
		return nullptr;
	}

	entity e = entityRegistry.create();
	entities.emplace_back(name, e);
	return &entities[entities.size() - 1];
}

//destroy entity
void EntityManager::Destroy(std::string& name)
{
	for (unsigned int i = 0; i < entities.size(); i++)
	{
		if (entities[i].name == name)
		{
			entityRegistry.destroy(entities[i].entity);
			vector<Entity>::iterator it = entities.begin() + i;
			entities.erase(it);
			return;
		}
	}

	printf("%s is not a entity\n", name.c_str());
}

//gets a entity
Entity* EntityManager::GetEntity(const string& name)
{
	for (unsigned int i = 0; i < entities.size(); i++)
	{
		if (entities[i].name == name)
			return &entities[i];
	}

	printf("%s is not a entity\n", name.c_str());
	return nullptr;
}

//return if a entity has the name already
bool EntityManager::IsEntity(const string& name)
{
	for (unsigned int i = 0; i < entities.size(); i++)
	{
		if (entities[i].name == name)
			return true;
	}

	//printf("%s is not a entity\n", name.c_str());
	return false;
}

//destroys all entities
void EntityManager::DestroyAllEntities()
{
	entities.clear();
	entityRegistry.clear();
}

//adds a layer
void EntityManager::AddLayer(const string& name)
{
	if (IsLayer(name))
	{
		printf("%s is already a layer name.\n", name.c_str());
		return;
	}

	layers.emplace_back(name);
}

//removes a layer
void EntityManager::RemoveLayer(const string& name)
{
	if (!IsLayer(name))
	{
		printf("%s is not a layer name.\n", name.c_str());
		return;
	}

	for (unsigned int i = 0; i < layers.size(); i++)
	{
		if (layers[i] == name)
		{
			vector<string>::iterator it = layers.begin() + i;
			layers.erase(it);
		}
	}
}

//returns if a layer already exists
bool EntityManager::IsLayer(const string& name)
{
	for (unsigned int i = 0; i < layers.size(); i++)
	{
		if (layers[i] == name)
			return true;
	}

	return false;
}