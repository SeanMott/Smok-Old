//allows GUI to be renderer over a scene

#ifndef GUIRenderer_h
#define GUIRenderer_h

#include <SmokGUI\Core\ImGUIContext.h>

enum class GUIStyle
{
	Dark,
	Light,
	Classic
};

class GUIRenderer
{
	//vars
private:

	static ImGUIContext* context;

	//methods
public:

	//inits the renderer
	static void Init(GUIStyle style = GUIStyle::Dark);
	//destroys the renderer
	static void Destroy();

	//starts a section of render code
	static void Begin();
	//ends a section of render code
	static void End();

	//returns the context
	static inline ImGUIContext* GetContext() { return context; }

private:

	//events
	static void KeyPressed(int key, bool isRepeat);
	static void KeyReleased(int key);
	static void KeyTyped(int key);
	static bool MousePressed(int button);
	static bool MouseReleased(int button);
	static void MouseMove(double xPos, double yPos);
	static void MouseScroll(double xOffset, double yOffset);
	static void OnResize(unsigned int width, unsigned int height);
	static void UpdateDeltaTime(float deltaTime);

};

#endif