#version 330 core

uniform mat4 model, view, projection;

// Light properties
const vec3 WorldSpace_lightPos = vec3(2, 2, 2); // world-space light position
uniform vec3 lightColor;
uniform float lightIntensity;

// Attenuation Properties
uniform float attQuadratic;
uniform float attLinear;
uniform float attConstant;

// Material properties
uniform vec3 color;
uniform float ambientIntensity;
uniform float diffuseIntensity;
uniform float specularIntensity;
uniform float shininess;

in vec4 WorldSpace_position;
in vec4 WorldSpace_normal;

out vec3 fragColor;


void main(){
    vec3 ambientComp = color * ambientIntensity;

    vec3 n = normalize(WorldSpace_normal.xyz);
    vec3 L = normalize(WorldSpace_lightPos - WorldSpace_position.xyz);
    float dotProductDiff = max(0,dot(n,L));

    vec3 diffuseComp = color * lightColor * diffuseIntensity * dotProductDiff;

//    vec3 eye = normalize(vec4(0.0, 0.0, 0.0, 1.0) - WorldSpace_position);
    vec3 eye = - normalize(WorldSpace_position.xyz);

    vec3 reflection = normalize(reflect(WorldSpace_position - WorldSpace_lightPos, WorldSpace_normal));
//    float dotProductSpec = max(0,dot(reflection, eye));

//    vec3 specularComp = color * lightColor * specularIntensity * pow(dotProductSpec,shininess);

//    float d = distance(WorldSpace_lightPos, WorldSpace_position);
//    float attenuation = lightIntensity * min(1 / (attConstant + attLinear * d + attQuadratic * pow(d,2)), 1);
//    attenuation = 1;
//    fragColor = ambientComp + attenuation * (diffuseComp + specularComp);
fragColor = ambientComp;

}
