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
#include <Renderer\FrameBuffer.h>

#include <Core\ECS\EntityManager.h>
#include <Core\ECS\Components\Transform.h>
//#include <Core\ECS\Components\Camera.h>

//Smok 3D includes
//#include <Smok3D\Components\Mesh.h>
//#include <Smok3D\Systems\MeshRenderer.h>

//Smok 2D includes
#include <Smok2D\Systems\SpriteRenderer.h>
#include <Smok2D\Components\OrthographicCamera.h>
#include <Smok2D\Components\Sprite.h>

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

static FrameBuffer* fb = nullptr;

class Editor
{
    //methods
public:

    static void Draw()
    {
        ImGui::Begin("Scene View");
        ImGui::Image((void*)Application::fb->GetColorBufferId(), ImVec2(DisplayI.GetScreenWidth(), DisplayI.GetScreenHeight()));
        //ImGui::Image((void*)AssetManager::GetTexture("Face")->GetID(), ImVec2(256.0f, 256.0f));

        ImGui::End();
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

    FrameBufferData data;
    data.width = DisplayI.GetScreenWidth();
    data.height = DisplayI.GetScreenHeight();
    FrameBuffer* sceneFrameBuffer = FrameBuffer::Create(data);
    sceneFrameBuffer->CreateColorBuffer();
    sceneFrameBuffer->CreateDepthBuffer();
    sceneFrameBuffer->Bind();
    Application::fb = sceneFrameBuffer; //fb = sceneFrameBuffer;

    //--load entities
    EntityManager::Create("Camera");
    EntityManager::AddComponet<OrthographicCamera>("Camera", (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
    EntityManager::AddComponet<Transform>("Camera", vec3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));

    //create entites with sprites
    EntityManager::Create("Face1");
    EntityManager::AddComponet<Transform>("Face1", vec3(150.0f, 170.0f, 0.0f), vec3(45.0f, 0.0f, 0.0f), vec3(2.0f, 2.0f, 1.0f));
    EntityManager::AddComponet<Sprite>("Face1", "Con", (unsigned int)0, "Shader");

    EntityManager::Create("Face2");
    EntityManager::AddComponet<Transform>("Face2", vec3(50.0f, 200.0f, 0.0f), vec3(45.0f, 0.0f, 0.0f), vec3(2.0f, 2.0f, 1.0f));
    EntityManager::AddComponet<Sprite>("Face2", "Face", (unsigned int)1, "Shader");

    EntityManager::Create("Face3");
    EntityManager::AddComponet<Transform>("Face3", vec3(550.0f, 100.0f, 0.0f), vec3(45.0f, 0.0f, 0.0f), vec3(2.0f, 2.0f, 1.0f));
    EntityManager::AddComponet<Sprite>("Face3", "Con", (unsigned int)0, "Shader");


    //--link systems and scripts

    ECSGUIRenderEvent::AddMethod(&Editor::Draw);
    //GUIRenderer::Init();
    SpriteRenderer::Init();

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