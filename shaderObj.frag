
#version 330 core
uniform uint id;

in vec3 TexCoords;
out vec4 color;

uniform samplerCube skybox;
uniform vec3 batSignalDir;
uniform vec3 batSignalPos;
in vec3 lightDir;
in vec3 lightDir1;
smooth in vec3 vNormal;


void main()
{
    
    float  attenuation =1.0;
    vec3 sd = normalize(vec3(-batSignalDir));
    vec3 lightD = normalize(vec3(lightDir));//surface to light
    vec3 lightD1 = normalize(vec3(lightDir1));//surface to light
    
    float distancetolight = length(lightDir);
    
    float fDiffuseIntensity = max(0.0, dot(normalize(vNormal), lightD ));
    float fDiffuseIntensity1 = max(0.0, dot(normalize(vec3(0,0,0)), -lightD1 ));
    attenuation = 1.0/(1.0 + 0.01*pow(distancetolight,2));
    
    float lighttosurfaceangle = degrees(acos(dot(-lightD, sd)));
    
    if(lighttosurfaceangle > 30.0){
        attenuation = 0.0;
    }
    
    float diffuseCoefficient = max(0.0, dot(vNormal, lightD));
    vec3 diffuse = diffuseCoefficient * vec3(1,1,1) * vec3(2,2,2);
    float specularCoefficient = 0.0;
    
    color = vec4(0.1,0.1,0.1,0);
    /*
    if (fDiffuseIntensity1 > 0.01){
        color = vec4(1.9,1.9,1.9,1.0)+color;
    }else if (fDiffuseIntensity1 > 0.001){
        color = vec4(1.2,1.2,1.2,1.0)+color;
    }else if(fDiffuseIntensity1 == 0){
       

    }else{
        color = vec4(1.01,1.01,1.01,1.0)+color;
    }*/
    
    color = color*vec4(1,1,1,0)*vec4(vec3(1,1,1)*(0.2+fDiffuseIntensity1), 1.0) + attenuation*(vec4(diffuse,0));
    
}
