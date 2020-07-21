#include "GUIRenderer.h"

#include <imgui.h>
#include <SmokGUI\Core\ImGUIContext.h>

#include <Renderer\Display.h>

#include <Core\Keycodes.h>
#include <Core\Events\InputEvents.h>
#include <Core\Events\EngineEvents.h>
#include <Core\Events\WindowEvents.h>

#include <SmokGUI\ImGUIBuild.h>

ImGUIContext* GUIRenderer::context = nullptr;
bool GUIRenderer::flags[(int)GUIFlags::GUIFlagsCount]; //the flags for GUI

//inits the renderer
void GUIRenderer::Init(GUIStyle style)
{
#ifdef DISABLE_SMOK_GUI
    return;
#endif

    ImGui::CreateContext();

    if (style == GUIStyle::Dark)
        ImGui::StyleColorsDark();
    else if (style == GUIStyle::Light)
        ImGui::StyleColorsLight();
    else
        ImGui::StyleColorsClassic();

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    UpdateImGUIFlags();

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        ImGuiStyle& style = ImGui::GetStyle();
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    context = ImGUIContext::Create();
    context->Init();

    //set events
    KeyPressEvent::AddMethod(&GUIRenderer::KeyPressed);
    KeyTypedEvent::AddMethod(&GUIRenderer::KeyTyped);
    KeyReleasedEvent::AddMethod(&GUIRenderer::KeyReleased);
    MousePressEvent::AddMethod(&GUIRenderer::MousePressed);
    MouseReleasedEvent::AddMethod(&GUIRenderer::MouseReleased);
    MouseMoveEvent::AddMethod(&GUIRenderer::MouseMove);
    MouseScrollEvent::AddMethod(&GUIRenderer::MouseScroll);
    //WindowResizeEvent::AddMethod(&GUIRenderer::OnResize);
    UpdateEvent::AddMethod(&GUIRenderer::UpdateDeltaTime);
}

//destroys the renderer
void GUIRenderer::Destroy()
{
#ifdef DISABLE_SMOK_GUI
    return;
#endif

    context->Destroy();
}

//updates the GUI flags for ImGUI
void GUIRenderer::UpdateImGUIFlags()
{
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    if (GetFlagState(GUIFlags::Keyboard))
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; //enable keyboard
    if (GetFlagState(GUIFlags::GamePad))
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; //enable game pad
    if (GetFlagState(GUIFlags::Docking))
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; //enable docking
    if (GetFlagState(GUIFlags::ViewPort))
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; //enable multi viewport / windows
    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons; //disable task bar icons
    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge; //disable viewport merging
}

//starts a section of render code
void GUIRenderer::Begin()
{
#ifdef DISABLE_SMOK_GUI
    return;
#endif

    context->NewFrame();
}

//ends a section of render code
void GUIRenderer::End()
{
#ifdef DISABLE_SMOK_GUI
    return;
#endif

    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2((float)DisplayI.GetScreenWidth(), (float)DisplayI.GetScreenHeight());
    io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);

    context->Render();

    //renders seprate window instances
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        ImGUIPlatformContextType platformContext = ImGUIPlatformGetContext;
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        ImGUIPlatformMakeContext(platformContext);
    }
}

//events
void GUIRenderer::KeyPressed(int key, bool isRepeat)
{
    ImGuiIO& io = ImGui::GetIO();
    io.KeysDown[key] = true;

    io.KeyCtrl = io.KeysDown[SMOK_KEY_LEFT_CONTROL] || io.KeysDown[SMOK_KEY_RIGHT_CONTROL];
    io.KeyShift = io.KeysDown[SMOK_KEY_LEFT_SHIFT] || io.KeysDown[SMOK_KEY_RIGHT_SHIFT];
    io.KeyAlt = io.KeysDown[SMOK_KEY_LEFT_ALT] || io.KeysDown[SMOK_KEY_RIGHT_ALT];
    io.KeySuper = io.KeysDown[SMOK_KEY_LEFT_SUPER] || io.KeysDown[SMOK_KEY_RIGHT_SUPER];
}

void GUIRenderer::KeyReleased(int key)
{
    ImGuiIO& io = ImGui::GetIO();
    io.KeysDown[key] = false;
}

void GUIRenderer::KeyTyped(int key)
{
    ImGuiIO& io = ImGui::GetIO();
    if (key > 0 && key < 0x10000)
        io.AddInputCharacter((unsigned short)key);
}

bool GUIRenderer::MousePressed(int button)
{
    ImGuiIO& io = ImGui::GetIO();
    io.MouseDown[button] = true;

    return false;
}

bool GUIRenderer::MouseReleased(int button)
{
    ImGuiIO& io = ImGui::GetIO();
    io.MouseDown[button] = false;

    return false;
}

void GUIRenderer::MouseMove(double xPos, double yPos)
{
    ImGuiIO& io = ImGui::GetIO();
    io.MousePos = ImVec2(xPos, yPos);
}

void GUIRenderer::MouseScroll(double xOffset, double yOffset)
{
    ImGuiIO& io = ImGui::GetIO();
    io.MouseWheelH += xOffset;
    io.MouseWheel += yOffset;
}

void GUIRenderer::OnResize(unsigned int width, unsigned int height)
{
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2(width, height);
    io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
}

void GUIRenderer::UpdateDeltaTime(float deltaTime)
{
    ImGuiIO& io = ImGui::GetIO();
    if (deltaTime < 0.5f)
        io.DeltaTime = 30.0f;
    else
        io.DeltaTime = deltaTime;
}