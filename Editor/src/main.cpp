//Smok Core includes
#include <Core\Application.h>

#include <Renderer\Display.h>
//#include <Renderer\Assets\Shader.h>
//#include <Renderer\Assets\Texture.h>
//#include <Renderer\BufferLayout.h>
//#include <Renderer\VertexBuffer.h>

//#include <Core\Input.h>
#include <Core\Logger.h>
//#include <Core\Events\InputEvents.h>
#include <Core\Events\EngineEvents.h>
#include <Core\AssetManager.h>

#include <Core\ECS\EntityManager.h>
//#include <Core\ECS\Components\Transform.h>
//#include <Core\ECS\Components\Camera.h>

//Smok 3D includes
//#include <Smok3D\Components\Mesh.h>
//#include <Smok3D\Systems\MeshRenderer.h>

/*Smok 2D includes
#include <Smok2D\Systems\SpriteRenderer.h>
#include <Smok2D\Components\OrthographicCamera.h>
#include <Smok2D\Components\Sprite.h>*/

//Smok GUI includes
#include <SmokGUI\Core\GUIRenderer.h>
#include <imgui.h>

//other
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <stb_image.h>

#include <glm.hpp>
//#include <gtc/matrix_transform.hpp>
//#include <gtc/type_ptr.hpp>

//#include <stdio.h>

#ifndef SMOK_DIST
#include <iostream>
#endif

using namespace std; using namespace glm;

// settings
const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

class Editor
{
    //methods
public:

    static void Draw()
    {

        //GUIRenderer::Begin();

        ImGui::Begin("Test 1");
        ImGui::Text("Hello Dockspace");  //GUIRenderer::DockSpace(&show);
        ImGui::End();

        ImGui::Begin("Test 2");
        ImGui::Text("Other text");  //GUIRenderer::DockSpace(&show);
        ImGui::Image((void*)AssetManager::GetTexture("Con")->GetID(), ImVec2(256.0f, 256.0f));
        ImGui::End();

        //GUIRenderer::End();
    }

    static void DrawTwo()
    {

        //GUIRenderer::Begin();

        ImGui::Begin("Test 3");
        ImGui::Text("Kill");  //GUIRenderer::DockSpace(&show);
        ImGui::End();

        ImGui::Begin("Test 4");
        ImGui::Text("Happy little face");  //GUIRenderer::DockSpace(&show);
        ImGui::Image((void*)AssetManager::GetTexture("Face")->GetID(), ImVec2(256.0f, 256.0f));
        ImGui::End();

        //GUIRenderer::End();
    }
};

int main(int args, char* argv[])
{
    //--set up application
    Application::Init(SCREEN_WIDTH, SCREEN_HEIGHT);
    
    //link GUI Render to system and setup dock space
    GUIRenderer::SetFlag(GUIFlags::Docking, true);
    GUIRenderer::SetFlag(GUIFlags::ViewPort, true);
    GUIRenderer::Init();

    //--load assets
    AssetManager::LoadShader("Shader", "res\\Shaders\\Vertex.shader", "res\\Shaders\\Fragment.shader");
    AssetManager::LoadTexture("Face", "res\\Textures\\awesomeface.png");
    AssetManager::LoadTexture("Con", "res\\Textures\\container.jpg");
    AssetManager::LoadTexture("S", "C:\\Users\\skyst\\Desktop\\Sprite Editor Unity.png");

    //--load entities

    //--link systems and scripts

    ECSGUIRenderEvent::AddMethod(&Editor::Draw);
    ECSGUIRenderEvent::AddMethod(&Editor::DrawTwo);

    //--game loop
    Application::Run();

    //--clean up data
    
    //systems
    GUIRenderer::Destroy();

    //entities
    EntityManager::DestroyAllEntities();

    //assets
    AssetManager::DestroyAllAssets();

    Application::Destroy();

#ifndef SMOK_DIST
    std::cin.get();
#endif
    return 0;
}