#version 330 core
out vec4 FragColor;

in vec2 outUV;

uniform sampler2D  ourTexture;

void main()
{
    FragColor = vec4(1.0f , 1.0f ,1.0f ,1.0f );
}
