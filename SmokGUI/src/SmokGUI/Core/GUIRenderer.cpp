#include "GUIRenderer.h"

#include <imgui.h>
#include <SmokGUI\Core\ImGUIContext.h>

#include <Renderer\Display.h>

#include <Core\Keycodes.h>
#include <Core\Events\InputEvents.h>
#include <Core\Events\EngineEvents.h>
#include <Core\Events\WindowEvents.h>

ImGUIContext* GUIRenderer::context = nullptr;

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

	ImGuiIO& io = ImGui::GetIO();
	io.BackendFlags != ImGuiBackendFlags_HasMouseCursors;
	io.BackendFlags != ImGuiBackendFlags_HasSetMousePos;

    //temporary
    io.KeyMap[ImGuiKey_Tab] = SMOK_KEY_TAB;
    io.KeyMap[ImGuiKey_LeftArrow] = SMOK_KEY_LEFT;
    io.KeyMap[ImGuiKey_RightArrow] = SMOK_KEY_RIGHT;
    io.KeyMap[ImGuiKey_UpArrow] = SMOK_KEY_UP;
    io.KeyMap[ImGuiKey_DownArrow] = SMOK_KEY_DOWN;
    io.KeyMap[ImGuiKey_PageUp] = SMOK_KEY_PAGE_UP;
    io.KeyMap[ImGuiKey_PageDown] = SMOK_KEY_PAGE_DOWN;
    io.KeyMap[ImGuiKey_Home] = SMOK_KEY_HOME;
    io.KeyMap[ImGuiKey_End] = SMOK_KEY_END;
    io.KeyMap[ImGuiKey_Insert] = SMOK_KEY_INSERT;
    io.KeyMap[ImGuiKey_Delete] = SMOK_KEY_DELETE;
    io.KeyMap[ImGuiKey_Backspace] = SMOK_KEY_BACKSPACE;
    io.KeyMap[ImGuiKey_Space] = SMOK_KEY_SPACE;
    io.KeyMap[ImGuiKey_Enter] = SMOK_KEY_ENTER;
    io.KeyMap[ImGuiKey_Escape] = SMOK_KEY_ESCAPE;
    io.KeyMap[ImGuiKey_A] = SMOK_KEY_A;
    io.KeyMap[ImGuiKey_C] = SMOK_KEY_C;
    io.KeyMap[ImGuiKey_V] = SMOK_KEY_V;
    io.KeyMap[ImGuiKey_X] = SMOK_KEY_X;
    io.KeyMap[ImGuiKey_Y] = SMOK_KEY_Y;
    io.KeyMap[ImGuiKey_Z] = SMOK_KEY_Z;

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
    context->Destroy();
}

//starts a section of render code
void GUIRenderer::Begin()
{
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2((float)DisplayI.GetScreenWidth(), (float)DisplayI.GetScreenHeight());
    io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);

    context->NewFrame();
}

//ends a section of render code
void GUIRenderer::End()
{
    context->Render();
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