//defines the Script component
//the Script component is used to allow scripts to trigger Start, Update, FixedUpdate, Enable, Disable, End methods
//they are similar to Unity or Unreal engine scripts

//Example Script
/*
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

#include <string>

struct Script
{
	std::string scriptPath;
	std::string className;
	bool isActive = true;
};