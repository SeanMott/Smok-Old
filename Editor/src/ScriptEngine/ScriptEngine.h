//the Script Engine allows the developer to write Componets, Scripts, and Systems
//All three can be used together to make a application

//Example System
/*

The Init, Shutdown, and System need to be void and take zero paramaters also make them static.
This is the formate for the events the names can be changed, but the Script Engine looks for Init and Shutdown automaticly.
You can force it to use other names by going into the Script Engine settinsg window. 
It is located under the Script Engine tab

----header

//pregened
#include <Core/Events/EngineEvents.h>

//include what every you like

class System
{
	//vars
	private:

		//place vars here, can be used when running the system

	//methods
	public:

	//inits the System, used commonly for linking it to the System event
	static void Init();
	//shuts down the System for when the app is done or if you wish to turn it on or off at run time
	static void Shutdown();

	//the actul method for acting on Componets name it what ever you want Init will link it
	static void SystemName();

};

--C/C++ file

//inits the System, used commonly for linking it to the System event
void System::Init()
{
	//other stuff here

	ECSSystemEvent::AddMethod(&System::SystemName); //the version for static methods are used, since a System never has a instance created
}

//shuts down the System for when the app is done or if you wish to turn it on or off at run time
void System::Shutdown()
{
	//remove the System from the event
	//clean up resources used
}

//the actul method for acting on Componets name it what ever you want Init will link it
void System::SystemName()
{
	//gets the entities with what ever Compoents you want, pass there class name so Transform and Sprite
	auto entities = EntityManager::GetReg().view<Comp1, Comp2>();

	for (auto entity : entities)
	{
		auto& compData1 = entities.get<Comp1>(entity);
		if (!compData.isActive)
			continue;

		auto& compData2 = entities.get<Comp2>(entity);

		float data = MathStuff(compData2.someVar, 2);

	}
}

*/

//Example Component
/*

Componets are ment to be have data but can have methods.
It is recommended that this methods are utility and not functionalty.
Functionality is ment for Systems to act upon the data inside the Componets.
They can be classes but structs are used since they are ment to be data containers.
They are also made pure headers, if you need untility methods use inline, and static if its not using its own data.

--header

#include <glm.hpp>

struct Transform
{
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);

	//returns the front of the entitie's Transform
	inline glm::vec3 Front() { return position + WorldForward(); } // glm::vec3(position.x, position.y, position.z - 1.0f); }
	//returns the back of the entitie's Transform
	inline glm::vec3 Back() { return position + WorldBackwards(); } //glm::vec3(position.x, position.y, position.z + 1.0f); }
	//returns the left of the entitie's Transform
	inline glm::vec3 Left() { return position + WorldLeft(); } //glm::vec3(position.x - 1.0f, position.y, position.z); }
	//returns the right of the entitie's Transform
	inline glm::vec3 Right() { return position + WorldRight(); }//glm::vec3(position.x + 1.0f, position.y, position.z); }
	//returns the top of the entitie's Transform
	inline glm::vec3 Top() { return position + WorldUp(); }//glm::vec3(position.x, position.y + 1.0f, position.z); }
	//returns the bottom of the entitie's Transform
	inline glm::vec3 Bottom() { return position + WorldDown(); } //glm::vec3(position.x, position.y - 1.0f, position.z); }

	//returns a vec3 pointing up (0.0f, 1.0f, 0.0f)
	static inline glm::vec3 WorldUp() { return glm::vec3(0.0f, 1.0f, 0.0f); }
	//returns a vec3 pointing down (0.0f, -1.0f, 0.0f)
	static inline glm::vec3 WorldDown() { return glm::vec3(0.0f, 1.0f, 0.0f); }
	//returns a vec3 pointing left (-1.0f, 0.0f, 0.0f)
	static inline glm::vec3 WorldLeft() { return glm::vec3(-1.0f, 0.0f, 0.0f); }
	//returns a vec3 pointing right (1.0f, 0.0f, 0.0f)
	static inline glm::vec3 WorldRight() { return glm::vec3(1.0f, 0.0f, 0.0f); }
	//returns a vec3 pointing forward (0.0f, 0.0f, -1.0f)
	static inline glm::vec3 WorldForward() { return glm::vec3(0.0f, 0.0f, -1.0f); }
	//returns a vec3 pointing backwards (0.0f, 0.0f, 1.0f)
	static inline glm::vec3 WorldBackwards() { return glm::vec3(0.0f, 0.0f, 1.0f); }
};

*/

