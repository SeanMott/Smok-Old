#include "OpenglImGUIContext.h"

#include <imgui.h>
#include <Renderer\RenderAPI\Opengl\OpenglImGui.h>

void OpenglImGUIContext::Init()
{
	ImGui_ImplOpenGL3_Init("#version 410");
}

void OpenglImGUIContext::Destroy()
{
}

void OpenglImGUIContext::NewFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui::NewFrame();
}

void OpenglImGUIContext::Render()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
