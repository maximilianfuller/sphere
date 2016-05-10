#version 330 core

in vec4 gl_FragCoord;
in vec4 eye_worldSpace;

out vec4 lightData;

/* Light uniforms */
uniform int lightType;
uniform vec3 lightInt;

/* Point Light */
uniform vec3 lightAtt;
uniform vec3 lightPos;
uniform float lightRadius;

/* Directional Light */
uniform vec3 lightDir;

/* Resolution */
uniform vec2 res;

/* G buffer */
uniform sampler2D position;
uniform sampler2D normal;
uniform sampler2D colorSpecular;

void main()
{
    /* Geometry data from textures */
    vec3 fragPos = vec3(texture(position, gl_FragCoord.xy / res));
    vec3 fragNormal = normalize(vec3(texture(normal, gl_FragCoord.xy / res)));
    vec4 fragColorSpecular = texture(colorSpecular, gl_FragCoord.xy / res);
    vec3 fragColor = vec3(fragColorSpecular) ;
    float fragSpecular = fragColorSpecular.w;

    // Pass if light does not cover this location
    if(distance(lightPos, fragPos) > lightRadius && lightType == 0)
    {
        lightData = vec4(0, 0, 0, 1);
        return;
    }

    lightData = vec4(0);

    /* Diffsue component */
    vec3 vertexToLight;

    // Point light
    if(lightType == 0)
    {
        vertexToLight = normalize(lightPos - fragPos);
    }
    // Directional light
    else if(lightType == 1)
    {
        vertexToLight = normalize(lightDir);
    }

    /* Diffuse component */
    float diffuseFactor = max(dot(fragNormal, vertexToLight), 0.0);
    lightData += vec4(fragColor * lightInt * diffuseFactor, 0.0);

    /* Specular component */
    if(diffuseFactor != 0)
    {
        vec3 lightReflection = normalize(-reflect(vertexToLight, fragNormal));
        vec3 eyeDirection = normalize(vec3(eye_worldSpace) - fragPos);
        float specFactor = pow(max(0.0, dot(eyeDirection, lightReflection)), fragSpecular * 256);
        lightData += vec4(fragColor * lightInt * specFactor, 0.0);
    }

    /* Attenuation for point light */
    if(lightType == 0)
    {
        float d = length(lightPos - fragPos);
        float totalAtt = max((lightAtt.x + d * lightAtt.y + d * d * lightAtt.z), 1.0);
        lightData /= totalAtt;
    }

    lightData.w = 1.0;
}
