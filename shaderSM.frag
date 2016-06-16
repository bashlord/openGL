
#version 330 core
in vec3 TexCoords;
out vec4 color;

uniform samplerCube skybox;
uniform int flag;

void main()
{
        color = texture(skybox, TexCoords);

}