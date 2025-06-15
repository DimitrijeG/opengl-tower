#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 2) in vec3 aNormal;
layout(location = 1) in vec2 aTexCoord; // Only used if mesh has texcoords

uniform mat4 uM;
uniform mat4 uV;
uniform mat4 uP;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;

void main()
{
    FragPos = vec3(uM * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(uM))) * aNormal;
    TexCoord = aTexCoord; // Will be (0,0) if not used
    gl_Position = uP * uV * uM * vec4(aPos, 1.0);
}