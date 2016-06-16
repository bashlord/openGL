#version 330 core

in vec3 Color;
in vec2 Texcoord;
smooth in vec3 vNormal;
smooth in vec3 vNormal1;

uniform vec3 batSignalDir;
uniform vec3 batSignalPos;
in vec3 lightDir;
in vec3 lightDir1;
in vec3 l_pos;
out vec4 outColor;

uniform sampler2D tex;

uniform vec4 color_in;

void main()
{
    float  attenuation =1.0;
    vec3 sd = normalize(vec3(-batSignalDir));
    vec3 lightD = normalize(vec3(lightDir));//surface to light
     vec3 lightD1 = normalize(vec3(lightDir1));//surface to light
    float distancetolight = length(lightDir);
    float fDiffuseIntensity = max(0.0, dot(normalize(vNormal), -lightD ));
    
    //DIRECTIONAL
    float fDiffuseIntensity1 = max(0.0, dot(vNormal1, -l_pos));
    
    attenuation = 1.0/(1.0 + 0.01*pow(distancetolight,2));
    float lighttosurfaceangle = degrees(acos(dot(-lightD, normalize(batSignalDir))));
    
    if(lighttosurfaceangle > 15.0){
        attenuation = 0.0;
    }
    
    float diffuseCoefficient = max(0.0, dot(vNormal, lightD));
    vec3 diffuse = diffuseCoefficient * vec3(1,1,1) * vec3(8,8,8);
    float specularCoefficient = 0.0;
    
    outColor = texture(tex, Texcoord) * color_in;
    
    float a = 1.0;
    //if (fDiffuseIntensity > 0.95){
        a = 0.5;
    //}else if (fDiffuseIntensity > 0.5){
      //  a =0.5;
    //}else if (fDiffuseIntensity > 0.1){
      //  a = 0.2;
    //}else{
        //a = 0.1;
    ///}
    // * vec4(Color, 1.0);
    outColor = outColor*vec4(1,1,1,0)* vec4(vec3(1,1,1)*(a+fDiffuseIntensity1), 1.0) + attenuation*(vec4(diffuse,0));
    


    //outColor = color_in;
   
}