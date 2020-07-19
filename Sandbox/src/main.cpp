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
#include <gtc/matrix_transform.hpp>
//#include <gtc/type_ptr.hpp>

#include <stdio.h>

#ifndef SMOK_DIST
#include <iostream>
#endif

using namespace std; using namespace glm;

// settings
const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

/*
// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class CameraController
{
public:
    // camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // euler Angles
    float Yaw;
    float Pitch;
    // camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    Transform* transform;
    Camera* cam;

    // constructor with vectors
    CameraController(float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        transform = &EntityManager::GetComponent<Transform>("Camera");
        cam = &EntityManager::GetComponent<Camera>("Camera");

        Position = transform->position;
        WorldUp = Position + Transform::Up();
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(Position, Position + Front, Up);
    }

    //the update loop for the camera
    void Update(float deltaTime)
    {
        if (transform == nullptr || cam == nullptr)
            return;

        vec2 mousePos = Input::GetMousePosition();
        vec2 mouseScroll = Input::GetMouseScroll();

        if (Input::GetKey(Smok_KEY_W))
            ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
        else if (Input::GetKey(Smok_KEY_S))
            ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
        else if (Input::GetKey(Smok_KEY_A))
            ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
        else if (Input::GetKey(Smok_KEY_D))
            ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);

        ProcessMouseMovement(mousePos.x, mousePos.y);
        ProcessMouseScroll(mouseScroll.y);
    }

    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        float velocity = MovementSpeed * deltaTime;
        if (direction == FORWARD)
            Position += Front * velocity;
        if (direction == BACKWARD)
            Position -= Front * velocity;
        if (direction == LEFT)
            Position -= Right * velocity;
        if (direction == RIGHT)
            Position += Right * velocity;
    }

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw += xoffset;
        Pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }

        // update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors();
    }

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset)
    {
        Zoom -= (float)yoffset;
        if (Zoom < 1.0f)
            Zoom = 1.0f;
        if (Zoom > 45.0f)
            Zoom = 45.0f;
    }

private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors()
    {
        // calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);
        // also re-calculate the Right and Up vector
        Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up = glm::normalize(glm::cross(Right, Front));

        transform->front = Front;
        transform->right = Right;
        transform->up = Up;
    }
};
*/

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
   // EntityManager::GetComponent<OrthographicCamera>("Camera").viewLength = SCREEN_WIDTH;
    //EntityManager::GetComponent<OrthographicCamera>("Camera").viewHeight = SCREEN_HEIGHT;
    EntityManager::AddComponet<Transform>("Camera", vec3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));

    //create entites with sprites
    EntityManager::Create("Face1");
    EntityManager::AddComponet<Transform>("Face1", vec3(150.0f, 170.0f, 0.0f), vec3(45.0f, 0.0f, 0.0f), vec3(2.0f, 1.0f, 1.0f));
    EntityManager::AddComponet<Sprite>("Face1", container, (unsigned int)0, shader);

    //EntityManager::GetComponent<Sprite>("Face1").PrintLayer();

    //--link systems and scripts

    //link 2D camera controll script
    
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