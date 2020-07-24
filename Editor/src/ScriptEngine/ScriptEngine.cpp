#include <smpch.h>
#include "ScriptEngine.h"

#include <fstream>
#include <filesystem>

using namespace std;

string ScriptEngine::settingFilePath = "";
vector<FileData> ScriptEngine::files;
FileData ScriptEngine::fileToken;

void ScriptEngine::Init(const string& _settingFilePath)
{
	settingFilePath = _settingFilePath;
	ParseSettingFile();
}

void ScriptEngine::Shutdown()
{
}

void ScriptEngine::GenComponent(const string& name, const string& directory)
{
	ofstream writeStream(directory + '/' + name + ".h");
	if (!writeStream.is_open())
	{
		Logger::LogErrorAlways("Script Engine", "Failed to write a file at file path: " + directory + '/' + name + ".h");
		return;
	}

	writeStream << "//defines a " + name + " Component\n\n #ifndef " + name + "_h\n #define " + name + "_h\n\nstruct " + name + "\n{\n};\n#endif";
	
	fileToken = { directory + '/' + name + ".h", name, FileType::Component };
	files.emplace_back(fileToken);
}

void ScriptEngine::GenComponent(const std::string& name, const std::string& directory, const std::string description)
{
	ofstream writeStream(directory + '/' + name + ".h");
	if (!writeStream.is_open())
	{
		Logger::LogErrorAlways("Script Engine", "Failed to write a file at file path: " + directory + '/' + name + ".h");
		return;
	}

	writeStream << "//defines a " + name + " Component\n/*\n " + description + "\n*/\n #ifndef " + name + "_h\n #define " + name + "_h\n\nstruct " + name + "\n{\n};\n#endif";

	fileToken = { directory + '/' + name + ".h", name, FileType::Component };
	files.emplace_back(fileToken);
}

void ScriptEngine::GenSystem(const string& name, const string& directory)
{
	//makes header
	ofstream writeStream(directory + '/' + name + ".h");
	if (!writeStream.is_open())
	{
		Logger::LogErrorAlways("Script Engine", "Failed to write a file at file path: " + directory + '/' + name + ".h");
		return;
	}

	writeStream << "//defines the " + name + " System\n\n #ifndef " + name + "_h\n #define " + name + "_h\n\nclass " + name +
		"\n{\n\t//vars\nprivate:\n\n\t//methods\npublic:\n\n\t//Starts the " + name + " System\n\tstatic void Init();\n\t//Shutsdown the " +
		name + " System\n\tstatic void Shutdown();\n\n\t//this is your system, it will be bound and unbound in the Init method.\n\tstatic void " + name + "System();\n};\n#endif";

	fileToken = { directory + '/' + name + ".h", name, FileType::System };
	files.emplace_back(fileToken);
	writeStream.close();

	//makes source
	//check for precompiled header - add later
	writeStream.open(directory + '/' + name + ".cpp");
	if (!writeStream.is_open())
	{
		Logger::LogErrorAlways("Script Engine", "Failed to write a file at file path: " + directory + '/' + name + ".cpp");
		return;
	}

	writeStream << "#include\"" + name + ".h\"\n\n#include<Core/ECS/.h>\n#include<Core/Events/EngineEvents.h>\n\nvoid " + name + "::Init()\n{\n\t//set up data here\n\tECSSystemEvent::AddMethod(&" +
		name + "::" + name + "System);\n}\n\nvoid " + name + "::Shutdown()\n{\n\t//clean up resources here\n\t//remove System from events\n}\n\nvoid " +
		name + "::" + name + "System()\n{\n\n\tauto entities = EntityManager::GetReg().view</*Components you want ex Transform, Sprite*/>();\n\n\tfor (auto entity : entities)\n\t{\n\t\t//iterate through entities\n\t}\n}";
	writeStream.close();
}

void ScriptEngine::GenSystem(const std::string& name, const std::string& directory, const std::string description)
{
	//makes header
	ofstream writeStream(directory + '/' + name + ".h");
	if (!writeStream.is_open())
	{
		Logger::LogErrorAlways("Script Engine", "Failed to write a file at file path: " + directory + '/' + name + ".h");
		return;
	}

	writeStream << "//defines the " + name + " System\n/*\n" + description + "\n*/\n\n #ifndef " + name + "_h\n #define " + name + "_h\n\nclass " + name +
		"\n{\n\t//vars\nprivate:\n\n\t//methods\npublic:\n\n\t//Starts the " + name + " System\n\tstatic void Init();\n\t//Shutsdown the " +
		name + " System\n\tstatic void Shutdown();\n\n\t//this is your system, it will be bound and unbound in the Init method.\n\tstatic void " + name + "System();\n};\n#endif";

	fileToken = { directory + '/' + name + ".h", name, FileType::System };
	files.emplace_back(fileToken);
	writeStream.close();

	//makes source
	//check for precompiled header - add later
	writeStream.open(directory + '/' + name + ".cpp");
	if (!writeStream.is_open())
	{
		Logger::LogErrorAlways("Script Engine", "Failed to write a file at file path: " + directory + '/' + name + ".cpp");
		return;
	}

	writeStream << "#include\"" + name + ".h\"\n\n#include<Core/ECS/.h>\n#include<Core/Events/EngineEvents.h>\n\nvoid " + name + "::Init()\n{\n\t//set up data here\n\tECSSystemEvent::AddMethod(&" +
		name + "::" + name + "System);\n}\n\nvoid " + name + "::Shutdown()\n{\n\t//clean up resources here\n\t//remove System from events\n}\n\nvoid " +
		name + "::" + name + "System()\n{\n\n\tauto entities = EntityManager::GetReg().view</*Components you want ex Transform, Sprite*/>();\n\n\tfor (auto entity : entities)\n\t{\n\t\t//iterate through entities\n\t}\n}";
	writeStream.close();
}

