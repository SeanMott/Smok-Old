//handles creating, modding, and deleting entities

#ifndef EntityManager_h
#define EntityManager_h

#include <entt\entity\registry.hpp>

#include <unordered_map>
#include <vector>
#include <string>
#include <Core\ECS\Components\Script.h>

//defines a entity
struct Entity
{
	std::string name = "Entity";
	entt::entity entity{ 0 };
	bool sceneIndependent = false; //allows the entity to exist outside of scenes
	Script scripts;

	//Constructor
	Entity(const std::string n, entt::entity& e)
	{
		name = n;
		entity = e;
	}

	//Constructor
	Entity(const char* n, entt::entity& e)
	{
		name = n;
		entity = e;
	}

	//adds a component || returns a pointer
	template<typename Comp, typename... Args>
	Comp* AddComponent(Args&&... args)
	{
		return &EntityManager::GetReg().emplace<Comp>(entity, std::forward<Args>(args)...);
	}

	//removes a component
	template<typename Comp>
	inline void RemoveComponent()
	{
		if (!EntityManager::GetReg().valid(entity))
		{
			Logger::LogError("Entity", name + " is not a valid entity.");
			return;
		}

		if (!HasComponent<Comp>())
		{
			Logger::LogErrorAlways("Entity", name + " does not have this Component add one first.");
			return;
		}

		EntityManager::GetReg().remove<Comp>(entity);
	}

	//gets a component || returns a pointer
	template<typename Comp>
	inline Comp* GetComponent()
	{
		if (!EntityManager::GetReg().valid(entity))
		{
			//Logger::LogError("Entity", name + " is not a valid entity.");
			return nullptr;
		}

		if (!HasComponent<Comp>())
		{
			Logger::LogErrorAlways("Entity", name + " does not have this Component add one first.");
			return nullptr;
		}

		return &EntityManager::GetReg().get<Comp>(EntityManager::GetEntity(name)->entity);
		//return entityRegistry.get<Comp>(entities[i].entity);
	}

	//checks if has a component
	template<typename Comp>
	inline bool HasComponent()
	{
		return EntityManager::GetReg().has<Comp>(entity);
	}

	//adds a script
	void AddScript(void* script, const std::string& name);
	//removes a Script
	void RemoveScript(const std::string& name);
	//gets a Script
	void* GetScript(const std::string& name);
	//checks if it has a Script
	bool HasScript(const std::string& name);

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
	static Entity& Create(const char* name);
	//create entity
	static Entity& Create(const std::string& name);
	//destroy entity
	static void Destroy(std::string& name);
	//gets a entity
	static Entity* GetEntity(const std::string& name);
	//destroys all entities || ignores scene independent ones
	static void DestroyAllEntities();
	//destroys all entities including scene independent ones
	static void DestroyAllEntitiesIndependent();
	//gets all the entities
	static inline std::vector<Entity>& GetAllEntities() { return entities; }

	//adds a component
	template<typename Comp, typename... Args>
	static inline void AddComponent(const char* name, Args&&... args)
	{
		entityRegistry.emplace<Comp>(GetEntity(name)->entity, std::forward<Args>(args)...);
	}

	//adds a component
	template<typename Comp, typename... Args>
	static inline void AddComponent(const std::string& name, Args&&... args)
	{
		entityRegistry.emplace<Comp>(GetEntity(name)->entity, std::forward<Args>(args)...);
	}

	//gets a component
	template<typename Comp>
	static inline Comp& GetComponent(const char* name)
	{
		for (unsigned int i = 0; i < entities.size(); i++)
		{
			if(entities[i].name == name)
				return entityRegistry.get<Comp>(entities[i].entity);
		}
	}

	//gets a component
	template<typename Comp>
	static inline Comp& GetComponent(const std::string& name)
	{
		for (unsigned int i = 0; i < entities.size(); i++)
		{
			if (entities[i].name == name)
				return entityRegistry.get<Comp>(entities[i].entity);
		}
	}

	//removes the component
	template<typename Comp>
	static inline void RemoveComponent(const char* name)
	{
		entityRegistry.remove<Comp>(GetEntity(name)->entity);
	}

	//removes the component
	template<typename Comp>
	static inline void RemoveComponent(const std::string& name)
	{
		entityRegistry.remove<Comp>(GetEntity(name)->entity);
	}

	//adds a layer
	static void AddLayer(const std::string& name);
	//removes a layer
	static void RemoveLayer(const std::string& name);

	//gets all entities by layer

	//adds a Script to the entity
	static void AddScript(const std::string& entityName, void* script, const std::string name);
	//removes a Script
	static void RemoveScript(const std::string& entityName, const std::string name);
	//gets a Script
	static void* GetScript(const std::string& entityName, const std::string name);
	//checks if a entity has a Script
	static bool HasScript(const std::string& entityName, const std::string name);

private:

	//return if a entity has the name already
	static bool IsEntity(const std::string& name);

	//returns if a layer already exists
	static bool IsLayer(const std::string& name);

};

#endif