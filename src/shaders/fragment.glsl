#version 330 core
out vec4 FragColor;

uniform vec3 tint;
in vec3 Normal;
in vec3 FragPos;
void main()
{ 
    vec3 norm = normalize(Normal);
    
    vec3 lightPosition = vec3(0.0f, 1.0f, -3.0f);

    vec3 lightDir = normalize(lightPosition - FragPos);
    
    float diff = max(dot(norm, lightDir), 0.0f);

    vec3 light = diff * vec3(1.0f, 1.0f, 1.0f) * 0.5f;
    
    vec3 result = tint;

    FragColor = vec4(result, 1.0);
} 