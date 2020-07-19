#version 330 core
layout(location = 0) in vec3 Position;

uniform mat4 PVM; //Projection * View * Model

void main()
{
    gl_Position = PVM * vec4(Position, 1.0);
}