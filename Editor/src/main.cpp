//Smok Core includes
#include <Core\Application.h>

#include <Renderer\Display.h>
//#include <Renderer\Assets\Shader.h>
//#include <Renderer\Assets\Texture.h>
//#include <Renderer\BufferLayout.h>
//#include <Renderer\VertexBuffer.h>

#include <Core\Input.h>
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
const unsigned int SCREEN_WIDTH = 1000;
const unsigned int SCREEN_HEIGHT = 1000;

//editor app code
class Editor
{
	//vars
private:

	vec2 viewportSize;

	static unsigned long entityCount;

	//methods
public:

	void Draw()
	{
		entityCount = EntityManager::GetAllEntities().size();

		//top menu
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				//opens a scene
				if (ImGui::MenuItem("Open Scene")) Logger::LogMessageAlways("Opening a scene through the editor is currently not supported, check GitHub for updates.");

				//saves a scene
				if (ImGui::MenuItem("Save Scene")) Logger::LogMessageAlways("Saving a scene through the editor is currently not supported, check GitHub for updates.");

				//saves a project
				if (ImGui::MenuItem("Save Project")) Logger::LogMessageAlways("Saving a project through the editor is currently not supported, check GitHub for updates.");

				//opens a project
				if (ImGui::MenuItem("Open Project")) Logger::LogMessageAlways("Opening a project through the editor is currently not supported, check GitHub for updates.");

				//shows build settings
				if (ImGui::MenuItem("Build Settings")) Logger::LogMessageAlways("Showing build settings through the editor is currently not supported, check GitHub for updates.");

				//builds the game
				if (ImGui::MenuItem("Build")) Logger::LogMessageAlways("Building through the editor is currently not supported, check GitHub for updates.");

				//exits the app
				if (ImGui::MenuItem("Exit")) DisplayI.Shutdown();

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Edit"))
			{
				//makes a entity
				if (ImGui::MenuItem("New Entity")) EntityManager::Create("Entity" + to_string(entityCount)); //Logger::LogMessageAlways("Making a Entity through the editor is currently not supported, check GitHub for updates.");

				//makes a script
				if (ImGui::MenuItem("New Script")) Logger::LogMessageAlways("Making a Script through the editor is currently not supported, check GitHub for updates.");

				//makes a system
				if (ImGui::MenuItem("New System")) Logger::LogMessageAlways("Making a System through the editor is currently not supported, check GitHub for updates.");

				//makes a component
				if (ImGui::MenuItem("New Component")) Logger::LogMessageAlways("Making a Component through the editor is currently not supported, check GitHub for updates.");

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Script Engine"))
			{
				//forces the script engine to find all scripts, componets, and systems
				if (ImGui::MenuItem("Relink")) Logger::LogMessageAlways("Forcing the Scirpt Engine to relink Scripts, Components, and Systems through the editor is currently not supported, check GitHub for updates.");

				//shows all loaded systems
				if (ImGui::MenuItem("Systems")) Logger::LogMessageAlways("Showing a window of all enabled and disabled systems through the editor is currently not supported, check GitHub for updates.");

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Windows"))
			{
				//makes a inspecter
				if (ImGui::MenuItem("Inspecter")) Logger::LogMessageAlways("Making a Inspecter window through the editor is currently not supported, check GitHub for updates.");

				//makes a entity hierarchy
				if (ImGui::MenuItem("Entity Hierarchy")) Logger::LogMessageAlways("Making a Entity Hierarchy window through the editor is currently not supported, check GitHub for updates.");

				//makes a scene view
				if (ImGui::MenuItem("Scene View")) Logger::LogMessageAlways("Making a Scene View window through the editor is currently not supported, check GitHub for updates.");

				//makes a asset hot bar
				if (ImGui::MenuItem("Asset Bar")) Logger::LogMessageAlways("Making a Asset Bar window through the editor is currently not supported, check GitHub for updates.");

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Help"))
			{
				//brings up the docs
				if (ImGui::MenuItem("Docs")) Logger::LogMessageAlways("Opening docs through the editor is currently not supported, check GitHub for updates.");

				//opens the Github
				if (ImGui::MenuItem("Github")) Logger::LogMessageAlways("Opening Github through the editor is currently not supported, check GitHub for updates.");

				//credits
				if (ImGui::MenuItem("Credits")) Logger::LogMessageAlways("Opening credits through the editor is currently not supported, check GitHub for updates.");

				//libraries
				if (ImGui::MenuItem("Libraries")) Logger::LogMessageAlways("Opening the library list through the editor is currently not supported, check GitHub for updates.");

				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		//entity hierarchy
		ImGui::Begin("Entity Hierarchy");
		vector<Entity> entities = EntityManager::GetAllEntities();

		for (unsigned int i = 0; i < entityCount; i++)
			ImGui::Text(entities[i].name.c_str());

		ImGui::End();

		//inspecter
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::Begin("Inspecter");

		//get all the components of the selected entity
		ImGui::Text("Stuff here.");

		ImGui::End();
		ImGui::PopStyleVar();

		//scene view
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		ImGui::Begin("Scene Viewport");
		ImVec2 viewPortSize = ImGui::GetContentRegionAvail();

		if (viewportSize != *((vec2*)&viewPortSize))
		{
			viewportSize = *((vec2*)&viewPortSize);
			Application::customeFrameBuffer->Resize((unsigned int)viewportSize.x, (unsigned int)viewportSize.y);
		}

		ImGui::Image((void*)Application::customeFrameBuffer->GetColorBufferId() /*AssetManager::GetTexture("Face")->GetID()*/, viewPortSize, ImVec2(0, 1), ImVec2(1, 0));
		ImGui::End();
		ImGui::PopStyleVar();

		//asset bar
	}
};

unsigned long Editor::entityCount;

//camera controller
class CameraCon
{
	//vars
private:

	float moveSpeed = 25.0f;
	//Transform* camTrans;

	//method
public:

	Transform* camTrans; //temp move back to private after OnSceneStart events are triggered

	//when the scene loads
	void Start()
	{
		camTrans = &EntityManager::GetComponent<Transform>("Camera");
	}

	//when update is called
	void Update(float deltaTime)
	{
		if (!camTrans)
			return;

		//move up
		if (Input::GetKey(SMOK_KEY_W))
			camTrans->position.y += moveSpeed * deltaTime;

		//move down
		else if (Input::GetKey(SMOK_KEY_S))
			camTrans->position.y -= moveSpeed * deltaTime;

		//move left
		else if (Input::GetKey(SMOK_KEY_A))
			camTrans->position.x += moveSpeed * deltaTime;

		//move right
		else if (Input::GetKey(SMOK_KEY_D))
			camTrans->position.x -= moveSpeed * deltaTime;
	}
};

int main(int args, char* argv[])
{
	//--set up application
	Application::Init(SCREEN_WIDTH, SCREEN_HEIGHT);
	//DisplayI.EnableVSync();

	//link GUI Render to system and setup dock space
	GUIRenderer::SetFlag(GUIFlags::Docking, true);
	GUIRenderer::SetFlag(GUIFlags::ViewPort, true);
	GUIRenderer::Init();

	//--load assets
	AssetManager::LoadShader("Shader", "res\\Shaders\\Vertex.shader", "res\\Shaders\\Fragment.shader");
	AssetManager::LoadTexture("Face", "res\\Textures\\awesomeface.png");
	AssetManager::LoadTexture("Con", "res\\Textures\\container.jpg");

	FrameBufferData data;
	data.width = 400;
	data.height = 200;
	data.colorBufferIds.resize(1);
	data.depthBufferIds.resize(1);
	FrameBuffer* sceneFrameBuffer = FrameBuffer::Create(data);
	//sceneFrameBuffer->Unbind();
	Application::customeFrameBuffer = sceneFrameBuffer; //fb = sceneFrameBuffer;

	//--load entities
	EntityManager::Create("Camera");
	EntityManager::AddComponet<OrthographicCamera>("Camera", (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	EntityManager::AddComponet<Transform>("Camera");//, vec3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));

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

	CameraCon camCon;
	camCon.camTrans = &EntityManager::GetComponent<Transform>("Camera"); //OnSceneLoadEvent::AddMethod(&camCon, &CameraCon::Start);
	UpdateEvent::AddMethod(&camCon, &CameraCon::Update);

	Editor editor;
	ECSGUIRenderEvent::AddMethod(&editor, &Editor::Draw);

	SpriteRenderer::Init();

	//--game loop
	Application::Run();

	//--clean up data

	//systems
	GUIRenderer::Destroy();

	//entities
	EntityManager::DestroyAllEntities();

	//assets
	/*sceneFrameBuffer->Destroy();*/ Application::customeFrameBuffer->Destroy();
	AssetManager::DestroyAllAssets();

	Application::Destroy();

#ifndef SMOK_DIST
	std::cin.get();
#endif
	return 0;
}