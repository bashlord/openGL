#version 330 core

in vec2 TexCoords;
smooth in vec3 vNormal;
in vec4 eye;
in vec3 normal1;

out vec4 color;

uniform sampler2D texture_diffuse1;
uniform mat4 normalMatrix;
uniform vec3 batSignalDir;
uniform vec3 batSignalPos;
in vec3 lightDir;

void main()
{
    float  attenuation =1.0;
    
    vec3 sd = normalize(vec3(-batSignalDir));
    vec3 ee = normalize( vec3(eye));
    vec3 nn = normalize( normal1 );
    
    vec3 lightD = normalize(vec3(lightDir));//surface to light
    float distancetolight = length(lightDir);
    //float intensity = dot(lightD,vNormal);
     //vec4 spec = vec4(0.0);
    vec4 vTexColor =vec4(texture(texture_diffuse1, TexCoords));
    float fDiffuseIntensity = max(0.0, dot(normalize(vNormal), lightD ));
      attenuation = 1.0/(1.0 + 0.0001*pow(distancetolight,2));
    
    float lighttosurfaceangle = degrees(acos(dot(-lightD, normalize(batSignalDir))));
    
    if(lighttosurfaceangle > 15.0){
        attenuation = 0.0;
    }
    
    float diffuseCoefficient = max(0.0, dot(vNormal, lightD));
    vec3 diffuse = diffuseCoefficient * vec3(1,1,1) * vec3(2,2,2);
    float specularCoefficient = 0.0;
    
    
    
    
    color = vTexColor*vec4(1,1,1,0)*vec4(vec3(1,1,1)*(1.5+fDiffuseIntensity), 1.0) + attenuation*(vec4(diffuse,0));
    
    if (fDiffuseIntensity > 0.95){
        color = vec4(1.0,1.0,1.0,1.0)*color;
    }else if (fDiffuseIntensity > 0.5){
        color = vec4(0.7,0.7,0.7,1.0)*color;
    }else if (fDiffuseIntensity > 0.05){
        color = vec4(0.5,0.5,0.5,1.0)*color;
    }else{
        color = vec4(0.2,0.2,0.2,1.0)*color;
    }

    
    /*
    if ( dot(sd,lightD) > -1000.0) {
        if (intensity > -1.0) {
            // compute the half vector
            vec3 h = normalize(lightD + ee);
            // compute the specular term into spec
            float intSpec = max(dot(h,nn), 0.0);
            spec =vTexColor * pow(intSpec,0.1);
        }
        color = intensity*spec;
    }else{
        color = vTexColor*vec4(1,1,1,0)*vec4(vec3(1,1,1)*(0.2+fDiffuseIntensity), 1.0);
    }*/
    //color = vec4(texture(texture_diffuse1, TexCoords));
}