#version 330 core
out vec4 FragColor;

uniform vec3 tint;
uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform float lightIntensity;
uniform vec3 lightAmbience;
uniform vec3 viewPos;

in vec3 Normal;
in vec3 FragPos;

float specularStrength = 0.5f; //TODO: Abstract to Material later

void main()
{
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPosition - FragPos);  

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
    vec3 specular = specularStrength * spec * lightColor;  

    float diff = max(dot(norm, lightDir), 0.0f);

    vec3 diffuse = diff * lightColor;

    vec3 result = (lightAmbience + diffuse + specular) * tint;
    FragColor = vec4(result, 1.0);
} 