//Example Script
/*

Scripts allow for actions to be taken during differnt events by naming methods.
Theses are not overrides they merly follow a method formate that is linked to the event system.
The method names can be changed but the Script Engine automaticly searchs for theses. They paramater names can be chnaged without issue though.
They can be changed by going into the Script Engine tab and changing settings for that Script.

-Also unlike Systems Scripts can use there Constructor and Deconstructor since they are instanced. Inheretence also works.

Event:
void Start() || when the script is loaded into the scene
void End() || when the scene is unloaded and the Script still exists, will call the Script's Deconstructor
void Destroy() || calls when the Script is destroyed, also calls the Deconstructor
void Enable() || when the script is enabled
void Disable() || when the script is disabled
void Update(float timeDelta) || when a update event is triggered
void FixedUpdate(float fixedTimeDelta) || when a fixed update event is trigger gives what ever the fixed delta time is set to


#include <Core/Input.h>
#include <Core/ECS/Components/Transform.h>

//pre gened includes
#include <Core/ECS/EntityManager.h>
#include <Core/Logger.h>

class Example
{

private:

	float moveSpeed = 50.0f
	Transform* camTrans;

public:

	//when the scene loads
	void Start()
	{
		camTrans = &EntityManager::GetComponent<Transform>("Camera");
	}

	//when update is called
	void Update(float deltaTime)
	{
		if (!camTrans)
			return;

		//move up
		if (Input::GetKey(SMOK_KEY_W))
			camTrans->position.y += moveSpeed * deltaTime;

		//move down
		else if (Input::GetKey(SMOK_KEY_S))
			camTrans->position.y -= moveSpeed * deltaTime;

		//move left
		else if (Input::GetKey(SMOK_KEY_A))
			camTrans->position.x += moveSpeed * deltaTime;

		//move right
		else if (Input::GetKey(SMOK_KEY_D))
			camTrans->position.x -= moveSpeed * deltaTime;
	}

	//when the scene ends with this instace of the script
	void End()
	{
		//not needed in this script
	}

};

*/

//defines the Script Engine System

#include <string>
#include <vector>

enum class FileType
{
	Script,
	Component,
	System
};

//stores data about a file
struct FileData
{
	std::string filePath, name;
	//add later the ability to change the method names
	FileType type;
};

class ScriptEngine
{
	//vars
private:

	static std::string settingFilePath;
	static std::vector<FileData> files;

	static FileData fileToken; //used to write data to the files vector

	//methods
public:

	//gets the files
	//static inline std::vector<FileData> GetFiles() { return files; }

	//inits the Script System
	static void Init(const std::string& _settingFilePath = "");
	//shutsdown the Script Engine
	static void Shutdown();

	//makes a Component
	static void GenComponent(const std::string& name, const std::string& directory);
	//makes a Component
	static void GenComponent(const std::string& name, const std::string& directory, const std::string description);
	//makes a System
	static void GenSystem(const std::string& name, const std::string& directory);
	//makes a System
	static void GenSystem(const std::string& name, const std::string& directory, const std::string description);
	//makes a Script
	static void GenScript(const std::string& name, const std::string& directory);
	//makes a Script
	static void GenScript(const std::string& name, const std::string& directory, const std::string description);

	//loads Dll data

	//links a Component
	static void LinkComponent(const std::string& name, const std::string& directory);
	//links a System
	static void LinkSystem(const std::string& name, const std::string& directory);
	//links a Script
	static void LinkScript(const std::string& name, const std::string& directory);

	//parses the settings file
	static void ParseSettingFile();
	//sets the setting file
	static inline void SetSettingFile(const std::string& path) { settingFilePath = path; }
};