void ScriptEngine::GenScript(const string& name, const string& directory)
{
	//makes header
	ofstream writeStream(directory + '/' + name + ".h");
	if (!writeStream.is_open())
	{
		Logger::LogErrorAlways("Script Engine", "Failed to write a file at file path: " + directory + '/' + name + ".h");
		return;
	}

	writeStream << "//defines the " + name + " Script\n #ifndef " + name + "_h\n #define " + name + "_h\n\nclass " + name +
		"\n{\n\t//vars\nprivate:\n\n\t//methods\npublic:\n\n\t//this is the start method called when the script is loaded into the scene\n"
		"\tvoid Start();\n\t//when the scene ends\n\tvoid End();\n\t//updates every frame\n\tvoid Update(float deltaTime);\n\n#endif";

	fileToken = { directory + '/' + name + ".h", name, FileType::System };
	files.emplace_back(fileToken);
	writeStream.close();

	//makes source
	//check for precompiled header - add later
	writeStream.open(directory + '/' + name + ".cpp");
	if (!writeStream.is_open())
	{
		Logger::LogErrorAlways("Script Engine", "Failed to write a file at file path: " + directory + '/' + name + ".cpp");
		return;
	}

	writeStream << "#include\"" + name + ".h\"\n\n#include<Core/ECS/.h>\n#include<Core/Events/EngineEvents.h>\n\nvoid " + name + "::Start()\n{\n\t//set up data here\n\tECSUpdateEvent::AddMethod(&this, &" +
		name + "::Update);\n}\n\nvoid " + name + "::End()\n{\n\t//clean up resources here\n\t//remove Script from events\n}\n\nvoid " + name + "::Update(float deltaTime)\n{\n\n\t//update stuff\n\n}";
	writeStream.close();
}

void ScriptEngine::GenScript(const std::string& name, const std::string& directory, const std::string description)
{
	//makes header
	ofstream writeStream(directory + '/' + name + ".h");
	if (!writeStream.is_open())
	{
		Logger::LogErrorAlways("Script Engine", "Failed to write a file at file path: " + directory + '/' + name + ".h");
		return;
	}

	writeStream << "//defines the " + name + " Script\n/*\n" + description + "\n*/\n\n #ifndef " + name + "_h\n #define " + name + "_h\n\nclass " + name +
		"\n{\n\t//vars\nprivate:\n\n\t//methods\npublic:\n\nt//this is the start method called when the script is loaded into the scene\n"
		"\tvoid Start();\n\t//when the scene ends\n\tvoid End();\n\t//updates every frame\n\tvoid Update(float deltaTime);\n\n#endif";

	fileToken = { directory + '/' + name + ".h", name, FileType::System };
	files.emplace_back(fileToken);
	writeStream.close();

	//makes source
	//check for precompiled header - add later
	writeStream.open(directory + '/' + name + ".cpp");
	if (!writeStream.is_open())
	{
		Logger::LogErrorAlways("Script Engine", "Failed to write a file at file path: " + directory + '/' + name + ".cpp");
		return;
	}

	writeStream << "#include\"" + name + ".h\"\n\n#include<Core/ECS/.h>\n#include<Core/Events/EngineEvents.h>\n\nvoid " + name + "::Start()\n{\n\t//set up data here\n\tECSUpdateEvent::AddMethod(&this, &" +
		name + "::Update);\n}\n\nvoid " + name + "::End()\n{\n\t//clean up resources here\n\t//remove Script from events\n}\n\nvoid " + name + "::Update(float deltaTime)\n{\n\n\t//update stuff\n\n}";
	writeStream.close();
}

void ScriptEngine::LinkComponent(const std::string& name, const std::string& directory)
{
	if (!filesystem::exists(directory + '/' + name + ".h"))
	{
		Logger::LogErrorAlways("Script Engine", "No file was found with the file path: " + directory + '/' + name + ".h");
		return;
	}

	fileToken = { directory + '/' + name + ".h", name, FileType::Component };
	files.emplace_back(fileToken);
}

void ScriptEngine::LinkSystem(const std::string& name, const std::string& directory)
{
	if (!filesystem::exists(directory + '/' + name + ".h"))
	{
		Logger::LogErrorAlways("Script Engine", "No file was found with the file path: " + directory + '/' + name + ".h");
		return;
	}

	fileToken = { directory + '/' + name + ".h", name, FileType::System };
	files.emplace_back(fileToken);
}

void ScriptEngine::LinkScript(const std::string& name, const std::string& directory)
{
	if (!filesystem::exists(directory + '/' + name + ".h"))
	{
		Logger::LogErrorAlways("Script Engine", "No file was found with the file path: " + directory + '/' + name + ".h");
		return;
	}

	fileToken = { directory + '/' + name + ".h", name, FileType::Script };
	files.emplace_back(fileToken);
}

void ScriptEngine::ParseSettingFile()
{
}
