#version 330 core

out vec4 FragColor;
in vec2 TexCoords;

uniform vec4 uColor;
uniform bool useTexture;
uniform sampler2D uTexture;

void main()
{
    if (useTexture)
    {
        FragColor = texture(uTexture, TexCoords);
    }
    else
    {
        FragColor = uColor;
    }
}