#version 330 core

in vec4 gl_FragCoord;
in vec4 eye_worldSpace;

out vec4 lightData;

/* Lights */
uniform int lightType;
uniform vec3 lightInt;
uniform float ambCoeff = 0.1;
uniform float diffCoeff = 1.0;
uniform float specCoeff = 0.8;

/* Point Light */
uniform vec3 lightAtt;
uniform vec3 lightPos;

/* Directional Light */
uniform vec3 lightDir;

/* Resolution */
uniform vec2 res;

uniform sampler2D position;
uniform sampler2D normal;
uniform sampler2D colorSpecular;

void main()
{
    vec3 fragPos = vec3(texture(position, gl_FragCoord.xy / res));
    vec3 fragNormal = normalize(vec3(texture(normal, gl_FragCoord.xy / res)));
    vec4 fragColorSpecular = texture(colorSpecular, gl_FragCoord.xy / res);
    vec3 fragColor = vec3(fragColorSpecular) ;
    float fragSpecular = fragColorSpecular.w;

    /* Lighting calculation */
    lightData = vec4(0);

    /* Ambient Component */
    lightData += ambCoeff * vec4(fragColor, 0.0);

    /* Diffuse component */
    vec3 vertexToLight;

    if(lightType == 0)
    {
        vertexToLight = normalize(lightPos - fragPos);
    }
    else if(lightType == 1)
    {
        vertexToLight = normalize(lightDir);
    }

    float diffuseFactor = max(dot(fragNormal, vertexToLight), 0.0);
    lightData += diffCoeff * vec4(max(vec3(0), fragColor * lightInt * diffuseFactor), 0.0);

    /* Specular component */
    vec3 lightReflection = normalize(-reflect(vertexToLight, fragNormal));
    vec3 eyeDirection = normalize(vec3(eye_worldSpace) - fragPos);
    float specFactor = pow(max(0.0, dot(eyeDirection, lightReflection)), fragSpecular * 256);
    lightData += specCoeff * vec4(max(vec3(0), fragColor * lightInt * specFactor), 0.0);

    /* Attenuation */
    if(lightType == 0)
    {
        float d = length(lightPos - fragPos);
        float totalAtt = max((lightAtt.x + d * lightAtt.y + d * d * lightAtt.z), 1.0);
        lightData /= totalAtt;
    }

    lightData.w = 1.0;
}
