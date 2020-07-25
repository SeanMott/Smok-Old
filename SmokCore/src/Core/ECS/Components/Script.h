//defines a Script || allows Unity and Unreal like scripts to be used along with Systems and Components

#ifndef Script_h
#define Script_h

#include <string>

struct Script
{
	void* script = nullptr; //pointer to the class instance
	std::string filePath, name; //place where the script header is stored, name of the script can be custome
	bool isActive = true;

	/*Deconstructor
	~Script()
	{
		if (script)
			delete script;

		filePath = ""; name = "";
	}*/
};

#endif