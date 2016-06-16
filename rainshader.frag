
#version 330 core

in vec3 FragPos;
in vec3 Normal;

out vec4 color;

uniform vec3 viewPos;

void main()
{    
    // Properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
	vec3 result = vec3(0.0f, 0.0f, 0.0f);
    
	color = vec4(0.5, 0.5, 1.0, 1.0);
}
