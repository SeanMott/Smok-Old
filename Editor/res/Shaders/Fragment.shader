#version 330 core
out vec4 FragColor;

in vec2 TextureCoords;

//uniform vec3 Color;
uniform sampler2D Sprite;

void main()
{
    FragColor = texture(Sprite, TextureCoords); //vec4(1.0f, 0.5f, 0.2f, 1.0f);
}