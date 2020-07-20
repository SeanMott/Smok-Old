//Smok Core includes
#include <Core\Application.h>

#include <Renderer\Display.h>
#include <Renderer\Assets\Shader.h>
#include <Renderer\Assets\Texture.h>
#include <Renderer\BufferLayout.h>
#include <Renderer\VertexBuffer.h>

#include <Core\Input.h>
#include <Core\Events\InputEvents.h>
#include <Core\Events\EngineEvents.h>

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

int main(int args, char* argv[])
{
    //--set up application
    Application::Init(SCREEN_WIDTH, SCREEN_HEIGHT);

    //DisplayI.EnableVSync(true);
    //DisplayI.LockMouse();

    //--loads textures and shaders
    Shader* shader = Shader::Create("res\\Shaders\\Vertex.shader", "res\\Shaders\\Fragment.shader");
    shader->Bind();
    Texture* container = Texture::Create("res\\Textures\\container.jpg");
    Texture* face = Texture::Create("res\\Textures\\awesomeface.png");
    
    //--create entities

    //create 2d camera
    EntityManager::Create("Camera");
    EntityManager::AddComponet<OrthographicCamera>("Camera", (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
    EntityManager::AddComponet<Transform>("Camera", vec3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));

    //create entites with sprites
    EntityManager::Create("Face1");
    EntityManager::AddComponet<Transform>("Face1", vec3(150.0f, 170.0f, 0.0f), vec3(45.0f, 0.0f, 0.0f), vec3(2.0f, 2.0f, 1.0f));
    EntityManager::AddComponet<Sprite>("Face1", container, (unsigned int)0, shader);

    EntityManager::Create("Face2");
    EntityManager::AddComponet<Transform>("Face2", vec3(50.0f, 200.0f, 0.0f), vec3(45.0f, 0.0f, 0.0f), vec3(2.0f, 2.0f, 1.0f));
    EntityManager::AddComponet<Sprite>("Face2", face, (unsigned int)1, shader);

    EntityManager::Create("Face3");
    EntityManager::AddComponet<Transform>("Face3", vec3(550.0f, 100.0f, 0.0f), vec3(45.0f, 0.0f, 0.0f), vec3(2.0f, 2.0f, 1.0f));
    EntityManager::AddComponet<Sprite>("Face3", container, (unsigned int)0, shader);

    //--link systems and scripts
    
    //link events for the GUI part of the engine
    //GUIRenderer::Init();

    //link events for the 3D part of the engine
    //MeshRenderer::Init();
    //3DPhysicsCollitions::Init();

    //link events for the 2D part of the engine
    SpriteRenderer::Init();
    //2DPhysicsCollitions::Init();
    //TileMapRenderer::Init();
    //TimeMapPhysics::Init();

    //--game loop
    Application::Run();

    //--clean up data
    
    //systems
    SpriteRenderer::Shutdown();

    //entities
    EntityManager::DestroyAllEntities();

    //assets
    face->Destroy();
    container->Destroy();
    shader->Destroy();

    Application::Destroy();

#ifndef SMOK_DIST
    std::cin.get();
#endif
    return 0;
}