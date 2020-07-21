#version 330 core
layout(location = 0) in vec3 Position;
layout(location = 1) in vec2 TexCoords;

uniform mat4 PVM; //Projection * View * Model

out vec2 TextureCoords;

void main()
{
    gl_Position = PVM * vec4(Position, 1.0);
    TextureCoords = TexCoords;
}