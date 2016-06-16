#version 330 core

// This is an example vertex shader. GLSL is very similar to C.
// You can define extra functions if needed, and the main() function is
// called when the vertex shader gets run.
// The vertex shader gets called once per vertex.

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

out vec3 Color;
out vec2 Texcoord;

uniform mat4 MVP;
uniform mat4 P;
uniform vec3 batSignalDir;
uniform vec3 batSignalPos;
smooth out vec3 vNormal;
out vec3 normal1;
out vec3 lightDir;
out vec3 lightDir1;
out vec3 vNormal1;
out vec3 l_pos;

void main()
{
    gl_Position = MVP * P* vec4(position.x, position.y, position.z, 1.0);
	Texcoord = texCoord;
    lightDir = vec3(batSignalPos - vec3(P*vec4(position.x, position.y, position.z, 1.0)));
    lightDir1 = vec3(vec3(P*vec4(position.x, position.y, position.z, 1.0)));
    vNormal =  color;
    vNormal1 = normalize( mat3(transpose(inverse(P)))*color);
    l_pos =  mat3(P)*vec3(1,1,1);
}


