#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform vec3 uLightPos;
uniform vec3 uLightColor;
uniform vec3 uViewPos;
uniform vec3 uObjectColor;
uniform bool useTexture;
uniform sampler2D uTexture;

out vec4 FragColor;

void main()
{
    vec3 baseColor = uObjectColor;
    if (useTexture)
        baseColor = texture(uTexture, TexCoord).rgb;

    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * uLightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(uLightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * uLightColor;

    float specularStrength = 0.5;
    vec3 viewDir = normalize(uViewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * uLightColor;

    vec3 result = (ambient + diffuse + specular) * baseColor;
    FragColor = vec4(result, 1.0);
}