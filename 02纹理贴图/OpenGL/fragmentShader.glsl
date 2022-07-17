#version 330 core
out vec4 FragColor;

in vec4 outColor;
in vec2 outUV;

uniform sampler2D  ourTexture;

void main()
{
    FragColor = texture(ourTexture , outUV);
}
