//handles the application

#ifndef Application_h
#define Application_h

#include <string>

class Application
{
	//vars
private:
	static const float FIXED_UPDATE_RATE;

	//methods
public:

	//inits the application
	static void Init(const unsigned int width, const int height, const std::string& name = "Smok");
	//destroys the application
	static void Destroy();
	//runs the application
	static void Run();
};

#endif