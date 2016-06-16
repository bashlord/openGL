
#version 330 core

// This is an example vertex shader. GLSL is very similar to C.
// You can define extra functions if needed, and the main() function is
// called when the vertex shader gets run.
// The vertex shader gets called once per vertex.

layout (location = 0) in vec3 position;
layout(location = 1) in vec3 vertexColor;//fairly sure this is the normalMatrix

uniform mat4 MVP;
uniform mat4 M;//toworld
uniform mat4 V;//camera view
uniform vec3 camerapos;//camera POV?
uniform mat4 LightPosition_worldspace;
uniform int flag;
uniform vec4 mdc;
uniform vec3 batSignalDir;
uniform vec3 batSignalPos;

smooth out vec3 vNormal;
out vec3 normal1;
out vec3 lightDir;
out vec3 lightDir1;
out float distance;

//lighthouse tutorial variables
out vec3 normal;

out vec4 sun;

void main()
{
    gl_Position = MVP*M * vec4(position.x, position.y, position.z, 1.0);
    lightDir = vec3(batSignalPos - vec3(vec4(position.x, position.y, position.z, 1.0)));
    lightDir1 = vec3(vec3(vec4(position.x, position.y, position.z, 1.0)));
    vNormal = vec3(0,1,0);

}
