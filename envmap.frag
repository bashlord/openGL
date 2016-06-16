#version 330 core
in vec3 Normal;
in vec3 Position;
out vec4 color;

uniform vec3 cameraPos;
uniform samplerCube skybox;
uniform float time;

void main()
{    
	vec3 cPos = -1.0 + 2.0 * Position.xyz / cameraPos.xyz;
	float cLength = length(cPos);

	vec3 uv = Position.xyz/cameraPos.xyz+(cPos/cLength)*cos(cLength*12.0-time*4.0)*0.03;
	color = texture(skybox, uv);

	//color = vec4(col,1.0);

    //vec3 I = normalize(Position - cameraPos);
    //vec3 R = reflect(I, normalize(Normal));

    //color = texture(skybox, R) ;
}