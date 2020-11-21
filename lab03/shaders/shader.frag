#version 330 core

uniform mat4 model, view, projection;

// Light properties
const vec3 WorldSpace_lightPos = vec3(2, 2, 2);
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
    //ambient
    vec3 ambientComp = color * ambientIntensity;

    //diffuse
    vec3 n = normalize(WorldSpace_normal.xyz);
    vec3 L = normalize(WorldSpace_lightPos - WorldSpace_position.xyz);
    float dotProductDiff = max(0,dot(n,L));
    vec3 diffuseComp = color * lightColor * diffuseIntensity * dotProductDiff;

    //specular
    vec3 eye = normalize(inverse(view)*vec4(0,0,0,1)- WorldSpace_position).xyz;
    vec3 reflection = normalize(reflect(WorldSpace_position.xyz - WorldSpace_lightPos, normalize(WorldSpace_normal.xyz)));
    float dotProductSpec = max(0,dot(reflection, eye));
    vec3 specularComp = color * lightColor * specularIntensity * pow(dotProductSpec,shininess);

    //attenuation
    float d = distance(WorldSpace_lightPos.xyz, WorldSpace_position.xyz);
    float attenuation = lightIntensity * min(1 / (attConstant + attLinear * d + attQuadratic * pow(d,2)), 1);

    //fragColor
    fragColor = ambientComp + attenuation * (diffuseComp + specularComp);


}
