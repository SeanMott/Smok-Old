//handles creating, modding, and deleting entities

#ifndef EntityManager_h
#define EntityManager_h

#include <entt\entity\registry.hpp>

#include <unordered_map>
#include <vector>
#include <string>

//defines a entity
struct Entity
{
	std::string name = "Entity";
	entt::entity entity;
	//std::string layer = "Base";

	Entity(const std::string n, entt::entity& e)
	{
		name = n;
		entity = e;
	}

	Entity(const char* n, entt::entity& e)
	{
		name = n;
		entity = e;
	}
};

class EntityManager
{
	//vars
private:

	static std::vector<Entity> entities;
	static entt::registry entityRegistry;
	static std::vector<std::string> layers; //stores the layers in order from 0

	//methods
public:

	static inline entt::registry& GetReg() { return entityRegistry; }
	static inline std::vector<std::string>& GetLayers() { return layers; }

	//create entity
	static Entity* Create(const char* name);
	//create entity
	static Entity* Create(const std::string& name);
	//destroy entity
	static void Destroy(std::string& name);
	//gets a entity
	static Entity* GetEntity(const std::string& name);
	//destroys all entities
	static void DestroyAllEntities();
	//gets all the entities
	static inline std::vector<Entity>& GetAllEntities() { return entities; }

	//adds a component
	template<typename Comp, typename... Args>
	static inline void AddComponet(char* name, Args&&... args)
	{
		entityRegistry.emplace<Comp>(GetEntity(name)->entity, std::forward<Args>(args)...);//std::forward<Args>(args)...);
	}
	//gets a component
	template<typename Comp>
	static inline Comp& GetComponent(char* name)
	{
		for (unsigned int i = 0; i < entities.size(); i++)
		{
			if(entities[i].name == name)
				return entityRegistry.get<Comp>(entities[i].entity);
		}

		
	}
	//removes the component
	template<typename Comp>
	static inline void RemoveComponet(char* name)
	{
		entityRegistry.remove<Comp>(GetEntity(name)->entity);
	}

	//adds a layer
	static void AddLayer(const std::string& name);
	//removes a layer
	static void RemoveLayer(const std::string& name);

	//gets all entities by layer

private:

	//return if a entity has the name already
	static bool IsEntity(const std::string& name);

	//returns if a layer already exists
	static bool IsLayer(const std::string& name);
};

#endif