#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat4 normalMatrix;
uniform vec3 batSignalDir;
uniform vec3 batSignalPos;
smooth out vec3 vNormal;

out vec2 TexCoords;
out vec4 eye;
out vec3 normal1;
out vec3 lightDir;

void main()
{
    gl_Position = projection * view *model * vec4(position, 1.0f);
    TexCoords = texCoords;
    vec4 vRes = normalMatrix*vec4(normal, 0.0);
    vNormal =  vec3(model *vec4(normal,0));
    eye = -(model*vec4(position.x, position.y, position.z, 1.0));
    normal1 = normalize( mat3(view*model)*normal  );
    lightDir = vec3(batSignalPos - vec3(model* vec4(position,0)));
}