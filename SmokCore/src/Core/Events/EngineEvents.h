//stores engine events || ECS Systems, Update, Fixed Update

#ifndef ECSEvents_h
#define ECSEvents_h

#include <vector>
#include <FastDelegate.h>

//triggers ECS systems
class ECSSystemEvent
{
	//vars
private:
	static std::vector<fastdelegate::DelegateMemento> methods;
	static fastdelegate::FastDelegate0<void> system;

	//methods
public:

	//adds a method || pass as a pointer
	template<typename ClassInstance, typename MethodName>
	static inline void AddMethod(ClassInstance classInstance, MethodName methodName)
	{
		system.bind(classInstance, methodName);
		methods.emplace_back(system.GetMemento());
	}

	//adds a method || pass as a pointer
	template<typename MethodName>
	static inline void AddMethod(MethodName methodName)
	{
		system.bind(methodName);
		methods.emplace_back(system.GetMemento());
	}

	//removes a method

	//calls all methods
	static inline void Call()
	{
		if (methods.size() > 0)
		{
			for (unsigned int i = 0; i < methods.size(); i++)
			{
				system.SetMemento(methods[i]);
				system();
			}
		}
	}
};

//triggers GUI Render methods
class ECSGUIRenderEvent
{
	//vars
private:
	static std::vector<fastdelegate::DelegateMemento> methods;
	static fastdelegate::FastDelegate0<void> system;

	//methods
public:

	//adds a method || pass as a pointer
	template<typename ClassInstance, typename MethodName>
	static inline void AddMethod(ClassInstance classInstance, MethodName methodName)
	{
		//system.bind(methodName);
		system.bind(classInstance, methodName);
		methods.emplace_back(system.GetMemento());
	}

	//adds a method || pass as a pointer
	template<typename MethodName>
	static inline void AddMethod(MethodName methodName)
	{
		system.bind(methodName);
		methods.emplace_back(system.GetMemento());
	}

	//removes a method

	//calls all methods
	static inline void Call()
	{
		if (methods.size() > 0)
		{
			for (unsigned int i = 0; i < methods.size(); i++)
			{
				system.SetMemento(methods[i]);
				system();
			}
		}
	}
};

//triggers Update
class UpdateEvent
{
	//vars
private:
	static std::vector<fastdelegate::DelegateMemento> methods;
	static fastdelegate::FastDelegate1<float> update;

	//methods
public:

	//adds a method || pass as a pointer
	template<typename ClassInstance, typename MethodName>
	static inline void AddMethod(ClassInstance classInstance, MethodName methodName)
	{
		update.bind(classInstance, methodName);
		methods.emplace_back(update.GetMemento());
	}

	//adds a method || pass as a pointer
	template<typename MethodName>
	static inline void AddMethod(MethodName methodName)
	{
		update.bind(methodName);
		methods.emplace_back(update.GetMemento());
	}

	//removes a method

	//calls all methods
	static inline void Call(float deltaTime)
	{
		if (methods.size() > 0)
		{
			for (unsigned int i = 0; i < methods.size(); i++)
			{
				update.SetMemento(methods[i]);
				update(deltaTime);
			}
		}
	}
};

//triggers Fixed Update
class FixedUpdateEvent
{
	//vars
private:
	static std::vector<fastdelegate::DelegateMemento> methods;
	static fastdelegate::FastDelegate1<float> fixedUpdate;

	//methods
public:

	//adds a method || pass as a pointer
	template<typename ClassInstance, typename MethodName>
	static inline void AddMethod(ClassInstance classInstance, MethodName methodName)
	{
		fixedUpdate.bind(classInstance, methodName);
		methods.emplace_back(fixedUpdate.GetMemento());
	}

	//adds a method || pass as a pointer
	template<typename MethodName>
	static inline void AddMethod(MethodName methodName)
	{
		fixedUpdate.bind(methodName);
		methods.emplace_back(fixedUpdate.GetMemento());
	}

	//removes a method

	//calls all methods
	static inline void Call(float fixedDeltaTime)
	{
		if (methods.size() > 0)
		{
			for (unsigned int i = 0; i < methods.size(); i++)
			{
				fixedUpdate.SetMemento(methods[i]);
				fixedUpdate(fixedDeltaTime);
			}
		}
	}
};

#endif